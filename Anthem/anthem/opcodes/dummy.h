#pragma once
#include "anthem_base.h"

namespace anthem {
namespace opcodes {
struct dummy;
}

//does nothing
template<typename... OPCODES>
struct anthem_compilation<opcodes::dummy, OPCODES...> : public anthem_compilation<OPCODES...> {
};
template<typename... OPCODES>
struct anthem<opcodes::dummy, OPCODES...> : public anthem<OPCODES...> {
};

}