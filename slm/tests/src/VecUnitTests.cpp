#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "HelperFunctions.h"

///////////
// Vec2f //
///////////

TEST_CASE("Vec2f") {
	SECTION("Vec2f()") {
		slm::Vec2f test{};

		CHECK(test == std::array<float, 2>{0.0f, 0.0f});
	}
	SECTION("Vec2f(const float vals[2])") {
		float testValues[2] = {0.0f, 0.0f};

		slm::Vec2f test{testValues};

		helpers::checkVec2fValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkVec2fValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkVec2fValues(test, testValues);
	}
	SECTION("Vec2f(const std::array<float, 2>& vals)") {
		std::array<float, 2> testValues = {0.0f, 0.0f};

		slm::Vec2f test{testValues};

		helpers::checkVec2fValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkVec2fValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkVec2fValues(test, testValues);
	}
	SECTION("Vec2f(const float x, const float y)") {
		float testX = 0.0f;
		float testY = 0.0f;

		slm::Vec2f test{testX, testY};

		helpers::checkVec2fValues(test, std::array<float, 2>{testX, testY});

		testX = 1.0f;
		testY = 2.0f;

		test = slm::Vec2f{testX, testY};

		helpers::checkVec2fValues(test, std::array<float, 2>{testX, testY});

		testX = -1.0f;
		testY = -2.0f;

		test = slm::Vec2f{testX, testY};

		helpers::checkVec2fValues(test, std::array<float, 2>{testX, testY});
	}
	SECTION("x(const float x) && x()") {
		slm::Vec2f test{15.0f, 30.0f};

		helpers::checkFloatValues(test.x(), 15.0f);

		test.x(150.0f);

		helpers::checkFloatValues(test.x(), 150.0f);
	}
	SECTION("y(const float y) && y()") {
		slm::Vec2f test{15.0f, 30.0f};

		helpers::checkFloatValues(test.y(), 30.0f);

		test.y(300.0f);

		helpers::checkFloatValues(test.y(), 300.0f);
	}
	SECTION("translate(const Vec2f& amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const slm::Vec2f translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translate(const std::array<float, 2>& amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const std::array<float, 2> translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translate(const float amount[2])") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount[2]{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("translateX(const float amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount{3.0f};

		test.translateX(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{4.0f, 2.0f});

		test.translateX(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{7.0f, 2.0f});
	}
	SECTION("translateY(const float amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount{4.0f};

		test.translateY(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{1.0f, 6.0f});

		test.translateY(translateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{1.0f, 10.0f});
	}
	SECTION("rotate(const int32_t degreesCounterClockwise)") {
		slm::Vec2f test{1.0f, 0.0f};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{0.0f, 1.0f});

		test.rotate(rotateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{-1.0f, 0.0f});

		test.rotate(rotateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{0.0f, -1.0f});

		test.rotate(rotateAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{1.0f, 0.0f});
	}
	SECTION("scale(const Vec2& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scale(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 9.0f});

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{18.0f, 27.0f});
	}
	SECTION("scale(const float factors[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scale(const std::array<float, 2>& factors)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scaleX(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 3.0f});

		test.scaleX(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{18.0f, 3.0f});
	}
	SECTION("scaleY(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{2, 12});

		test.scaleY(scaleAmount);

		helpers::checkVec2fValues(test, std::array<float, 2>{2, 48});
	}
	SECTION("operator[](const std::size_t idx)") {
		slm::Vec2f test{2.0f, 3.0f};

		helpers::checkFloatValues(test[0], 2.0f);
		helpers::checkFloatValues(test[1], 3.0f);

		test.x(10.0f);
		test.y(20.0f);

		helpers::checkFloatValues(test[0], 10.0f);
		helpers::checkFloatValues(test[1], 20.0f);
	}
	SECTION("operator+=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f addAmount{4.0f, 5.0f};

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator+=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> addAmount{4.0f, 5.0f};

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator+=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float addAmount[2]{4.0f, 5.0f};

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("operator-=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator-=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator-=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float subtractAmount[2]{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("operator*=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator*=(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{8.0f, 12.0f});

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{32.0f, 48.0f});
	}
	SECTION("operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator*=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float multiplyAmount[2]{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkVec2fValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("operator==(const Vec2f& other)") {
		slm::Vec2f test{1.0f, 2.0f};
		slm::Vec2f test2{1.0f, 2.0f};

		CHECK(test == test2);

		test2.x(3.0f);

		CHECK(!(test == test2));

		test.x(3.0f);

		CHECK(test == test2);

		test2.y(3.0f);

		CHECK(!(test == test2));
	}
	SECTION("operator==(const std::array<float, 2>& other)") {
		slm::Vec2f test{1.0f, 2.0f};
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
		slm::Vec2f test{1.0f, 2.0f};
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
		slm::Vec2f test{1.0f, 2.0f};
		slm::Vec2f test2{1.0f, 2.0f};

		CHECK(!(test != test2));

		test2.x(3.0f);

		CHECK(test != test2);

		test.x(3.0f);

		CHECK(!(test != test2));

		test2.y(3.0f);

		CHECK(test != test2);
	}
	SECTION("operator!=(const std::array<float, 2>& other)") {
		slm::Vec2f test{1.0f, 2.0f};
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
		slm::Vec2f test{1.0f, 2.0f};
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
		slm::Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsFloat();

		helpers::checkFloatValues(values[0], 1.0f);
		helpers::checkFloatValues(values[1], 2.0f);
	}
	SECTION("getValsAsInt()") {
		slm::Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("getValsAsUint()") {
		slm::Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsUint();

		CHECK(values[0] == 1u);
		CHECK(values[1] == 2u);
	}
}




