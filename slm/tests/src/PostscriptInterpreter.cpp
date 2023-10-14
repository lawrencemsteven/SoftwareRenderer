#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "slm.h"

TEST_CASE("PostscriptInterpreter") {
	const std::string filePath = static_cast<std::string>(TEST_ASSETS_FOLDER).append("/hw1.ps");
	// clang-format off
	const float expectedResult[21 * 4] =
		{
			0, 0, 499, 0,
			0, 499, 499, 499,
			0, 0, 0, 499,
			499, 0, 499, 499,
			260, 250, 300, 250,
			250, 260, 250, 300,
			240, 250, 200, 250,
			250, 240, 250, 200,
			260, 260, 300, 300,
			240, 260, 200, 300,
			260, 240, 300, 200,
			240, 240, 200, 200,
			10, 20, 20, 490,
			20, 490, 490, 480,
			490, 480, 480, 10,
			480, 10, 10, 20,
			-50, -50, 50, 50,
			-100, 250, 250, -100,
			600, 250, 250, -100,
			-100, 250, 250, 600,
			600, 250, 250, 600,
		};
	// clang-format on
	const int expectedSize{21};

	SECTION("PostScriptInterpreter") {
		slm::Scene<slm::LineT<slm::vec2f>> testScene =
			slm::PostscriptInterpreter::interpret<slm::vec2f>(filePath);

		CHECK(testScene.getSize() == expectedSize);

		for (int i = 0; i < expectedSize; i++) {
			CHECK_THAT(testScene[i][0][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4], 0.0001));
			CHECK_THAT(testScene[i][0][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 1], 0.0001));
			CHECK_THAT(testScene[i][1][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 2], 0.0001));
			CHECK_THAT(testScene[i][1][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 3], 0.0001));
		}
	}

	SECTION("Scene Translate") {
		slm::Scene<slm::LineT<slm::vec2f>> testScene =
			slm::PostscriptInterpreter::interpret<slm::vec2f>(filePath);

		testScene.translateAll(slm::vec2i{10, 20});

		for (int i = 0; i < expectedSize; i++) {
			CHECK_THAT(testScene[i][0][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4] + 10, 0.0001));
			CHECK_THAT(testScene[i][0][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 1] + 20, 0.0001));
			CHECK_THAT(testScene[i][1][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 2] + 10, 0.0001));
			CHECK_THAT(testScene[i][1][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 3] + 20, 0.0001));
		}
	}

	SECTION("Scene Scale") {
		slm::Scene<slm::LineT<slm::vec2f>> testScene =
			slm::PostscriptInterpreter::interpret<slm::vec2f>(filePath);

		testScene.scaleAll(0.5);

		for (int i = 0; i < expectedSize; i++) {
			CHECK_THAT(testScene[i][0][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4] * 0.5, 0.0001));
			CHECK_THAT(testScene[i][0][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 1] * 0.5, 0.0001));
			CHECK_THAT(testScene[i][1][0],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 2] * 0.5, 0.0001));
			CHECK_THAT(testScene[i][1][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 3] * 0.5, 0.0001));
		}
	}

	SECTION("Scene Rotate") {
		slm::Scene<slm::LineT<slm::vec2f>> testScene =
			slm::PostscriptInterpreter::interpret<slm::vec2f>(filePath);

		testScene.rotateAll(90);

		for (int i = 0; i < expectedSize; i++) {
			CHECK_THAT(testScene[i][0][0],
					   Catch::Matchers::WithinAbs(-expectedResult[i * 4 + 1], 0.0001));
			CHECK_THAT(testScene[i][0][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4], 0.0001));
			CHECK_THAT(testScene[i][1][0],
					   Catch::Matchers::WithinAbs(-expectedResult[i * 4 + 3], 0.0001));
			CHECK_THAT(testScene[i][1][1],
					   Catch::Matchers::WithinAbs(expectedResult[i * 4 + 2], 0.0001));
		}
	}
}