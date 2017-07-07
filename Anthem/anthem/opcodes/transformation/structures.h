#pragma once
#include "..\tag.h"
#include "..\..\containers\containers.h"

namespace anthem {
	namespace opcodes {
		namespace transformation {
			template<
				template<char...> typename TAG,
				char... TAG_C,
				template<typename..., typename...> typename... CASES,
				typename... CONDITIONS, typename... RESULTS>
				struct tranformation_s {

				using tag = tag<TAG_C...>;
				using case_list = CASES<CONDITIONS..., RESULTS...>;

			};
		}
	}
}
