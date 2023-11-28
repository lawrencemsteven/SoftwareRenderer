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

	ClippingStatus Line2f::clip(const AxisAlignedBox2u& clippingBox) {
		std::array<slm::BitLocation, 2> pointBitLocations{m_points[0].insideBox(clippingBox),
														  m_points[1].insideBox(clippingBox)};

		// Both Inside
		if (pointBitLocations[0].getInside() && pointBitLocations[1].getInside()) {
			return ClippingStatus::Inside;
		}

		// Outside on same side (0b1010 & 0b1001 = 0b1000 => Fully above)
		if (pointBitLocations[0].getLocation() & pointBitLocations[1].getLocation()) {
			return ClippingStatus::Outside;
		}

		// Move points until inside or invalid
		for (std::size_t i = 0; i < pointBitLocations.size(); i++) {
			std::optional<slm::Vec2f> newPointOptional{};
			bool successfulMove = true;

			if (pointBitLocations[i].getAbove()) {
				successfulMove = movePointVertically(i, clippingBox.getTop());
			}
			else if (pointBitLocations[i].getBelow()) {
				successfulMove = movePointVertically(i, clippingBox.getBottom());
			}

			pointBitLocations[i] = m_points[i].insideBox(clippingBox);

			if (pointBitLocations[i].getLeft()) {
				successfulMove = successfulMove && movePointHorizontally(i, clippingBox.getLeft());
			}
			else if (pointBitLocations[i].getRight()) {
				successfulMove = successfulMove && movePointHorizontally(i, clippingBox.getRight());
			}

			if (!successfulMove) {
				return ClippingStatus::Outside;
			}
		}

		return ClippingStatus::Modified;
	}

	void Line2f::printPostscript() const {
		std::cout << static_cast<int32_t>(m_points[0].x()) << " "
				  << static_cast<int32_t>(m_points[0].y()) << " moveto\n"
				  << static_cast<int32_t>(m_points[1].x()) << " "
				  << static_cast<int32_t>(m_points[1].y()) << " lineto\nstroke\n";
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

	std::optional<slm::Vec2f> Line2f::getIntersectionPoint(const Line2f& other) const {
		const auto x1 = m_points[0][0];
		const auto x2 = m_points[1][0];
		const auto x3 = other[0][0];
		const auto x4 = other[1][0];
		const auto y1 = m_points[0][1];
		const auto y2 = m_points[1][1];
		const auto y3 = other[0][1];
		const auto y4 = other[1][1];

		const auto denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

		if (denominator == 0.0f) {
			return std::nullopt;
		}

		const auto t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
		const auto u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / denominator;

		if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
			const auto outX = x1 + t * (x2 - x1);
			const auto outY = y1 + t * (y2 - y1);

			return slm::Vec2f{outX, outY};
		}

		return std::nullopt;
	}

	std::optional<slm::Vec2f> Line2f::getHorizontalIntersectionPoint(const float yVal) const {
		const auto xValOptional = getXAtY(yVal);

		if (!xValOptional.has_value()) {
			return std::nullopt;
		}

		const auto xVal = xValOptional.value();

		return slm::Vec2f{xVal, yVal};
	}

	std::optional<slm::Vec2f> Line2f::getVerticalIntersectionPoint(const float xVal) const {
		const auto yValOptional = getYAtX(xVal);

		if (!yValOptional.has_value()) {
			return std::nullopt;
		}

		const auto yVal = yValOptional.value();

		return slm::Vec2f{xVal, yVal};
	}

	std::optional<float> Line2f::getYAtX(const float horizontalValue) const {
		const auto x1 = m_points[0][0];
		const auto x2 = m_points[1][0];
		const auto y1 = m_points[0][1];
		const auto y2 = m_points[1][1];
		const auto dy = y2 - y1;
		const auto dx = x2 - x1;

		// Outside of line segment
		if ((horizontalValue < x1 && horizontalValue < x2) ||
			(horizontalValue > x1 && horizontalValue > x2)) {
			return std::nullopt;
		}

		// Vertical Line
		if (dx == 0.0f) {
			return std::nullopt;
		}

		const auto outY = (dy / dx) * (horizontalValue - x1) + y1;

		// Outside of line segment
		if ((outY < y1 && outY < y2) || (outY > y1 && outY > y2)) {
			return std::nullopt;
		}

		return outY;
	}

	std::optional<float> Line2f::getXAtY(const float verticalValue) const {

		const auto x1 = m_points[0][0];
		const auto x2 = m_points[1][0];
		const auto y1 = m_points[0][1];
		const auto y2 = m_points[1][1];
		const auto dy = y2 - y1;
		const auto dx = x2 - x1;

		// Outside of line segment
		if ((verticalValue < y1 && verticalValue < y2) ||
			(verticalValue > y1 && verticalValue > y2)) {
			return std::nullopt;
		}

		// Horizontal Line
		if (dy == 0.0f) {
			return std::nullopt;
		}

		const auto outX = (dx / dy) * (verticalValue - y1) + x1;

		// Outside of line segment
		if ((outX < x1 && outX < x2) || (outX > x1 && outX > x2)) {
			return std::nullopt;
		}

		return outX;
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

	bool Line2f::movePointVertically(const std::size_t pointIdx, const float yVal) {
		const auto xValOptional = getXAtY(yVal);

		if (!xValOptional.has_value()) {
			return false;
		}

		const auto xVal = xValOptional.value();

		m_points[pointIdx].x(xVal);
		m_points[pointIdx].y(yVal);

		return true;
	}

	bool Line2f::movePointHorizontally(const std::size_t pointIdx, const float xVal) {
		const auto yValOptional = getYAtX(xVal);

		if (!yValOptional.has_value()) {
			return false;
		}

		const auto yVal = yValOptional.value();

		m_points[pointIdx].x(xVal);
		m_points[pointIdx].y(yVal);

		return true;
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

	uint32_t AxisAlignedBox2u::getWidth() const {
		return getRight() - getLeft();
	}

	uint32_t AxisAlignedBox2u::getHeight() const {
		return getTop() - getBottom();
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




	///////////////
	// Polygon2f //
	///////////////

	Polygon2f::Polygon2f() {}

	void Polygon2f::addPoint(Vec2f point) {
		m_points.push_back(std::move(point));
	}

	void Polygon2f::setPoint(std::size_t idx, slm::Vec2f point) {
		m_points[idx] = std::move(point);
	}

	const Vec2f& Polygon2f::getPoint(std::size_t idx) const {
		return m_points[idx];
	}

	std::size_t Polygon2f::getSize() const {
		return m_points.size();
	}

	const std::vector<slm::Vec2f>& Polygon2f::getPoints() const {
		return m_points;
	}

	void Polygon2f::translate(const Vec2& amount) {
		for (auto& point : m_points) {
			point.translate(amount);
		}
	}

	void Polygon2f::rotate(const int32_t degreesCounterClockwise) {
		for (auto& point : m_points) {
			point.rotate(degreesCounterClockwise);
		}
	}

	void Polygon2f::scale(const float factor) {
		for (auto& point : m_points) {
			point.scale(factor);
		}
	}

	void Polygon2f::scaleX(const float factor) {
		for (auto& point : m_points) {
			point.scaleX(factor);
		}
	}

	void Polygon2f::scaleY(const float factor) {
		for (auto& point : m_points) {
			point.scaleY(factor);
		}
	}

	ClippingStatus Polygon2f::clip(const AxisAlignedBox2u& clippingBox) {
		typedef slm::BitLocation::BIT_LOCATIONS BIT_LOCATIONS;

		bool completelyInside = true;
		std::vector<slm::Vec2f> outputPoints{m_points};
		const float borderValues[4]{static_cast<float>(clippingBox.getLeft()),
									static_cast<float>(clippingBox.getTop()),
									static_cast<float>(clippingBox.getRight()),
									static_cast<float>(clippingBox.getBottom())};
		const BitLocation borderBitValues[4]{
			BitLocation{BIT_LOCATIONS::LEFT}, BitLocation{BIT_LOCATIONS::ABOVE},
			BitLocation{BIT_LOCATIONS::RIGHT}, BitLocation{BIT_LOCATIONS::BELOW}};

		for (std::size_t i = 0; i < 4; i++) {
			std::vector<slm::Vec2f> inputPoints{outputPoints};
			outputPoints.clear();

			for (std::size_t j = 0; j < inputPoints.size(); j++) {
				const slm::Vec2f currentPoint		   = inputPoints[j];
				const slm::BitLocation currentPointLoc = currentPoint.insideBox(clippingBox);

				std::size_t prevPointIndex = j - 1;
				if (j == 0) {
					prevPointIndex = inputPoints.size() - 1;
				}
				const slm::Vec2f prevPoint			= inputPoints[prevPointIndex];
				const slm::BitLocation prevPointLoc = prevPoint.insideBox(clippingBox);

				const slm::Line2f line{prevPoint, currentPoint};

				const auto intersectionPointOptional =
					borderBitValues[i].getVertical()
						? line.getHorizontalIntersectionPoint(borderValues[i])
						: line.getVerticalIntersectionPoint(borderValues[i]);

				const bool currentPointInside =
					!currentPointLoc.compareLocations(borderBitValues[i]);
				const bool previousPointInside = !prevPointLoc.compareLocations(borderBitValues[i]);

				if (currentPointInside) {
					if (!previousPointInside) {
						outputPoints.push_back(intersectionPointOptional.value());
						completelyInside = false;
					}
					outputPoints.push_back(currentPoint);
				}
				else if (previousPointInside) {
					outputPoints.push_back(intersectionPointOptional.value());
					completelyInside = false;
				}
			}
		}

		if (outputPoints.size() == 0) {
			return ClippingStatus::Outside;
		}

		if (completelyInside) {
			return ClippingStatus::Inside;
		}

		m_points = outputPoints;
		return ClippingStatus::Modified;
	}

	void Polygon2f::printPostscript() const {
		std::cout << "Polygon2f::printPostscript() TO IMPLEMENT!\n";
	}

	float Polygon2f::getXMin() const {
		auto xMin = m_points[0].x();

		for (const auto& point : m_points) {
			if (point.x() < xMin) {
				xMin = point.x();
			}
		}

		return xMin;
	}

	float Polygon2f::getXMax() const {
		auto xMax = m_points[0].x();

		for (const auto& point : m_points) {
			if (point.x() > xMax) {
				xMax = point.x();
			}
		}

		return xMax;
	}

	float Polygon2f::getYMin() const {
		auto yMin = m_points[0].y();

		for (const auto& point : m_points) {
			if (point.y() < yMin) {
				yMin = point.y();
			}
		}

		return yMin;
	}

	float Polygon2f::getYMax() const {
		auto yMax = m_points[0].y();

		for (const auto& point : m_points) {
			if (point.y() > yMax) {
				yMax = point.y();
			}
		}

		return yMax;
	}

	const Vec2f& Polygon2f::operator[](const std::size_t idx) const {
		return getPoint(idx);
	}

	bool Polygon2f::operator==(const Polygon2f& other) const {
		// TODO: CHECK REVERSE DIRECTION OF POLYGON POINTS!!!

		if (getSize() != other.getSize()) {
			return false;
		}

		if (getSize() == 0) {
			return true;
		}

		const auto& startingPoint			= getPoint(0);
		bool pointFound						= false;
		std::size_t otherStartingPointIndex = 0;

		for (std::size_t i = 0; i < other.getSize(); i++) {
			if (startingPoint == other.getPoint(i)) {
				pointFound				= true;
				otherStartingPointIndex = i;
				break;
			}
		}

		if (!pointFound) {
			return false;
		}

		// Check Forward Direction
		bool allPointsMatch				 = true;
		auto otherStartingPointIndexCopy = otherStartingPointIndex;
		for (std::size_t i = 1; i < getSize(); i++) {
			otherStartingPointIndexCopy = (otherStartingPointIndexCopy + 1) % other.getSize();
			if (getPoint(i) != other.getPoint(otherStartingPointIndexCopy)) {
				allPointsMatch = false;
				break;
			}
		}

		if (allPointsMatch) {
			return true;
		}

		// Check Reverse Direction
		for (std::size_t i = 1; i < getSize(); i++) {
			if (otherStartingPointIndex == 0) {
				otherStartingPointIndex = other.getSize();
			}
			otherStartingPointIndex = otherStartingPointIndex - 1;
			if (getPoint(i) != other.getPoint(otherStartingPointIndex)) {
				return false;
			}
		}

		return true;
	}

	bool Polygon2f::operator!=(const Polygon2f& other) const {
		return !(*this == other);
	}




	//////////////
	// SMFModel //
	//////////////

	SMFModel::SMFModel() {}

	std::size_t SMFModel::getVertexCount() const {
		return m_vertices.size();
	}

	std::size_t SMFModel::getFaceCount() const {
		return m_faces.size();
	}

	const slm::Vec3f& SMFModel::getVertex(std::size_t idx) const {
		return m_vertices[idx];
	}

	const std::array<const slm::Vec3f*, 3> SMFModel::getFaceVertices(std::size_t faceIdx) const {
		std::array<const slm::Vec3f*, 3> faceVertices;
		const auto& face = m_faces[faceIdx];

		for (std::size_t i = 0; i < 3; i++) {
			std::size_t vertexIndex = face[i] - 1;
			faceVertices[i]			= &getVertex(vertexIndex);
		}

		return faceVertices;
	}

	void SMFModel::addVertex(slm::Vec3f vertex) {
		m_vertices.push_back(std::move(vertex));
	}

	void SMFModel::addVertex(const float x, const float y, const float z) {
		addVertex(slm::Vec3f{x, y, z});
	}

	void SMFModel::addFace(slm::Vec3i face) {
		if (notEnoughVertices(face)) {
			throw std::runtime_error("Attempted to add face for insufficient vertices!");
		}

		m_faces.push_back(std::move(face));
	}

	void SMFModel::addFace(const int32_t vertex1, const int32_t vertex2, const int32_t vertex3) {
		addFace(slm::Vec3i{vertex1, vertex2, vertex3});
	}

	bool SMFModel::notEnoughVertices(const slm::Vec3i& face) {
		return face[0] > getVertexCount() || face[1] > getVertexCount() ||
			   face[2] > getVertexCount();
	}




	////////////////
	// ViewVolume //
	////////////////

	ViewVolume::ViewVolume() {}

	const slm::Vec3f& ViewVolume::getProjectionReferencePoint() const {
		return m_projectionReferencePoint;
	}

	const slm::Vec3f& ViewVolume::getViewReferencePoint() const {
		return m_viewReferencePoint;
	}

	const slm::Vec3f& ViewVolume::getViewPlaneNormal() const {
		return m_viewPlaneNormal;
	}

	const slm::Vec3f& ViewVolume::getViewUpVector() const {
		return m_viewUpVector;
	}

	float ViewVolume::getVRCUMin() const {
		return m_uMin;
	}

	float ViewVolume::getVRCVMin() const {
		return m_vMin;
	}

	float ViewVolume::getVRCUMax() const {
		return m_uMax;
	}

	float ViewVolume::getVRCVMax() const {
		return m_vMax;
	}

	bool ViewVolume::getParallelProjection() const {
		return m_parallelProjection;
	}

	void ViewVolume::setProjectionReferencePoint(slm::Vec3f projectionReferencePoint) {
		m_projectionReferencePoint = std::move(projectionReferencePoint);
	}

	void ViewVolume::setViewReferencePoint(slm::Vec3f viewReferencePoint) {
		m_viewReferencePoint = std::move(viewReferencePoint);
	}

	void ViewVolume::setViewPlaneNormal(slm::Vec3f viewPlaneNormal) {
		m_viewPlaneNormal = std::move(viewPlaneNormal);
	}

	void ViewVolume::setViewUpVector(slm::Vec3f viewUpVector) {
		m_viewUpVector = std::move(viewUpVector);
	}

	void ViewVolume::setVRCMinMaxUV(const float uMin, const float vMin, const float uMax,
									const float vMax) {
		m_uMin = uMin;
		m_vMin = vMin;
		m_uMax = uMax;
		m_vMax = vMax;
	}

	void ViewVolume::setParallelProjection(const bool parallel) {
		m_parallelProjection = parallel;
	}




	///////////
	// Scene //
	///////////

	Scene::Scene() {}

	void Scene::addPrimitive(std::unique_ptr<slm::Primitive2> primitive) {
		m_primitives.push_back(std::move(primitive));
	}

	const std::unique_ptr<slm::Primitive2>& Scene::getPrimitive(std::size_t idx) const {
		return m_primitives[idx];
	}

	std::size_t Scene::getSize() const {
		return m_primitives.size();
	}

	void Scene::translate(const Vec2& amount) {
		for (auto& primtive : m_primitives) {
			primtive->translate(amount);
		}
	}

	void Scene::rotate(const int32_t degreesCounterClockwise) {
		for (auto& primtive : m_primitives) {
			primtive->rotate(degreesCounterClockwise);
		}
	}

	void Scene::scale(const float factor) {
		for (auto& primtive : m_primitives) {
			primtive->scale(factor);
		}
	}

	void Scene::scaleX(const float factor) {
		for (auto& primtive : m_primitives) {
			primtive->scaleX(factor);
		}
	}

	void Scene::scaleY(const float factor) {
		for (auto& primtive : m_primitives) {
			primtive->scaleY(factor);
		}
	}

	void Scene::clip(const AxisAlignedBox2u& clippingBox) {
		for (std::size_t i = 0; i < m_primitives.size(); i++) {
			const auto clippingStatus = m_primitives[i]->clip(clippingBox);

			if (clippingStatus == ClippingStatus::Outside) {
				m_primitives.erase(m_primitives.begin() + i);
				i--;
			}
		}
	}

	void Scene::convertModel(const ViewVolume& viewVolume, const SMFModel& model,
							 const AxisAlignedBox2u& viewport) {
		const float F = 0.6f;
		const float B = -0.6f;
		glm::mat4 projectionMatrix{};

		slm::Vec2f scaleValues{1.0f, 1.0f};
		slm::Vec2f translateValues{0.0f, 0.0f};

		const auto vrp	= viewVolume.getViewReferencePoint();
		const auto vpn	= viewVolume.getViewPlaneNormal();
		const auto vup	= viewVolume.getViewUpVector();
		const auto prp	= viewVolume.getProjectionReferencePoint();
		const auto uMax = viewVolume.getVRCUMax();
		const auto uMin = viewVolume.getVRCUMin();
		const auto vMax = viewVolume.getVRCVMax();
		const auto vMin = viewVolume.getVRCVMin();

		// Translate VRP to origin
		glm::mat4 translation{1.0f};
		translation[0][3] = -vrp.x();
		translation[1][3] = -vrp.y();
		translation[2][3] = -vrp.z();

		// Rotate
		glm::mat4 rotation{1.0f};
		const auto rz  = glm::normalize(glm::vec3{vpn.x(), vpn.y(), vpn.z()});
		const auto rx  = glm::normalize(glm::cross(glm::vec3{vup.x(), vup.y(), vup.z()}, rz));
		const auto ry  = glm::cross(rz, rx);
		rotation[0][0] = rx[0];
		rotation[0][1] = rx[1];
		rotation[0][2] = rx[2];
		rotation[1][0] = ry[0];
		rotation[1][1] = ry[1];
		rotation[1][2] = ry[2];
		rotation[2][0] = rz[0];
		rotation[2][1] = rz[1];
		rotation[2][2] = rz[2];

		// Parallel Projection
		if (viewVolume.getParallelProjection()) {
			// Shear
			glm::mat4 parallelShear{1.0f};
			parallelShear[0][2] = (0.5f * (uMax + uMin) - prp.x()) / prp.z();
			parallelShear[1][2] = (0.5f * (vMax + vMin) - prp.y()) / prp.z();

			// Parallel Translation
			glm::mat4 parallelTranslation{1.0f};
			parallelTranslation[0][3] = -0.5f * (uMax + uMin);
			parallelTranslation[1][3] = -0.5f * (vMax + vMin);
			parallelTranslation[2][3] = -F;

			// Parallel Scale
			glm::mat4 parallelScale{1.0f};
			parallelScale[0][0] = 2.0f / (uMax - uMin);
			parallelScale[1][1] = 2.0f / (vMax - vMin);
			parallelScale[2][2] = 1.0f / (F - B);

			projectionMatrix =
				parallelScale * parallelTranslation * parallelShear * rotation * translation;

			scaleValues.x(static_cast<float>(viewport.getWidth()) / 2.0f);
			scaleValues.y(static_cast<float>(viewport.getHeight()) / 2.0f);

			translateValues.x(static_cast<float>(viewport.getWidth()) / 2.0f);
			translateValues.y(static_cast<float>(viewport.getHeight()) / 2.0f);
		}
		// Perspective Projection
		else {
			// Translate
			glm::mat4 perspectiveTranslate{1.0f};
			perspectiveTranslate[0][3] = -prp.x();
			perspectiveTranslate[1][3] = -prp.y();
			perspectiveTranslate[2][3] = -prp.z();

			// Shear
			glm::mat4 perspectiveShear{1.0f};
			perspectiveShear[0][2] = (0.5f * (uMax + uMin) - prp.x()) / prp.z();
			perspectiveShear[1][2] = (0.5f * (vMax + vMin) - prp.y()) / prp.z();

			// Scale
			glm::mat4 perspectiveScale{1.0f};
			perspectiveScale[0][0] = (2.0f * prp.z()) / ((uMax - uMin) * (prp.z() - B));
			perspectiveScale[1][1] = (2.0f * prp.z()) / ((vMax - vMin) * (prp.z() - B));
			perspectiveScale[2][2] = 1.0f / (prp.z() - B);

			projectionMatrix =
				perspectiveScale * perspectiveShear * perspectiveTranslate * rotation * translation;

			const auto d	= prp.z() / (B - prp.z());

			scaleValues.x(static_cast<float>(viewport.getWidth()));
			scaleValues.y(static_cast<float>(viewport.getHeight()));

			translateValues.x(d * static_cast<float>(viewport.getWidth()) / 2.0f);
			translateValues.y(d * static_cast<float>(viewport.getHeight()) / 2.0f);
		}

		for (std::size_t i = 0; i < model.getFaceCount(); i++) {
			auto faceVertices = model.getFaceVertices(i);

			std::array<glm::vec4, 3> faceVerticesGLM{
				glm::vec4{(*(faceVertices[0]))[0], (*(faceVertices[0]))[1], (*(faceVertices[0]))[2],
						  1.0f},
				glm::vec4{(*(faceVertices[1]))[0], (*(faceVertices[1]))[1], (*(faceVertices[1]))[2],
						  1.0f},
				glm::vec4{(*(faceVertices[2]))[0], (*(faceVertices[2]))[1], (*(faceVertices[2]))[2],
						  1.0f}};

			faceVerticesGLM[0] = (projectionMatrix * faceVerticesGLM[0]);
			faceVerticesGLM[1] = (projectionMatrix * faceVerticesGLM[1]);
			faceVerticesGLM[2] = (projectionMatrix * faceVerticesGLM[2]);

			std::vector<slm::Vec2f> newFaceVertices{};
			newFaceVertices.resize(3);
			newFaceVertices[0] = slm::Vec2f{faceVerticesGLM[0][0], faceVerticesGLM[0][1]};
			newFaceVertices[1] = slm::Vec2f{faceVerticesGLM[1][0], faceVerticesGLM[1][1]};
			newFaceVertices[2] = slm::Vec2f{faceVerticesGLM[2][0], faceVerticesGLM[2][1]};

			newFaceVertices[0].scale(scaleValues);
			newFaceVertices[1].scale(scaleValues);
			newFaceVertices[2].scale(scaleValues);

			newFaceVertices[0].translate(translateValues);
			newFaceVertices[1].translate(translateValues);
			newFaceVertices[2].translate(translateValues);

			m_primitives.push_back(
				std::make_unique<slm::Line2f>(slm::Line2f{newFaceVertices[0], newFaceVertices[1]}));
			m_primitives.push_back(
				std::make_unique<slm::Line2f>(slm::Line2f{newFaceVertices[1], newFaceVertices[2]}));
			m_primitives.push_back(
				std::make_unique<slm::Line2f>(slm::Line2f{newFaceVertices[2], newFaceVertices[0]}));
		}
	}

	void Scene::printPostscript(const AxisAlignedBox2u& viewport) {
		translate(slm::Vec2f{-static_cast<float>(viewport.getLeft()),
							 -static_cast<float>(viewport.getBottom())});

		std::cout << "%!PS\n\n0.1 setlinewidth\n\n%%BeginSetup\n  << /PageSize ["
				  << viewport.getWidth() << " " << viewport.getHeight()
				  << "] >> setpagedevice\n%%EndSetup\n\n%%%BEGIN\n";
		for (const auto& primitive : m_primitives) {
			primitive->printPostscript();
		}
		std::cout << "0 setgray\n%%%END\n";

		translate(slm::Vec2f{static_cast<float>(viewport.getLeft()),
							 static_cast<float>(viewport.getBottom())});
	}
}