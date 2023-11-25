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

	float Line2f::getXMin() const {
		return std::min(m_points[0].x(), m_points[1].x());
	}

	float Line2f::getXMax() const {
		return std::max(m_points[0].x(), m_points[1].x());
	}

	float Line2f::getYMin() const {
		return std::min(m_points[0].y(), m_points[1].y());
	}

	float Line2f::getYMax() const {
		return std::max(m_points[0].y(), m_points[1].y());
	}

	std::optional<float> Line2f::getSlope() const {
		const auto xDifference = m_points[1].x() - m_points[0].x();
		if (xDifference == 0.0f) {
			return std::nullopt;
		}

		const auto yDifference = m_points[1].y() - m_points[0].y();
		return yDifference / xDifference;
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




	//////////////////////
	// AxisAlignedBox2u //
	//////////////////////

	AxisAlignedBox2u::AxisAlignedBox2u()
		: m_points{Vec2u{}, Vec2u{}} {}

	AxisAlignedBox2u::AxisAlignedBox2u(Vec2u bottomLeft, Vec2u topRight)
		: m_points{std::move(bottomLeft), std::move(topRight)} {
		checkDimensionSwap();
	}

	AxisAlignedBox2u::AxisAlignedBox2u(uint32_t left, uint32_t bottom, uint32_t right, uint32_t top)
		: m_points{Vec2u{left, bottom}, Vec2u{right, top}} {
		checkDimensionSwap();
	}

	void AxisAlignedBox2u::setBottomLeft(Vec2u bottomLeft) {
		m_points[0] = std::move(bottomLeft);
		checkAndMoveRight();
		checkAndMoveTop();
	}

	void AxisAlignedBox2u::setTopRight(Vec2u topRight) {
		m_points[1] = std::move(topRight);
		checkAndMoveLeft();
		checkAndMoveBottom();
	}

	void AxisAlignedBox2u::setBottom(const uint32_t bottom) {
		m_points[0].y(bottom);
		checkAndMoveTop();
	}

	void AxisAlignedBox2u::setLeft(const uint32_t left) {
		m_points[0].x(left);
		checkAndMoveRight();
	}

	void AxisAlignedBox2u::setTop(const uint32_t top) {
		m_points[1].y(top);
		checkAndMoveBottom();
	}

	void AxisAlignedBox2u::setRight(const uint32_t right) {
		m_points[1].x(right);
		checkAndMoveLeft();
	}

	const Vec2u& AxisAlignedBox2u::getBottomLeft() const {
		return m_points[0];
	}

	const Vec2u& AxisAlignedBox2u::getTopRight() const {
		return m_points[1];
	}

	uint32_t AxisAlignedBox2u::getBottom() const {
		return m_points[0].y();
	}

	uint32_t AxisAlignedBox2u::getLeft() const {
		return m_points[0].x();
	}

	uint32_t AxisAlignedBox2u::getTop() const {
		return m_points[1].y();
	}

	uint32_t AxisAlignedBox2u::getRight() const {
		return m_points[1].x();
	}

	void AxisAlignedBox2u::translate(const Vec2& amount) {
		for (auto& point : m_points) {
			point.translate(amount);
		}
	}

	void AxisAlignedBox2u::rotate(const int32_t degreesCounterClockwise) {
		for (auto& point : m_points) {
			point.rotate(degreesCounterClockwise);
		}
		checkDimensionSwap();
	}

	void AxisAlignedBox2u::scale(const float factor) {
		for (auto& point : m_points) {
			point.scale(factor);
		}
		checkDimensionSwap();
	}

	void AxisAlignedBox2u::scaleX(const float factor) {
		for (auto& point : m_points) {
			point.scaleX(factor);
		}
		checkDimensionSwap();
	}

	void AxisAlignedBox2u::scaleY(const float factor) {
		for (auto& point : m_points) {
			point.scaleY(factor);
		}
		checkDimensionSwap();
	}

	void AxisAlignedBox2u::clip() {
		std::cout << "AxisAlignedBox2u::clip() STILL TO COMPLETE!!!\n";
	}

	const Vec2u& AxisAlignedBox2u::operator[](const std::size_t idx) const {
		return m_points[idx];
	}

	bool AxisAlignedBox2u::operator==(const AxisAlignedBox2u& other) const {
		return m_points[0] == other[0] && m_points[1] == other[1];
	}

	bool AxisAlignedBox2u::operator!=(const AxisAlignedBox2u& other) const {
		return !(*this == other);
	}

	void AxisAlignedBox2u::checkDimensionSwap() {
		if (getLeft() > getRight()) {
			swapLeftAndRight();
		}
		if (getBottom() > getTop()) {
			swapBottomAndTop();
		}
	}

	void AxisAlignedBox2u::swapBottomAndTop() {
		const auto temp = m_points[0].x();
		m_points[0].x(m_points[1].x());
		m_points[1].x(temp);
	}

	void AxisAlignedBox2u::swapLeftAndRight() {
		const auto temp = m_points[0].y();
		m_points[0].y(m_points[1].y());
		m_points[1].y(temp);
	}

	void AxisAlignedBox2u::checkAndMoveLeft() {
		if (getRight() < getLeft()) {
			m_points[0].x(getRight());
		}
	}

	void AxisAlignedBox2u::checkAndMoveRight() {
		if (getLeft() > getRight()) {
			m_points[1].x(getLeft());
		}
	}

	void AxisAlignedBox2u::checkAndMoveBottom() {
		if (getTop() < getBottom()) {
			m_points[0].y(getTop());
		}
	}

	void AxisAlignedBox2u::checkAndMoveTop() {
		if (getBottom() > getTop()) {
			m_points[1].y(getBottom());
		}
	}




	//////////////
	// SMFModel //
	//////////////

	SMFModel::SMFModel() {}

	uint32_t SMFModel::getVertexCount() const {
		return m_vertices.size();
	}

	uint32_t SMFModel::getFaceCount() const {
		return m_faces.size();
	}

	const slm::Vec3f& SMFModel::getVertex(std::size_t idx) const {
		return m_vertices[idx];
	}

	const std::array<slm::Vec3f&, 3> SMFModel::getFaceVertices(std::size_t faceIdx) const {
		std::array<slm::Vec3f&, 3> faceVertices;
		const auto& face = m_faces[faceIdx];

		for (std::size_t i = 0; i < 3; i++) {
			std::size_t vertexIndex = face[i] - 1;
			faceVertices[i]			= getVertex(vertexIndex);
		}

		return faceVertices;
	}

	void SMFModel::addVertex(slm::Vec3f vertex) {
		m_vertices.push_back(std::move(vertex));
	}

	void SMFModel::addFace(slm::Vec3i face) {
		if (notEnoughVertices(face)) {
			std::cerr <<"Attempted to add face for insufficient vertices!";
		}

		m_faces.push_back(std::move(face));
	}

	bool SMFModel::notEnoughVertices(const slm::Vec3i& face) {
		return face[0] > getVertexCount() || face[1] > getVertexCount() ||
			   face[2] > getVertexCount();
	}

}