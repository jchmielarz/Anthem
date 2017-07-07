#include <type_traits>
#include <tuple>
#include <iostream>
#include <utility>
#include "anthem/anthem.h"
#include "anthem_test/tests.h"


//struct t_4 {
//	using value = std::integral_constant<int, 4>;
//};
//
//struct t_5 {
//	using value = std::integral_constant<int, 5>;
//};
//
//template<int I, typename Y>
//struct T {
//	using value = std::false_type;
//};
//
//template<int I, typename Y, typename = std::enable_if_t<I != Y::value::value>>
//struct T<I, Y> {
//	using value = std::false_type;
//};
//
//template<int I, typename Y, typename = std::enable_if_t<I == Y::value::value>>
//struct T<I, Y> {
//	using value = std::true_type;
//};

int main()
{
	AnthemTest::runTests();

	//using t = T<4, t_4>;

	//static_assert, "");

	return 0;
}

