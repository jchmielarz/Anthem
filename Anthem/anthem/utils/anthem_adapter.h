#pragma once
#include "..\opcodes\anthem_base.h"
#include "..\opcodes\run.h"
#include "..\containers\list.h"

namespace anthem{
namespace utils {
template<typename... OPCODES>
struct anthem_parse_adapter {
private:
	template<typename OPCODE_LIST>
	struct make_anthem_parse_from_list;

	template<
		template<typename...> typename OPCODE_LIST,
		typename... OPCODES
	>struct make_anthem_parse_from_list<OPCODE_LIST<OPCODES...>> {
		using value = typename anthem_parse<opcodes::run, OPCODES...>;
	};

public:
	//all of the code has to be reversed for inheritance
	//to make sense
	using compilation = typename
		make_anthem_parse_from_list
		<typename containers::list<OPCODES...>::reverse>::value;
};
}//namespace utils
}//namespace anthem