#pragma once
#include "anthem_base.h"


namespace anthem {
	namespace opcodes {
		template<typename T>
		class skip_until;
	}

	//implementation
	template<typename LOOK_FOR, typename SKIPPED_KEYWORD, typename... FOLLOWING_KEYWORDS>
	struct anthem<opcodes::skip_until<LOOK_FOR>, SKIPPED_KEYWORD, FOLLOWING_KEYWORDS...>
		: public anthem<FOLLOWING_KEYWORDS...> {
	};

	template<typename LOOK_FOR, typename... FOLLOWING_KEYWORDS>
	struct anthem<opcodes::skip_until<LOOK_FOR>, LOOK_FOR, FOLLOWING_KEYWORDS...>
		: public anthem<LOOK_FOR, FOLLOWING_KEYWORDS...> {
	};
}