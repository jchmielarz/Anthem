#pragma once
#include <type_traits>
#include "anthem/anthem.h"

//testing utils
template<typename T>
struct size {
	using value = std::integral_constant<size_t, 0>;
};

template<template<typename...> typename LIST, typename... ELEMS>
struct size<LIST<ELEMS...>> {
	using value = std::integral_constant<size_t, sizeof...(ELEMS)>;
};

template<typename T>
struct TD;

class AnthemTest {
public:
	static void runTests() {
	}

private:

	static void list_test()
	{
		using namespace anthem::containers;

		using l1 = list<float>; // <float>
		using l2 = list<>::append_s<l1, int, double>; //<float, int, double>
		using l3 = l2::prepend<char, bool>; //<char, bool, float, int, double>
		using e1 = list<>::first_s<l3>;
		using e2 = l3::last;
		using s1 = l3::split<char>;
		using s2 = l3::split<float>;
		using s3 = l3::split<double>;
		using s4 = l3::split<unsigned>;

		static_assert(
			std::is_same<typename l3,
			anthem::containers::list<char, bool, float, int, double>>::value,
			"containers::list::append/prepend broke");

		static_assert(
			std::is_same<l3::reverse, list<double, int, float, bool, char>>::value,
			"containers::list::reverse broke");

		static_assert(
			std::is_same<e1, char>::value,
			"containers::list::first broke");

		static_assert(
			std::is_same<e2, double>::value,
			"containers::list::last broke");

		static_assert(
			std::is_same<e2, double>::value,
			"containers::list::last broke");

		static_assert(
			std::is_same_v<s1::value, list<>> &&
			std::is_same_v<s1::remainder, list<bool, float, int, double>> &&
			std::is_same_v<s2::value, list<char, bool>> &&
			std::is_same_v<s2::remainder, list<int, double>> &&
			std::is_same_v<s3::value, list<char, bool, float, int>> &&
			std::is_same_v<s3::remainder, list<>> &&
			std::is_same_v<s4::value, list<char, bool, float, int, double>> &&
			std::is_same_v<s4::remainder, list<>>,
			"containers::list::split broke");
	}

	static void map_test() {
		using namespace anthem::containers;

		using m0 = map<>::set<int, int>;
		using m0t = map<pair<int, int>>;
		using p1 = pair<int, float>;
		using m1 = map<p1>;
		using m2 = m1::set<char, float>;
		using m2t = map<pair<char, float>, pair<int, float>>;
		using m3 = m2::set<int, list<int, bool, bool>>;
		using m3t = map<pair<char, float>, pair<int, list<int, bool, bool>>>;

		static_assert(
			std::is_same<m2, m2t>::value &&
			std::is_same<m3, m3t>::value,
			"containers::map::set broke");

		static_assert(
			m1::has_key<int>::value && !m2::has_key<float>::value,
			"containers::map::has_key broke");

		static_assert(
			std::is_same<m3::get_value<char>, float>::value &&
			std::is_same<m3::get_value<int>, list<int, bool, bool>>::value,
			"containers::map::get_value broke");

	}

	static void anthem_set_test() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;

		using simple_comp = anthem_parse_adapter<
			set, VAR(test), int,
			set, VAR(test), float,
			set, VAR(test2), list<int, float, bool>
		>::compilation;
		using anth = simple_comp::anthem;

