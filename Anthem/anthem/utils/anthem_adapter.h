#pragma once
#include "..\opcodes\anthem_base.h"
#include "..\opcodes\run.h"
#include "..\containers\list.h"

namespace anthem
{
	namespace utils {
		template<typename... OPCODES>
		struct anthem_compilation_adapter {
		private:
			template<typename OPCODE_LIST>
			struct make_anthem_compilation_from_list;

			template<
				template<typename...> typename OPCODE_LIST,
				typename... OPCODES>
				struct make_anthem_compilation_from_list<OPCODE_LIST<OPCODES...>> {
				using value = typename anthem_compilation<opcodes::run,OPCODES...>;
			};

		public:
			//all of the code has to be reversed for inheritance
			//to make sense
			using compilation = typename
				make_anthem_compilation_from_list
				<typename containers::list<OPCODES...>::reverse>::value;
		};
		
		//
		//template<typename... WORDS>
		//struct anthem_adapter {
		//private:
		//	template<typename WORD_LIST>
		//	struct make_anthem_from_list;

		//	template<
		//		template<typename...> typename WORD_LIST,
		//		typename... WORDS>
		//		struct make_anthem_from_list<WORD_LIST<WORDS...>> {
		//		using value = typename anthem<WORDS...>;
		//	};
		//	
		//public:
		//	//all of the code has to be reversed for inheritance
		//	//to make sense
		//	using anthem = typename 
		//		make_anthem_from_list<typename containers::list<WORDS...>::reverse>::value;
		//};
	}
}