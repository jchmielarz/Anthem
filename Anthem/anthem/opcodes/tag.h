#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"

namespace anthem {
namespace opcodes {
template<char... C>
struct tag;
}

//implementation
template<typename... OPCODES, char... C>
struct anthem<opcodes::tag<C...>, OPCODES...> : public anthem<OPCODES...> {
	using previous_state = anthem<WORDS...>;
	using stack =
		typename previous_state::stack
		::template prepend<opcodes::tag<C...>>;
};
}