		static_assert(
			std::is_same_v<
				anth::variable_map::get_value<VAR(test)>,
				float> &&
			std::is_same_v<
				anth::variable_map::get_value<VAR(test2)>,
				list<int, float, bool>>,
			"anthem::set broke");

	}

	static void anthem_eval_parse_test() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;
		
		using eval_p1 = anthem::opcodes::detail::eval_parse<5,
			list<
			int, equals, int, and, float, equals, float
			//(int == int) && (float == float)
			>
		>::value::first;

		using eval_p1t =
			eval_s<and_e,
			eval_s<equals_e, int, int>,
			eval_s<equals_e, float, float>>;

		static_assert(std::is_same_v<eval_p1, eval_p1t>,
			"eval parse broke");

	}

	static void anthem_eval_test() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;

		//int == int && float == float && true
		using eval_comp_true = anthem_parse_adapter<
			eval,
				int, equals, int,
					and,
				float, equals, float,
					and,
				std::true_type,
			end_eval
		>::compilation::anthem;
		using eval_result_true = 
			eval_comp_true::variable_map::get_value<VAR(@EVAL)>;

		//int == bool && float == float
		using eval_comp_false = anthem_parse_adapter<
			eval,
				int, equals, bool,
					and,
				float, equals, float,
			end_eval
		>::compilation::anthem;
		using eval_result_false =
			eval_comp_false::variable_map::get_value<VAR(@EVAL)>;

		static_assert(
			eval_result_true::value &&
			eval_result_false::value == false,
			"eval broke");

	}

	static void anthem_eval_test_w_var() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;

		//var test_int = int
		//var test_float = float
		//test_int == int && float == test_float && true
		using eval_comp_true = anthem_parse_adapter<
			set, VAR(test_int), int,
			set, VAR(test_float), float,
			eval,
				VAR(test_int), equals, int,
					and,
				float, equals, VAR(test_float),
					and,
				std::true_type,
			end_eval
		>::compilation::anthem;
		using eval_result_true = eval_comp_true::variable_map::get_value<VAR(@EVAL)>;

		//var test_bool = bool
		//var test_float = float
		//test_bool == int && float == test_float
		using eval_comp_false = anthem_parse_adapter<
			set, VAR(test_bool), bool,
			set, VAR(test_float), float,
			eval,
				VAR(test_bool), equals, int,
					and,
				float, equals, VAR(test_float),
			end_eval
		>::compilation::anthem;
		using eval_result_false = eval_comp_false::variable_map::get_value<VAR(@EVAL)>;

		static_assert(
			eval_result_true::value &&
			eval_result_false::value == false,
			"eval broke");

	}


	static void anthem_block_test() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;


		using eval_comp_true = typename anthem_parse_adapter<
			block,
				set, VAR(test_int), int,
				set, VAR(test_float), float,
				eval,
					VAR(test_int), equals, int,
						and,
					float, equals, VAR(test_float),
						and,
					std::true_type,
				end_eval,
			end_block
		>::compilation::anthem;

		using eval_block_order = typename anthem_parse_adapter<
			block,
				set, VAR(test), int,
				set, VAR(test), float,
			end_block
		>::compilation::anthem;
		using test = typename
			eval_block_order::variable_map::get_value<VAR(test)>;
				
		static_assert(
			eval_comp_true
				::variable_map::get_value<VAR(@EVAL)>::value &&
			std::is_same_v<test, float>,
			"block broke");

	}

	template<typename CASE_LIST>
	struct adapter{
	};
	template<template<typename...> typename CASE_LIST, typename... CASES>
	struct adapter<CASE_LIST<CASES...>> {
		using value = typename 
			anthem::opcodes::detail::if_evaluator<void,CASES...>::value;
	};

	static void anthem_if_test() {
		using namespace anthem::utils;
		using namespace anthem::containers;
		using namespace anthem::opcodes;
		using namespace anthem::opcode_s;

		using if_test = typename anthem_parse_adapter<
			//true case
			set, VAR(int), int,
			if_, 
				eval, VAR(int), equals, int, end_eval,
				block,
					set, VAR(test_float), float,
				end_block,
				//else
				eval, float, equals, float, end_eval,
				block,
					set, VAR(test_float), bool,
				end_block,
			end_if,
			//false case
			if_,
				eval, VAR(int), equals, float, end_eval,
				block,
					set, VAR(test_bool), float,
				end_block,
				//else
				eval, float, equals, float, end_eval,
				block,
					set, VAR(test_bool), bool,
				end_block,
			end_if
		>::compilation::anthem;

		
		using test_float = if_test::variable_map::get_value<VAR(test_float)>;
		using test_bool = if_test::variable_map::get_value<VAR(test_bool)>;

		static_assert(
			std::is_same_v<test_float, float>&&
			std::is_same_v<test_bool, bool>, 
		"if broke");
	}

	static void anthem_if_test_macro() {
		using macro_test =
		ANTHEM_SCRIPT_BEGIN
			SET VAR(int_t), int,

			IF VAR(int_t), EQUALS int, 
			THEN
				SET VAR(float_t), float,
			ELSE THEN
				SET VAR(float_t), void,
			END_IF
		ANTHEM_SCRIPT_END

		using float_t = ANTHEM_GET_VAR(macro_test, float_t);
		static_assert(std::is_same_v<float_t, float>,"");
	}

};