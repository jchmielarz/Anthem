#pragma once
#include "anthem_base.h"
#include "..\containers\map.h"
#include "var.h"

namespace anthem {
namespace opcodes {
struct set;
}//namespace anthem::opcodes
namespace opcode_s {
template<typename TAG, typename VALUE>
struct set_s;
}//namespace anthem::opcode_s

//compilation
template<typename... OPCODES, typename TAG, typename VALUE>
struct anthem_parse<VALUE, TAG, opcodes::set, OPCODES...>
	: public anthem_parse<OPCODES...>
{
	using previous_state = anthem_parse<OPCODES...>;
	using stack = typename previous_state::stack
		::template prepend<opcode_s::set_s<TAG, VALUE>>;
};

//implementation
template<typename... OPCODES,
	typename TAG, typename VALUE>
	struct anthem<opcode_s::set_s<TAG, VALUE>, OPCODES...> : public anthem<OPCODES...> {
	using previous_state = anthem<OPCODES...>;
	using variable_map = typename previous_state::variable_map::template set<TAG, VALUE>;
};
}//namespace anthem
