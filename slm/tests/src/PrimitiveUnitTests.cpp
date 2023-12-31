#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "HelperFunctions.h"




////////////
// Line2f //
////////////

TEST_CASE("Line2f") {
	SECTION("Line2f()") {
		slm::Line2f test{};

		helpers::checkValues(test, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	SECTION("Line2f(Vec2f start, Vec2f end)") {
		slm::Vec2f start{1.0f, 2.0f};
		slm::Vec2f end{3.0f, 4.0f};
		slm::Line2f test{start, end};

		helpers::checkValues(test, start, end);
	}
	SECTION("Line2f(const float x1, const float y1, const float x2, const float y2)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		helpers::checkValues(test, 1.0f, 2.0f, 3.0f, 4.0f);
	}
	SECTION("void setStart(Vec2f start)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.setStart(slm::Vec2f{5.0f, 6.0f});

		helpers::checkValues(test, 5.0f, 6.0f, 3.0f, 4.0f);
	}
	SECTION("void setEnd(Vec2f end)") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.setEnd(slm::Vec2f{5.0f, 6.0f});

		helpers::checkValues(test, 1.0f, 2.0f, 5.0f, 6.0f);
	}
	SECTION("const Vec2f& getStart() const") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		const auto start = test.getStart();

		helpers::checkValues(start, 1.0f, 2.0f);
	}
	SECTION("const Vec2f& getEnd() const") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		const auto end = test.getEnd();

		helpers::checkValues(end, 3.0f, 4.0f);
	}
	SECTION("void translate(const Vec2& amount) override") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.translate(slm::Vec2f{5.0f, 6.0f});

		helpers::checkValues(test, 6.0f, 8.0f, 8.0f, 10.0f);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise) override") {
		slm::Line2f test{0.0f, 0.0f, 1.0f, 0.0f};

		test.rotate(90);

		helpers::checkValues(test, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	SECTION("void scale(const float factor) override") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scale(2);

		helpers::checkValues(test, 2.0f, 4.0f, 6.0f, 8.0f);
	}
	SECTION("void scaleX(const float factor) override") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scaleX(2);

		helpers::checkValues(test, 2.0f, 2.0f, 6.0f, 4.0f);
	}
	SECTION("void scaleY(const float factor) override") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		test.scaleY(2);

		helpers::checkValues(test, 1.0f, 4.0f, 3.0f, 8.0f);
	}

	SECTION("ClippingStatus clip(const AxisAlignedBox2u& clippingBox) override") {
		const slm::AxisAlignedBox2u clippingBox{1u, 1u, 3u, 3u};

		SECTION("Inside Line") {
			slm::Line2f test{1.5f, 1.5f, 2.5f, 2.5f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Inside);
		}
		SECTION("Horizontal Line Above") {
			slm::Line2f test{0.0f, 4.0f, 4.0f, 4.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Outside);
		}
		SECTION("Horizontal Line Below") {
			slm::Line2f test{0.0f, 0.0f, 4.0f, 0.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Outside);
		}
		SECTION("Vertical Line Left") {
			slm::Line2f test{0.0f, 0.0f, 0.0f, 4.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Outside);
		}
		SECTION("Vertical Line Right") {
			slm::Line2f test{4.0f, 0.0f, 4.0f, 4.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Outside);
		}
		SECTION("Horizontal Line Intersection") {
			slm::Line2f test{0.0f, 2.0f, 4.0f, 2.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 1.0f, 2.0f);
			helpers::checkValues(test.getEnd(), 3.0f, 2.0f);
		}
		SECTION("Vertical Line Intersecting") {
			slm::Line2f test{2.0f, 0.0f, 2.0f, 4.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 2.0f, 1.0f);
			helpers::checkValues(test.getEnd(), 2.0f, 3.0f);
		}
		SECTION("Longest Diagonal Line 45 Degrees") {
			slm::Line2f test{0.0f, 0.0f, 4.0f, 4.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 1.0f, 1.0f);
			helpers::checkValues(test.getEnd(), 3.0f, 3.0f);
		}
		SECTION("Longest Diagonal Line -45 Degrees") {
			slm::Line2f test{0.0f, 4.0f, 4.0f, 0.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 1.0f, 3.0f);
			helpers::checkValues(test.getEnd(), 3.0f, 1.0f);
		}
		SECTION("Short Diagonal Line 45 Degrees") {
			slm::Line2f test{0.0f, 1.0f, 4.0f, 5.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 1.0f, 2.0f);
			helpers::checkValues(test.getEnd(), 2.0f, 3.0f);
		}
		SECTION("Short Diagonal Line -45 Degrees") {
			slm::Line2f test{0.0f, 5.0f, 4.0f, 1.0f};

			CHECK(test.clip(clippingBox) == slm::ClippingStatus::Modified);
			helpers::checkValues(test.getStart(), 2.0f, 3.0f);
			helpers::checkValues(test.getEnd(), 3.0f, 2.0f);
		}
	}
	SECTION("float getXMin() const") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkValues(test.getXMin(), 1.0f);
		}
		{
			slm::Line2f test{30.0f, 20.0f, 10.0f, 40.0f};
			helpers::checkValues(test.getXMin(), 10.0f);
		}
	}
	SECTION("float getXMax() const") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkValues(test.getXMax(), 3.0f);
		}
		{
			slm::Line2f test{30.0f, 20.0f, 10.0f, 40.0f};
			helpers::checkValues(test.getXMax(), 30.0f);
		}
	}
	SECTION("float getYMin() const") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkValues(test.getYMin(), 2.0f);
		}
		{
			slm::Line2f test{10.0f, 40.0f, 30.0f, 20.0f};
			helpers::checkValues(test.getYMin(), 20.0f);
		}
	}
	SECTION("float getYMax() const") {
		{
			slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
			helpers::checkValues(test.getYMax(), 4.0f);
		}
		{
			slm::Line2f test{10.0f, 40.0f, 30.0f, 20.0f};
			helpers::checkValues(test.getYMax(), 40.0f);
		}
	}
	SECTION("std::optional<float> getSlope() const") {
		SECTION("Horizontal Line") {
			const slm::Line2f test{0.0f, 0.0f, 10.0f, 0.0f};

			const auto slopeOptional = test.getSlope();

			REQUIRE(slopeOptional.has_value());
			helpers::checkValues(slopeOptional.value(), 0.0f);
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
				helpers::checkValues(slopeOptional.value(), 1.0f);
			}
			{
				const slm::Line2f test{1.0f, 1.0f, 0.0f, 0.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkValues(slopeOptional.value(), 1.0f);
			}
			{
				const slm::Line2f test{-1.0f, 1.0f, 0.0f, 0.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkValues(slopeOptional.value(), -1.0f);
			}
			{
				const slm::Line2f test{0.0f, 0.0f, 1.0f, 2.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkValues(slopeOptional.value(), 2.0f);
			}
			{
				const slm::Line2f test{0.0f, 0.0f, 2.0f, 1.0f};

				const auto slopeOptional = test.getSlope();

				REQUIRE(slopeOptional.has_value());
				helpers::checkValues(slopeOptional.value(), 0.5f);
			}
		}
	}
	SECTION("std::optional<slm::Vec2f> getIntersectionPoint(const Line2f& other) const") {
		SECTION("Horizontal & Vertical Lines") {
			slm::Line2f line1(0.0f, 1.0f, 2.0f, 1.0f);
			slm::Line2f line2(1.0f, 0.0f, 1.0f, 2.0f);

			auto intersectionPointOptional = line1.getIntersectionPoint(line2);
			REQUIRE(intersectionPointOptional.has_value());
			auto intersectionPoint = intersectionPointOptional.value();
			helpers::checkValues(intersectionPoint, 1.0f, 1.0f);

			intersectionPointOptional = line2.getIntersectionPoint(line1);
			REQUIRE(intersectionPointOptional.has_value());
			intersectionPoint = intersectionPointOptional.value();
			helpers::checkValues(intersectionPoint, 1.0f, 1.0f);
		}
		SECTION("45 Degree Lines") {
			slm::Line2f line1(0.0f, 0.0f, 2.0f, 2.0f);
			slm::Line2f line2(0.0f, 2.0f, 2.0f, 0.0f);

			auto intersectionPointOptional = line1.getIntersectionPoint(line2);
			REQUIRE(intersectionPointOptional.has_value());
			auto intersectionPoint = intersectionPointOptional.value();
			helpers::checkValues(intersectionPoint, 1.0f, 1.0f);

			intersectionPointOptional = line2.getIntersectionPoint(line1);
			REQUIRE(intersectionPointOptional.has_value());
			intersectionPoint = intersectionPointOptional.value();
			helpers::checkValues(intersectionPoint, 1.0f, 1.0f);
		}
	}
	SECTION("std::optional<slm::Vec2f> getHorizontalIntersectionPoint(const float yVal) "
			"const") {
		slm::Line2f test{0.0f, 1.0f, 2.0f, 3.0f};

		auto intersectionPointOptional = test.getHorizontalIntersectionPoint(2.0f);
		REQUIRE(intersectionPointOptional.has_value());
		helpers::checkValues(intersectionPointOptional.value(), 1.0f, 2.0f);

		intersectionPointOptional = test.getHorizontalIntersectionPoint(0.0f);
		CHECK(!intersectionPointOptional.has_value());

		intersectionPointOptional = test.getHorizontalIntersectionPoint(4.0f);
		CHECK(!intersectionPointOptional.has_value());
	}
	SECTION("std::optional<slm::Vec2f> getVerticalIntersectionPoint(const float xVal) const") {
		slm::Line2f test{0.0f, 1.0f, 2.0f, 3.0f};

		auto intersectionPointOptional = test.getVerticalIntersectionPoint(1.0f);
		REQUIRE(intersectionPointOptional.has_value());
		helpers::checkValues(intersectionPointOptional.value(), 1.0f, 2.0f);

		intersectionPointOptional = test.getVerticalIntersectionPoint(-1.0f);
		CHECK(!intersectionPointOptional.has_value());

		intersectionPointOptional = test.getVerticalIntersectionPoint(3.0f);
		CHECK(!intersectionPointOptional.has_value());
	}
	SECTION("std::optional<float> getYAtX(const float horizontalValue) const") {
		SECTION("Horizontal Line") {
			slm::Line2f line{0.0f, 0.0f, 2.0f, 0.0f};

			auto yValOptional = line.getYAtX(1.0f);
			REQUIRE(yValOptional.has_value());
			auto yVal = yValOptional.value();
			helpers::checkValues(yVal, 0.0f);

			yValOptional = line.getYAtX(-1.0f);
			REQUIRE(!yValOptional.has_value());

			yValOptional = line.getYAtX(4.0f);
			REQUIRE(!yValOptional.has_value());
		}
		SECTION("Vertical Line") {
			slm::Line2f line{0.0f, 0.0f, 0.0f, 2.0f};

			auto yValOptional = line.getYAtX(1.0f);
			REQUIRE(!yValOptional.has_value());

			yValOptional = line.getYAtX(-1.0f);
			REQUIRE(!yValOptional.has_value());

			yValOptional = line.getYAtX(4.0f);
			REQUIRE(!yValOptional.has_value());
		}
		SECTION("45 Degree Line") {
			slm::Line2f line{0.0f, 0.0f, 2.0f, 2.0f};

			auto yValOptional = line.getYAtX(1.0f);
			REQUIRE(yValOptional.has_value());
			auto yVal = yValOptional.value();
			helpers::checkValues(yVal, 1.0f);

			yValOptional = line.getYAtX(-1.0f);
			REQUIRE(!yValOptional.has_value());

			yValOptional = line.getYAtX(4.0f);
			REQUIRE(!yValOptional.has_value());
		}
		SECTION("-45 Degree Line") {
			slm::Line2f line{2.0f, 2.0f, 0.0f, 0.0f};

			auto yValOptional = line.getYAtX(1.0f);
			REQUIRE(yValOptional.has_value());
			auto yVal = yValOptional.value();
			helpers::checkValues(yVal, 1.0f);

			yValOptional = line.getYAtX(-1.0f);
			REQUIRE(!yValOptional.has_value());

			yValOptional = line.getYAtX(4.0f);
			REQUIRE(!yValOptional.has_value());
		}
	}
	SECTION("std::optional<float> getXAtY(const float verticalValue) const") {
		SECTION("Horizontal Line") {
			slm::Line2f line{0.0f, 0.0f, 2.0f, 0.0f};

			auto xValOptional = line.getXAtY(1.0f);
			REQUIRE(!xValOptional.has_value());

			xValOptional = line.getXAtY(-1.0f);
			REQUIRE(!xValOptional.has_value());

			xValOptional = line.getXAtY(4.0f);
			REQUIRE(!xValOptional.has_value());
		}
		SECTION("Vertical Line") {
			slm::Line2f line{0.0f, 0.0f, 0.0f, 2.0f};

			auto xValOptional = line.getXAtY(1.0f);
			REQUIRE(xValOptional.has_value());
			auto xVal = xValOptional.value();
			helpers::checkValues(xVal, 0.0f);

			xValOptional = line.getXAtY(-1.0f);
			REQUIRE(!xValOptional.has_value());

			xValOptional = line.getXAtY(4.0f);
			REQUIRE(!xValOptional.has_value());
		}
		SECTION("45 Degree Line") {
			slm::Line2f line{0.0f, 0.0f, 2.0f, 2.0f};

			auto xValOptional = line.getXAtY(1.0f);
			REQUIRE(xValOptional.has_value());
			auto xVal = xValOptional.value();
			helpers::checkValues(xVal, 1.0f);

			xValOptional = line.getXAtY(-1.0f);
			REQUIRE(!xValOptional.has_value());

			xValOptional = line.getXAtY(4.0f);
			REQUIRE(!xValOptional.has_value());
		}
		SECTION("-45 Degree Line") {
			slm::Line2f line{2.0f, 2.0f, 0.0f, 0.0f};

			auto xValOptional = line.getXAtY(1.0f);
			REQUIRE(xValOptional.has_value());
			auto xVal = xValOptional.value();
			helpers::checkValues(xVal, 1.0f);

			xValOptional = line.getXAtY(-1.0f);
			REQUIRE(!xValOptional.has_value());

			xValOptional = line.getXAtY(4.0f);
			REQUIRE(!xValOptional.has_value());
		}
	}
	SECTION("const Vec2f& operator[](const std::size_t idx) const override") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};

		helpers::checkValues(test[0], test.getStart());
		helpers::checkValues(test[1], test.getEnd());
	}
	SECTION("bool operator==(const Line2f& other) const") {
		slm::Line2f test{1.0f, 2.0f, 3.0f, 4.0f};
		slm::Line2f test1{1.0f, 2.0f, 3.0f, 4.0f};

		CHECK(test == test1);
	}
	SECTION("bool operator!=(const Line2f& other) const") {
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

		helpers::checkValues(test, 0u, 0u, 0u, 0u);
	}
	SECTION("AxisAlignedBox2u(Vec2u bottomLeft, Vec2u topRight)") {
		slm::AxisAlignedBox2u test{slm::Vec2u{1u, 2u}, slm::Vec2u{3u, 4u}};

		helpers::checkValues(test, 1u, 2u, 3u, 4u);
	}
	SECTION("AxisAlignedBox2u(const uint32_t x1, const uint32_t y1, const uint32_t x2, const "
			"uint32_t y2)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		helpers::checkValues(test, 1u, 2u, 3u, 4u);
	}
	SECTION("void setBottomLeft(Vec2u bottomLeft)") {
		slm::AxisAlignedBox2u test{1u, 2u, 5u, 6u};

		test.setBottomLeft(slm::Vec2u{3u, 4u});

		helpers::checkValues(test, 3u, 4u, 5u, 6u);
	}
	SECTION("void setTopRight(Vec2u topRight)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setTopRight(slm::Vec2u{5u, 6u});

		helpers::checkValues(test, 1u, 2u, 5u, 6u);
	}
	SECTION("void setBottom(const uint32_t bottom)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setBottom(0u);

		helpers::checkValues(test, 1u, 0u, 3u, 4u);
	}
	SECTION("void setLeft(const uint32_t left)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setLeft(0u);

		helpers::checkValues(test, 0u, 2u, 3u, 4u);
	}
	SECTION("void setTop(const uint32_t top)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setTop(5u);

		helpers::checkValues(test, 1u, 2u, 3u, 5u);
	}
	SECTION("void setRight(const uint32_t right)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.setRight(5u);

		helpers::checkValues(test, 1u, 2u, 5u, 4u);
	}
	SECTION("const Vec2u& getBottomLeft() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto bottomLeft = test.getBottomLeft();

		helpers::checkValues(bottomLeft, 1u, 2u);
	}
	SECTION("const Vec2u& getTopRight() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto topRight = test.getTopRight();

		helpers::checkValues(topRight, 3u, 4u);
	}
	SECTION("uint32_t getBottom() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto bottom = test.getBottom();

		helpers::checkValues(bottom, 2u);
	}
	SECTION("uint32_t getLeft() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto left = test.getLeft();

		helpers::checkValues(left, 1u);
	}
	SECTION("uint32_t getTop() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto top = test.getTop();

		helpers::checkValues(top, 4u);
	}
	SECTION("uint32_t getRight() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		const auto right = test.getRight();

		helpers::checkValues(right, 3u);
	}
	SECTION("uint32_t getWidth() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 5u};

		const auto width = test.getWidth();

		helpers::checkValues(width, 2u);
	}
	SECTION("uint32_t getHeight() const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 5u};

		const auto height = test.getHeight();

		helpers::checkValues(height, 3u);
	}
	SECTION("void translate(const Vec2& amount)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.translate(slm::Vec2u{5u, 6u});

		helpers::checkValues(test, 6u, 8u, 8u, 10u);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::AxisAlignedBox2u test{1u, 0u, 2u, 0u};

		test.rotate(90);

		helpers::checkValues(test, 0u, 1u, 0u, 2u);
	}
	SECTION("void scale(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scale(3.0f);

		helpers::checkValues(test, 3u, 6u, 9u, 12u);
	}
	SECTION("void scaleX(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scaleX(4.0f);

		helpers::checkValues(test, 4u, 2u, 12u, 4u);
	}
	SECTION("void scaleY(const float factor)") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		test.scaleY(4.0f);

		helpers::checkValues(test, 1u, 8u, 3u, 16u);
	}
	SECTION("const Vec2u& operator[](const std::size_t idx) const") {
		slm::AxisAlignedBox2u test{1u, 2u, 3u, 4u};

		helpers::checkValues(test[0], 1u, 2u);
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




///////////////
// Polygon2f //
///////////////

TEST_CASE("Polygon2f") {
	SECTION("Polygon2f()") {
		slm::Polygon2f test{};

		helpers::checkValues(test.getSize(), 0);
	}
	SECTION("void addPoint(Vec2f point)") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 1.0f});

		helpers::checkValues(test.getSize(), 1);
		helpers::checkValues(test.getPoint(0), 0.0f, 1.0f);

		test.addPoint({2.0f, 3.0f});

		helpers::checkValues(test.getSize(), 2);
		helpers::checkValues(test.getPoint(1), 2.0f, 3.0f);

		test.addPoint({4.0f, 5.0f});

		helpers::checkValues(test.getSize(), 3);
		helpers::checkValues(test.getPoint(2), 4.0f, 5.0f);
	}
	SECTION("void setPoint(std::size_t idx, slm::Vec2f point)") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 1.0f});
		test.addPoint({2.0f, 3.0f});
		test.addPoint({4.0f, 5.0f});

		helpers::checkValues(test.getSize(), 3);
		helpers::checkValues(test.getPoint(0), 0.0f, 1.0f);
		helpers::checkValues(test.getPoint(1), 2.0f, 3.0f);
		helpers::checkValues(test.getPoint(2), 4.0f, 5.0f);

		test.setPoint(1, {6.0f, 7.0f});

		helpers::checkValues(test.getSize(), 3);
		helpers::checkValues(test.getPoint(0), 0.0f, 1.0f);
		helpers::checkValues(test.getPoint(1), 6.0f, 7.0f);
		helpers::checkValues(test.getPoint(2), 4.0f, 5.0f);
	}
	SECTION("const Vec2f& getPoint(std::size_t idx) const") {
		slm::Polygon2f test{};

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			test.addPoint({pointVal, pointVal});
		}

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			helpers::checkValues(test.getPoint(i), pointVal, pointVal);
		}
	}
	SECTION("std::size_t getSize() const") {
		slm::Polygon2f test{};

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			test.addPoint({pointVal, pointVal});
		}

		helpers::checkValues(test.getSize(), 10);
	}
	SECTION("const std::vector<slm::Vec2f>& getPoints() const") {
		slm::Polygon2f test{};

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			test.addPoint({pointVal, pointVal});
		}

		const auto allPoints = test.getPoints();

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			helpers::checkValues(allPoints[i], pointVal, pointVal);
		}
	}
	SECTION("void translate(const Vec2& amount) override") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 0.0f});
		test.addPoint({2.0f, 0.0f});
		test.addPoint({1.0f, 2.0f});

		test.translate(slm::Vec2f{1.0f, 2.0f});

		helpers::checkValues(test.getPoint(0), 1.0f, 2.0f);
		helpers::checkValues(test.getPoint(1), 3.0f, 2.0f);
		helpers::checkValues(test.getPoint(2), 2.0f, 4.0f);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise) override") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 0.0f});
		test.addPoint({2.0f, 0.0f});
		test.addPoint({2.0f, 2.0f});
		test.addPoint({0.0f, 2.0f});

		test.rotate(90);

		helpers::checkValues(test.getPoint(0), 0.0f, 0.0f);
		helpers::checkValues(test.getPoint(1), 0.0f, 2.0f);
		helpers::checkValues(test.getPoint(2), -2.0f, 2.0f);
		helpers::checkValues(test.getPoint(3), -2.0f, 0.0f);
	}
	SECTION("void scale(const float factor) override") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 0.0f});
		test.addPoint({2.0f, 0.0f});
		test.addPoint({2.0f, 2.0f});
		test.addPoint({0.0f, 2.0f});

		test.scale(2.0f);

		helpers::checkValues(test.getPoint(0), 0.0f, 0.0f);
		helpers::checkValues(test.getPoint(1), 4.0f, 0.0f);
		helpers::checkValues(test.getPoint(2), 4.0f, 4.0f);
		helpers::checkValues(test.getPoint(3), 0.0f, 4.0f);
	}
	SECTION("void scaleX(const float factor) override") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 0.0f});
		test.addPoint({2.0f, 0.0f});
		test.addPoint({2.0f, 2.0f});
		test.addPoint({0.0f, 2.0f});

		test.scaleX(2.0f);

		helpers::checkValues(test.getPoint(0), 0.0f, 0.0f);
		helpers::checkValues(test.getPoint(1), 4.0f, 0.0f);
		helpers::checkValues(test.getPoint(2), 4.0f, 2.0f);
		helpers::checkValues(test.getPoint(3), 0.0f, 2.0f);
	}
	SECTION("void scaleY(const float factor) override") {
		slm::Polygon2f test{};

		test.addPoint({0.0f, 0.0f});
		test.addPoint({2.0f, 0.0f});
		test.addPoint({2.0f, 2.0f});
		test.addPoint({0.0f, 2.0f});

		test.scaleY(2.0f);

		helpers::checkValues(test.getPoint(0), 0.0f, 0.0f);
		helpers::checkValues(test.getPoint(1), 2.0f, 0.0f);
		helpers::checkValues(test.getPoint(2), 2.0f, 4.0f);
		helpers::checkValues(test.getPoint(3), 0.0f, 4.0f);
	}
	SECTION("ClippingStatus clip(const AxisAlignedBox2u& clippingBox) override") {
		slm::AxisAlignedBox2u clippingBox{1u, 1u, 3u, 3u};

		SECTION("Completely Inside") {
			slm::Polygon2f test{};

			test.addPoint({1.5f, 1.5f});
			test.addPoint({2.5f, 1.5f});
			test.addPoint({2.5f, 2.5f});
			test.addPoint({1.5f, 2.5f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Inside);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(0), 1.5f, 1.5f);
			helpers::checkValues(test.getPoint(1), 2.5f, 1.5f);
			helpers::checkValues(test.getPoint(2), 2.5f, 2.5f);
			helpers::checkValues(test.getPoint(3), 1.5f, 2.5f);
		}
		SECTION("Completely Outside") {
			slm::Polygon2f test{};

			test.addPoint({0.0f, 0.0f});
			test.addPoint({-1.0f, 0.0f});
			test.addPoint({-1.0f, -1.0f});
			test.addPoint({0.0f, -1.0f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Outside);
		}
		SECTION("Outside On Left") {
			slm::Polygon2f test{};

			test.addPoint({0.0f, 1.5f});
			test.addPoint({2.5f, 1.5f});
			test.addPoint({2.5f, 2.5f});
			test.addPoint({0.0f, 2.5f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(0), 1.0f, 1.5f);
			helpers::checkValues(test.getPoint(1), 2.5f, 1.5f);
			helpers::checkValues(test.getPoint(2), 2.5f, 2.5f);
			helpers::checkValues(test.getPoint(3), 1.0f, 2.5f);
		}
		SECTION("Outside On Top") {
			slm::Polygon2f test{};

			test.addPoint({1.5f, 1.5f});
			test.addPoint({2.5f, 1.5f});
			test.addPoint({2.5f, 4.0f});
			test.addPoint({1.5f, 4.0f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(1), 1.5f, 1.5f);
			helpers::checkValues(test.getPoint(2), 2.5f, 1.5f);
			helpers::checkValues(test.getPoint(3), 2.5f, 3.0f);
			helpers::checkValues(test.getPoint(0), 1.5f, 3.0f);
		}
		SECTION("Outside On Right") {
			slm::Polygon2f test{};

			test.addPoint({1.5f, 1.5f});
			test.addPoint({4.0f, 1.5f});
			test.addPoint({4.0f, 2.5f});
			test.addPoint({1.5f, 2.5f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(0), 1.5f, 1.5f);
			helpers::checkValues(test.getPoint(1), 3.0f, 1.5f);
			helpers::checkValues(test.getPoint(2), 3.0f, 2.5f);
			helpers::checkValues(test.getPoint(3), 1.5f, 2.5f);
		}
		SECTION("Outside On Bottom") {
			slm::Polygon2f test{};

			test.addPoint({1.5f, 0.0f});
			test.addPoint({2.5f, 0.0f});
			test.addPoint({2.5f, 2.5f});
			test.addPoint({1.5f, 2.5f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(0), 1.5f, 1.0f);
			helpers::checkValues(test.getPoint(1), 2.5f, 1.0f);
			helpers::checkValues(test.getPoint(2), 2.5f, 2.5f);
			helpers::checkValues(test.getPoint(3), 1.5f, 2.5f);
		}
		SECTION("Outside On All Sides") {
			slm::Polygon2f test{};

			test.addPoint({2.0f, 0.5f});
			test.addPoint({0.5f, 2.0f});
			test.addPoint({2.0f, 3.5f});
			test.addPoint({3.5f, 2.0f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 8);
			helpers::checkValues(test.getPoint(0), 3.0f, 1.5f);
			helpers::checkValues(test.getPoint(1), 2.5f, 1.0f);
			helpers::checkValues(test.getPoint(2), 1.5f, 1.0f);
			helpers::checkValues(test.getPoint(3), 1.0f, 1.5f);
			helpers::checkValues(test.getPoint(4), 1.0f, 2.5f);
			helpers::checkValues(test.getPoint(5), 1.5f, 3.0f);
			helpers::checkValues(test.getPoint(6), 2.5f, 3.0f);
			helpers::checkValues(test.getPoint(7), 3.0f, 2.5f);
		}
		SECTION("Surrounding Box") {
			slm::Polygon2f test{};

			test.addPoint({0.0f, 0.0f});
			test.addPoint({0.0f, 4.0f});
			test.addPoint({4.0f, 4.0f});
			test.addPoint({4.0f, 0.0f});

			const auto clipStatus = test.clip(clippingBox);

			CHECK(clipStatus == slm::ClippingStatus::Modified);

			helpers::checkValues(test.getSize(), 4);
			helpers::checkValues(test.getPoint(1), 1.0f, 1.0f);
			helpers::checkValues(test.getPoint(0), 3.0f, 1.0f);
			helpers::checkValues(test.getPoint(3), 3.0f, 3.0f);
			helpers::checkValues(test.getPoint(2), 1.0f, 3.0f);
		}
	}
	SECTION("float getXMin() const") {
		slm::Polygon2f test{};

		test.addPoint({-2.0f, 10.0f});
		test.addPoint({-1.0f, -4.0f});
		test.addPoint({-10.0f, 15.0f});
		test.addPoint({5.0f, 2.0f});

		helpers::checkValues(test.getXMin(), -10.0f);
	}
	SECTION("float getXMax() const") {
		slm::Polygon2f test{};

		test.addPoint({-2.0f, 10.0f});
		test.addPoint({-1.0f, -4.0f});
		test.addPoint({-10.0f, 15.0f});
		test.addPoint({5.0f, 2.0f});

		helpers::checkValues(test.getXMax(), 5.0f);
	}
	SECTION("float getYMin() const") {
		slm::Polygon2f test{};

		test.addPoint({-2.0f, 10.0f});
		test.addPoint({-1.0f, -4.0f});
		test.addPoint({-10.0f, 15.0f});
		test.addPoint({5.0f, 2.0f});

		helpers::checkValues(test.getYMin(), -4.0f);
	}
	SECTION("float getYMax() const") {
		slm::Polygon2f test{};

		test.addPoint({-2.0f, 10.0f});
		test.addPoint({-1.0f, -4.0f});
		test.addPoint({-10.0f, 15.0f});
		test.addPoint({5.0f, 2.0f});

		helpers::checkValues(test.getYMax(), 15.0f);
	}
	SECTION("const Vec2f& operator[](const std::size_t idx) const override") {
		slm::Polygon2f test{};

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			test.addPoint({pointVal, pointVal});
		}

		for (std::size_t i = 0; i < 10; i++) {
			const auto pointVal = static_cast<float>(i);
			helpers::checkValues(test[i], pointVal, pointVal);
		}
	}
	SECTION("bool operator==(const Polygon2f& other) const") {
		SECTION("Empty") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			CHECK(test1 == test2);
		}
		SECTION("Different Size") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal, pointVal});
			}

			test2.addPoint({10.0f, 10.0f});

			CHECK(!(test1 == test2));
		}
		SECTION("Different Values") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal + 1.0f, pointVal + 1.0f});
			}

			CHECK(!(test1 == test2));
		}
		SECTION("Many of the same") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal, pointVal});
			}

			CHECK(test1 == test2);
		}
		SECTION("Many of the same offset") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 7; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 0; i < 7; i++) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			CHECK(test1 == test2);
		}
		SECTION("Many of the same reverse") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
			}
			for (std::size_t i = 10; i-- > 0;) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}
			test1 == test2;
			CHECK(test1 == test2);
		}
		SECTION("Many of the same offset reverse") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 7; i-- > 0;) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 10; i-- > 7;) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			test1 == test2;
			CHECK(test1 == test2);
		}
	}
	SECTION("bool operator!=(const Polygon2f& other) const") {
		SECTION("Empty") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			CHECK(!(test1 != test2));
		}
		SECTION("Different Size") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal, pointVal});
			}

			test2.addPoint({10.0f, 10.0f});

			CHECK(test1 != test2);
		}
		SECTION("Different Values") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal + 1.0f, pointVal + 1.0f});
			}

			CHECK(test1 != test2);
		}
		SECTION("Many of the same") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
				test2.addPoint({pointVal, pointVal});
			}

			CHECK(!(test1 != test2));
		}
		SECTION("Many of the same offset") {
			slm::Polygon2f test1{};
			slm::Polygon2f test2{};

			for (std::size_t i = 0; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test1.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 7; i < 10; i++) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			for (std::size_t i = 0; i < 7; i++) {
				const auto pointVal = static_cast<float>(i);
				test2.addPoint({pointVal, pointVal});
			}

			CHECK(!(test1 != test2));
		}
	}
}




