#pragma once
#define VAR(a) anthem::opcodes::var<ANTHEM_STRING_SPLIT(#a)>

//general usage
#define ANTHEM_SCRIPT_BEGIN \
	typename anthem::utils::anthem_compilation_adapter<anthem::opcodes::dummy,
#define ANTHEM_SCRIPT_END \
	anthem::opcodes::dummy>::compilation::anthem;

#define ANTHEM_GET_VAR(anthem_script, tag) typename anthem_script::variable_map::get_value<anthem::opcodes::var<ANTHEM_STRING_SPLIT(#tag)>>

//opcodes
#define BLOCK anthem::opcodes::block,
#define END_BLOCK anthem::opcodes::end_block,

#define IF anthem::opcodes::if_,anthem::opcodes::eval,
#define END_IF anthem::opcodes::end_block,anthem::opcodes::end_if,
#define THEN anthem::opcodes::end_eval,anthem::opcodes::block,
#define ELSE anthem::opcodes::end_block,anthem::opcodes::eval, int, \
 anthem::opcodes::equals, int, anthem::opcodes::end_eval, anthem::opcodes::block,
#define ELSE_IF anthem::opcodes::end_block,anthem::opcodes::eval,

#define SET anthem::opcodes::set,

//operator opcodes
#define EQUALS anthem::opcodes::equals,
#define AND anthem::opcodes::and,


