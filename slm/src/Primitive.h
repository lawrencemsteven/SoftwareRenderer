#pragma once

#include "Vec.h"

namespace slm {

	////////////////
	// Primitive2 //
	////////////////

	class Primitive2 {
	public:
		virtual void clip() = 0;
	protected:
	};




	////////////
	// Line2f //
	////////////

	class Line2f : public Primitive2 {
	public:
		Line2f();
		Line2f(Vec2f start, Vec2f end);
		Line2f(const float x1, const float y1, const float x2, const float y2);

		void setStart(Vec2f start);
		void setEnd(Vec2f end);
		const Vec2f& getStart() const;
		const Vec2f& getEnd() const;

		void translate(const Vec2& amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const float factor);
		void scaleX(const float factor);
		void scaleY(const float factor);

		void clip() override;

		float getXMin() const;
		float getXMax() const;
		float getYMin() const;
		float getYMax() const;
		std::optional<float> getSlope() const;

		const Vec2f& operator[](const std::size_t idx) const;
		bool operator==(const Line2f& other) const;
		bool operator!=(const Line2f& other) const;
	protected:
		std::array<Vec2f, 2> m_points{};
	};




	///////////
	// Box2D //
	///////////

	class Box2f : public Primitive2 {
	public:
	protected:
	};




	///////////////
	// Polygon2D //
	///////////////

	class Polygon2f : public Primitive2 {
	public:
	protected:
	};
}