//////////////
// SMFModel //
//////////////

TEST_CASE("SMFModel") {
	SECTION("SMFModel()") {
		slm::SMFModel test{};

		helpers::checkValues(test.getVertexCount(), 0);
		helpers::checkValues(test.getFaceCount(), 0);
	}
	SECTION("uint32_t getVertexCount() const") {
		slm::SMFModel test{};

		test.addVertex({0.0f, 0.0f, 0.0f});

		helpers::checkValues(test.getVertexCount(), 1);

		test.addVertex({1.0f, 1.0f, 1.0f});

		helpers::checkValues(test.getVertexCount(), 2);
	}
	SECTION("uint32_t getFaceCount() const") {
		slm::SMFModel test{};

		test.addVertex({0.0f, 0.0f, 0.0f});
		test.addVertex({1.0f, 1.0f, 1.0f});
		test.addVertex({2.0f, 2.0f, 2.0f});

		helpers::checkValues(test.getFaceCount(), 0);
		test.addFace({1, 1, 1});

		helpers::checkValues(test.getFaceCount(), 1);

		test.addFace({2, 2, 2});

		helpers::checkValues(test.getFaceCount(), 2);
	}
	SECTION("const slm::Vec3f& getVertex(std::size_t idx) const") {
		slm::SMFModel test{};

		test.addVertex({0.0f, 1.0f, 2.0f});
		test.addVertex({3.0f, 4.0f, 5.0f});
		test.addVertex({6.0f, 7.0f, 8.0f});

		helpers::checkValues(test.getVertex(0), 0.0f, 1.0f, 2.0f);
		helpers::checkValues(test.getVertex(1), 3.0f, 4.0f, 5.0f);
		helpers::checkValues(test.getVertex(2), 6.0f, 7.0f, 8.0f);
	}
	SECTION("const std::array<slm::Vec3f&, 3> getFaceVertices(std::size_t faceIdx) const") {
		slm::SMFModel test{};

		test.addVertex({0.0f, 1.0f, 2.0f});
		test.addVertex({3.0f, 4.0f, 5.0f});
		test.addVertex({6.0f, 7.0f, 8.0f});

		test.addFace({1, 2, 3});

		const auto faceVertices = test.getFaceVertices(0);

		helpers::checkValues(*faceVertices[0], 0.0f, 1.0f, 2.0f);
		helpers::checkValues(*faceVertices[1], 3.0f, 4.0f, 5.0f);
		helpers::checkValues(*faceVertices[2], 6.0f, 7.0f, 8.0f);
	}
	SECTION("void addVertex(slm::Vec3f vertex)") {
		slm::SMFModel test{};

		test.addVertex(slm::Vec3f{0.0f, 1.0f, 2.0f});

		helpers::checkValues(test.getVertexCount(), 1);

		test.addVertex(slm::Vec3f{3.0f, 4.0f, 5.0f});

		helpers::checkValues(test.getVertexCount(), 2);

		test.addVertex(slm::Vec3f{6.0f, 7.0f, 8.0f});

		helpers::checkValues(test.getVertexCount(), 3);
	}
	SECTION("void addVertex(const float x, const float y, const float z)") {
		slm::SMFModel test{};

		test.addVertex(0.0f, 1.0f, 2.0f);

		helpers::checkValues(test.getVertexCount(), 1);

		test.addVertex(3.0f, 4.0f, 5.0f);

		helpers::checkValues(test.getVertexCount(), 2);

		test.addVertex(6.0f, 7.0f, 8.0f);

		helpers::checkValues(test.getVertexCount(), 3);
	}
	SECTION("void addFace(slm::Vec3i face)") {
		{
			slm::SMFModel test{};

			test.addVertex({0.0f, 1.0f, 2.0f});
			test.addVertex({3.0f, 4.0f, 5.0f});
			test.addVertex({6.0f, 7.0f, 8.0f});

			test.addFace(slm::Vec3i{1, 2, 3});

			helpers::checkValues(test.getFaceCount(), 1);

			test.addFace(slm::Vec3i{1, 2, 3});

			helpers::checkValues(test.getFaceCount(), 2);

			test.addFace(slm::Vec3i{1, 2, 3});

			helpers::checkValues(test.getFaceCount(), 3);
		}
		{
			slm::SMFModel test{};

			test.addVertex({0.0f, 1.0f, 2.0f});
			test.addVertex({3.0f, 4.0f, 5.0f});
			test.addVertex({6.0f, 7.0f, 8.0f});

			try {
				test.addFace(slm::Vec3i{4, 2, 3});
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);

			try {
				test.addFace(slm::Vec3i{1, 4, 3});
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);

			try {
				test.addFace(slm::Vec3i{1, 2, 4});
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);
		}
	}
	SECTION("void addFace(const int32_t vertex1, const int32_t vertex2, const int32_t vertex3)") {
		{
			slm::SMFModel test{};

			test.addVertex({0.0f, 1.0f, 2.0f});
			test.addVertex({3.0f, 4.0f, 5.0f});
			test.addVertex({6.0f, 7.0f, 8.0f});

			test.addFace(1, 2, 3);

			helpers::checkValues(test.getFaceCount(), 1);

			test.addFace(1, 2, 3);

			helpers::checkValues(test.getFaceCount(), 2);

			test.addFace(1, 2, 3);

			helpers::checkValues(test.getFaceCount(), 3);
		}
		{
			slm::SMFModel test{};

			test.addVertex({0.0f, 1.0f, 2.0f});
			test.addVertex({3.0f, 4.0f, 5.0f});
			test.addVertex({6.0f, 7.0f, 8.0f});

			try {
				test.addFace(4, 2, 3);
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);

			try {
				test.addFace(1, 4, 3);
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);

			try {
				test.addFace(1, 2, 4);
				REQUIRE(false);
			}
			catch (...) {
				REQUIRE(true);
			}

			helpers::checkValues(test.getFaceCount(), 0);
		}
	}
}




