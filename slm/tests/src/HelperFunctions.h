#pragma once

#include "slm.h"

namespace helpers {

	///////////
	// float //
	///////////

	const float FLOATING_POINT_ERROR_MARGIN = 0.0001f;
	void checkFloatValues(const float float1, const float float2);




	///////////
	// Vec2f //
	///////////

	void checkVec2fValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec);
	void checkVec2fValues(const slm::Vec2f& vec, const std::array<float, 2>& values);
	void checkVec2fValues(const slm::Vec2f& vec, const float x, const float y);




	////////////
	// Line2f //
	////////////

	void checkLine2fValues(const slm::Line2f& line, const slm::Vec2f& start, const slm::Vec2f& end);
	void checkLine2fValues(const slm::Line2f& line, float x1, float y1, float x2, float y2);
}