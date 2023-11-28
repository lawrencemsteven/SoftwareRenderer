#pragma once

#include "Mat.h"
#include "Vec.h"
#include "glm/glm.hpp"

namespace slm {

	////////////////////
	// ClippingStatus //
	////////////////////

	enum class ClippingStatus { Inside, Modified, Outside };




	////////////////
	// Primitive2 //
	////////////////

	class Primitive2 {
	public:
		virtual void translate(const Vec2& amount)				   = 0;
		virtual void rotate(const int32_t degreesCounterClockwise) = 0;
		virtual void scale(const float factor)					   = 0;
		virtual void scaleX(const float factor)					   = 0;
		virtual void scaleY(const float factor)					   = 0;

		virtual void printPostscript() const = 0;

		virtual ClippingStatus clip(const AxisAlignedBox2u& clippingBox) = 0;

		virtual const Vec2f& operator[](const std::size_t idx) const = 0;

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

		void translate(const Vec2& amount) override;
		void rotate(const int32_t degreesCounterClockwise) override;
		void scale(const float factor) override;
		void scaleX(const float factor) override;
		void scaleY(const float factor) override;

		ClippingStatus clip(const AxisAlignedBox2u& clippingBox) override;

		void printPostscript() const;

		float getXMin() const;
		float getXMax() const;
		float getYMin() const;
		float getYMax() const;
		std::optional<float> getSlope() const;
		std::optional<slm::Vec2f> getIntersectionPoint(const Line2f& other) const;
		std::optional<slm::Vec2f> getHorizontalIntersectionPoint(const float yVal) const;
		std::optional<slm::Vec2f> getVerticalIntersectionPoint(const float xVal) const;
		std::optional<float> getYAtX(const float horizontalValue) const;
		std::optional<float> getXAtY(const float verticalValue) const;

		const Vec2f& operator[](const std::size_t idx) const override;
		bool operator==(const Line2f& other) const;
		bool operator!=(const Line2f& other) const;

	protected:
		std::array<Vec2f, 2> m_points{};

		bool movePointVertically(const std::size_t pointIdx, const float yVal);
		bool movePointHorizontally(const std::size_t pointIdx, const float xVal);
	};




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	class AxisAlignedBox2u {
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
		uint32_t getWidth() const;
		uint32_t getHeight() const;

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
	// Polygon2f //
	///////////////

	class Polygon2f : public Primitive2 {
	public:
		Polygon2f();

		void addPoint(Vec2f point);
		void setPoint(std::size_t idx, slm::Vec2f point);
		const Vec2f& getPoint(std::size_t idx) const;

		std::size_t getSize() const;
		const std::vector<slm::Vec2f>& getPoints() const;

		void translate(const Vec2& amount) override;
		void rotate(const int32_t degreesCounterClockwise) override;
		void scale(const float factor) override;
		void scaleX(const float factor) override;
		void scaleY(const float factor) override;

		ClippingStatus clip(const AxisAlignedBox2u& clippingBox) override;

		void printPostscript() const;

		float getXMin() const;
		float getXMax() const;
		float getYMin() const;
		float getYMax() const;

		const Vec2f& operator[](const std::size_t idx) const override;
		bool operator==(const Polygon2f& other) const;
		bool operator!=(const Polygon2f& other) const;

	protected:
		std::vector<slm::Vec2f> m_points{};
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




	////////////////
	// ViewVolume //
	////////////////

	class ViewVolume {
	public:
		ViewVolume();

		const slm::Vec3f& getProjectionReferencePoint() const;
		const slm::Vec3f& getViewReferencePoint() const;
		const slm::Vec3f& getViewPlaneNormal() const;
		const slm::Vec3f& getViewUpVector() const;
		float getVRCUMin() const;
		float getVRCVMin() const;
		float getVRCUMax() const;
		float getVRCVMax() const;
		bool getParallelProjection() const;

		void setProjectionReferencePoint(slm::Vec3f projectionReferencePoint);
		void setViewReferencePoint(slm::Vec3f viewReferencePoint);
		void setViewPlaneNormal(slm::Vec3f viewPlaneNormal);
		void setViewUpVector(slm::Vec3f viewUpVector);
		void setVRCMinMaxUV(const float uMin, const float vMin, const float uMax, const float vMax);
		void setParallelProjection(const bool parallel);

	protected:
		slm::Vec3f m_projectionReferencePoint{0.0f, 0.0f, 1.0f};
		slm::Vec3f m_viewReferencePoint{0.0f, 0.0f, 0.0f};
		slm::Vec3f m_viewPlaneNormal{0.0f, 0.0f, -1.0f};
		slm::Vec3f m_viewUpVector{0.0f, 1.0f, 0.0f};
		float m_uMin{-0.7f};
		float m_vMin{-0.7f};
		float m_uMax{0.7f};
		float m_vMax{0.7f};
		bool m_parallelProjection{false};
	};




	///////////
	// Scene //
	///////////

	class Scene {
	public:
		Scene();

		void addPrimitive(std::unique_ptr<slm::Primitive2> primitive);
		const std::unique_ptr<slm::Primitive2>& getPrimitive(std::size_t idx) const;
		std::size_t getSize() const;

		void translate(const Vec2& amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const float factor);
		void scaleX(const float factor);
		void scaleY(const float factor);

		void clip(const AxisAlignedBox2u& clippingBox);

		void convertModel(const ViewVolume& viewVolume, const SMFModel& model,
						  const AxisAlignedBox2u& viewport);

		void printPostscript(const AxisAlignedBox2u& viewport);

	protected:
		std::vector<std::unique_ptr<slm::Primitive2>> m_primitives{};
	};
}