////////////////
// ViewVolume //
////////////////

TEST_CASE("ViewVolume") {
	SECTION("ViewVolume()") {
		slm::ViewVolume test{};

		CHECK(true);
	}
	SECTION("const slm::Vec3f& getProjectionReferencePoint() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getProjectionReferencePoint(), 0.0f, 0.0f, 1.0f);
	}
	SECTION("const slm::Vec3f& getViewReferencePoint() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getViewReferencePoint(), 0.0f, 0.0f, 0.0f);
	}
	SECTION("const slm::Vec3f& getViewPlaneNormal() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getViewPlaneNormal(), 0.0f, 0.0f, -1.0f);
	}
	SECTION("const slm::Vec3f& getViewUpVector() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getViewUpVector(), 0.0f, 1.0f, 0.0f);
	}
	SECTION("float getVRCUMin() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getVRCUMin(), -0.7f);
	}
	SECTION("float getVRCVMin() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getVRCVMin(), -0.7f);
	}
	SECTION("float getVRCUMax() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getVRCUMax(), 0.7f);
	}
	SECTION("float getVRCVMax() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getVRCVMax(), 0.7f);
	}
	SECTION("bool getParallelProjection() const") {
		slm::ViewVolume test{};

		helpers::checkValues(test.getParallelProjection(), false);
	}
	SECTION("void setProjectionReferencePoint(slm::Vec3f projectionReferencePoint)") {
		slm::ViewVolume test{};

		test.setProjectionReferencePoint({1.0f, 2.0f, 3.0f});

		helpers::checkValues(test.getProjectionReferencePoint(), 1.0f, 2.0f, 3.0f);
	}
	SECTION("void setViewReferencePoint(slm::Vec3f viewReferencePoint)") {
		slm::ViewVolume test{};

		test.setViewReferencePoint({1.0f, 2.0f, 3.0f});

		helpers::checkValues(test.getViewReferencePoint(), 1.0f, 2.0f, 3.0f);
	}
	SECTION("void setViewPlaneNormal(slm::Vec3f viewPlaneNormal)") {
		slm::ViewVolume test{};

		test.setViewPlaneNormal({1.0f, 2.0f, 3.0f});

		helpers::checkValues(test.getViewPlaneNormal(), 1.0f, 2.0f, 3.0f);
	}
	SECTION("void setViewUpVector(slm::Vec3f viewUpVector)") {
		slm::ViewVolume test{};

		test.setViewUpVector({1.0f, 2.0f, 3.0f});

		helpers::checkValues(test.getViewUpVector(), 1.0f, 2.0f, 3.0f);
	}
	SECTION("void setVRCMinMaxUV(const float uMin, const float vMin, const float uMax, const float "
			"vMax)") {
		slm::ViewVolume test{};

		test.setVRCMinMaxUV(1.0f, 2.0f, 3.0f, 4.0f);

		helpers::checkValues(test.getVRCUMin(), 1.0f);
		helpers::checkValues(test.getVRCVMin(), 2.0f);
		helpers::checkValues(test.getVRCUMax(), 3.0f);
		helpers::checkValues(test.getVRCVMax(), 4.0f);
	}
	SECTION("void setParallelProjection(const bool parallel)") {
		slm::ViewVolume test{};

		test.setParallelProjection(true);

		helpers::checkValues(test.getParallelProjection(), true);
	}
}




