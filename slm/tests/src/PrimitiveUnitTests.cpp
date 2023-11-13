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
	SECTION("Line2f(Vec2f start, Vec2f end)"){
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