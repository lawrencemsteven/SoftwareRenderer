#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Vec.h"

using namespace slm;

//////////////////////
// Helper Functions //
//////////////////////

void checkVec2fValues(const Vec2f& vec, const Vec2f& otherVec) {
	for (std::size_t i = 0; i < 2; i++) {
		CHECK_THAT(vec[i], Catch::Matchers::WithinAbs(otherVec[i], 0.0001f));
	}
}
void checkVec2fValues(const Vec2f& vec, const std::array<float, 2>& values) {
	for (std::size_t i = 0; i < 2; i++) {
		CHECK_THAT(vec[i], Catch::Matchers::WithinAbs(values[i], 0.0001f));
	}
}




///////////
// Vec2f //
///////////

TEST_CASE("Vec2f") {
	SECTION("Vec2f()") {
		Vec2f test{};

		CHECK(test == std::array<float, 2>{0.0f, 0.0f});
	}
	SECTION("Vec2f(const float vals[2])") {
		float testValues[2] = {0.0f, 0.0f};

		Vec2f test{testValues};

		checkVec2fValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = Vec2f{testValues};

		checkVec2fValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = Vec2f{testValues};

		checkVec2fValues(test, testValues);
	}
	SECTION("Vec2f(const std::array<float, 2>& vals)") {
		std::array<float, 2> testValues = {0.0f, 0.0f};

		Vec2f test{testValues};

		checkVec2fValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = Vec2f{testValues};

		checkVec2fValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = Vec2f{testValues};

		checkVec2fValues(test, testValues);
	}
	SECTION("Vec2f(const float x, const float y)") {
		float testX = 0.0f;
		float testY = 0.0f;

		Vec2f test{testX, testY};

		checkVec2fValues(test, std::array<float, 2>{testX, testY});

		testX = 1.0f;
		testY = 2.0f;

		test = Vec2f{testX, testY};

		checkVec2fValues(test, std::array<float, 2>{testX, testY});

		testX = -1.0f;
		testY = -2.0f;

		test = Vec2f{testX, testY};

		checkVec2fValues(test, std::array<float, 2>{testX, testY});
	}
	SECTION("x(const float x) && x()") {
		Vec2f test{15.0f, 30.0f};

		CHECK_THAT(test.x(), Catch::Matchers::WithinAbs(15.0f, 0.0001f));

		test.x(150.0f);

		CHECK_THAT(test.x(), Catch::Matchers::WithinAbs(150.0f, 0.0001f));
	}
	SECTION("y(const int32_t y) && y()") {
		Vec2f test{15.0f, 30.0f};

		CHECK_THAT(test.y(), Catch::Matchers::WithinAbs(30.0f, 0.0001f));

		test.y(300.0f);

		CHECK_THAT(test.y(), Catch::Matchers::WithinAbs(300.0f, 0.0001));
	}
	SECTION("translate(const Vec2f& amount)") {
		Vec2f test{1.0f, 2.0f};
		const Vec2f translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translate(const std::array<float, 2>& amount)") {
		Vec2f test{1.0f, 2.0f};
		const std::array<float, 2> translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translate(const float amount[2])") {
		Vec2f test{1.0f, 2.0f};
		const float translateAmount[2]{3.0f, 4.0f};

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translateX(const float amount)") {
		Vec2f test{1.0f, 2.0f};
		const float translateAmount{3.0f};

		test.translateX(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{4.0f, 2.0f});

		test.translateX(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{7.0f, 2.0f});
	}
	SECTION("translateY(const float amount)") {
		Vec2f test{1.0f, 2.0f};
		const float translateAmount{4.0f};

		test.translateY(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{1.0f, 6.0f});

		test.translateY(translateAmount);

		checkVec2fValues(test, std::array<float, 2>{1.0f, 10.0f});
	}
	SECTION("rotate(const int32_t degreesCounterClockwise)") {
		Vec2f test{1.0f, 0.0f};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		checkVec2fValues(test, std::array<float, 2>{0.0f, 1.0f});

		test.rotate(rotateAmount);

		checkVec2fValues(test, std::array<float, 2>{-1.0f, 0.0f});

		test.rotate(rotateAmount);

		checkVec2fValues(test, std::array<float, 2>{0.0f, -1.0f});

		test.rotate(rotateAmount);

		checkVec2fValues(test, std::array<float, 2>{1.0f, 0.0f});
	}
	SECTION("scale(const Vec2& amount)") {
		Vec2f test{2.0f, 3.0f};
		const Vec2f scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scale(const float factor)") {
		Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{6.0f, 9.0f});

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{18.0f, 27.0f});
	}
	SECTION("scale(const float factors[2])") {
		Vec2f test{2.0f, 3.0f};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scale(const std::array<float, 2>& factors)") {
		Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scaleX(const float factor)") {
		Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{6.0f, 3.0f});

		test.scaleX(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{18.0f, 3.0f});
	}
	SECTION("scaleY(const float factor)") {
		Vec2f test{2.0f, 3.0f};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{2, 12});

		test.scaleY(scaleAmount);

		checkVec2fValues(test, std::array<float, 2>{2, 48});
	}
	SECTION("operator[](const std::size_t idx)") {
		Vec2f test{2.0f, 3.0f};

		CHECK_THAT(test[0], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
		CHECK_THAT(test[1], Catch::Matchers::WithinAbs(3.0f, 0.0001f));

		test.x(10.0f);
		test.y(20.0f);

		CHECK_THAT(test[0], Catch::Matchers::WithinAbs(10.0f, 0.0001f));
		CHECK_THAT(test[1], Catch::Matchers::WithinAbs(20.0f, 0.0001f));
	}
	SECTION("operator+=(const Vec2& other)") {
		Vec2f test{2.0f, 3.0f};
		const Vec2f addAmount{4.0f, 5.0f};

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator+=(const std::array<float, 2>& amount)") {
		Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> addAmount{4.0f, 5.0f};

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator+=(const float amount[2])") {
		Vec2f test{2.0f, 3.0f};
		const float addAmount[2]{4.0f, 5.0f};

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator-=(const Vec2& other)") {
		Vec2f test{2.0f, 3.0f};
		const Vec2f subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator-=(const std::array<float, 2>& amount)") {
		Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator-=(const float amount[2])") {
		Vec2f test{2.0f, 3.0f};
		const float subtractAmount[2]{4.0f, 5.0f};

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator*=(const Vec2& other)") {
		Vec2f test{2.0f, 3.0f};
		const Vec2f multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator*=(const float factor)") {
		Vec2f test{2.0f, 3.0f};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{8.0f, 12.0f});

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{32.0f, 48.0f});
	}
	SECTION("operator*=(const std::array<float, 2>& amount)") {
		Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator*=(const float amount[2])") {
		Vec2f test{2.0f, 3.0f};
		const float multiplyAmount[2]{4.0f, 5.0f};

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator==(const Vec2f& other)") {
		Vec2f test{1.0f, 2.0f};
		Vec2f test2{1.0f, 2.0f};

		CHECK(test == test2);

		test2.x(3.0f);

		CHECK(!(test == test2));

		test.x(3.0f);

		CHECK(test == test2);

		test2.y(3.0f);

		CHECK(!(test == test2));
	}
	SECTION("operator==(const std::array<float, 2>& other)") {
		Vec2f test{1.0f, 2.0f};
		std::array<float, 2> values{1.0f, 2.0f};

		CHECK(test == values);

		values[0] = 3.0f;

		CHECK(!(test == values));

		test.x(3.0f);

		CHECK(test == values);

		values[1] = 3.0f;

		CHECK(!(test == values));
	}
	SECTION("operator==(const float other[2])") {
		Vec2f test{1.0f, 2.0f};
		float values[2]{1.0f, 2.0f};

		CHECK(test == values);

		values[0] = 3.0f;

		CHECK(!(test == values));

		test.x(3.0f);

		CHECK(test == values);

		values[1] = 3.0f;

		CHECK(!(test == values));
	}
	SECTION("operator!=(const Vec2f& other)") {
		Vec2f test{1.0f, 2.0f};
		Vec2f test2{1.0f, 2.0f};

		CHECK(!(test != test2));

		test2.x(3.0f);

		CHECK(test != test2);

		test.x(3.0f);

		CHECK(!(test != test2));

		test2.y(3.0f);

		CHECK(test != test2);
	}
	SECTION("operator!=(const std::array<float, 2>& other)") {
		Vec2f test{1.0f, 2.0f};
		std::array<float, 2> values{1.0f, 2.0f};

		CHECK(!(test != values));

		values[0] = 3.0f;

		CHECK(test != values);

		test.x(3.0f);

		CHECK(!(test != values));

		values[1] = 3.0f;

		CHECK(test != values);
	}
	SECTION("operator!=(const float other[2])") {
		Vec2f test{1.0f, 2.0f};
		float values[2]{1.0f, 2.0f};

		CHECK(!(test != values));

		values[0] = 3.0f;

		CHECK(test != values);

		test.x(3.0f);

		CHECK(!(test != values));

		values[1] = 3.0f;

		CHECK(test != values);
	}
	SECTION("getValsAsFloat()") {
		Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsFloat();

		CHECK_THAT(values[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
		CHECK_THAT(values[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
	}
	SECTION("getValsAsInt()") {
		Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
}




///////////
// Vec2i //
///////////

TEST_CASE("Vec2i") {
	SECTION("Vec2i()") {
		Vec2i test{};

		CHECK(test == std::array<int32_t, 2>{0, 0});
	}
	SECTION("Vec2i(const int32_t vals[2])") {
		int32_t testValues[2] = {0, 0};

		Vec2i test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1;
		testValues[1] = 2;

		test = Vec2i{testValues};

		CHECK(test == testValues);

		testValues[0] = -1;
		testValues[1] = -2;

		test = Vec2i{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2i(const std::array<int32_t, 2>& vals)") {
		std::array<int32_t, 2> testValues = {0, 0};

		Vec2i test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1;
		testValues[1] = 2;

		test = Vec2i{testValues};

		CHECK(test == testValues);

		testValues[0] = -1;
		testValues[1] = -2;

		test = Vec2i{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2i(const int32_t x, const int32_t y)") {
		int32_t testX = 0;
		int32_t testY = 0;

		Vec2i test{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});

		testX = 1;
		testY = 2;

		test = Vec2i{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});

		testX = -1;
		testY = -2;

		test = Vec2i{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});
	}
	SECTION("x(const int32_t x) && x()") {
		Vec2i test{15, 30};

		CHECK(test.x() == 15);

		test.x(150);

		CHECK(test.x() == 150);
	}
	SECTION("y(const int32_t y) && y()") {
		Vec2i test{15, 30};

		CHECK(test.y() == 30);

		test.y(300);

		CHECK(test.y() == 300);
	}
	SECTION("translate(const Vec2i& amount)") {
		Vec2i test{1, 2};
		const Vec2i translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translate(const std::array<int32_t, 2>& amount)") {
		Vec2i test{1, 2};
		const std::array<int32_t, 2> translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translate(const int32_t amount[2])") {
		Vec2i test{1, 2};
		const int32_t translateAmount[2]{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translateX(const int32_t amount)") {
		Vec2i test{1, 2};
		const int32_t translateAmount{3};

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 2});

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 2});
	}
	SECTION("translateY(const int32_t amount)") {
		Vec2i test{1, 2};
		const int32_t translateAmount{4};

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 6});

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 10});
	}
	SECTION("rotate(const int32_t degreesCounterClockwise)") {
		Vec2i test{1, 0};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		CHECK(test == std::array<int32_t, 2>{0, 1});

		test.rotate(rotateAmount);

		CHECK(test == std::array<int32_t, 2>{-1, 0});

		test.rotate(rotateAmount);

		CHECK(test == std::array<int32_t, 2>{0, -1});

		test.rotate(rotateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 0});
	}
	SECTION("scale(const Vec2& amount)") {
		Vec2i test{2, 3};
		const Vec2i scaleAmount{3, 4};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scale(const float factor)") {
		Vec2i test{2, 3};
		const float scaleAmount{3};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 9});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 27});
	}
	SECTION("scale(const float factors[2])") {
		Vec2i test{2, 3};
		const float scaleAmount[2]{3, 4};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scale(const std::array<float, 2>& factors)") {
		Vec2i test{2, 3};
		const std::array<float, 2> scaleAmount{3, 4};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scaleX(const float factor)") {
		Vec2i test{2, 3};
		const float scaleAmount{3};

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 3});

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 3});
	}
	SECTION("scaleY(const float factor)") {
		Vec2i test{2, 3};
		const float scaleAmount{4};

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 12});

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 48});
	}
	SECTION("operator[](const std::size_t idx)") {
		Vec2i test{2, 3};

		CHECK(test[0] == 2);
		CHECK(test[1] == 3);

		test.x(10);
		test.y(20);

		CHECK(test[0] == 10);
		CHECK(test[1] == 20);
	}
	SECTION("operator+=(const Vec2& other)") {
		Vec2i test{2, 3};
		const Vec2i addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator+=(const std::array<int32_t, 2>& amount)") {
		Vec2i test{2, 3};
		const std::array<int32_t, 2> addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator+=(const int32_t amount[2])") {
		Vec2i test{2, 3};
		const int32_t addAmount[2]{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator-=(const Vec2& other)") {
		Vec2i test{2, 3};
		const Vec2i subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator-=(const std::array<int32_t, 2>& amount)") {
		Vec2i test{2, 3};
		const std::array<int32_t, 2> subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator-=(const int32_t amount[2])") {
		Vec2i test{2, 3};
		const int32_t subtractAmount[2]{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator*=(const Vec2& other)") {
		Vec2i test{2, 3};
		const Vec2i multiplyAmount{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator*=(const float factor)") {
		Vec2i test{2, 3};
		const float multiplyAmount{4};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 12});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 48});
	}
	SECTION("operator*=(const std::array<float, 2>& amount)") {
		Vec2i test{2, 3};
		const std::array<float, 2> multiplyAmount{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator*=(const float amount[2])") {
		Vec2i test{2, 3};
		const float multiplyAmount[2]{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator==(const Vec2i& other)") {
		Vec2i test{1, 2};
		Vec2i test2{1, 2};

		CHECK(test == test2);

		test2.x(3);

		CHECK(!(test == test2));

		test.x(3);

		CHECK(test == test2);

		test2.y(3);

		CHECK(!(test == test2));
	}
	SECTION("operator==(const std::array<int32_t, 2>& other)") {
		Vec2i test{1, 2};
		std::array<int32_t, 2> values{1, 2};

		CHECK(test == values);

		values[0] = 3;

		CHECK(!(test == values));

		test.x(3);

		CHECK(test == values);

		values[1] = 3;

		CHECK(!(test == values));
	}
	SECTION("operator==(const int32_t other[2])") {
		Vec2i test{1, 2};
		int32_t values[2]{1, 2};

		CHECK(test == values);

		values[0] = 3;

		CHECK(!(test == values));

		test.x(3);

		CHECK(test == values);

		values[1] = 3;

		CHECK(!(test == values));
	}
	SECTION("operator!=(const Vec2i& other)") {
		Vec2i test{1, 2};
		Vec2i test2{1, 2};

		CHECK(!(test != test2));

		test2.x(3);

		CHECK(test != test2);

		test.x(3);

		CHECK(!(test != test2));

		test2.y(3);

		CHECK(test != test2);
	}
	SECTION("operator!=(const std::array<int32_t, 2>& other)") {
		Vec2i test{1, 2};
		std::array<int32_t, 2> values{1, 2};

		CHECK(!(test != values));

		values[0] = 3;

		CHECK(test != values);

		test.x(3);

		CHECK(!(test != values));

		values[1] = 3;

		CHECK(test != values);
	}
	SECTION("operator!=(const int32_t other[2])") {
		Vec2i test{1, 2};
		int32_t values[2]{1, 2};

		CHECK(!(test != values));

		values[0] = 3;

		CHECK(test != values);

		test.x(3);

		CHECK(!(test != values));

		values[1] = 3;

		CHECK(test != values);
	}
	SECTION("getValsAsFloat()") {
		Vec2i test{1, 2};

		const auto values = test.getValsAsFloat();

		CHECK_THAT(values[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
		CHECK_THAT(values[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
	}
	SECTION("getValsAsInt()") {
		Vec2i test{1, 2};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
}