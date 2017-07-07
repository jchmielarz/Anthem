#pragma once
#include "anthem_base.h"
#include "../containers/containers.h"

namespace anthem {
	namespace opcodes {
		class init {};
	}



	//initial state
	template<>
	struct anthem<opcodes::init> {
		using variable_map = containers::map<>;
		using transformation_map = containers::map<>;
		using function_map = containers::map<>;


		using stack = containers::list<>;
		using op_stack = containers::list<>;
	};
}
