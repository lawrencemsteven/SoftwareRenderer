#include "HelperFunctions.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace helpers {

	void checkVec2fValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec) {
		for (std::size_t i = 0; i < 2; i++) {
			CHECK_THAT(vec[i], Catch::Matchers::WithinAbs(otherVec[i], 0.0001f));
		}
	}
	void checkVec2fValues(const slm::Vec2f& vec, const std::array<float, 2>& values) {
		for (std::size_t i = 0; i < 2; i++) {
			CHECK_THAT(vec[i], Catch::Matchers::WithinAbs(values[i], 0.0001f));
		}
	}

}