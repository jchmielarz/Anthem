#pragma once
#include <utility>
#include "anthem_base.h"
#include "..\containers\map.h"
#include "..\containers\list.h"
#include "set.h"
#include "var.h"
#include "..\utils\split_string.h"

namespace anthem {
namespace opcode_s {
template<typename OPCODE, typename LEFT, typename RIGHT>
struct eval_s {
	struct not_implemented_t;
	using value = not_implemented_t;
};
}//namespace anthem::opcode_s

namespace opcodes {

template<typename OPCODE, int PRECEDENCE>
struct evaluable;

struct eval;
struct end_eval;
template<typename EVAL_S>
struct evaluable_expr;
struct dummy;


namespace detail {

template<int PRECEDENCE, typename RESULT, typename INPUT>
struct eval_parse_impl;

//wrong precedence - omit
template<
	int PRECEDENCE,
	template<typename...> typename RESULT,
	template<typename...> typename INPUT,
	typename... RESULT_ELEMS,
	typename LEFT, typename RIGHT,
	typename OPCODE, int PRECEDENCE_,
	typename NEXT_1, typename NEXT_2,
	typename... REST
>struct eval_parse_impl<PRECEDENCE, RESULT<RESULT_ELEMS...>,
	INPUT<LEFT, evaluable<OPCODE, PRECEDENCE_>, RIGHT, NEXT_1, NEXT_2, REST... >> {
	using value = typename eval_parse_impl<
		PRECEDENCE,
		RESULT<RESULT_ELEMS..., LEFT, evaluable<OPCODE, PRECEDENCE_>>,
		INPUT<RIGHT, NEXT_1, NEXT_2, REST...>>::value;
};

//matching precendence - eval
template<
	int PRECEDENCE,
	template<typename...> typename RESULT,
	template<typename...> typename INPUT,
	typename... RESULT_ELEMS,
	typename LEFT, typename RIGHT,
	typename OPCODE,
	typename NEXT_1, typename NEXT_2,
	typename... REST
>struct eval_parse_impl<PRECEDENCE, RESULT<RESULT_ELEMS...>,
	INPUT<LEFT, evaluable<OPCODE, PRECEDENCE>, RIGHT, NEXT_1, NEXT_2, REST...> > {
	
	using value = typename eval_parse_impl<
		PRECEDENCE,
		RESULT<RESULT_ELEMS...>,
		INPUT<
		//evaluation of an opcode
		typename opcode_s::eval_s<OPCODE, LEFT, RIGHT>,
		NEXT_1, NEXT_2, REST...>
	>::value;
};

//end case
//wrong precedence - omit
template<
	int PRECEDENCE,
	template<typename...> typename RESULT,
	template<typename...> typename INPUT,
	typename... RESULT_ELEMS,
	typename LEFT, typename RIGHT,
	typename OPCODE, int PRECEDENCE_
>struct eval_parse_impl<PRECEDENCE, RESULT<RESULT_ELEMS...>,
	INPUT<LEFT, evaluable<OPCODE, PRECEDENCE_>, RIGHT>> {
	using value = RESULT<RESULT_ELEMS..., LEFT, evaluable<OPCODE, PRECEDENCE_>, RIGHT>;
};

//end case
//matching precendence - eval
template<
	int PRECEDENCE,
	template<typename...> typename RESULT,
	template<typename...> typename INPUT,
	typename... RESULT_ELEMS,
	typename LEFT, typename RIGHT,
	typename OPCODE
>struct eval_parse_impl<PRECEDENCE, RESULT<RESULT_ELEMS...>,
	INPUT<LEFT, evaluable<OPCODE, PRECEDENCE>, RIGHT>> {
	using value = RESULT<RESULT_ELEMS...,
		//evaluation of an opcode
		typename opcode_s::eval_s<OPCODE, LEFT, RIGHT>>;
};


//allows for result fallthrough if evaluation ended at a precedence higher than 0
template<int I, typename INPUT>
struct eval_parse_adapter {
	using value = typename eval_parse_impl<I, containers::list<>, INPUT>::value;
};
//ready
template<int I, template<typename...> typename INPUT, typename READY_EVAL>
struct eval_parse_adapter<I, INPUT<READY_EVAL>> {
	using value = INPUT<READY_EVAL>;
};
//empty
template<int I, template<typename...> typename INPUT>
struct eval_parse_adapter<I, INPUT<>> {
	using value = INPUT<>;
};


template<int I, typename INPUT>
struct eval_parse {
private:
	using prev_value = typename eval_parse<I - 1, INPUT>::value;
public:
	using value = typename eval_parse_adapter<I, prev_value>::value;
};

template<typename INPUT>
struct eval_parse<0, INPUT> {
	using value = typename eval_parse_adapter<0, INPUT>::value;
};


template<typename EVAL_S, typename CONTEXT>
struct evaluator;

template<typename VAL, typename CONTEXT>
struct evaluate {
	using value = VAL;
};

template<char... TAG_C, typename CONTEXT>
struct evaluate<var<TAG_C...>, CONTEXT> {
	using value = typename CONTEXT::variable_map
		::template get_value<var<TAG_C...>>;
};

template<typename OPCODE, typename LEFT, typename RIGHT, typename CONTEXT>
struct evaluate<opcode_s::eval_s<OPCODE, LEFT, RIGHT>, CONTEXT> {
	using value =
		typename evaluator<opcode_s::eval_s<OPCODE, LEFT, RIGHT>, CONTEXT>::value;
};

template<typename OPCODE, typename LEFT, typename RIGHT, typename CONTEXT>
struct evaluator<opcode_s::eval_s<OPCODE, LEFT, RIGHT>, CONTEXT> {
private:
	using ev_left = typename evaluate<LEFT, CONTEXT>::value;
	using ev_right = typename evaluate<RIGHT, CONTEXT>::value;
public:
	using value = typename opcode_s::eval_s<OPCODE, ev_left, ev_right>::value;
};

}//namespace anthem::opcodes::detail
}//namespace anthem::opcodes


template<typename... OPCODES>
struct anthem_parse<opcodes::end_eval, OPCODES...>
	: public anthem_parse<OPCODES...>
{
public:
	using previous_state = anthem_parse<OPCODES...>;
private:
	using stack_till_eval = typename previous_state::stack
		::template split<opcodes::eval>;
	using eval_p =
		typename opcodes::detail::eval_parse
		<5, typename stack_till_eval::value>::value::first;
public:
	using stack = typename stack_till_eval::remainder
		::template prepend<opcodes::evaluable_expr<eval_p>>;
};

//implementation
template<typename... OPCODES,
	typename EVAL_P
>struct anthem<opcodes::evaluable_expr<EVAL_P>, OPCODES...>
	: public anthem<
	opcode_s::set_s<opcodes::var<ANTHEM_STRING_SPLIT("@EVAL")>,
	typename opcodes::detail
	::evaluator<EVAL_P, anthem<OPCODES...>>::value>,
	OPCODES...> {
};


}//namespace anthem
