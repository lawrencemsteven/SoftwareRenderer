#include "HelperFunctions.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace helpers {

	///////////
	// float //
	///////////

	void checkFloatValues(const float float1, const float float2) {
		CHECK_THAT(float1, Catch::Matchers::WithinAbs(float2, FLOATING_POINT_ERROR_MARGIN));
	}




	///////////
	// Vec2f //
	///////////

	void checkVec2fValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec) {
		for (std::size_t i = 0; i < 2; i++) {
			checkFloatValues(vec[i], otherVec[i]);
		}
	}

	void checkVec2fValues(const slm::Vec2f& vec, const std::array<float, 2>& values) {
		for (std::size_t i = 0; i < 2; i++) {
			checkFloatValues(vec[i], values[i]);
		}
	}

	void checkVec2fValues(const slm::Vec2f& vec, const float x, const float y) {
		checkFloatValues(vec.x(), x);
		checkFloatValues(vec.y(), y);
	}




	////////////
	// Line2f //
	////////////

	void checkLine2fValues(const slm::Line2f& line, const slm::Vec2f& start,
						   const slm::Vec2f& end) {
		checkVec2fValues(line.getStart(), start);
		checkVec2fValues(line.getEnd(), end);
	}

	void checkLine2fValues(const slm::Line2f& line, float x1, float y1, float x2, float y2) {
		checkVec2fValues(line.getStart(), x1, y1);
		checkVec2fValues(line.getEnd(), x2, y2);
	}
}