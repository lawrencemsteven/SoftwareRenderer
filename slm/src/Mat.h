#pragma once

#include "Vec.h"

namespace slm {

	///////////
	// Mat4f //
	///////////

	class Mat4f {
	public:
		Mat4f();
		Mat4f(Vec4f row1, Vec4f row2, Vec4f row3, Vec4f row4);

		Vec4f& operator[](const std::size_t idx);

		Vec4f operator*(const Vec4f other);

	protected:
		std::array<Vec4f, 4> rows{};
	};

}