#pragma once

namespace slm {

	template <class T>
	class LineT {
	public:
		LineT() = default;
		LineT(T start, T end) {
			m_start = std::move(start);
			m_end	= std::move(end);
		}

		const T& getStart() const {
			return m_start;
		}
		const T& getEnd() const {
			return m_end;
		}

		template <class U>
		void translate(U amount) {
			m_start.translate(amount);
			m_end.translate(amount);
		}
		void rotate(int degreesCounterClockwise) {
			m_start.rotate(degreesCounterClockwise);
			m_end.rotate(degreesCounterClockwise);
		}
		void scale(float factor) {
			m_start.scale(factor);
			m_end.scale(factor);
		}

		const T& operator[](std::size_t idx) const {
			if (idx == 0) {
				return m_start;
			}
			return m_end;
		}
		T& operator[](std::size_t idx) {
			if (idx == 0) {
				return m_start;
			}
			return m_end;
		}

		float getSlope() const {
			return (m_end.y() - m_start.y()) / (m_end.x() - m_start.x());
		}

		float getYAtX(float x) const {
			return getSlope() * (x - m_start.x()) + m_start.y();
		}
		float getXAtY(float y) const {
			return ((y - m_start.y()) / getSlope()) + m_start.x();
		}

		std::string toPostscript() const {
			std::string output{""};

			output = std::to_string(static_cast<int>(m_start.x()))
					 + " " + std::to_string(static_cast<int>(m_start.y())) + " moveto\n"
					 + std::to_string(static_cast<int>(m_end.x())) + " "
					 + std::to_string(static_cast<int>(m_end.y())) + " lineto\nstroke\n";

			return std::move(output);
		}

	private:
		T m_start{};
		T m_end{};
	};

}