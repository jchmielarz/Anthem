#pragma once

#define DEFINE_ANTHEM_STACKED_OPCODE(opcode) \
template<typename... OPCODES> \
struct anthem_compilation<opcode, OPCODES...>: public anthem_compilation<OPCODES...>\
{ using stack = typename anthem_compilation<OPCODES...>::stack::template prepend<opcode>; };

namespace anthem {
	namespace opcodes {
		namespace utils {

		}
	}
}