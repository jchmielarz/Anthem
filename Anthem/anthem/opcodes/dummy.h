#pragma once
#include "anthem_base.h"

namespace anthem {
namespace opcodes {
struct dummy;
}//namespace anthem::opcodes

//does nothing
template<typename... OPCODES>
struct anthem_parse<opcodes::dummy, OPCODES...> : public anthem_parse<OPCODES...> {
};
template<typename... OPCODES>
struct anthem<opcodes::dummy, OPCODES...> : public anthem<OPCODES...> {
};

}//namespace anthem