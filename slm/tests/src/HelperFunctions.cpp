#include "HelperFunctions.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace helpers {

	///////////
	// float //
	///////////

	void checkValues(const float float1, const float float2) {
		CHECK_THAT(float1, Catch::Matchers::WithinAbs(float2, FLOATING_POINT_ERROR_MARGIN));
	}




	/////////////
	// int32_t //
	/////////////

	void checkValues(const int32_t int1, const int32_t int2) {
		CHECK(int1 == int2);
	}




	//////////////
	// uint32_t //
	//////////////

	void checkValues(const uint32_t uint1, const uint32_t uint2) {
		CHECK(uint1 == uint2);
	}




	/////////////////
	// BitLocation //
	/////////////////

	void checkValues(const slm::BitLocation& loc, const bool above, const bool below,
					 const bool left, const bool right) {
		CHECK(loc.above == above);
		CHECK(loc.below == below);
		CHECK(loc.left == left);
		CHECK(loc.right == right);
	}

	void checkValues(const slm::BitLocation& loc1, const slm::BitLocation& loc2) {
		CHECK(loc1.above == loc2.above);
		CHECK(loc1.below == loc2.below);
		CHECK(loc1.left == loc2.left);
		CHECK(loc1.right == loc2.right);
	}




	///////////
	// Vec2f //
	///////////

	void checkValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec) {
		for (std::size_t i = 0; i < 2; i++) {
			checkValues(vec[i], otherVec[i]);
		}
	}

	void checkValues(const slm::Vec2f& vec, const std::array<float, 2>& values) {
		for (std::size_t i = 0; i < 2; i++) {
			checkValues(vec[i], values[i]);
		}
	}

	void checkValues(const slm::Vec2f& vec, const float x, const float y) {
		checkValues(vec.x(), x);
		checkValues(vec.y(), y);
	}




	///////////
	// Vec2u //
	///////////

	void checkValues(const slm::Vec2u& vec, const slm::Vec2u& otherVec) {
		for (std::size_t i = 0; i < 2; i++) {
			checkValues(vec[i], otherVec[i]);
		}
	}

	void checkValues(const slm::Vec2u& vec, const std::array<uint32_t, 2>& values) {
		for (std::size_t i = 0; i < 2; i++) {
			checkValues(vec[i], values[i]);
		}
	}

	void checkValues(const slm::Vec2u& vec, const uint32_t x, const uint32_t y) {
		checkValues(vec.x(), x);
		checkValues(vec.y(), y);
	}




	///////////
	// Vec3f //
	///////////

	void checkValues(const slm::Vec3f& vec, const slm::Vec3f& otherVec) {
		for (std::size_t i = 0; i < 3; i++) {
			checkValues(vec[i], otherVec[i]);
		}
	}

	void checkValues(const slm::Vec3f& vec, const std::array<float, 3>& values) {
		for (std::size_t i = 0; i < 3; i++) {
			checkValues(vec[i], values[i]);
		}
	}

	void checkValues(const slm::Vec3f& vec, const float x, const float y, const float z) {
		checkValues(vec.x(), x);
		checkValues(vec.y(), y);
		checkValues(vec.z(), z);
	}




	///////////
	// Vec3i //
	///////////

	void checkValues(const slm::Vec3i& vec, const slm::Vec3i& otherVec) {
		for (std::size_t i = 0; i < 3; i++) {
			checkValues(vec[i], otherVec[i]);
		}
	}

	void checkValues(const slm::Vec3i& vec, const std::array<int32_t, 3>& values) {
		for (std::size_t i = 0; i < 3; i++) {
			checkValues(vec[i], values[i]);
		}
	}

	void checkValues(const slm::Vec3i& vec, const int32_t x, const int32_t y,
						  const int32_t z) {
		checkValues(vec.x(), x);
		checkValues(vec.y(), y);
		checkValues(vec.z(), z);
	}




	////////////
	// Line2f //
	////////////

	void checkValues(const slm::Line2f& line, const slm::Vec2f& start, const slm::Vec2f& end) {
		checkValues(line.getStart(), start);
		checkValues(line.getEnd(), end);
	}

	void checkValues(const slm::Line2f& line, const float x1, const float y1, const float x2,
					 const float y2) {
		checkValues(line.getStart(), x1, y1);
		checkValues(line.getEnd(), x2, y2);
	}




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	void checkValues(const slm::AxisAlignedBox2u& axisAlignedBox, const slm::Vec2u& bottomLeft,
					 const slm::Vec2u& topRight) {
		checkValues(axisAlignedBox.getBottomLeft(), bottomLeft);
	}
	void checkValues(const slm::AxisAlignedBox2u& axisAlignedBox, const uint32_t left,
					 const uint32_t bottom, const uint32_t right, const uint32_t top) {
		checkValues(axisAlignedBox.getBottomLeft(), left, bottom);
		checkValues(axisAlignedBox.getTopRight(), right, top);
	}
}