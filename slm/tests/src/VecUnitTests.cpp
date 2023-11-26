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

		helpers::checkValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkValues(test, testValues);
	}
	SECTION("Vec2f(const std::array<float, 2>& vals)") {
		std::array<float, 2> testValues = {0.0f, 0.0f};

		slm::Vec2f test{testValues};

		helpers::checkValues(test, testValues);

		testValues[0] = 1.0f;
		testValues[1] = 2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkValues(test, testValues);

		testValues[0] = -1.0f;
		testValues[1] = -2.0f;

		test = slm::Vec2f{testValues};

		helpers::checkValues(test, testValues);
	}
	SECTION("Vec2f(const float x, const float y)") {
		float testX = 0.0f;
		float testY = 0.0f;

		slm::Vec2f test{testX, testY};

		helpers::checkValues(test, std::array<float, 2>{testX, testY});

		testX = 1.0f;
		testY = 2.0f;

		test = slm::Vec2f{testX, testY};

		helpers::checkValues(test, std::array<float, 2>{testX, testY});

		testX = -1.0f;
		testY = -2.0f;

		test = slm::Vec2f{testX, testY};

		helpers::checkValues(test, std::array<float, 2>{testX, testY});
	}
	SECTION("void x(const float x)") {
		slm::Vec2f test{15.0f, 30.0f};

		helpers::checkValues(test, 15.0f, 30.0f);

		test.x(150.0f);

		helpers::checkValues(test, 150.0f, 30.0f);
	}
	SECTION("void y(const float y)") {
		slm::Vec2f test{15.0f, 30.0f};

		helpers::checkValues(test.y(), 30.0f);

		test.y(300.0f);

		helpers::checkValues(test.y(), 300.0f);
	}
	SECTION("float x() const") {
		{
			slm::Vec2f test{15.0f, 30.0f};

			helpers::checkValues(test.x(), 15.0f);
		}
		{
			slm::Vec2f test{150.0f, 30.0f};

			helpers::checkValues(test.x(), 150.0f);
		}
	}
	SECTION("float y() const") {
		{
			slm::Vec2f test{15.0f, 30.0f};

			helpers::checkValues(test.y(), 30.0f);
		}
		{
			slm::Vec2f test{15.0f, 300.0f};

			helpers::checkValues(test.y(), 300.0f);
		}
	}
	SECTION("BitLocation insideBox(const AxisAlignedBox2u& box) const") {
		slm::AxisAlignedBox2u testBox{1u, 1u, 3u, 3u};

		slm::Vec2f test{2.0f, 2.0f};
		slm::BitLocation loc = test.insideBox(testBox);
		CHECK(loc.inside());
		helpers::checkValues(loc, false, false, false, false);

		test.x(4.0f);
		test.y(2.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, false, false, false, true);

		test.x(0.0f);
		test.y(2.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, false, false, true, false);

		test.x(2.0f);
		test.y(4.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, true, false, false, false);

		test.x(2.0f);
		test.y(0.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, false, true, false, false);

		test.x(0.0f);
		test.y(0.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, false, true, true, false);

		test.x(0.0f);
		test.y(4.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, true, false, true, false);

		test.x(4.0f);
		test.y(4.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, true, false, false, true);

		test.x(4.0f);
		test.y(0.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.outside());
		helpers::checkValues(loc, false, true, false, true);

		test.x(2.0f);
		test.y(2.0f);
		loc = test.insideBox(testBox);
		CHECK(loc.inside());
		helpers::checkValues(loc, false, false, false, false);
	}
	SECTION("void translate(const Vec2f& amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const slm::Vec2f translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("void translate(const std::array<float, 2>& amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const std::array<float, 2> translateAmount{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("void translate(const float amount[2])") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount[2]{3.0f, 4.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{4.0f, 6.0f});

		test.translate(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{7.0f, 10.0f});
	}
	SECTION("void translateX(const float amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount{3.0f};

		test.translateX(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{4.0f, 2.0f});

		test.translateX(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{7.0f, 2.0f});
	}
	SECTION("void translateY(const float amount)") {
		slm::Vec2f test{1.0f, 2.0f};
		const float translateAmount{4.0f};

		test.translateY(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{1.0f, 6.0f});

		test.translateY(translateAmount);

		helpers::checkValues(test, std::array<float, 2>{1.0f, 10.0f});
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::Vec2f test{1.0f, 0.0f};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		helpers::checkValues(test, std::array<float, 2>{0.0f, 1.0f});

		test.rotate(rotateAmount);

		helpers::checkValues(test, std::array<float, 2>{-1.0f, 0.0f});

		test.rotate(rotateAmount);

		helpers::checkValues(test, std::array<float, 2>{0.0f, -1.0f});

		test.rotate(rotateAmount);

		helpers::checkValues(test, std::array<float, 2>{1.0f, 0.0f});
	}
	SECTION("void scale(const Vec2& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("scale(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{6.0f, 9.0f});

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{18.0f, 27.0f});
	}
	SECTION("void scale(const float factors[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("void scale(const std::array<float, 2>& factors)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{6.0f, 12.0f});

		test.scale(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{18.0f, 48.0f});
	}
	SECTION("void scaleX(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{6.0f, 3.0f});

		test.scaleX(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{18.0f, 3.0f});
	}
	SECTION("void scaleY(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{2, 12});

		test.scaleY(scaleAmount);

		helpers::checkValues(test, std::array<float, 2>{2, 48});
	}
	SECTION("float operator[](const std::size_t idx) const") {
		slm::Vec2f test{2.0f, 3.0f};

		helpers::checkValues(test[0], 2.0f);
		helpers::checkValues(test[1], 3.0f);

		test.x(10.0f);
		test.y(20.0f);

		helpers::checkValues(test[0], 10.0f);
		helpers::checkValues(test[1], 20.0f);
	}
	SECTION("Vec2f& operator+=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f addAmount{4.0f, 5.0f};

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("Vec2f& operator+=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> addAmount{4.0f, 5.0f};

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("Vec2f& operator+=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float addAmount[2]{4.0f, 5.0f};

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{6.0f, 8.0f});

		test += addAmount;

		helpers::checkValues(test, std::array<float, 2>{10.0f, 13.0f});
	}
	SECTION("Vec2f& operator-=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("Vec2f& operator-=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> subtractAmount{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("Vec2f& operator-=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float subtractAmount[2]{4.0f, 5.0f};

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-2.0f, -2.0f});

		test -= subtractAmount;

		helpers::checkValues(test, std::array<float, 2>{-6.0f, -7.0f});
	}
	SECTION("Vec2f& operator*=(const Vec2& other)") {
		slm::Vec2f test{2.0f, 3.0f};
		const slm::Vec2f multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("Vec2f& operator*=(const float factor)") {
		slm::Vec2f test{2.0f, 3.0f};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{8.0f, 12.0f});

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{32.0f, 48.0f});
	}
	SECTION("Vec2f& operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2f test{2.0f, 3.0f};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("Vec2f& operator*=(const float amount[2])") {
		slm::Vec2f test{2.0f, 3.0f};
		const float multiplyAmount[2]{4.0f, 5.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{8.0f, 15.0f});

		test *= multiplyAmount;

		helpers::checkValues(test, std::array<float, 2>{32.0f, 75.0f});
	}
	SECTION("bool operator==(const Vec2f& other) const") {
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
	SECTION("bool operator==(const std::array<float, 2>& other) const") {
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
	SECTION("bool operator==(const float other[2]) const") {
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
	SECTION("bool operator!=(const Vec2f& other) const") {
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
	SECTION("bool operator!=(const std::array<float, 2>& other) const") {
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
	SECTION("bool operator!=(const float other[2]) const") {
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
	SECTION("std::array<float, 2> getValsAsFloat() const override") {
		slm::Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsFloat();

		helpers::checkValues(values[0], 1.0f);
		helpers::checkValues(values[1], 2.0f);
	}
	SECTION("std::array<int32_t, 2> getValsAsInt() const override") {
		slm::Vec2f test{1.0f, 2.0f};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("std::array<uint32_t, 2> getValsAsUint() const override") {
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
	SECTION("void x(const int32_t x)") {
		slm::Vec2i test{15, 30};

		CHECK(test.x() == 15);

		test.x(150);

		CHECK(test.x() == 150);
	}
	SECTION("void y(const int32_t y)") {
		slm::Vec2i test{15, 30};

		CHECK(test.y() == 30);

		test.y(300);

		CHECK(test.y() == 300);
	}
	SECTION("int32_t x() const") {
		{
			slm::Vec2i test{15, 30};

			CHECK(test.x() == 15);
		}
		{
			slm::Vec2i test{150, 30};

			CHECK(test.x() == 150);
		}
	}
	SECTION("int32_t y() const") {
		{
			slm::Vec2i test{15, 30};

			CHECK(test.y() == 30);
		}
		{
			slm::Vec2i test{15, 300};

			CHECK(test.y() == 300);
		}
	}
	SECTION("void translate(const Vec2i& amount)") {
		slm::Vec2i test{1, 2};
		const slm::Vec2i translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("void translate(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{1, 2};
		const std::array<int32_t, 2> translateAmount{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("void translate(const int32_t amount[2])") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount[2]{3, 4};

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 6});

		test.translate(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 10});
	}
	SECTION("void translateX(const int32_t amount)") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount{3};

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{4, 2});

		test.translateX(translateAmount);

		CHECK(test == std::array<int32_t, 2>{7, 2});
	}
	SECTION("void translateY(const int32_t amount)") {
		slm::Vec2i test{1, 2};
		const int32_t translateAmount{4};

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 6});

		test.translateY(translateAmount);

		CHECK(test == std::array<int32_t, 2>{1, 10});
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
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
	SECTION("void scale(const Vec2& amount)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i scaleAmount{3, 4};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("void scale(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 9});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 27});
	}
	SECTION("void scale(const float factors[2])") {
		slm::Vec2i test{2, 3};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("void scale(const std::array<float, 2>& factors)") {
		slm::Vec2i test{2, 3};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 12});

		test.scale(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 48});
	}
	SECTION("void scaleX(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{6, 3});

		test.scaleX(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{18, 3});
	}
	SECTION("void scaleY(const float factor)") {
		slm::Vec2i test{2, 3};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 12});

		test.scaleY(scaleAmount);

		CHECK(test == std::array<int32_t, 2>{2, 48});
	}
	SECTION("int32_t operator[](const std::size_t idx) const") {
		slm::Vec2i test{2, 3};

		CHECK(test[0] == 2);
		CHECK(test[1] == 3);

		test.x(10);
		test.y(20);

		CHECK(test[0] == 10);
		CHECK(test[1] == 20);
	}
	SECTION("Vec2i& operator+=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("Vec2i& operator+=(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<int32_t, 2> addAmount{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("Vec2i& operator+=(const int32_t amount[2])") {
		slm::Vec2i test{2, 3};
		const int32_t addAmount[2]{4, 5};

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{6, 8});

		test += addAmount;

		CHECK(test == std::array<int32_t, 2>{10, 13});
	}
	SECTION("Vec2i& operator-=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("Vec2i& operator-=(const std::array<int32_t, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<int32_t, 2> subtractAmount{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("Vec2i& operator-=(const int32_t amount[2])") {
		slm::Vec2i test{2, 3};
		const int32_t subtractAmount[2]{4, 5};

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-2, -2});

		test -= subtractAmount;

		CHECK(test == std::array<int32_t, 2>{-6, -7});
	}
	SECTION("Vec2i& operator*=(const Vec2& other)") {
		slm::Vec2i test{2, 3};
		const slm::Vec2i multiplyAmount{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("Vec2i& operator*=(const float factor)") {
		slm::Vec2i test{2, 3};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 12});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 48});
	}
	SECTION("Vec2i& operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2i test{2, 3};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("Vec2i& operator*=(const float amount[2])") {
		slm::Vec2i test{2, 3};
		const float multiplyAmount[2]{4, 5};

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{8, 15});

		test *= multiplyAmount;

		CHECK(test == std::array<int32_t, 2>{32, 75});
	}
	SECTION("bool operator==(const Vec2i& other) const") {
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
	SECTION("bool operator==(const std::array<int32_t, 2>& other) const") {
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
	SECTION("bool operator==(const int32_t other[2]) const") {
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
	SECTION("bool operator!=(const Vec2i& other) const") {
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
	SECTION("bool operator!=(const std::array<int32_t, 2>& other) const") {
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
	SECTION("bool operator!=(const int32_t other[2]) const") {
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
	SECTION("std::array<float, 2> getValsAsFloat() const override") {
		slm::Vec2i test{1, 2};

		const auto values = test.getValsAsFloat();

		helpers::checkValues(values[0], 1.0f);
		helpers::checkValues(values[1], 2.0f);
	}
	SECTION("std::array<int32_t, 2> getValsAsInt() const override") {
		slm::Vec2i test{1, 2};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("std::array<uint32_t, 2> getValsAsUint() const override") {
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
	SECTION("void x(const uint32_t x)") {
		slm::Vec2u test{15u, 30u};

		CHECK(test.x() == 15u);

		test.x(150u);

		CHECK(test.x() == 150u);
	}
	SECTION("void y(const uint32_t y)") {
		slm::Vec2u test{15u, 30u};

		CHECK(test.y() == 30u);

		test.y(300u);

		CHECK(test.y() == 300u);
	}
	SECTION("uint32_t x() const") {
		{
			slm::Vec2u test{15u, 30u};

			CHECK(test.x() == 15u);
		}
		{
			slm::Vec2u test{150u, 30u};

			CHECK(test.x() == 150u);
		}
	}
	SECTION("uint32_t y() const") {
		{
			slm::Vec2u test{15u, 30u};

			CHECK(test.y() == 30u);
		}
		{
			slm::Vec2u test{15u, 300u};

			CHECK(test.y() == 300u);
		}
	}
	SECTION("void translate(const Vec2u& amount)") {
		slm::Vec2u test{1u, 2u};
		const slm::Vec2u translateAmount{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("void translate(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{1u, 2u};
		const std::array<uint32_t, 2> translateAmount{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("void translate(const uint32_t amount[2])") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount[2]{3u, 4u};

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 6u});

		test.translate(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 10u});
	}
	SECTION("void translateX(const uint32_t amount)") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount{3};

		test.translateX(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{4u, 2u});

		test.translateX(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{7u, 2u});
	}
	SECTION("void translateY(const uint32_t amount)") {
		slm::Vec2u test{1u, 2u};
		const uint32_t translateAmount{4u};

		test.translateY(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{1u, 6u});

		test.translateY(translateAmount);

		CHECK(test == std::array<uint32_t, 2>{1u, 10u});
	}
	SECTION("void rotate(const int32_t degreesCounterClockwise)") {
		slm::Vec2u test{1u, 0u};
		int32_t rotateAmount{90};

		test.rotate(rotateAmount);

		CHECK(test == std::array<uint32_t, 2>{0u, 1u});
	}
	SECTION("void scale(const Vec2& amount)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u scaleAmount{3u, 4u};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("void scale(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{3.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 9u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 27u});
	}
	SECTION("void scale(const float factors[2])") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount[2]{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("void scale(const std::array<float, 2>& factors)") {
		slm::Vec2u test{2u, 3u};
		const std::array<float, 2> scaleAmount{3.0f, 4.0f};

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 12u});

		test.scale(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 48u});
	}
	SECTION("void scaleX(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{3.0f};

		test.scaleX(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{6u, 3u});

		test.scaleX(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{18u, 3u});
	}
	SECTION("void scaleY(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float scaleAmount{4.0f};

		test.scaleY(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{2u, 12u});

		test.scaleY(scaleAmount);

		CHECK(test == std::array<uint32_t, 2>{2u, 48u});
	}
	SECTION("uint32_t operator[](const std::size_t idx) const") {
		slm::Vec2u test{2u, 3u};

		CHECK(test[0] == 2u);
		CHECK(test[1] == 3u);

		test.x(10u);
		test.y(20u);

		CHECK(test[0] == 10u);
		CHECK(test[1] == 20u);
	}
	SECTION("Vec2u& operator+=(const Vec2& other)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u addAmount{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("Vec2u& operator+=(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{2u, 3u};
		const std::array<uint32_t, 2> addAmount{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("Vec2u& operator+=(const uint32_t amount[2])") {
		slm::Vec2u test{2u, 3u};
		const uint32_t addAmount[2]{4u, 5u};

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{6u, 8u});

		test += addAmount;

		CHECK(test == std::array<uint32_t, 2>{10u, 13u});
	}
	SECTION("Vec2u& operator-=(const Vec2& other)") {
		slm::Vec2u test{20u, 30u};
		const slm::Vec2u subtractAmount{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("Vec2u& operator-=(const std::array<uint32_t, 2>& amount)") {
		slm::Vec2u test{20u, 30u};
		const std::array<uint32_t, 2> subtractAmount{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("Vec2u& operator-=(const uint32_t amount[2])") {
		slm::Vec2u test{20u, 30u};
		const uint32_t subtractAmount[2]{4u, 5u};

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{16u, 25u});

		test -= subtractAmount;

		CHECK(test == std::array<uint32_t, 2>{12u, 20u});
	}
	SECTION("Vec2u& operator*=(const Vec2& other)") {
		slm::Vec2u test{2u, 3u};
		const slm::Vec2u multiplyAmount{4u, 5u};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("Vec2u& operator*=(const float factor)") {
		slm::Vec2u test{2u, 3u};
		const float multiplyAmount{4.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 12u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 48u});
	}
	SECTION("Vec2u& operator*=(const std::array<float, 2>& amount)") {
		slm::Vec2u test{2u, 3u};
		const std::array<float, 2> multiplyAmount{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("Vec2u& operator*=(const float amount[2])") {
		slm::Vec2u test{2u, 3u};
		const float multiplyAmount[2]{4.0f, 5.0f};

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{8u, 15u});

		test *= multiplyAmount;

		CHECK(test == std::array<uint32_t, 2>{32u, 75u});
	}
	SECTION("bool operator==(const Vec2u& other) const") {
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
	SECTION("bool operator==(const std::array<uint32_t, 2>& other) const") {
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
	SECTION("bool operator==(const uint32_t other[2]) const") {
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
	SECTION("bool operator!=(const Vec2u& other) const") {
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
	SECTION("bool operator!=(const std::array<uint32_t, 2>& other) const") {
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
	SECTION("bool operator!=(const uint32_t other[2]) const") {
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
	SECTION("std::array<float, 2> getValsAsFloat() const override") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsFloat();

		helpers::checkValues(values[0], 1.0f);
		helpers::checkValues(values[1], 2.0f);
	}
	SECTION("std::array<int32_t, 2> getValsAsInt() const override") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsInt();

		CHECK(values[0] == 1);
		CHECK(values[1] == 2);
	}
	SECTION("std::array<uint32_t, 2> getValsAsUint() const override") {
		slm::Vec2u test{1u, 2u};

		const auto values = test.getValsAsUint();

		CHECK(values[0] == 1u);
		CHECK(values[1] == 2u);
	}
}




///////////
// Vec3f //
///////////

TEST_CASE("Vec3f") {
	SECTION("Vec3f()") {
		slm::Vec3f test{};

		helpers::checkValues(test, 0.0f, 0.0f, 0.0f);
	}
	SECTION("Vec3f(const float vals[3])") {
		float testValues[3] = {1.0f, 2.0f, 3.0f};

		slm::Vec3f test{testValues};

		helpers::checkValues(test, 1.0f, 2.0f, 3.0f);
	}
	SECTION("Vec3f(const std::array<float, 3>& vals)") {
		std::array<float, 3> testValues = {1.0f, 2.0f, 3.0f};

		slm::Vec3f test{testValues};

		helpers::checkValues(test, 1.0f, 2.0f, 3.0f);
	}
	SECTION("Vec3f(const float x, const float y, const float z)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		helpers::checkValues(test, 1.0f, 2.0f, 3.0f);
	}
	SECTION("void x(const float x)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		test.x(4.0f);

		helpers::checkValues(test, 4.0f, 2.0f, 3.0f);
	}
	SECTION("void y(const float y)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		test.y(4.0f);

		helpers::checkValues(test, 1.0f, 4.0f, 3.0f);
	}
	SECTION("void z(const float z)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		test.z(4.0f);

		helpers::checkValues(test, 1.0f, 2.0f, 4.0f);
	}
	SECTION("float x() const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		helpers::checkValues(test.x(), 1.0f);
	}
	SECTION("float y() const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		helpers::checkValues(test.y(), 2.0f);
	}
	SECTION("float z() const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		helpers::checkValues(test.z(), 3.0f);
	}
	SECTION("void translate(const Vec3& amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const slm::Vec3f translateAmount{4.0f, 5.0f, 6.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test.translate(translateAmount);

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("void translate(const std::array<float, 3>& amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const std::array<float, 3> translateAmount{4.0f, 5.0f, 6.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test.translate(translateAmount);

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("void translate(const float amount[3])") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float translateAmount[3]{4.0f, 5.0f, 6.0f};

		test.translate(translateAmount);

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test.translate(translateAmount);

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("void translateX(const float amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float translateAmount{4.0f};

		test.translateX(translateAmount);

		helpers::checkValues(test, 5.0f, 2.0f, 3.0f);
	}
	SECTION("void translateY(const float amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float translateAmount{4.0f};

		test.translateY(translateAmount);

		helpers::checkValues(test, 1.0f, 6.0f, 3.0f);
	}
	SECTION("void translateZ(const float amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float translateAmount{4.0f};

		test.translateZ(translateAmount);

		helpers::checkValues(test, 1.0f, 2.0f, 7.0f);
	}
	SECTION("void scale(const Vec3& amount)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const slm::Vec3f scaleAmount{5.0f, 6.0f, 7.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);
	}
	SECTION("void scale(const float factor)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float scaleAmount{5.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10.0f, 15.0f, 20.0f);
	}
	SECTION("void scale(const float factors[3])") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float scaleAmount[3]{5.0f, 6.0f, 7.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);
	}
	SECTION("void scale(const std::array<float, 3>& factors)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const std::array<float, 3> scaleAmount{5.0f, 6.0f, 7.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);
	}
	SECTION("void scaleX(const float factor)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float scaleAmount{5.0f};

		test.scaleX(scaleAmount);

		helpers::checkValues(test, 10.0f, 3.0f, 4.0f);
	}
	SECTION("void scaleY(const float factor)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float scaleAmount{5.0f};

		test.scaleY(scaleAmount);

		helpers::checkValues(test, 2.0f, 15.0f, 4.0f);
	}
	SECTION("void scaleZ(const float factor)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float scaleAmount{5.0f};

		test.scaleZ(scaleAmount);

		helpers::checkValues(test, 2.0f, 3.0f, 20.0f);
	}
	SECTION("float operator[](const std::size_t idx) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		helpers::checkValues(test[0], 1.0f);
		helpers::checkValues(test[1], 2.0f);
		helpers::checkValues(test[2], 3.0f);

		test.x(10.0f);
		test.y(20.0f);
		test.z(30.0f);

		helpers::checkValues(test[0], 10.0f);
		helpers::checkValues(test[1], 20.0f);
		helpers::checkValues(test[2], 30.0f);
	}
	SECTION("Vec3f& operator+=(const Vec3& other)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const slm::Vec3f addAmount{4.0f, 5.0f, 6.0f};

		test += addAmount;

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test += addAmount;

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("Vec3f& operator+=(const std::array<float, 3>& amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const std::array<float, 3> addAmount{4.0f, 5.0f, 6.0f};

		test += addAmount;

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test += addAmount;

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("Vec3f& operator+=(const float amount[3])") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float addAmount[3]{4.0f, 5.0f, 6.0f};

		test += addAmount;

		helpers::checkValues(test, 5.0f, 7.0f, 9.0f);

		test += addAmount;

		helpers::checkValues(test, 9.0f, 12.0f, 15.0f);
	}
	SECTION("Vec3f& operator-=(const Vec3& other)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const slm::Vec3f subtractAmount{4.0f, 5.0f, 6.0f};

		test -= subtractAmount;

		helpers::checkValues(test, -3.0f, -3.0f, -3.0f);

		test -= subtractAmount;

		helpers::checkValues(test, -7.0f, -8.0f, -9.0f);
	}
	SECTION("Vec3f& operator-=(const std::array<float, 3>& amount)") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const std::array<float, 3> subtractAmount{4.0f, 5.0f, 6.0f};

		test -= subtractAmount;

		helpers::checkValues(test, -3.0f, -3.0f, -3.0f);

		test -= subtractAmount;

		helpers::checkValues(test, -7.0f, -8.0f, -9.0f);
	}
	SECTION("Vec3f& operator-=(const float amount[3])") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		const float subtractAmount[3]{4.0f, 5.0f, 6.0f};

		test -= subtractAmount;

		helpers::checkValues(test, -3.0f, -3.0f, -3.0f);

		test -= subtractAmount;

		helpers::checkValues(test, -7.0f, -8.0f, -9.0f);
	}
	SECTION("Vec3f& operator*=(const Vec3& other)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const slm::Vec3f multiplyAmount{5.0f, 6.0f, 7.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);

		test *= multiplyAmount;

		helpers::checkValues(test, 50.0f, 108.0f, 196.0f);
	}
	SECTION("Vec3f& operator*=(const float factor)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float multiplyAmount{5.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, 10.0f, 15.0f, 20.0f);

		test *= multiplyAmount;

		helpers::checkValues(test, 50.0f, 75.0f, 100.0f);
	}
	SECTION("Vec3f& operator*=(const std::array<float, 3>& amount)") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const std::array<float, 3> multiplyAmount{5.0f, 6.0f, 7.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);

		test *= multiplyAmount;

		helpers::checkValues(test, 50.0f, 108.0f, 196.0f);
	}
	SECTION("Vec3f& operator*=(const float amount[3])") {
		slm::Vec3f test{2.0f, 3.0f, 4.0f};
		const float multiplyAmount[3]{5.0f, 6.0f, 7.0f};

		test *= multiplyAmount;

		helpers::checkValues(test, 10.0f, 18.0f, 28.0f);

		test *= multiplyAmount;

		helpers::checkValues(test, 50.0f, 108.0f, 196.0f);
	}
	SECTION("bool operator==(const Vec3f& other) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		slm::Vec3f test2{1.0f, 2.0f, 3.0f};

		CHECK(test == test2);

		test2.x(4.0f);

		CHECK(!(test == test2));

		test.x(4.0f);

		CHECK(test == test2);

		test2.y(5.0f);

		CHECK(!(test == test2));

		test.y(5.0f);

		CHECK(test == test2);

		test2.z(6.0f);

		CHECK(!(test == test2));

		test.z(6.0f);

		CHECK(test == test2);
	}
	SECTION("bool operator==(const std::array<float, 3>& other) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		std::array<float, 3> test2{1.0f, 2.0f, 3.0f};

		CHECK(test == test2);

		test2[0] = 4.0f;

		CHECK(!(test == test2));

		test.x(4.0f);

		CHECK(test == test2);

		test2[1] = 5.0f;

		CHECK(!(test == test2));

		test.y(5.0f);

		CHECK(test == test2);

		test2[2] = 6.0f;

		CHECK(!(test == test2));

		test.z(6.0f);

		CHECK(test == test2);
	}
	SECTION("bool operator==(const float other[3]) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		float test2[3]{1.0f, 2.0f, 3.0f};

		CHECK(test == test2);

		test2[0] = 4.0f;

		CHECK(!(test == test2));

		test.x(4.0f);

		CHECK(test == test2);

		test2[1] = 5.0f;

		CHECK(!(test == test2));

		test.y(5.0f);

		CHECK(test == test2);

		test2[2] = 6.0f;

		CHECK(!(test == test2));

		test.z(6.0f);

		CHECK(test == test2);
	}
	SECTION("bool operator!=(const Vec3f& other) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		slm::Vec3f test2{1.0f, 2.0f, 3.0f};

		CHECK(!(test != test2));

		test2.x(4.0f);

		CHECK(test != test2);

		test.x(4.0f);

		CHECK(!(test != test2));

		test2.y(5.0f);

		CHECK(test != test2);

		test.y(5.0f);

		CHECK(!(test != test2));

		test2.z(6.0f);

		CHECK(test != test2);

		test.z(6.0f);

		CHECK(!(test != test2));
	}
	SECTION("bool operator!=(const std::array<float, 3>& other) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		std::array<float, 3> test2{1.0f, 2.0f, 3.0f};

		CHECK(!(test != test2));

		test2[0] = 4.0f;

		CHECK(test != test2);

		test.x(4.0f);

		CHECK(!(test != test2));

		test2[1] = 5.0f;

		CHECK(test != test2);

		test.y(5.0f);

		CHECK(!(test != test2));

		test2[2] = 6.0f;

		CHECK(test != test2);

		test.z(6.0f);

		CHECK(!(test != test2));
	}
	SECTION("bool operator!=(const float other[3]) const") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};
		float test2[3]{1.0f, 2.0f, 3.0f};

		CHECK(!(test != test2));

		test2[0] = 4.0f;

		CHECK(test != test2);

		test.x(4.0f);

		CHECK(!(test != test2));

		test2[1] = 5.0f;

		CHECK(test != test2);

		test.y(5.0f);

		CHECK(!(test != test2));

		test2[2] = 6.0f;

		CHECK(test != test2);

		test.z(6.0f);

		CHECK(!(test != test2));
	}
	SECTION("std::array<float, 3> getValsAsFloat() const override") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		const auto values = test.getValsAsFloat();

		helpers::checkValues(values[0], 1.0f);
		helpers::checkValues(values[1], 2.0f);
		helpers::checkValues(values[2], 3.0f);
	}
	SECTION("std::array<int32_t, 3> getValsAsInt() const override") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		const auto values = test.getValsAsInt();

		helpers::checkValues(values[0], 1);
		helpers::checkValues(values[1], 2);
		helpers::checkValues(values[2], 3);
	}
	SECTION("std::array<uint32_t, 3> getValsAsUint() const override") {
		slm::Vec3f test{1.0f, 2.0f, 3.0f};

		const auto values = test.getValsAsUint();

		helpers::checkValues(values[0], 1u);
		helpers::checkValues(values[1], 2u);
		helpers::checkValues(values[2], 3u);
	}
}




///////////
// Vec3i //
///////////

TEST_CASE("Vec3i") {
	SECTION("Vec3i()") {
		slm::Vec3i test{};

		helpers::checkValues(test, 0, 0, 0);
	}
	SECTION("Vec3i(const int32_t vals[3])") {
		const int32_t testValues[3] = {1, 2, 3};

		slm::Vec3i test{testValues};

		helpers::checkValues(test, 1, 2, 3);
	}
	SECTION("Vec3i(const std::array<int32_t, 3>& vals)") {
		const std::array<int32_t, 3> testValues = {1, 2, 3};

		slm::Vec3i test{testValues};

		helpers::checkValues(test, 1, 2, 3);
	}
	SECTION("Vec3i(const int32_t x, const int32_t y, const int32_t z)") {
		slm::Vec3i test{1, 2, 3};

		helpers::checkValues(test, 1, 2, 3);
	}
	SECTION("void x(const int32_t x)") {
		slm::Vec3i test{1, 2, 3};

		test.x(4);

		helpers::checkValues(test, 4, 2, 3);
	}
	SECTION("void y(const int32_t y)") {
		slm::Vec3i test{1, 2, 3};

		test.y(4);

		helpers::checkValues(test, 1, 4, 3);
	}
	SECTION("void z(const int32_t z)") {
		slm::Vec3i test{1, 2, 3};

		test.z(4);

		helpers::checkValues(test, 1, 2, 4);
	}
	SECTION("float x() const") {
		slm::Vec3i test{1, 2, 3};

		helpers::checkValues(test.x(), 1);

		test.x(4);

		helpers::checkValues(test.x(), 4);
	}
	SECTION("float y() const") {
		slm::Vec3i test{1, 2, 3};

		helpers::checkValues(test.y(), 2);

		test.y(4);

		helpers::checkValues(test.y(), 4);
	}
	SECTION("float z() const") {
		slm::Vec3i test{1, 2, 3};

		helpers::checkValues(test.z(), 3);

		test.z(4);

		helpers::checkValues(test.z(), 4);
	}
	SECTION("void translate(const Vec3& amount)") {
		slm::Vec3i test{1, 2, 3};
		const slm::Vec3i translateAmount{4, 5, 6};

		test.translate(translateAmount);

		helpers::checkValues(test, 5, 7, 9);

		test.translate(translateAmount);

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("void translate(const std::array<int32_t, 3>& amount)") {
		slm::Vec3i test{1, 2, 3};
		const std::array<int32_t, 3> translateAmount{4, 5, 6};

		test.translate(translateAmount);

		helpers::checkValues(test, 5, 7, 9);

		test.translate(translateAmount);

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("void translate(const int32_t amount[3])") {
		slm::Vec3i test{1, 2, 3};
		const int32_t translateAmount[3]{4, 5, 6};

		test.translate(translateAmount);

		helpers::checkValues(test, 5, 7, 9);

		test.translate(translateAmount);

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("void translateX(const int32_t amount)") {
		slm::Vec3i test{1, 2, 3};
		const int32_t translateAmount = 4;

		test.translateX(translateAmount);

		helpers::checkValues(test, 5, 2, 3);

		test.translateX(translateAmount);

		helpers::checkValues(test, 9, 2, 3);
	}
	SECTION("void translateY(const int32_t amount)") {
		slm::Vec3i test{1, 2, 3};
		const int32_t translateAmount = 4;

		test.translateY(translateAmount);

		helpers::checkValues(test, 1, 6, 3);

		test.translateY(translateAmount);

		helpers::checkValues(test, 1, 10, 3);
	}
	SECTION("void translateZ(const int32_t amount)") {
		slm::Vec3i test{1, 2, 3};
		const int32_t translateAmount = 4;

		test.translateZ(translateAmount);

		helpers::checkValues(test, 1, 2, 7);

		test.translateZ(translateAmount);

		helpers::checkValues(test, 1, 2, 11);
	}
	SECTION("void scale(const Vec3& amount)") {
		slm::Vec3i test{2, 3, 4};
		const slm::Vec3i scaleAmount{5, 6, 7};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10, 18, 28);

		test.scale(scaleAmount);

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("void scale(const float factor)") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount{5};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10, 15, 20);

		test.scale(scaleAmount);

		helpers::checkValues(test, 50, 75, 100);
	}
	SECTION("void scale(const float factors[3])") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount[3]{5.0f, 6.0f, 7.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10, 18, 28);

		test.scale(scaleAmount);

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("void scale(const std::array<float, 3>& factors)") {
		slm::Vec3i test{2, 3, 4};
		const std::array<float, 3> scaleAmount{5.0f, 6.0f, 7.0f};

		test.scale(scaleAmount);

		helpers::checkValues(test, 10, 18, 28);

		test.scale(scaleAmount);

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("void scaleX(const float factor)") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount{5};

		test.scaleX(scaleAmount);

		helpers::checkValues(test, 10, 3, 4);

		test.scaleX(scaleAmount);

		helpers::checkValues(test, 50, 3, 4);
	}
	SECTION("void scaleY(const float factor)") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount{5};

		test.scaleY(scaleAmount);

		helpers::checkValues(test, 2, 15, 4);

		test.scaleY(scaleAmount);

		helpers::checkValues(test, 2, 75, 4);
	}
	SECTION("void scaleZ(const float factor)") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount{5};

		test.scaleZ(scaleAmount);

		helpers::checkValues(test, 2, 3, 20);

		test.scaleZ(scaleAmount);

		helpers::checkValues(test, 2, 3, 100);
	}
	SECTION("float operator[](const std::size_t idx) const") {
		slm::Vec3i test{1, 2, 3};

		CHECK(test[0] == 1);
		CHECK(test[1] == 2);
		CHECK(test[2] == 3);

		test.x(10);
		test.y(20);
		test.z(30);

		CHECK(test[0] == 10);
		CHECK(test[1] == 20);
		CHECK(test[2] == 30);
	}
	SECTION("Vec3i& operator+=(const Vec3& other)") {
		slm::Vec3i test{1, 2, 3};
		const slm::Vec3i addAmount{4, 5, 6};

		test += addAmount;

		helpers::checkValues(test, 5, 7, 9);

		test += addAmount;

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("Vec3i& operator+=(const std::array<int32_t, 3>& amount)") {
		slm::Vec3i test{1, 2, 3};
		const std::array<int32_t, 3> addAmount{4, 5, 6};

		test += addAmount;

		helpers::checkValues(test, 5, 7, 9);

		test += addAmount;

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("Vec3i& operator+=(const int32_t amount[3])") {
		slm::Vec3i test{1, 2, 3};
		const int32_t addAmount[3]{4, 5, 6};

		test += addAmount;

		helpers::checkValues(test, 5, 7, 9);

		test += addAmount;

		helpers::checkValues(test, 9, 12, 15);
	}
	SECTION("Vec3i& operator-=(const Vec3& other)") {
		slm::Vec3i test{1, 2, 3};
		const slm::Vec3i subtractAmount{4, 5, 6};

		test -= subtractAmount;

		helpers::checkValues(test, -3, -3, -3);

		test -= subtractAmount;

		helpers::checkValues(test, -7, -8, -9);
	}
	SECTION("Vec3i& operator-=(const std::array<int32_t, 3>& amount)") {
		slm::Vec3i test{1, 2, 3};
		const std::array<int32_t, 3> subtractAmount{4, 5, 6};

		test -= subtractAmount;

		helpers::checkValues(test, -3, -3, -3);

		test -= subtractAmount;

		helpers::checkValues(test, -7, -8, -9);
	}
	SECTION("Vec3i& operator-=(const int32_t amount[3])") {
		slm::Vec3i test{1, 2, 3};
		const int32_t subtractAmount[3]{4, 5, 6};

		test -= subtractAmount;

		helpers::checkValues(test, -3, -3, -3);

		test -= subtractAmount;

		helpers::checkValues(test, -7, -8, -9);
	}
	SECTION("Vec3i& operator*=(const Vec3& other)") {
		slm::Vec3i test{2, 3, 4};
		const slm::Vec3i scaleAmount{5, 6, 7};

		test *= scaleAmount;

		helpers::checkValues(test, 10, 18, 28);

		test *= scaleAmount;

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("Vec3i& operator*=(const float factor)") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount = 5;

		test *= scaleAmount;

		helpers::checkValues(test, 10, 15, 20);

		test *= scaleAmount;

		helpers::checkValues(test, 50, 75, 100);
	}
	SECTION("Vec3i& operator*=(const std::array<float, 3>& amount)") {
		slm::Vec3i test{2, 3, 4};
		const std::array<float, 3> scaleAmount{5, 6, 7};

		test *= scaleAmount;

		helpers::checkValues(test, 10, 18, 28);

		test *= scaleAmount;

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("Vec3i& operator*=(const float amount[3])") {
		slm::Vec3i test{2, 3, 4};
		const float scaleAmount[3]{5, 6, 7};

		test *= scaleAmount;

		helpers::checkValues(test, 10, 18, 28);

		test *= scaleAmount;

		helpers::checkValues(test, 50, 108, 196);
	}
	SECTION("bool operator==(const Vec3i& other) const") {
		slm::Vec3i test{1, 2, 3};
		slm::Vec3i test2{1, 2, 3};

		CHECK(test == test2);

		test2.x(4);

		CHECK(!(test == test2));

		test.x(4);

		CHECK(test == test2);

		test2.y(5);

		CHECK(!(test == test2));

		test.y(5);

		CHECK(test == test2);

		test2.z(6);

		CHECK(!(test == test2));

		test.z(6);

		CHECK(test == test2);
	}
	SECTION("bool operator==(const std::array<int32_t, 3>& other) const") {
		slm::Vec3i test{1, 2, 3};
		std::array<int32_t, 3> test2{1, 2, 3};

		CHECK(test == test2);

		test2[0] = 4;

		CHECK(!(test == test2));

		test.x(4);

		CHECK(test == test2);

		test2[1] = 5;

		CHECK(!(test == test2));

		test.y(5);

		CHECK(test == test2);

		test2[2] = 6;

		CHECK(!(test == test2));

		test.z(6);

		CHECK(test == test2);
	}
	SECTION("bool operator==(const int32_t other[3]) const") {
		slm::Vec3i test{1, 2, 3};
		int32_t test2[3]{1, 2, 3};

		CHECK(test == test2);

		test2[0] = 4;

		CHECK(!(test == test2));

		test.x(4);

		CHECK(test == test2);

		test2[1] = 5;

		CHECK(!(test == test2));

		test.y(5);

		CHECK(test == test2);

		test2[2] = 6;

		CHECK(!(test == test2));

		test.z(6);

		CHECK(test == test2);
	}
	SECTION("bool operator!=(const Vec3i& other) const") {
		slm::Vec3i test{1, 2, 3};
		slm::Vec3i test2{1, 2, 3};

		CHECK(!(test != test2));

		test2.x(4);

		CHECK(test != test2);

		test.x(4);

		CHECK(!(test != test2));

		test2.y(5);

		CHECK(test != test2);

		test.y(5);

		CHECK(!(test != test2));

		test2.z(6);

		CHECK(test != test2);

		test.z(6);

		CHECK(!(test != test2));
	}
	SECTION("bool operator!=(const std::array<int32_t, 3>& other) const") {
		slm::Vec3i test{1, 2, 3};
		std::array<int32_t, 3> test2{1, 2, 3};

		CHECK(!(test != test2));

		test2[0] = 4;

		CHECK(test != test2);

		test.x(4);

		CHECK(!(test != test2));

		test2[1] = 5;

		CHECK(test != test2);

		test.y(5);

		CHECK(!(test != test2));

		test2[2] = 6;

		CHECK(test != test2);

		test.z(6);

		CHECK(!(test != test2));
	}
	SECTION("bool operator!=(const int32_t other[3]) const") {
		slm::Vec3i test{1, 2, 3};
		int32_t test2[3]{1, 2, 3};

		CHECK(!(test != test2));

		test2[0] = 4;

		CHECK(test != test2);

		test.x(4);

		CHECK(!(test != test2));

		test2[1] = 5;

		CHECK(test != test2);

		test.y(5);

		CHECK(!(test != test2));

		test2[2] = 6;

		CHECK(test != test2);

		test.z(6);

		CHECK(!(test != test2));
	}
	SECTION("std::array<float, 3> getValsAsFloat() const override") {
		slm::Vec3i test{1, 2, 3};

		const auto values = test.getValsAsFloat();

		helpers::checkValues(values[0], 1.0f);
		helpers::checkValues(values[1], 2.0f);
		helpers::checkValues(values[2], 3.0f);
	}
	SECTION("std::array<int32_t, 3> getValsAsInt() const override") {
		slm::Vec3i test{1, 2, 3};

		const auto values = test.getValsAsInt();

		helpers::checkValues(values[0], 1);
		helpers::checkValues(values[1], 2);
		helpers::checkValues(values[2], 3);
	}
	SECTION("std::array<uint32_t, 3> getValsAsUint() const override") {
		slm::Vec3i test{1, 2, 3};

		const auto values = test.getValsAsUint();

		helpers::checkValues(values[0], 1u);
		helpers::checkValues(values[1], 2u);
		helpers::checkValues(values[2], 3u);
	}
}