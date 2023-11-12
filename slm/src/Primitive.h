#pragma once

#include "Vec.h"

namespace slm {

	/////////////////
	// Primitive2D //
	/////////////////

	class Primitive2D {
	public:
		virtual void clip() = 0;
	protected:
	};




	////////////
	// Line2D //
	////////////

	class Line2D : public Primitive2D {
	public:
		Line2D();
		Line2D(Vec2f start, Vec2f end);
		Line2D(const float x1, const float y1, const float x2, const float y2);

		void setStart(Vec2f start);
		void setEnd(Vec2f end);
		const Vec2f& getStart() const;
		const Vec2f& getEnd() const;

		void translate(const Vec2& amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const float factor);
		void scaleX(const float factor);
		void scaleY(const float factor);

		const Vec2f& operator[](const std::size_t idx) const;
		bool operator==(const Line2D& other) const;
		bool operator!=(const Line2D& other) const;
	protected:
		std::array<Vec2f, 2> m_points{};
	};




	///////////
	// Box2D //
	///////////

	class Box2D : public Primitive2D {
	public:
	protected:
	};




	///////////////
	// Polygon2D //
	///////////////

	class Polygon2D : public Primitive2D {
	public:
	protected:
	};
}