///////////
// Vec2i //
///////////

TEST_CASE("Vec2i") {
	SECTION("Vec2i()") {
		slm::Vec2i test{};

		CHECK(test == std::array<int32_t, 2>{0, 0});
	}
	SECTION("Vec2i(const int32_t vals[2])") {
		int32_t testValues[2] = {0, 0};

		slm::Vec2i test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1;
		testValues[1] = 2;

		test = slm::Vec2i{testValues};

		CHECK(test == testValues);

		testValues[0] = -1;
		testValues[1] = -2;

		test = slm::Vec2i{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2i(const std::array<int32_t, 2>& vals)") {
		std::array<int32_t, 2> testValues = {0, 0};

		slm::Vec2i test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1;
		testValues[1] = 2;

		test = slm::Vec2i{testValues};

		CHECK(test == testValues);

		testValues[0] = -1;
		testValues[1] = -2;

		test = slm::Vec2i{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2i(const int32_t x, const int32_t y)") {
		int32_t testX = 0;
		int32_t testY = 0;

		slm::Vec2i test{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});

		testX = 1;
		testY = 2;

		test = slm::Vec2i{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});

		testX = -1;
		testY = -2;

		test = slm::Vec2i{testX, testY};

		CHECK(test == std::array<int32_t, 2>{testX, testY});
	}
	SECTION("x(const int32_t x) && x()") {
		slm::Vec2i test{15, 30};

		CHECK(test.x() == 15);

		test.x(150);

		CHECK(test.x() == 150);
	}
	SECTION("y(const int32_t y) && y()") {
		slm::Vec2i test{15, 30};

		CHECK(test.y() == 30);

		test.y(300);

		CHECK(test.y() == 300);
	}
	SECTION("translate(const Vec2i& amount)") {
		slm::Vec2i test{1, 2};
		const slm::Vec2i translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translate(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{1, 2};
		const std::array<int32_t, 2> translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translate(const int32_t amount[2])") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount[2]{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("translateX(const int32_t amount)") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount{3};

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 2});

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 2});
	}
	SECTION("translateY(const int32_t amount)") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount{4};

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 6});

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 10});
	}
	SECTION("rotate(const int32_t degreesCounterClockwise)") {
		slm::Vec2i test{1, 0};
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
		slm::Vec2i test{2, 3};
		const slm::Vec2i scaleAmount{3, 4};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scale(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 9});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 27});
	}
	SECTION("scale(const float factors[2])") {
		slm::Vec2i test{2, 3};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scale(const std::array<float, 2>& factors)") {
		slm::Vec2i test{2, 3};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("scaleX(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 3});

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 3});
	}
	SECTION("scaleY(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 12});

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 48});
	}
	SECTION("operator[](const std::size_t idx)") {
		slm::Vec2i test{2, 3};

		CHECK(test[0] == 2);
		CHECK(test[1] == 3);

		test.x(10);
		test.y(20);

		CHECK(test[0] == 10);
		CHECK(test[1] == 20);
	}
	SECTION("operator+=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator+=(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<int32_t, 2> addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator+=(const int32_t amount[2])") {
		slm::Vec2i test{2, 3};
		const int32_t addAmount[2]{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("operator-=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator-=(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<int32_t, 2> subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator-=(const int32_t amount[2])") {
		slm::Vec2i test{2, 3};
		const int32_t subtractAmount[2]{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("operator*=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i multiplyAmount{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator*=(const float factor)") {
		slm::Vec2i test{2, 3};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 12});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 48});
	}
	SECTION("operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator*=(const float amount[2])") {
		slm::Vec2i test{2, 3};
		const float multiplyAmount[2]{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("operator==(const Vec2i& other)") {
		slm::Vec2i test{1, 2};
		slm::Vec2i test2{1, 2};

		CHECK(test == test2);

		test2.x(3);

		CHECK(!(test == test2));

		test.x(3);

		CHECK(test == test2);

		test2.y(3);

		CHECK(!(test == test2));
	}
	SECTION("operator==(const std::array<int32_t, 2>& other)") {
		slm::Vec2i test{1, 2};
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
		slm::Vec2i test{1, 2};
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
		slm::Vec2i test{1, 2};
		slm::Vec2i test2{1, 2};

		CHECK(!(test != test2));

		test2.x(3);

		CHECK(test != test2);

		test.x(3);

		CHECK(!(test != test2));

		test2.y(3);

		CHECK(test != test2);
	}
	SECTION("operator!=(const std::array<int32_t, 2>& other)") {
		slm::Vec2i test{1, 2};
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
		slm::Vec2i test{1, 2};
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
		slm::Vec2i test{1, 2};

		const auto values = test.getValsAsFloat();

		helpers::checkFloatValues(values[0], 1.0f);
		helpers::checkFloatValues(values[1], 2.0f);
	}
	SECTION("getValsAsInt()") {
		slm::Vec2i test{1, 2};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("getValsAsUint()") {
		slm::Vec2i test{1, 2};

		const auto values = test.getValsAsUint();

		CHECK(values[0] == 1u);
		CHECK(values[1] == 2u);
	}
}




///////////
// Vec2u //
///////////

TEST_CASE("Vec2u") {
	SECTION("Vec2u()") {
		slm::Vec2u test{};

		CHECK(test == std::array<uint32_t, 2>{0u, 0u});
	}
	SECTION("Vec2u(const uint32_t vals[2])") {
		uint32_t testValues[2] = {0u, 0u};

		slm::Vec2u test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1u;
		testValues[1] = 2u;

		test = slm::Vec2u{testValues};

		CHECK(test == testValues);

		testValues[0] = 10u;
		testValues[1] = 20u;

		test = slm::Vec2u{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2u(const std::array<uint32_t, 2>& vals)") {
		std::array<uint32_t, 2> testValues = {0u, 0u};

		slm::Vec2u test{testValues};

		CHECK(test == testValues);

		testValues[0] = 1u;
		testValues[1] = 2u;

		test = slm::Vec2u{testValues};

		CHECK(test == testValues);

		testValues[0] = 10u;
		testValues[1] = 20u;

		test = slm::Vec2u{testValues};

		CHECK(test == testValues);
	}
	SECTION("Vec2u(const uint32_t x, const uint32_t y)") {
		uint32_t testX = 0u;
		uint32_t testY = 0u;

		slm::Vec2u test{testX, testY};

		CHECK(test == std::array<uint32_t, 2>{testX, testY});

		testX = 1u;
		testY = 2u;

		test = slm::Vec2u{testX, testY};

		CHECK(test == std::array<uint32_t, 2>{testX, testY});

		testX = 10u;
		testY = 20u;

		test = slm::Vec2u{testX, testY};

		CHECK(test == std::array<uint32_t, 2>{testX, testY});
	}
	SECTION("x(const uint32_t x) && x()") {
		slm::Vec2u test{15u, 30u};

		CHECK(test.x() == 15u);

		test.x(150u);

		CHECK(test.x() == 150u);
	}
	SECTION("y(const uint32_t y) && y()") {
		slm::Vec2u test{15u, 30u};

		CHECK(test.y() == 30u);

		test.y(300u);

		CHECK(test.y() == 300u);
	}
	SECTION("translate(const Vec2u& amount)") {
		slm::Vec2u test{1u, 2u};
		const slm::Vec2u translateAmount{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("translate(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{1u, 2u};
		const std::array<uint32_t, 2> translateAmount{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("translate(const uint32_t amount[2])") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount[2]{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("translateX(const uint32_t amount)") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount{3};

		test.translateX(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 2u});

		test.translateX(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 2u});
	}
	SECTION("translateY(const uint32_t amount)") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount{4u};

		test.translateY(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{1u, 6u});

		test.translateY(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{1u, 10u});
	}
	SECTION("rotate(const int32_t degreesCounterClockwise)") {
		slm::Vec2u test{1u, 0u};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		CHECK(test == std::array<uint32_t, 2>{0u, 1u});
	}
	SECTION("scale(const Vec2& amount)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u scaleAmount{3u, 4u};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("scale(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 9u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 27u});
	}
	SECTION("scale(const float factors[2])") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("scale(const std::array<float, 2>& factors)") {
		slm::Vec2u test{2u, 3u};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("scaleX(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 3u});

		test.scaleX(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 3u});
	}
	SECTION("scaleY(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{2u, 12u});

		test.scaleY(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{2u, 48u});
	}
	SECTION("operator[](const std::size_t idx)") {
		slm::Vec2u test{2u, 3u};

		CHECK(test[0] == 2u);
		CHECK(test[1] == 3u);

		test.x(10u);
		test.y(20u);

		CHECK(test[0] == 10u);
		CHECK(test[1] == 20u);
	}
	SECTION("operator+=(const Vec2& other)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u addAmount{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("operator+=(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{2u, 3u};
		const std::array<uint32_t, 2> addAmount{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("operator+=(const uint32_t amount[2])") {
		slm::Vec2u test{2u, 3u};
		const uint32_t addAmount[2]{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("operator-=(const Vec2& other)") {
		slm::Vec2u test{20u, 30u};
		const slm::Vec2u subtractAmount{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("operator-=(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{20u, 30u};
		const std::array<uint32_t, 2> subtractAmount{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("operator-=(const uint32_t amount[2])") {
		slm::Vec2u test{20u, 30u};
		const uint32_t subtractAmount[2]{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("operator*=(const Vec2& other)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u multiplyAmount{4u, 5u};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("operator*=(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 12u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 48u});
	}
	SECTION("operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2u test{2u, 3u};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("operator*=(const float amount[2])") {
		slm::Vec2u test{2u, 3u};
		const float multiplyAmount[2]{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("operator==(const Vec2u& other)") {
		slm::Vec2u test{1u, 2u};
		slm::Vec2u test2{1u, 2u};

		CHECK(test == test2);

		test2.x(3u);

		CHECK(!(test == test2));

		test.x(3u);

		CHECK(test == test2);

		test2.y(3u);

		CHECK(!(test == test2));
	}
	SECTION("operator==(const std::array<uint32_t, 2>& other)") {
		slm::Vec2u test{1u, 2u};
		std::array<uint32_t, 2> values{1u, 2u};

		CHECK(test == values);

		values[0] = 3u;

		CHECK(!(test == values));

		test.x(3u);

		CHECK(test == values);

		values[1] = 3u;

		CHECK(!(test == values));
	}
	SECTION("operator==(const uint32_t other[2])") {
		slm::Vec2u test{1u, 2u};
		uint32_t values[2]{1u, 2u};

		CHECK(test == values);

		values[0] = 3u;

		CHECK(!(test == values));

		test.x(3u);

		CHECK(test == values);

		values[1] = 3u;

		CHECK(!(test == values));
	}
	SECTION("operator!=(const Vec2u& other)") {
		slm::Vec2u test{1u, 2u};
		slm::Vec2u test2{1u, 2u};

		CHECK(!(test != test2));

		test2.x(3u);

		CHECK(test != test2);

		test.x(3u);

		CHECK(!(test != test2));

		test2.y(3u);

		CHECK(test != test2);
	}
	SECTION("operator!=(const std::array<uint32_t, 2>& other)") {
		slm::Vec2u test{1u, 2u};
		std::array<uint32_t, 2> values{1u, 2u};

		CHECK(!(test != values));

		values[0] = 3u;

		CHECK(test != values);

		test.x(3u);

		CHECK(!(test != values));

		values[1] = 3u;

		CHECK(test != values);
	}
	SECTION("operator!=(const uint32_t other[2])") {
		slm::Vec2u test{1u, 2u};
		uint32_t values[2]{1u, 2u};

		CHECK(!(test != values));

		values[0] = 3u;

		CHECK(test != values);

		test.x(3u);

		CHECK(!(test != values));

		values[1] = 3u;

		CHECK(test != values);
	}
	SECTION("getValsAsFloat()") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsFloat();

		helpers::checkFloatValues(values[0], 1.0f);
		helpers::checkFloatValues(values[1], 2.0f);
	}
	SECTION("getValsAsInt()") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("getValsAsUint()") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsUint();

		CHECK(values[0] == 1u);
		CHECK(values[1] == 2u);
	}
}