#pragma once

#include "LineT.h"

namespace slm {

	template <class T>
	class PolygonT {
	public:
		PolygonT() = default;

		const std::size_t getNumPoints() const {
			return m_points.size();
		}

		void extend(T point) {
			m_points.push_back(std::move(point));
		}

		const T& operator[](std::size_t idx) const {
			return m_points[idx];
		}
		T& operator[](std::size_t idx) {
			return m_points[idx];
		}

		std::string toPostscript() const {
			std::string output{""};

			output = std::to_string(static_cast<int>(m_points[0].x())) + " " +
					 std::to_string(static_cast<int>(m_points[0].y())) + " moveto\n";
			for (std::size_t i = 1; i < m_points.size(); i++) {
				output += std::to_string(static_cast<int>(m_points[i].x())) + " " +
						  std::to_string(static_cast<int>(m_points[i].y())) + " lineto\n";
			}
			output += std::to_string(static_cast<int>(m_points[0].x())) + " " +
					  std::to_string(static_cast<int>(m_points[0].y())) + " lineto\nstroke\n";

			return std::move(output);
		}

		template <class U>
		void translate(U amount) {
			for (std::size_t i = 0; i < getNumPoints(); i++) {
				m_points[i].translate(amount);
			}
		}
		void rotate(int degreesCounterClockwise) {
			for (std::size_t i = 0; i < getNumPoints(); i++) {
				m_points[i].rotate(degreesCounterClockwise);
			}
		}
		void scale(float factor) {
			for (std::size_t i = 0; i < getNumPoints(); i++) {
				m_points[i].scale(factor);
			}
		}

