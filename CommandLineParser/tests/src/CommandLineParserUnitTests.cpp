#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "CommandLineParser.h"

TEST_CASE("CommandLineParser") {
	SECTION("Creation") {
		CommandLineParser clp{0, nullptr};
		REQUIRE(true);
	}

	SECTION("Three Arguments") {
		const char* testArgs[] = {"./test", "-a", "5", "-b", "arg2", "-c", "5.04"};
		int testArgsSize	   = 7;

		CommandLineParser clp{testArgsSize, testArgs};

		int a		  = clp.getValueOr("-a", 10);
		std::string b = clp.getValueOr("-b", std::string{"default"});
		float c		  = clp.getValueOr("-c", 10.05f);

		CHECK(a == 5);
		CHECK(b.compare("arg2") == 0);
		CHECK_THAT(c, Catch::Matchers::WithinAbs(5.04, 0.01));
	}

	SECTION("Default Values") {
		const char* testArgs[] = {"./test"};
		int testArgsSize	   = 1;

		CommandLineParser clp{testArgsSize, testArgs};

		int a		  = clp.getValueOr("-a", 10);
		std::string b = clp.getValueOr("-b", std::string{"default"});
		float c		  = clp.getValueOr("-c", 10.05f);

		CHECK(a == 10);
		CHECK(b.compare("default") == 0);
		CHECK_THAT(c, Catch::Matchers::WithinAbs(10.05, 0.01));
	}
}