#pragma once
#include "list.h"

namespace anthem {
namespace containers {

template<typename... PAIRS>
struct map;

namespace detail {
template<typename NEW_PAIR, typename... PAIRS>
struct add_impl {
	using value = typename list<>::prepend_s<map<PAIRS...>, NEW_PAIR>;
};


template<
	typename KEY,
	typename VALUE,
	typename NEW_MAP,
	typename... PAIRS
>struct find_key_and_set_impl;

template<
	typename KEY,
	typename VALUE,
	template <typename...> typename NEW_MAP,
	typename... NEW_MAP_PAIRS,
	template<typename, typename> typename HEAD,
	typename KEY_, typename VALUE_,
	typename... TAIL
>struct find_key_and_set_impl
<KEY, VALUE, NEW_MAP<NEW_MAP_PAIRS...>, HEAD<KEY_, VALUE_>, TAIL...> {
	using value = typename find_key_and_set_impl<
		KEY, VALUE,
		NEW_MAP<NEW_MAP_PAIRS..., HEAD<KEY_, VALUE_>>,
		TAIL...>::value;
};

template<
	typename KEY,
	typename VALUE,
	template <typename...> typename NEW_MAP,
	typename... NEW_MAP_PAIRS,
	template<typename, typename> typename HEAD,
	typename VALUE_,
	typename... TAIL
>struct find_key_and_set_impl
<KEY, VALUE, NEW_MAP<NEW_MAP_PAIRS...>, HEAD<KEY, VALUE_>, TAIL...> {
	using value = typename find_key_and_set_impl<
		KEY, VALUE,
		NEW_MAP<NEW_MAP_PAIRS..., HEAD<KEY, VALUE>>,
		TAIL...>::value;
};

template<
	typename KEY,
	typename VALUE,
	template <typename...> typename NEW_MAP,
	typename... NEW_MAP_PAIRS>
	struct find_key_and_set_impl
	<KEY, VALUE, NEW_MAP<NEW_MAP_PAIRS...>> {
	using value = typename NEW_MAP<NEW_MAP_PAIRS...>;
};

template<typename KEY, typename VALUE, typename... PAIRS>
struct find_key_and_set {
	using value =
		typename find_key_and_set_impl<KEY, VALUE, map<>, PAIRS...>::value;
};

template<bool HAS_KEY, typename KEY, typename VALUE, typename... PAIRS>
struct set_inner_impl;

//add new pair if key does not exist
template<typename KEY, typename VALUE, typename... PAIRS>
struct set_inner_impl<false, KEY, VALUE, PAIRS...> {
	using value = typename add_impl<pair<KEY, VALUE>, PAIRS...>::value;
};

//replace value if key exists
template<typename KEY, typename VALUE, typename... PAIRS>
struct set_inner_impl<true, KEY, VALUE, PAIRS...> {
	using value = typename find_key_and_set<KEY, VALUE, PAIRS...>::value;
};


template<typename KEY, typename... PAIRS>
struct has_key_inner_impl {
	using value = std::false_type;
};

template<
	typename KEY,
	typename HEAD,
	typename... TAIL
>struct has_key_inner_impl<KEY, HEAD, TAIL...> {
	using value = typename has_key_inner_impl<KEY, TAIL...>::value;
};

template<
	typename KEY,
	template<typename, typename> typename HEAD,
	typename VALUE,
	typename... TAIL
>struct has_key_inner_impl<KEY, HEAD<KEY, VALUE>, TAIL...> {
	using value = std::true_type;
};

template<typename KEY>
struct has_key_inner_impl<KEY> {
	using value = std::false_type;
};


template<typename MAP, typename KEY>
struct has_key_impl;

template<
	template<typename...> typename MAP,
	typename KEY,
	typename... PAIRS
>struct has_key_impl<MAP<PAIRS...>, KEY> {
	using value = typename has_key_inner_impl<KEY, PAIRS...>::value;
};



template<typename KEY, typename VALUE, typename... PAIRS>
struct set_impl {
	using value = typename set_inner_impl<
		has_key_inner_impl<KEY, PAIRS...>::value::value,
		KEY, VALUE, PAIRS...>::value;
};

template<typename KEY, typename... PAIRS>
struct get_value_impl;

template<typename KEY>
struct get_value_impl<KEY> {
	using value = void;
};

template<
	typename KEY,
	template<typename, typename> typename HEAD,
	typename... TAIL,
	typename KEY_,
	typename VALUE_
>struct get_value_impl<KEY, HEAD<KEY_, VALUE_>, TAIL...> {
	using value = typename get_value_impl<KEY, TAIL...>::value;
};

template<
	typename KEY,
	template<typename, typename>typename HEAD,
	typename... TAIL,
	typename VALUE_
>struct get_value_impl<KEY, HEAD<KEY, VALUE_>, TAIL...> {
	using value = VALUE_;
};
}

template<typename... PAIRS>
struct map {
	template<typename KEY, typename VALUE>
	using set = typename detail::set_impl<KEY, VALUE, PAIRS...>::value;

	template<typename KEY>
	using has_key = typename detail::has_key_impl<map<PAIRS...>, KEY>::value;

	template<typename KEY>
	using get_value = typename detail::get_value_impl<KEY, PAIRS...>::value;
};


}
}