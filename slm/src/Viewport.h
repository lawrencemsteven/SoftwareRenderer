#pragma once

namespace slm {

	template<class T, std::size_t N>
	class Viewport {
	public:
		enum class Corner {
			BOTTOM_LEFT = 0,
			TOP_RIGHT = 1,
		};

		enum class Side {
			LEFT = 0,
			RIGHT = 1,
			BOTTOM = 2,
			TOP = 3,
		};

		Viewport() = default;
		Viewport(VecT<T, N> bottomLeft, VecT<T, N> topRight) {
			m_corners[0] = std::move(bottomLeft);
			m_corners[1] = std::move(topRight);
		}

		T getLeft() const {
			return m_corners[0][0];
		}
		T getRight() const {
			return m_corners[1][0];
		}
		T getBottom() const {
			return m_corners[0][1];
		}
		T getTop() const {
			return m_corners[1][1];
		}

		T getWidth() const {
			return m_corners[1][0] - m_corners[0][0];
		}
		T getHeight() const {
			return m_corners[1][1] - m_corners[0][1];
		}

		T getSide(Side side) const {
			switch (side) {
				case Side::LEFT: return getLeft();
				case Side::RIGHT: return getRight();
				case Side::BOTTOM: return getBottom();
				case Side::TOP: return getTop();
			}
		}

		const VecT<T, N>& getCorner(Corner corner) const {
			return m_corners[corner];
		}

		const VecT<T, N>& operator[](std::size_t idx) const {
			return m_corners[idx];
		}

	private:
		VecT<T, N> m_corners[2]{};
	};

}