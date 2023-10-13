#include <catch2/catch_test_macros.hpp>

#include "slm.h"

TEST_CASE("VecT") {
	SECTION("Vec2") {
		slm::VecT<int, 2> test{};
		slm::VecT<int, 2> test2{1, 2};

		CHECK(test.x() == 0);
		CHECK(test.y() == 0);

		CHECK(test2.x() == 1);
		CHECK(test2.y() == 2);

		CHECK(test[0] == 0);
		CHECK(test[1] == 0);

		CHECK(test2[0] == 1);
		CHECK(test2[1] == 2);
	}
}