#pragma once

#include "Clipping.h"

namespace slm {

	template <class T>
	class LineT {
	public:
		LineT() = default;
		LineT(T start, T end) {
			m_start = std::move(start);
			m_end	= std::move(end);
		}

		void setStart(T start) {
			m_start = start;
		}
		void setEnd(T end) {
			m_end = end;
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
			return (m_end.y() - m_start.y()) / m_end.x() - m_start.x();
		}
		bool isHorizontal() const {
			return m_end.x() - m_start.x() == 0;
		}

		float getYAtX(float x) const {
			return getSlope() * (x - m_start.x()) + m_start.y();
		}
		float getXAtY(float y) const {
			return ((y - m_start.y()) / getSlope()) + m_start.x();
		}

		std::optional<T> intersectionPoint(LineT<T> other) const {
			const auto x1 = static_cast<float>(m_start.x());
			const auto y1 = static_cast<float>(m_start.y());
			const auto x2 = static_cast<float>(m_end.x());
			const auto y2 = static_cast<float>(m_end.y());
			const auto x3 = static_cast<float>(other.getStart().x());
			const auto y3 = static_cast<float>(other.getStart().y());
			const auto x4 = static_cast<float>(other.getEnd().x());
			const auto y4 = static_cast<float>(other.getEnd().y());

			const auto denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

			// Lines are parallel
			if (denominator == 0) {
				return std::nullopt;
			}

			const auto t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
			const auto u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / denominator;

			if (t < 0 || t > 1 || u < 0 || u > 1) {
				return std::nullopt;
			}

			const auto outX = static_cast<int>(x1 + t * (x2 - x1));
			const auto outY = static_cast<int>(y1 + t * (y2 - y1));

			return T{outX, outY};
		}

		template <class U>
		ClippingStatus clip(const U& viewport) {
			// Cohen-Sutherland Clipping Algorithm
			std::pair<uint8_t, uint8_t> pointLocInfo{};

			// Classify point Locations
			uint8_t locInfo[2] = {0b0000, 0b0000};
			for (int j = 0; j < 2; j++) {
				if (operator[](j).x() < viewport.getLeft()) {
					locInfo[j] = locInfo[j] | 0b0001;
				}
				else if (operator[](j).x() > viewport.getRight()) {
					locInfo[j] = locInfo[j] | 0b0010;
				}
				if (operator[](j).y() < viewport.getBottom()) {
					locInfo[j] = locInfo[j] | 0b0100;
				}
				else if (operator[](j).y() > viewport.getTop()) {
					locInfo[j] = locInfo[j] | 0b1000;
				}
			}
			pointLocInfo.first	= locInfo[0];
			pointLocInfo.second = locInfo[1];

			// Remove Outside Lines
			if ((pointLocInfo.first & pointLocInfo.second) != 0) {
				return ClippingStatus::Outside;
			}

			// Clip Remaining Lines
			if ((pointLocInfo.first & 0b0001) != 0) {
				const auto xPos = viewport.getLeft();
				const auto yPos = getYAtX(xPos);
				m_start.x(xPos);
				m_start.y(yPos);
				pointLocInfo.first = pointLocInfo.first & 0b1110;
			}
			else if ((pointLocInfo.first & 0b0010) != 0) {
				const auto xPos = viewport.getRight();
				const auto yPos = getYAtX(xPos);
				m_start.x(xPos);
				m_start.y(yPos);
				pointLocInfo.first = pointLocInfo.first & 0b1101;
			}
			if ((pointLocInfo.second & 0b0001) != 0) {
				const auto xPos = viewport.getLeft();
				const auto yPos = getYAtX(xPos);
				m_end.x(xPos);
				m_end.y(yPos);
				pointLocInfo.second = pointLocInfo.second & 0b1110;
			}
			else if ((pointLocInfo.second & 0b0010) != 0) {
				const auto xPos = viewport.getRight();
				const auto yPos = getYAtX(xPos);
				m_end.x(xPos);
				m_end.y(yPos);
				pointLocInfo.second = pointLocInfo.second & 0b1101;
			}
			if ((pointLocInfo.first & 0b1000) != 0) {
				const auto yPos = viewport.getTop();
				const auto xPos = getXAtY(yPos);
				m_start.x(xPos);
				m_start.y(yPos);
				pointLocInfo.first = pointLocInfo.first & 0b0111;
			}
			else if ((pointLocInfo.first & 0b0100) != 0) {
				const auto yPos = viewport.getBottom();
				const auto xPos = getXAtY(yPos);
				m_start.x(xPos);
				m_start.y(yPos);
				pointLocInfo.first = pointLocInfo.first & 0b1011;
			}
			if ((pointLocInfo.second & 0b1000) != 0) {
				const auto yPos = viewport.getTop();
				const auto xPos = getXAtY(yPos);
				m_end.x(xPos);
				m_end.y(yPos);
				pointLocInfo.second = pointLocInfo.second & 0b0111;
			}
			else if ((pointLocInfo.second & 0b0100) != 0) {
				const auto yPos = viewport.getBottom();
				const auto xPos = getXAtY(yPos);
				m_end.x(xPos);
				m_end.y(yPos);
				pointLocInfo.second = pointLocInfo.second & 0b1011;
			}

			locInfo[0] = 0b0000;
			locInfo[1] = 0b0000;
			for (int j = 0; j < 2; j++) {
				if (operator[](j).x() < viewport.getLeft()) {
					locInfo[j] = locInfo[j] | 0b0001;
				}
				else if (operator[](j).x() > viewport.getRight()) {
					locInfo[j] = locInfo[j] | 0b0010;
				}
				if (operator[](j).y() < viewport.getBottom()) {
					locInfo[j] = locInfo[j] | 0b0100;
				}
				else if (operator[](j).y() > viewport.getTop()) {
					locInfo[j] = locInfo[j] | 0b1000;
				}
			}
			pointLocInfo.first	= locInfo[0];
			pointLocInfo.second = locInfo[1];

			if ((pointLocInfo.first & pointLocInfo.second) != 0) {
				return ClippingStatus::Outside;
			}

			return ClippingStatus::Inside;
		}

		std::string toPostscript() const {
			std::string output{""};

			output = std::to_string(static_cast<int>(m_start.x())) + " " +
					 std::to_string(static_cast<int>(m_start.y())) + " moveto\n" +
					 std::to_string(static_cast<int>(m_end.x())) + " " +
					 std::to_string(static_cast<int>(m_end.y())) + " lineto\nstroke\n";

			return std::move(output);
		}

	private:
		T m_start{};
		T m_end{};
	};

}