///////////
// Scene //
///////////

TEST_CASE("Scene") {
	SECTION("Scene()") {
		slm::Scene test{};

		helpers::checkValues(test.getSize(), 0);
	}
	SECTION("void addPrimitive(std::unique_ptr<slm::Primitive2> primitive)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		helpers::checkValues(test.getSize(), 1);

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		helpers::checkValues(test.getSize(), 2);

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		helpers::checkValues(test.getSize(), 3);
	}
	SECTION("const std::unique_ptr<slm::Primitive2>& getPrimitive(std::size_t idx) const") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		helpers::checkValues(test.getSize(), 1);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 1.0f, 1.0f);

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		helpers::checkValues(test.getSize(), 2);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 1.0f, 1.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 2.0f, 2.0f, 3.0f, 3.0f);

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));
		helpers::checkValues(test.getSize(), 3);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 1.0f, 1.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 2.0f, 2.0f, 3.0f, 3.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, 4.0f, 4.0f, 5.0f, 5.0f);
	}
	SECTION("std::size_t getSize() const") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));

		helpers::checkValues(test.getSize(), 3);
	}
	SECTION("void translate(const Vec2& amount)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.translate(slm::Vec2f{1.0f, 2.0f});

		helpers::checkValues(test.getSize(), 3);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 1.0f, 2.0f, 2.0f, 3.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 3.0f, 4.0f, 4.0f, 5.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, 5.0f, 6.0f, 6.0f, 7.0f);
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.rotate(90);

		helpers::checkValues(test.getSize(), 3);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, -1.0f, 1.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, -2.0f, 2.0f, -3.0f, 3.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, -4.0f, 4.0f, -5.0f, 5.0f);
	}
	SECTION("void scale(const float factor)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.scale(2.0f);

		helpers::checkValues(test.getSize(), 3);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 2.0f, 2.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 4.0f, 4.0f, 6.0f, 6.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, 8.0f, 8.0f, 10.0f, 10.0f);
	}
	SECTION("void scaleX(const float factor)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.scaleX(2.0f);

		helpers::checkValues(test.getSize(), 3);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 2.0f, 1.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 4.0f, 2.0f, 6.0f, 3.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, 8.0f, 4.0f, 10.0f, 5.0f);
	}
	SECTION("void scaleY(const float factor)") {
		slm::Scene test{};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 1.0f, 1.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.scaleY(2.0f);

		helpers::checkValues(test.getSize(), 3);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 0.0f, 0.0f, 1.0f, 2.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(1).get());
		helpers::checkValues(line, 2.0f, 4.0f, 3.0f, 6.0f);
		line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(2).get());
		helpers::checkValues(line, 4.0f, 8.0f, 5.0f, 10.0f);
	}
	SECTION("void clip(const AxisAlignedBox2u& clippingBox)") {
		slm::Scene test{};
		slm::AxisAlignedBox2u clippingBox{1u, 1u, 3u, 3u};

		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{0.0f, 0.0f, 0.5f, 0.5f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{2.0f, 2.0f, 3.0f, 3.0f}));
		test.addPrimitive(std::make_unique<slm::Line2f>(slm::Line2f{4.0f, 4.0f, 5.0f, 5.0f}));

		test.clip(clippingBox);

		helpers::checkValues(test.getSize(), 1);
		auto line = *dynamic_cast<slm::Line2f*>(test.getPrimitive(0).get());
		helpers::checkValues(line, 2.0f, 2.0f, 3.0f, 3.0f);
	}
}