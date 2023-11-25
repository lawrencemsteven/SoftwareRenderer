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




	/////////////
	// int32_t //
	/////////////

	void checkInt32_tValues(const int32_t int1, const int32_t int2) {
		CHECK(int1 == int2);
	}




	//////////////
	// uint32_t //
	//////////////

	void checkUint32_tValues(const uint32_t uint1, const uint32_t uint2) {
		CHECK(uint1 == uint2);
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




	///////////
	// Vec2u //
	///////////

	void checkVec2uValues(const slm::Vec2u& vec, const slm::Vec2u& otherVec) {
		for (std::size_t i = 0; i < 2; i++) {
			checkUint32_tValues(vec[i], otherVec[i]);
		}
	}

	void checkVec2uValues(const slm::Vec2u& vec, const std::array<uint32_t, 2>& values) {
		for (std::size_t i = 0; i < 2; i++) {
			checkUint32_tValues(vec[i], values[i]);
		}
	}

	void checkVec2uValues(const slm::Vec2u& vec, const uint32_t x, const uint32_t y) {
		checkUint32_tValues(vec.x(), x);
		checkUint32_tValues(vec.y(), y);
	}




	///////////
	// Vec3f //
	///////////

	void checkVec3fValues(const slm::Vec3f& vec, const slm::Vec3f& otherVec) {
		for (std::size_t i = 0; i < 3; i++) {
			checkFloatValues(vec[i], otherVec[i]);
		}
	}

	void checkVec3fValues(const slm::Vec3f& vec, const std::array<float, 3>& values) {
		for (std::size_t i = 0; i < 3; i++) {
			checkFloatValues(vec[i], values[i]);
		}
	}

	void checkVec3fValues(const slm::Vec3f& vec, const float x, const float y, const float z) {
		checkFloatValues(vec.x(), x);
		checkFloatValues(vec.y(), y);
		checkFloatValues(vec.z(), z);
	}




	///////////
	// Vec3i //
	///////////

	void checkVec3iValues(const slm::Vec3i& vec, const slm::Vec3i& otherVec) {
		for (std::size_t i = 0; i < 3; i++) {
			checkInt32_tValues(vec[i], otherVec[i]);
		}
	}

	void checkVec3iValues(const slm::Vec3i& vec, const std::array<int32_t, 3>& values) {
		for (std::size_t i = 0; i < 3; i++) {
			checkInt32_tValues(vec[i], values[i]);
		}
	}

	void checkVec3iValues(const slm::Vec3i& vec, const int32_t x, const int32_t y,
						  const int32_t z) {
		checkInt32_tValues(vec.x(), x);
		checkInt32_tValues(vec.y(), y);
		checkInt32_tValues(vec.z(), z);
	}




	////////////
	// Line2f //
	////////////

	void checkLine2fValues(const slm::Line2f& line, const slm::Vec2f& start,
						   const slm::Vec2f& end) {
		checkVec2fValues(line.getStart(), start);
		checkVec2fValues(line.getEnd(), end);
	}

	void checkLine2fValues(const slm::Line2f& line, const float x1, const float y1, const float x2, const float y2) {
		checkVec2fValues(line.getStart(), x1, y1);
		checkVec2fValues(line.getEnd(), x2, y2);
	}




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////
	
	void checkAxisAlignedBox2uValues(const slm::AxisAlignedBox2u& axisAlignedBox,
									 const slm::Vec2u& bottomLeft, const slm::Vec2u& topRight) {
		checkVec2uValues(axisAlignedBox.getBottomLeft(), bottomLeft);
	}
	void checkAxisAlignedBox2uValues(const slm::AxisAlignedBox2u& axisAlignedBox,
									 const uint32_t left, const uint32_t bottom,
									 const uint32_t right, const uint32_t top) {
		checkVec2uValues(axisAlignedBox.getBottomLeft(), left, bottom);
		checkVec2uValues(axisAlignedBox.getTopRight(), right, top);
	}
}