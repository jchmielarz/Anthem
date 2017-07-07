#pragma once
#include "anthem_base.h"
#include "..\containers\list.h"

namespace anthem {
	namespace opcodes {
		struct run;
	}

	//compilation
	template<typename... OPCODES>
	struct anthem_parse<opcodes::run, OPCODES...>
	{
	public:
		using compilation = anthem_parse<OPCODES...>;

	private:
		template<typename STACK>
		struct make_anthem;

		template<typename... OPCODES>
		struct make_anthem<containers::list<OPCODES...>>
		{
			using value = anthem<OPCODES..., compilation>;
		};

	public:
		using anthem = typename make_anthem<typename compilation::stack>::value;
	};
		
}