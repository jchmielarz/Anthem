#pragma once

namespace anthem {

template<typename... OPCODES>
struct anthem_parse {};

template<>
struct anthem_parse<> {
	using variable_map = containers::map<>;
	using transformation_map = containers::map<>;
	using function_map = containers::map<>;

	using stack = containers::list<>;
};

template<typename OPCODE, typename... OPCODES>
struct anthem_parse<OPCODE, OPCODES...> : anthem_parse<OPCODES...> {
	using stack = typename anthem_parse<OPCODES...>::stack
		::template prepend<OPCODE>;
};


template<typename... OPCODES>
struct anthem {};

template<>
struct anthem<> {
	using variable_map = containers::map<>;
};

template<typename OPCODE, typename... OPCODES>
struct anthem<OPCODE, OPCODES...> : anthem<OPCODES...> {
	using stack = typename anthem<OPCODES...>::stack
		::template prepend<OPCODE>;
};

template<typename... OPCODES>
struct anthem<anthem_parse<OPCODES...>> {
private:
	using compilation = typename anthem_parse<OPCODES...>;
public:
	using variable_map = typename compilation::variable_map;
	using transformation_map = typename compilation::transformation_map;
	using function_map = typename compilation::function_map;

	using stack = containers::list<>;
};

}//namespace anthem