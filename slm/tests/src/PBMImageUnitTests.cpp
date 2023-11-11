#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "slm.h"

TEST_CASE("PBMImage") {
	const std::string filePath = static_cast<std::string>(TEST_ASSETS_FOLDER).append("/hw3.ps");
	const std::size_t expectedSize = 8;

	SECTION("PBMImage") {
		slm::Scene<slm::vec2f> testScene =
			slm::PostscriptInterpreter::interpret<slm::vec2f>(filePath);

		slm::Viewport<int, 2> viewport{{0, 0}, {499, 499}};
		slm::Viewport<int, 2> window{{0, 0}, {500, 500}};

		testScene.scaleAll(1.0f);
		testScene.translateAll(slm::vec2i{0, 0});
		testScene.rotateAll(0);

		testScene.clip(window);

		//testScene.printPBM(window, viewport);
	}
}