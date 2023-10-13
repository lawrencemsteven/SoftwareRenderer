#include <catch2/catch_test_macros.hpp>

#include "slm.h"

TEST_CASE("Line") {
	SECTION("Line Creation") {
		slm::LineT<slm::VecT<int, 2>> test{};

		CHECK(test.getStart().x() == 0);
		CHECK(test.getStart().y() == 0);
		CHECK(test.getEnd().x() == 0);
		CHECK(test.getEnd().y() == 0);

		CHECK(test[0][0] == 0);
		CHECK(test[0][1] == 0);
		CHECK(test[1][0] == 0);
		CHECK(test[1][1] == 0);

		slm::LineT<slm::VecT<int, 2>> test2{{1, 2}, {3, 4}};

		CHECK(test2.getStart().x() == 1);
		CHECK(test2.getStart().y() == 2);
		CHECK(test2.getEnd().x() == 3);
		CHECK(test2.getEnd().y() == 4);

		CHECK(test2[0][0] == 1);
		CHECK(test2[0][1] == 2);
		CHECK(test2[1][0] == 3);
		CHECK(test2[1][1] == 4);
	}
}