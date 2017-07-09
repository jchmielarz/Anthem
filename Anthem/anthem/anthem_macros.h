#pragma once
//utils
#include "utils\split_string.h"


//general usage
#define ANTHEM_SCRIPT_BEGIN \
	typename anthem::utils::anthem_parse_adapter<anthem::opcodes::dummy,
#define ANTHEM_SCRIPT_END \
	anthem::opcodes::dummy>::compilation::anthem;
#define ANTHEM_GET_VAR(anthem_script, tag) typename anthem_script::variable_map::get_value<anthem::opcodes::var<ANTHEM_STRING_SPLIT(#tag)>>

//opcodes
#define VAR(a) anthem::opcodes::var<ANTHEM_STRING_SPLIT(#a)>,
#define VAR_(a) anthem::opcodes::var<ANTHEM_STRING_SPLIT(#a)>

#define BLOCK anthem::opcodes::block,
#define END_BLOCK anthem::opcodes::end_block,

#define IF anthem::opcodes::if_,anthem::opcodes::eval,
#define END_IF anthem::opcodes::end_block,anthem::opcodes::end_if,
#define THEN anthem::opcodes::end_eval,anthem::opcodes::block,
#define ELSE anthem::opcodes::end_block,anthem::opcodes::eval, int, \
 anthem::opcodes::equals, int,
#define ELSE_IF anthem::opcodes::end_block,anthem::opcodes::eval,

#define SET anthem::opcodes::set,

//operator opcodes
#define EQUALS anthem::opcodes::equals,
#define AND anthem::opcodes::and,


