#pragma once

#include "slm.h"

namespace helpers {

	void checkVec2fValues(const slm::Vec2f& vec, const slm::Vec2f& otherVec);
	void checkVec2fValues(const slm::Vec2f& vec, const std::array<float, 2>& values);

}