#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "HelperFunctions.h"




////////////
// Line2f //
////////////

TEST_CASE("Line2f") {
	SECTION("Line2f()") {
		slm::Line2f test{};

		helpers::checkLine2fValues(test, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	SECTION("Line2f(Vec2f start, Vec2f end)") {
		slm::Vec2f start{1.0f, 2.0f};
		slm::Vec2f end{3.0f, 4.0f};
		slm::Line2f test{start, end};

		helpers::checkLine2fValues(test, start, end);
	}
	SECTION("Line2f(const float x1, const float y1, const float x2, const float y2)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		helpers::checkLine2fValues(test, 1.0f, 2.0f, 3.0f, 4.0f);
	}
	SECTION("void setStart(Vec2f start)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.setStart(slm::Vec2f{5.0f, 6.0f});

		helpers::checkLine2fValues(test, 5.0f, 6.0f, 3.0f, 4.0f);
	}
	SECTION("void setEnd(Vec2f end)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.setEnd(slm::Vec2f{5.0f, 6.0f});

		helpers::checkLine2fValues(test, 1.0f, 2.0f, 5.0f, 6.0f);
	}
	SECTION("const Vec2f& getStart()") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		const auto start = test.getStart();

		helpers::checkVec2fValues(start, 1.0f, 2.0f);
	}
	SECTION("const Vec2f& getEnd()") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		const auto end = test.getEnd();

		helpers::checkVec2fValues(end, 3.0f, 4.0f);
	}
	SECTION("void translate(const Vec2& amount)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.translate(slm::Vec2f{5.0f, 6.0f});

		helpers::checkLine2fValues(test, 6.0f, 8.0f, 8.0f, 10.0f);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::Line2f test{0.0f, 0.0f, 1.0f, 0.0f};

		test.rotate(90);

		helpers::checkLine2fValues(test, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	SECTION("void scale(const float factor)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scale(2);

		helpers::checkLine2fValues(test, 2.0f, 4.0f, 6.0f, 8.0f);
	}
	SECTION("void scaleX(const float factor)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scaleX(2);

		helpers::checkLine2fValues(test, 2.0f, 2.0f, 6.0f, 4.0f);
	}
	SECTION("void scaleY(const float factor)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scaleY(2);

		helpers::checkLine2fValues(test, 1.0f, 4.0f, 3.0f, 8.0f);
	}
	SECTION("void clip()") {
		// TODO: CLIPPING
	}
	SECTION("float getXMin()") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkFloatValues(test.getXMin(), 1.0f);
		}
		{
			slm::Line2f test{30.0f, 20.0f, 10.0f, 40.0f};
			helpers::checkFloatValues(test.getXMin(), 10.0f);
		}
	}
	SECTION("float getXMax()") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkFloatValues(test.getXMax(), 3.0f);
		}
		{
			slm::Line2f test{30.0f, 20.0f, 10.0f, 40.0f};
			helpers::checkFloatValues(test.getXMax(), 30.0f);
		}
	}
	SECTION("float getYMin()") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkFloatValues(test.getYMin(), 2.0f);
		}
		{
			slm::Line2f test{10.0f, 40.0f, 30.0f, 20.0f};
			helpers::checkFloatValues(test.getYMin(), 20.0f);
		}
	}
	SECTION("float getYMax()") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkFloatValues(test.getYMax(), 4.0f);
		}
		{
			slm::Line2f test{10.0f, 40.0f, 30.0f, 20.0f};
			helpers::checkFloatValues(test.getYMax(), 40.0f);
		}
	}
	SECTION("std::optional<float> getSlope()") {
		SECTION("Horizontal Line") {
			const slm::Line2f test{0.0f, 0.0f, 10.0f, 0.0f};

			const auto slopeOptional = test.getSlope();

			REQUIRE(slopeOptional.has_value());
			helpers::checkFloatValues(slopeOptional.value(), 0.0f);
		}
		SECTION("Vertical Line") {
			const slm::Line2f test{0.0f, 0.0f, 0.0f, 10.0f};

			const auto slopeOptional = test.getSlope();

			REQUIRE(!slopeOptional.has_value());
		}
		SECTION("Same Points") {
			const slm::Line2f test{0.0f, 0.0f, 0.0f, 0.0f};

			const auto slopeOptional = test.getSlope();

			REQUIRE(!slopeOptional.has_value());
		}
		SECTION("Actual Slope") {
			{
				const slm::Line2f test{0.0f, 0.0f, 1.0f, 1.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkFloatValues(slopeOptional.value(), 1.0f);
			}
			{
				const slm::Line2f test{1.0f, 1.0f, 0.0f, 0.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkFloatValues(slopeOptional.value(), 1.0f);
			}
			{
				const slm::Line2f test{-1.0f, 1.0f, 0.0f, 0.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkFloatValues(slopeOptional.value(), -1.0f);
			}
			{
				const slm::Line2f test{0.0f, 0.0f, 1.0f, 2.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkFloatValues(slopeOptional.value(), 2.0f);
			}
			{
				const slm::Line2f test{0.0f, 0.0f, 2.0f, 1.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkFloatValues(slopeOptional.value(), 0.5f);
			}
		}
	}
	SECTION("const Vec2f& operator[](const std::size_t idx)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		helpers::checkVec2fValues(test[0], test.getStart());
		helpers::checkVec2fValues(test[1], test.getEnd());
	}
	SECTION("bool operator==(const Line2f& other)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
		slm::Line2f test1{1.0f, 2.0f, 3.0f, 4.0f};

		CHECK(test == test1);
	}
	SECTION("bool operator!=(const Line2f& other)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
		slm::Line2f test1{5.0f, 2.0f, 3.0f, 4.0f};
		slm::Line2f test2{1.0f, 5.0f, 3.0f, 4.0f};
		slm::Line2f test3{1.0f, 2.0f, 5.0f, 4.0f};
		slm::Line2f test4{1.0f, 2.0f, 3.0f, 5.0f};

		CHECK(test != test1);
		CHECK(test != test2);
		CHECK(test != test3);
		CHECK(test != test4);
	}
}




//////////////////////
// AxisAlignedBox2u //
//////////////////////

TEST_CASE("AxisAlignedBox2u") {
	SECTION("AxisAlignedBox2u()") {
		slm::AxisAlignedBox2u test{};

		helpers::checkAxisAlignedBox2uValues(test, 0u, 0u, 0u, 0u);
	}
	SECTION("AxisAlignedBox2u(Vec2u bottomLeft, Vec2u topRight)") {
		slm::AxisAlignedBox2u test{slm::Vec2u{1u, 2u}, slm::Vec2u{3u, 4u}};

		helpers::checkAxisAlignedBox2uValues(test, 1u, 2u, 3u, 4u);
	}
	SECTION("AxisAlignedBox2u(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		helpers::checkAxisAlignedBox2uValues(test, 1u, 2u, 3u, 4u);
	}
	SECTION("void setBottomLeft(Vec2u bottomLeft)") {
		slm::AxisAlignedBox2u test{1u, 2u, 5u, 6u};

		test.setBottomLeft(slm::Vec2u{3u, 4u});

		helpers::checkAxisAlignedBox2uValues(test, 3u, 4u, 5u, 6u);
	}
	SECTION("void setTopRight(Vec2u topRight)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setTopRight(slm::Vec2u{5u, 6u});

		helpers::checkAxisAlignedBox2uValues(test, 1u, 2u, 5u, 6u);
	}
	SECTION("void setBottom(const uint32_t bottom)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setBottom(0u);

		helpers::checkAxisAlignedBox2uValues(test, 1u, 0u, 3u, 4u);
	}
	SECTION("void setLeft(const uint32_t left)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setLeft(0u);

		helpers::checkAxisAlignedBox2uValues(test, 0u, 2u, 3u, 4u);
	}
	SECTION("void setTop(const uint32_t top)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setTop(5u);

		helpers::checkAxisAlignedBox2uValues(test, 1u, 2u, 3u, 5u);
	}
	SECTION("void setRight(const uint32_t right)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setRight(5u);

		helpers::checkAxisAlignedBox2uValues(test, 1u, 2u, 5u, 4u);
	}
	SECTION("const Vec2u& getBottomLeft() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto bottomLeft = test.getBottomLeft();

		helpers::checkVec2uValues(bottomLeft, 1u, 2u);
	}
	SECTION("const Vec2u& getTopRight() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto topRight = test.getTopRight();

		helpers::checkVec2uValues(topRight, 3u, 4u);
	}
	SECTION("uint32_t getBottom() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto bottom = test.getBottom();

		helpers::checkUint32_tValues(bottom, 2u);
	}
	SECTION("uint32_t getLeft() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto left = test.getLeft();

		helpers::checkUint32_tValues(left, 1u);
	}
	SECTION("uint32_t getTop() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto top = test.getTop();

		helpers::checkUint32_tValues(top, 4u);
	}
	SECTION("uint32_t getRight() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto right = test.getRight();

		helpers::checkUint32_tValues(right, 3u);
	}
	SECTION("void translate(const Vec2& amount)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.translate(slm::Vec2u{5u, 6u});

		helpers::checkAxisAlignedBox2uValues(test, 6u, 8u, 8u, 10u);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::AxisAlignedBox2u test{1u, 0u, 2u, 0u};

		test.rotate(90);

		helpers::checkAxisAlignedBox2uValues(test, 0u, 1u, 0u, 2u);
	}
	SECTION("void scale(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scale(3.0f);

		helpers::checkAxisAlignedBox2uValues(test, 3u, 6u, 9u, 12u);
	}
	SECTION("void scaleX(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scaleX(4.0f);

		helpers::checkAxisAlignedBox2uValues(test, 4u, 2u, 12u, 4u);
	}
	SECTION("void scaleY(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scaleY(4.0f);

		helpers::checkAxisAlignedBox2uValues(test, 1u, 8u, 3u, 16u);
	}
	SECTION("void clip() override") {
		// TODO: Clipping
	}
	SECTION("const Vec2u& operator[](const std::size_t idx) const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		helpers::checkVec2uValues(test[0], 1u, 2u);
	}
	SECTION("bool operator==(const AxisAlignedBox2u& other) const") {
		slm::AxisAlignedBox2u test1{1u, 2u, 3u, 4u};
		slm::AxisAlignedBox2u test2{1u, 2u, 3u, 4u};

		CHECK(test1 == test2);

		test2.setBottom(0u);

		CHECK(!(test1 == test2));

		test1.setBottom(0u);

		CHECK(test1 == test2);
	}
	SECTION("bool operator!=(const AxisAlignedBox2u& other) const") {
		slm::AxisAlignedBox2u test1{1u, 2u, 3u, 4u};
		slm::AxisAlignedBox2u test2{1u, 2u, 3u, 4u};

		CHECK(!(test1 != test2));

		test2.setBottom(0u);

		CHECK(test1 != test2);

		test1.setBottom(0u);

		CHECK(!(test1 != test2));
	}
}




//////////////
// SMFModel //
//////////////

TEST_CASE("SMFModel") {
	SECTION("SMFModel()") {}
	SECTION("uint32_t getVertexCount() const") {}
	SECTION("uint32_t getFaceCount() const") {}
	SECTION("const slm::Vec3f& getVertex(std::size_t idx) const") {}
	SECTION("const std::array<slm::Vec3f&, 3> getFaceVertices(std::size_t faceIdx) const") {}
	SECTION("void addVertex(slm::Vec3f vertex)") {}
	SECTION("void addFace(slm::Vec3i face)") {}
}