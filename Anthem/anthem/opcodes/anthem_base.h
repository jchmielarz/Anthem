#pragma once
//#include "..\containers\list.h"

namespace anthem {

	template<typename... OPCODES>
	struct anthem_compilation {};

	template<>
	struct anthem_compilation<> {
		using variable_map = containers::map<>;
		using transformation_map = containers::map<>;
		using function_map = containers::map<>;

		using stack = containers::list<>;
	};

	template<typename OPCODE, typename... OPCODES>
	struct anthem_compilation<OPCODE, OPCODES...> : anthem_compilation<OPCODES...> {
		using stack = typename anthem_compilation<OPCODES...>::stack
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
	struct anthem<anthem_compilation<OPCODES...>> {
	private:
		using compilation = typename anthem_compilation<OPCODES...>;
	public:
		using variable_map = typename compilation::variable_map;
		using transformation_map = typename compilation::transformation_map;
		using function_map = typename compilation::function_map;

		using stack = containers::list<>;
	};

	
}