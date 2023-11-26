#pragma once

#include "Vec.h"

namespace slm {

	////////////////////
	// ClippingStatus //
	////////////////////

	enum class ClippingStatus {
		Inside,
		Modified,
		Outside
	};




	////////////////
	// Primitive2 //
	////////////////

	class Primitive2 {
	public:

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

		ClippingStatus clip(const AxisAlignedBox2u& clippingBox);

		float getXMin() const;
		float getXMax() const;
		float getYMin() const;
		float getYMax() const;
		std::optional<float> getSlope() const;
		std::optional<slm::Vec2f> getIntersectionPoint(const Line2f& other) const;

		const Vec2f& operator[](const std::size_t idx) const;
		bool operator==(const Line2f& other) const;
		bool operator!=(const Line2f& other) const;

	protected:
		std::array<Vec2f, 2> m_points{};
	};




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	class AxisAlignedBox2u : public Primitive2 {
	public:
		AxisAlignedBox2u();
		AxisAlignedBox2u(Vec2u bottomLeft, Vec2u topRight);
		AxisAlignedBox2u(const uint32_t x1, const uint32_t y1, const uint32_t x2,
						 const uint32_t y2);

		void setBottomLeft(Vec2u bottomLeft);
		void setTopRight(Vec2u topRight);
		void setBottom(const uint32_t bottom);
		void setLeft(const uint32_t left);
		void setTop(const uint32_t top);
		void setRight(const uint32_t right);
		const Vec2u& getBottomLeft() const;
		const Vec2u& getTopRight() const;
		uint32_t getBottom() const;
		uint32_t getLeft() const;
		uint32_t getTop() const;
		uint32_t getRight() const;

		void translate(const Vec2& amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const float factor);
		void scaleX(const float factor);
		void scaleY(const float factor);

		const Vec2u& operator[](const std::size_t idx) const;
		bool operator==(const AxisAlignedBox2u& other) const;
		bool operator!=(const AxisAlignedBox2u& other) const;

	protected:
		std::array<Vec2u, 2> m_points{};

		void checkDimensionSwap();
		void swapBottomAndTop();
		void swapLeftAndRight();
		void checkAndMoveLeft();
		void checkAndMoveRight();
		void checkAndMoveBottom();
		void checkAndMoveTop();
	};




	///////////////
	// Polygon2D //
	///////////////

	class Polygon2f : public Primitive2 {
	public:
	protected:
	};




	//////////////
	// SMFModel //
	//////////////

	class SMFModel {
	public:
		SMFModel();

		std::size_t getVertexCount() const;
		std::size_t getFaceCount() const;

		const slm::Vec3f& getVertex(std::size_t idx) const;

		const std::array<const slm::Vec3f*, 3> getFaceVertices(std::size_t faceIdx) const;

		void addVertex(slm::Vec3f vertex);
		void addVertex(const float x, const float y, const float z);
		void addFace(slm::Vec3i face);
		void addFace(const int32_t vertex1, const int32_t vertex2, const int32_t vertex3);
	protected:
		std::vector<slm::Vec3f> m_vertices{};
		std::vector<slm::Vec3i> m_faces{};

		bool notEnoughVertices(const slm::Vec3i& face);
	};
}