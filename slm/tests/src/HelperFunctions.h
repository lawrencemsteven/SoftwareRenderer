#pragma once

#include "slm.h"

namespace helpers {

	///////////
	// float //
	///////////

	const float FLOATING_POINT_ERROR_MARGIN = 0.0001f;
	void checkValues(const float float1, const float float2);




	/////////////
	// int32_t //
	/////////////

	void checkInt32_tValues(const int32_t int1, const int32_t int2);




	//////////////
	// uint32_t //
	//////////////

	void checkValues(const uint32_t uint1, const uint32_t uint2);




	///////////
	// Vec2f //
	///////////

	void checkValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec);
	void checkValues(const slm::Vec2f& vec, const std::array<float, 2>& values);
	void checkValues(const slm::Vec2f& vec, const float x, const float y);




	///////////
	// Vec2u //
	///////////

	void checkValues(const slm::Vec2u& vec, const slm::Vec2u& otherVec);
	void checkValues(const slm::Vec2u& vec, const std::array<uint32_t, 2>& values);
	void checkValues(const slm::Vec2u& vec, const uint32_t x, const uint32_t y);




	///////////
	// Vec3f //
	///////////

	void checkVec3fValues(const slm::Vec3f& vec, const slm::Vec3f& otherVec);
	void checkVec3fValues(const slm::Vec3f& vec, const std::array<float, 3>& values);
	void checkVec3fValues(const slm::Vec3f& vec, const float x, const float y, const float z);




	///////////
	// Vec3i //
	///////////

	void checkVec3iValues(const slm::Vec3i& vec, const slm::Vec3i& otherVec);
	void checkVec3iValues(const slm::Vec3i& vec, const std::array<int32_t, 3>& values);
	void checkVec3iValues(const slm::Vec3i& vec, const int32_t x, const int32_t y, const int32_t z);




	////////////
	// Line2f //
	////////////

	void checkValues(const slm::Line2f& line, const slm::Vec2f& start, const slm::Vec2f& end);
	void checkValues(const slm::Line2f& line, const float x1, const float y1, const float x2,
					 const float y2);




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	void checkValues(const slm::AxisAlignedBox2u& axisAlignedBox, const slm::Vec2u& bottomLeft,
					 const slm::Vec2u& topRight);
	void checkValues(const slm::AxisAlignedBox2u& axisAlignedBox, const uint32_t left,
					 const uint32_t bottom, const uint32_t right, const uint32_t top);
}