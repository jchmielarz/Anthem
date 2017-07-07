#pragma once

namespace anthem{
namespace containers {

template<typename TAG, typename VAL>
struct pair {
	using tag = TAG;
	using value = VAL;
};

}//namespace anthem::containers
}//namespace anthem