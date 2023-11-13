#include "Primitive.h"

namespace slm {

	////////////
	// Line2f //
	////////////

	Line2f::Line2f()
		: m_points{Vec2f{}, Vec2f{}} {}

	Line2f::Line2f(Vec2f start, Vec2f end)
		: m_points{std::move(start), std::move(end)} {}

	Line2f::Line2f(const float x1, const float y1, const float x2, const float y2)
		: m_points{Vec2f{x1, y1}, Vec2f{x2, y2}} {}

	void Line2f::setStart(Vec2f start) {
		m_points[0] = std::move(start);
	}

	void Line2f::setEnd(Vec2f end) {
		m_points[1] = std::move(end);
	}
		
	const Vec2f& Line2f::getStart() const {
		return m_points[0];
	}

	const Vec2f& Line2f::getEnd() const {
		return m_points[1];
	}

	void Line2f::translate(const Vec2& amount) {
		for (auto& point : m_points) {
			point.translate(amount);
		}
	}

	void Line2f::rotate(const int32_t degreesCounterClockwise) {
		for (auto& point : m_points) {
			point.rotate(degreesCounterClockwise);
		}
	}

	void Line2f::scale(const float factor) {
		for (auto& point : m_points) {
			point.scale(factor);
		}
	}

	void Line2f::scaleX(const float factor) {
		for (auto& point : m_points) {
			point.scaleX(factor);
		}
	}

	void Line2f::scaleY(const float factor) {
		for (auto& point : m_points) {
			point.scaleY(factor);
		}
	}

	void Line2f::clip() {
		std::cout << "Line2f::clip() STILL TO COMPLETE!!!\n";
	}

	const Vec2f& Line2f::operator[](const std::size_t idx) const {
		return m_points[idx];
	}

	bool Line2f::operator==(const Line2f& other) const {
		return m_points[0] == other[0] && m_points[1] == other[1];
	}

	bool Line2f::operator!=(const Line2f& other) const {
		return !(*this == other);
	}

}