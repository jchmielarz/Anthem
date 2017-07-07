#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"

namespace anthem {
	namespace opcodes {
		template<typename OPCODE>
		struct stack_opcode;
	}

	//implementation
	template<typename... WORDS, typename OPCODE>
	struct anthem<opcodes::stack_opcode<OPCODE>, WORDS...> : public anthem<WORDS...> {
		using previous_state = anthem<WORDS...>;
		using stack =
			typename previous_state::op_stack
				::template prepend<OPCODE>>;
	};
}