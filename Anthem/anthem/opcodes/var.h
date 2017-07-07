#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"

namespace anthem {
	namespace opcodes {
		template<char... C>
		struct var;
	}

	//implementation
	/*template<typename... WORDS, char... C>
	struct anthem<opcodes::var<C...>, WORDS...> : public anthem<WORDS...> {
		using previous_state = anthem<WORDS...>;
		using stack = 
			typename previous_state::stack
				::template prepend<opcodes::var<C...>>;
	};*/
}