		template <class U>
		ClippingStatus clip(const U& viewport) {
			T point = m_points[0];
			m_points.push_back(point);
			bool startingPointInside = true;

			if (getNumPoints() == 0) {
				return ClippingStatus::Outside;
			}

			// Right Clip Boundary
			auto previousPointStatus = ClippingStatus::Inside;
			auto previousPoint		 = m_points[0];
			std::size_t i			 = 1;
			if (m_points[0].x() > viewport.getRight()) {
				previousPointStatus = ClippingStatus::Outside;
				startingPointInside = false;
				previousPoint		= m_points[0];
				m_points.erase(m_points.begin());
				i = 0;
			}
			for (i = i > 1 ? 1 : 0; i < getNumPoints(); i++) {
				auto currentPointStatus = m_points[i].x() > viewport.getRight()
											  ? ClippingStatus::Outside
											  : ClippingStatus::Inside;
				if (previousPointStatus == ClippingStatus::Outside &&
					currentPointStatus == ClippingStatus::Outside) {
					previousPoint = m_points[i];
					m_points.erase(std::next(m_points.begin(), i));
					i -= 1;
				}
				else if (previousPointStatus == ClippingStatus::Outside &&
						 currentPointStatus == ClippingStatus::Inside) {
					const LineT<T> tempLine{previousPoint, m_points[i]};
					previousPoint	= m_points[i];
					const auto yVal = tempLine.getYAtX(viewport.getRight());
					m_points.insert(std::next(m_points.begin(), i),
									T{static_cast<float>(viewport.getRight()), yVal});
				}
				else if (previousPointStatus == ClippingStatus::Inside &&
						 currentPointStatus == ClippingStatus::Outside) {
					const LineT<T> tempLine{m_points[i - 1], m_points[i]};
					previousPoint	= m_points[i];
					const auto yVal = tempLine.getYAtX(viewport.getRight());
					m_points[i]		= T{static_cast<float>(viewport.getRight()), yVal};
				}

				previousPointStatus = currentPointStatus;
			}

			if (getNumPoints() == 0) {
				return ClippingStatus::Outside;
			}
			if (!startingPointInside) {
				m_points.insert(m_points.begin(), m_points[m_points.size()-1]);
				startingPointInside = true;
			}

			// Left Clip Boundary
			previousPointStatus = ClippingStatus::Inside;
			if (m_points[0].x() < viewport.getLeft()) {
				previousPointStatus = ClippingStatus::Outside;
				previousPoint		= m_points[0];
				i					= 0;
				startingPointInside = false;
				m_points.erase(m_points.begin());
			}
			for (i = i > 1 ? 1 : 0; i < getNumPoints(); i++) {
				auto currentPointStatus = m_points[i].x() < viewport.getLeft()
											  ? ClippingStatus::Outside
											  : ClippingStatus::Inside;
				if (previousPointStatus == ClippingStatus::Outside &&
					currentPointStatus == ClippingStatus::Outside) {
					previousPoint = m_points[i];
					m_points.erase(std::next(m_points.begin(), i));
					i -= 1;
				}
				else if (previousPointStatus == ClippingStatus::Outside &&
						 currentPointStatus == ClippingStatus::Inside) {
					const LineT<T> tempLine{previousPoint, m_points[i]};
					previousPoint	= m_points[i];
					const auto yVal = tempLine.getYAtX(viewport.getLeft());
					m_points.insert(std::next(m_points.begin(), i),
									T{static_cast<float>(viewport.getLeft()), yVal});
				}
				else if (previousPointStatus == ClippingStatus::Inside &&
						 currentPointStatus == ClippingStatus::Outside) {
					const LineT<T> tempLine{m_points[i - 1], m_points[i]};
					previousPoint	= m_points[i];
					const auto yVal = tempLine.getYAtX(viewport.getLeft());
					m_points[i]		= T{static_cast<float>(viewport.getLeft()), yVal};
				}

				previousPointStatus = currentPointStatus;
			}

			if (getNumPoints() == 0) {
				return ClippingStatus::Outside;
			}
			if (!startingPointInside) {
				m_points.insert(m_points.begin(), m_points[m_points.size() - 1]);
				startingPointInside = true;
			}

			// Top Clip Boundary
			previousPointStatus = ClippingStatus::Inside;
			if (m_points[0].y() > viewport.getTop()) {
				previousPointStatus = ClippingStatus::Outside;
				previousPoint		= m_points[0];
				i					= 0;
				startingPointInside = false;
				m_points.erase(m_points.begin());
			}
			for (i = i > 1 ? 1 : 0; i < getNumPoints(); i++) {
				auto currentPointStatus = m_points[i].y() > viewport.getTop()
											  ? ClippingStatus::Outside
											  : ClippingStatus::Inside;
				if (previousPointStatus == ClippingStatus::Outside &&
					currentPointStatus == ClippingStatus::Outside) {
					previousPoint = m_points[i];
					m_points.erase(std::next(m_points.begin(), i));
					i -= 1;
				}
				else if (previousPointStatus == ClippingStatus::Outside &&
						 currentPointStatus == ClippingStatus::Inside) {
					const LineT<T> tempLine{previousPoint, m_points[i]};
					previousPoint	= m_points[i];
					const auto xVal = tempLine.getXAtY(viewport.getTop());
					m_points.insert(std::next(m_points.begin(), i),
									T{xVal, static_cast<float>(viewport.getTop())});
				}
				else if (previousPointStatus == ClippingStatus::Inside &&
						 currentPointStatus == ClippingStatus::Outside) {
					const LineT<T> tempLine{m_points[i - 1], m_points[i]};
					previousPoint	= m_points[i];
					const auto xVal = tempLine.getXAtY(viewport.getTop());
					m_points[i]		= T{xVal, static_cast<float>(viewport.getTop())};
				}

				previousPointStatus = currentPointStatus;
			}

			if (getNumPoints() == 0) {
				return ClippingStatus::Outside;
			}
			if (!startingPointInside) {
				m_points.insert(m_points.begin(), m_points[m_points.size() - 1]);
				startingPointInside = true;
			}

			// Bottom Clip Boundary
			previousPointStatus = ClippingStatus::Inside;
			if (m_points[0].y() < viewport.getBottom()) {
				previousPointStatus = ClippingStatus::Outside;
				previousPoint		= m_points[0];
				i					= 0;
				startingPointInside = false;
				m_points.erase(m_points.begin());
			}
			for (i = i > 1 ? 1 : 0; i < getNumPoints(); i++) {
				auto currentPointStatus = m_points[i].y() < viewport.getBottom()
											  ? ClippingStatus::Outside
											  : ClippingStatus::Inside;
				if (previousPointStatus == ClippingStatus::Outside &&
					currentPointStatus == ClippingStatus::Outside) {
					previousPoint = m_points[i];
					m_points.erase(std::next(m_points.begin(), i));
					i -= 1;
				}
				else if (previousPointStatus == ClippingStatus::Outside &&
						 currentPointStatus == ClippingStatus::Inside) {
					const LineT<T> tempLine{previousPoint, m_points[i]};
					previousPoint	= m_points[i];
					const auto xVal = tempLine.getXAtY(viewport.getBottom());
					m_points.insert(std::next(m_points.begin(), i),
									T{xVal, static_cast<float>(viewport.getBottom())});
				}
				else if (previousPointStatus == ClippingStatus::Inside &&
						 currentPointStatus == ClippingStatus::Outside) {
					const LineT<T> tempLine{m_points[i - 1], m_points[i]};
					previousPoint	= m_points[i];
					const auto xVal = tempLine.getXAtY(viewport.getBottom());
					m_points[i]		= T{xVal, static_cast<float>(viewport.getBottom())};
				}

				previousPointStatus = currentPointStatus;
			}

			if (getNumPoints() == 0) {
				return ClippingStatus::Outside;
			}
			if (!startingPointInside) {
				m_points.insert(m_points.begin(), m_points[m_points.size() - 1]);
				startingPointInside = true;
			}

			if (startingPointInside) {
				m_points.pop_back();
			}

			return ClippingStatus::Inside;
		}

	private:
		std::vector<T> m_points{};
	};

	template <class T>
	class PolygonTFactory {
	public:
		void startNewPolygon() {
			m_points.clear();
		}

		PolygonT<T> exportPolygon() {
			PolygonT<T> polygon;

			for (auto point : m_points) {
				polygon.extend(point);
			}

			return polygon;
		}

		void addPoint(T point) {
			m_points.push_back(std::move(point));
		}

	private:
		std::vector<T> m_points;
	};

}