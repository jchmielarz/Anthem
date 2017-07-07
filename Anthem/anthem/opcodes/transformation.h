#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"
#include "stack_opcode.h"
#include "tag.h"

namespace anthem {
	namespace opcodes {
		struct transformation;
	}

	//implementation
	template<typename... WORDS, char... CALLED>
	struct anthem<opcodes::tag<CALLED...>, opcodes::transformation, WORDS...> 
		: public anthem<opcodes::stack_opcode<opcodes::transformation>,
				WORDS...> {
		
	};
}