#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"
#include "var.h"

namespace anthem {
	
	namespace opcode_s {
		template<typename... OPCODES>
		struct block_s;
	}

	namespace opcodes {
		struct block;
		struct end_block;

		namespace detail {
			template<typename LIST>
			struct make_block;

			template<
				template<typename...> typename LIST,
				typename... OPCODES
			>struct make_block<LIST<OPCODES...>> {
				using value = opcode_s::block_s<OPCODES...>;
			};
		}
	}
	

	//compilation
	template<typename... OPCODES>
	struct anthem_compilation<opcodes::end_block, OPCODES...>
		: public anthem_compilation<OPCODES...>
	{
		using previous_state = anthem_compilation<OPCODES...>;
	private:
		using stack_till_block = typename previous_state::stack
			::template split<opcodes::block>;
		using block_elems = typename stack_till_block::value;
	public:
		using stack = typename stack_till_block::remainder
			::template prepend<
				typename opcodes::detail::make_block<block_elems>::value>;
	};

	//implementation
	template<
		typename... OPCODES,
		typename... BLOCK_OPCODES
	>struct anthem<opcode_s::block_s<BLOCK_OPCODES...>, OPCODES...> : public anthem<BLOCK_OPCODES...,OPCODES...> {
	};
}
