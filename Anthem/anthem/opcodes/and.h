#pragma once
#include <type_traits>
#include "anthem_base.h"
#include "eval.h"

namespace anthem {
namespace opcodes {

struct and_e;
using and = evaluable<and_e, 1>;

namespace detail {
template<bool LEFT, bool RIGHT>
struct and_impl {
	using value = std::false_type;
};

template<>
struct and_impl<true, true> {
	using value = std::true_type;
};

}//namespace anthem::opcodes::detail
}//namespace anthem::opcodes

namespace opcode_s {

template<typename LEFT, typename RIGHT>
struct eval_s<opcodes::and_e, LEFT, RIGHT> {
	using value = typename opcodes::detail::and_impl<LEFT::value, RIGHT::value>::value;
};

}//namespace anthem::opcode_s
}//namespace anthem