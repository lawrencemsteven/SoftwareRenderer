#pragma once

namespace slm {

	template<class T, std::size_t N>
	class Viewport {
	public:
		static enum class Corner {
			BOTTOM_LEFT = 0,
			BOTTOM_RIGHT = 1,
			TOP_RIGHT = 2,
			TOP_LEFT = 3,
		};

		Viewport() = default;
		Viewport(VecT<T, N> bottomLeft, VecT<T, N> bottomRight, VecT<T, N> topRight,
			VecT<T, N> topLeft) {
			m_corners[0] = std::move(bottomLeft);
			m_corners[1] = std::move(bottomRight);
			m_corners[2] = std::move(topRight);
			m_corners[3] = std::move(topLeft);
		}

		const VecT<T, N>& getCorner(Corner corner) const {
			return m_corners[corner];
		}

		const VecT<T, N>& operator[](std::size_t idx) const {
			return m_corners[idx];
		}

	private:
		VecT<T, N> m_corners[4]{};
	};

}