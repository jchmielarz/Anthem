#pragma once

namespace anthem
{
	namespace containers {

		template<typename VALUE, typename REMAINDER>
		struct list_split_result {
			using value = typename VALUE;
			using remainder = typename REMAINDER;
		};

		template<typename... ELEMS>
		struct list {

		private:
			template<typename LIST, typename... NEW_ELEMS>
			struct append_s_impl {};

			template<template<typename...> typename LIST, typename... LIST_ELEMS, typename... NEW_ELEMS>
			struct append_s_impl<LIST<LIST_ELEMS...>, NEW_ELEMS...> {
				using value = LIST<LIST_ELEMS..., NEW_ELEMS...>;
			};


			template<typename LIST, typename... NEW_ELEMS>
			struct prepend_s_impl {};

			template<template<typename...> typename LIST, typename... LIST_ELEMS, typename... NEW_ELEMS>
			struct prepend_s_impl<LIST<LIST_ELEMS...>, NEW_ELEMS...> {
				using value = LIST<NEW_ELEMS..., LIST_ELEMS...>;
			};


			template<typename LIST>
			struct first_s_impl {
				using value = void;
			};

			template<template<typename...> typename LIST, typename FIRST_ELEM, typename... TAIL>
			struct first_s_impl<LIST<FIRST_ELEM, TAIL...>> {
				using value = FIRST_ELEM;
			};


			template<typename LIST>
			struct last_s_impl {
				using value = void;
			};

			template<template<typename...> typename LIST, typename LAST_ELEM>
			struct last_s_impl<LIST<LAST_ELEM>> {
				using value = LAST_ELEM;
			};

			template<template<typename...> typename LIST, typename HEAD, typename... TAIL>
			struct last_s_impl<LIST<HEAD, TAIL...>> : public last_s_impl<LIST<TAIL...>> {
			};

			template<typename LIST, typename NEW_LIST>
			struct reverse_s_impl;

			template<
				template<typename...> typename LIST,
				typename HEAD, typename... TAIL,
				template<typename...> typename REVERSED_LIST,
				typename... REVERSED_LIST_ELEMS>
				struct reverse_s_impl<LIST<HEAD, TAIL...>, REVERSED_LIST<REVERSED_LIST_ELEMS...>> {
				using value = typename reverse_s_impl<LIST<TAIL...>,
					REVERSED_LIST<HEAD, REVERSED_LIST_ELEMS...>>::value;
			};

			template<
				template<typename...> typename LIST,
				template<typename...> typename REVERSED_LIST,
				typename... REVERSED_LIST_ELEMS>
				struct reverse_s_impl<LIST<>, REVERSED_LIST<REVERSED_LIST_ELEMS...>> {
				using value = REVERSED_LIST<REVERSED_LIST_ELEMS...>;
			};

			/*template<typename SPLIT_WITH, template<typename...> typename LIST,
				template<typename...> typename REVERSED_LIST>*/

			template<
				typename SPLIT_WITH,
				typename RESULT,
				typename... PAIRS>
				struct split_inner_impl;

			template<
				typename SPLIT_WITH,
				template <typename...> typename RESULT,
				typename... RESULT_ELEMENTS,
				typename HEAD,
				typename... TAIL>
				struct split_inner_impl
				<SPLIT_WITH, RESULT<RESULT_ELEMENTS...>, HEAD, TAIL...> :
				split_inner_impl<SPLIT_WITH, RESULT<RESULT_ELEMENTS..., HEAD>, TAIL...> {
			};

			template<
				typename SPLIT_WITH,
				template <typename...> typename RESULT,
				typename... RESULT_ELEMENTS,
				typename... TAIL>
				struct split_inner_impl
				<SPLIT_WITH, RESULT<RESULT_ELEMENTS...>, SPLIT_WITH, TAIL...> {

				using value = RESULT<RESULT_ELEMENTS...>;
				using remainder = list<TAIL...>;
			};

			template<
				typename SPLIT_WITH,
				template <typename...> typename RESULT,
				typename... RESULT_ELEMENTS>
				struct split_inner_impl
				<SPLIT_WITH, RESULT<RESULT_ELEMENTS...>> {

				using value = RESULT<RESULT_ELEMENTS...>;
				using remainder = list<>;
			};

			template<
				typename SPLIT_WITH,
				typename LIST>
				struct split_impl;

			template<
				typename SPLIT_WITH,
				template <typename...> typename LIST,
				typename... LIST_ELEMENTS>
				struct split_impl<SPLIT_WITH, LIST<LIST_ELEMENTS...>> {

				using inner = split_inner_impl<SPLIT_WITH, list<>, LIST_ELEMENTS...>;
				using value = list_split_result<typename inner::value, typename inner::remainder>;
			};

		public:

			template<typename LIST, typename... NEW_ELEMS>
			using append_s = typename append_s_impl<LIST, NEW_ELEMS...>::value;

			template<typename... NEW_ELEMS>
			using append = typename append_s_impl<list<ELEMS...>, NEW_ELEMS...>::value;

			template<typename LIST, typename... NEW_ELEMS>
			using prepend_s = typename prepend_s_impl<LIST, NEW_ELEMS...>::value;

			template<typename... NEW_ELEMS>
			using prepend = typename prepend_s_impl<list<ELEMS...>, NEW_ELEMS...>::value;

			template<typename LIST>
			using first_s = typename first_s_impl<LIST>::value;

			using first = typename first_s_impl<list<ELEMS...>>::value;

			template<typename LIST>
			using last_s = typename last_s_impl<LIST>::value;

			using last = typename last_s_impl<list<ELEMS...>>::value;

			template<typename LIST>
			using reverse_s = typename reverse_s_impl<LIST, list<>>::value;

			using reverse = typename reverse_s_impl<list<ELEMS...>, list<>>::value;

			template<typename SPLIT_WITH, typename LIST>
			using split_s = typename split_impl<SPLIT_WITH, LIST>::value;

			template<typename SPLIT_WITH>
			using split = typename split_impl<SPLIT_WITH, list<ELEMS...>>::value;
		};

	}
}