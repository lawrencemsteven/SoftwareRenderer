#include "Primitive.h"

namespace slm {

	////////////
	// Line2D //
	////////////

	Line2D::Line2D()
		: m_points{Vec2f{}, Vec2f{}} {}

	Line2D::Line2D(Vec2f start, Vec2f end)
		: m_points{std::move(start), std::move(end)} {}

	Line2D::Line2D(const float x1, const float y1, const float x2, const float y2)
		: m_points{Vec2f{x1, y2}, Vec2f{x2, y2}} {}

	void Line2D::setStart(Vec2f start) {
		m_points[0] = std::move(start);
	}

	void Line2D::setEnd(Vec2f end) {
		m_points[1] = std::move(end);
	}
		
	const Vec2f& Line2D::getStart() const {
		return m_points[0];
	}

	const Vec2f& Line2D::getEnd() const {
		return m_points[1];
	}

	void Line2D::translate(const Vec2& amount) {
		for (auto& point : m_points) {
			point.translate(amount);
		}
	}

	void Line2D::rotate(const int32_t degreesCounterClockwise) {
		for (auto& point : m_points) {
			point.rotate(degreesCounterClockwise);
		}
	}

	void Line2D::scale(const float factor) {
		for (auto& point : m_points) {
			point.scale(factor);
		}
	}

	void Line2D::scaleX(const float factor) {
		for (auto& point : m_points) {
			point.scaleX(factor);
		}
	}

	void Line2D::scaleY(const float factor) {
		for (auto& point : m_points) {
			point.scaleY(factor);
		}
	}

	const Vec2f& Line2D::operator[](const std::size_t idx) const {
		return m_points[idx];
	}

	bool Line2D::operator==(const Line2D& other) const {
		return m_points[0] == other[0] && m_points[1] == other[1];
	}

	bool Line2D::operator!=(const Line2D& other) const {
		return !(*this == other);
	}

}