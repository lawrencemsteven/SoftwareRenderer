#pragma once

#include "slm.h"

namespace helpers {

	///////////
	// float //
	///////////

	const float FLOATING_POINT_ERROR_MARGIN = 0.0001f;
	void checkFloatValues(const float float1, const float float2);




	//////////////
	// uint32_t //
	//////////////
	
	void checkUint32_tValues(const uint32_t uint1, const uint32_t uint2);




	///////////
	// Vec2f //
	///////////

	void checkVec2fValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec);
	void checkVec2fValues(const slm::Vec2f& vec, const std::array<float, 2>& values);
	void checkVec2fValues(const slm::Vec2f& vec, const float x, const float y);




	///////////
	// Vec2u //
	///////////

	void checkVec2uValues(const slm::Vec2u& vec, const slm::Vec2u& otherVec);
	void checkVec2uValues(const slm::Vec2u& vec, const std::array<uint32_t, 2>& values);
	void checkVec2uValues(const slm::Vec2u& vec, const uint32_t x, const uint32_t y);




	////////////
	// Line2f //
	////////////

	void checkLine2fValues(const slm::Line2f& line, const slm::Vec2f& start, const slm::Vec2f& end);
	void checkLine2fValues(const slm::Line2f& line, const float x1, const float y1, const float x2, const float y2);




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	void checkAxisAlignedBox2uValues(const slm::AxisAlignedBox2u& axisAlignedBox,
									 const slm::Vec2u& bottomLeft, const slm::Vec2u& topRight);
	void checkAxisAlignedBox2uValues(const slm::AxisAlignedBox2u& axisAlignedBox,
									 const uint32_t left, const uint32_t bottom,
									 const uint32_t right, const uint32_t top);
}