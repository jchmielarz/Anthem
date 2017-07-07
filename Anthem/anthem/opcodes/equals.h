#pragma once
#include <type_traits>
#include "anthem_base.h"
#include "eval.h"

namespace anthem {
	namespace opcodes {
		struct equals_e;
		using equals = evaluable<equals_e, 0>;
	}

	namespace opcode_s {
		template<typename LEFT, typename RIGHT>
		struct eval_s<opcodes::equals_e, LEFT, RIGHT> {
			using value = std::is_same<LEFT, RIGHT>;
		};
	}
}