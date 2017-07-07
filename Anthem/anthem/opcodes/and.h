#pragma once
#include <type_traits>
#include "anthem_base.h"
#include "eval.h"

namespace anthem {
	namespace opcodes {
		struct and_e;
		using and = evaluable<and_e, 1>;
	}

	namespace opcode_s {
		namespace detail {
			template<bool LEFT, bool RIGHT>
			struct and_impl{
				using value = std::false_type;
			};

			template<>
			struct and_impl<true, true> {
				using value = std::true_type;
			};
		}

		template<typename LEFT, typename RIGHT>
		struct eval_s<opcodes::and_e, LEFT, RIGHT> {
			using value = typename detail::and_impl<LEFT::value, RIGHT::value>::value;
		};
	}
}