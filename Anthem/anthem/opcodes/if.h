#pragma once
#include "anthem_base.h"
#include "..\containers\map.h"
#include "block.h"
#include "eval.h"
#include "var.h"

namespace anthem {
namespace opcodes {
struct if_;
struct end_if;

struct if_execute;
}

namespace opcode_s {
template<typename... CASES>
struct if_s;

template<typename... CASES>
struct if_eval_s;


template<typename EVAL, typename BLOCK>
struct case_s;
}

namespace opcodes {
namespace detail {

using namespace containers;
using namespace opcode_s;

template<typename... CASE_DATA>
struct make_case_list_inner {
	//using value = list<>;
};

template<
	template<typename> typename EVAL_E,
	typename EVAL_S,
	template<typename...> typename BLOCK,
	typename... BLOCK_ELEMS,
	typename... CASE_DATA
>struct make_case_list_inner<
	EVAL_E<EVAL_S>,
	BLOCK<BLOCK_ELEMS...>,
	CASE_DATA...>
{
	using previous_step = make_case_list_inner<CASE_DATA...>;
	using value = typename previous_step::value
		::template prepend<
		case_s<
		evaluable_expr<EVAL_S>,
		block_s<BLOCK_ELEMS...>>>;
};

template<>
struct make_case_list_inner<>
{
	using value = list<>;
};

template<typename CASE_LIST>
struct make_case_list;

template<typename... CASE_DATA>
struct make_case_list<list<CASE_DATA...>> {
	using value =
		typename make_case_list_inner<CASE_DATA...>::value;
};

template<typename CASE_LIST>
struct make_if_s_from_list;

template<template<typename...>typename CASE_LIST, typename... CASES>
struct make_if_s_from_list<CASE_LIST<CASES...>> {
	using value = if_s<CASES...>;
};

template<bool IS_COND_TRUE, typename CONTEXT, typename BLOCK, typename... CASES>
struct if_evaluator_inner;

template<typename CONTEXT, typename... CASES>
struct if_evaluator;

//if the condition was fulfilled we return the underlying code
template<typename BLOCK, typename... CASES, typename CONTEXT>
struct if_evaluator_inner<true, CONTEXT, BLOCK, CASES...> {
	using value = BLOCK;
};

//if the condition was not fulfilled we go back and pass the rest of the cases
template<typename BLOCK, typename... CASES, typename CONTEXT>
struct if_evaluator_inner<false, CONTEXT, BLOCK, CASES...> {
	using value = typename if_evaluator<CONTEXT, CASES...>::value;
};

template<typename EVAL_S, typename BLOCK, typename... CASES, typename CONTEXT>
struct if_evaluator<CONTEXT, case_s<evaluable_expr<EVAL_S>, BLOCK>, CASES...> {
private:
	using is_cond_true = typename evaluator<EVAL_S, CONTEXT>::value;
public:
	using value = typename if_evaluator_inner
		<is_cond_true::value, CONTEXT, BLOCK, CASES...>::value;
};

//empty case - can occur when none of the cases were appliable
template<typename CONTEXT>
struct if_evaluator<CONTEXT> {
	using value = block_s<>;
};




}
}


//compilation
template<typename... OPCODES>
struct anthem_compilation<opcodes::end_if, OPCODES...>
	: public anthem_compilation<OPCODES...>
{
	using previous_state = anthem_compilation<OPCODES...>;
//private:
	using stack_till_if = typename previous_state::stack
		::template split<opcodes::if_>;
	using case_data = typename stack_till_if::value::reverse;
	using cases = typename opcodes::detail::make_case_list<case_data>::value;
public:
	using stack = typename stack_till_if::remainder
		::template prepend<typename opcodes::detail::make_if_s_from_list<cases>::value>;
};

//implementation
template<typename... OPCODES, typename... CASES>
struct anthem<opcode_s::if_s<CASES...>, OPCODES...> 
	: public anthem<
	//we prepend the block with opcodes to execute
	typename opcodes::detail::if_evaluator<anthem<OPCODES...>, CASES...>::value,
	OPCODES...> {

	using BLOCK = typename opcodes::detail::if_evaluator<anthem<OPCODES...>, CASES...>;
};
}