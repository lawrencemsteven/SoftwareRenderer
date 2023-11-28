#pragma once

#include "Vec.h"

namespace slm {

	///////////
	// Mat4f //
	///////////

	class Mat4f {
	public:
		Mat4f();


	protected:
		std::array<Vec4f, 4> rows{};
	};

}