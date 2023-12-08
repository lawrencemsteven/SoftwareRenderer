#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "HelperFunctions.h"
#include "PPMImage.h"

//////////////
// PBMImage //
//////////////

TEST_CASE("PPMImage") {
	const slm::AxisAlignedBox2u defaultWindow{0, 0, 50, 50};
	SECTION("PPMImage(const slm::AxisAlignedBox2u& outputWindow)") {
		SECTION("Default Value") {
			slm::PPMImage test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto color = test.getColor(xVal, yVal);
					helpers::checkValues(color[0], 0.0f);
					helpers::checkValues(color[1], 0.0f);
					helpers::checkValues(color[2], 0.0f);
				}
			}
		}
	}
	SECTION("void setPixel(const std::size_t x, const std::size_t y, const float red, const float "
			"green, const float blue)") {
		SECTION("Set all colors") {
			slm::PPMImage test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					test.setPixel(xVal, yVal, 5.0f, 10.0f, 15.0f);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto color = test.getColor(xVal, yVal);
					helpers::checkValues(color[0], 5.0f);
					helpers::checkValues(color[1], 10.0f);
					helpers::checkValues(color[2], 15.0f);
				}
			}
		}
	}
	SECTION(
		"const std::array<float, 3>& getColor(const std::size_t x, const std::size_t y) const") {
		SECTION("Wrapping Getter") {
			slm::PPMImage test{defaultWindow};

			test.setPixel(0u, 0u, 5u, 10u, 15u);

			auto color = test.getColor(50u, 50u);
			helpers::checkValues(color[0], 5.0f);
			helpers::checkValues(color[1], 10.0f);
			helpers::checkValues(color[2], 15.0f);
		}
	}
	SECTION("std::ostream& operator<<(std::ostream& os)") {
		slm::PPMImage test{defaultWindow};

		test.setPixel(1u, 0u, 5.0f, 10.0f, 15.0f);

		// std::cout << test;
	}
}




/////////////////
// DepthBuffer //
/////////////////

TEST_CASE("DepthBuffer") {
	const slm::AxisAlignedBox2u defaultWindow{0, 0, 50, 50};
	SECTION("DepthBuffer(const slm::AxisAlignedBox2u& outputWindow)") {
		SECTION("Default Value") {
			slm::DepthBuffer test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal = test.getZVal(xVal, yVal);
					helpers::checkValues(zVal, -2.0f);
				}
			}
		}
	}
	SECTION("void setZVal(const std::size_t x, const std::size_t y, const float zVal)") {
		SECTION("Set all colors") {
			slm::DepthBuffer test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					test.setZVal(xVal, yVal, 1.5f);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal = test.getZVal(xVal, yVal);
					helpers::checkValues(zVal, 1.5f);
				}
			}
		}
	}
	SECTION("float getZVal(const std::size_t x, const std::size_t y) const") {
		SECTION("Wrapping Getter") {
			slm::DepthBuffer test{defaultWindow};

			test.setZVal(0u, 0u, 1.0f);

			auto zVal = test.getZVal(50u, 50u);
			helpers::checkValues(zVal, 1.0f);
		}
	}
}




//////////////////////
// ColorDepthBuffer //
//////////////////////

TEST_CASE("ColorDepthBuffer") {
	const slm::AxisAlignedBox2u defaultWindow{0, 0, 50, 50};
	SECTION("ColorDepthBuffer(const slm::AxisAlignedBox2u& outputWindow)") {
		slm::ColorDepthBuffer test{defaultWindow};

		for (std::size_t yVal = 0; yVal < 50; yVal++) {
			for (std::size_t xVal = 0; xVal < 50; xVal++) {
				const auto pixel = test.getPixel(xVal, yVal);
				const auto zVal	 = pixel.first;
				const auto color = pixel.second;
				helpers::checkValues(zVal, -2.0f);
				helpers::checkValues(color[0], 0.0f);
				helpers::checkValues(color[1], 0.0f);
				helpers::checkValues(color[2], 0.0f);
			}
		}
	}
	SECTION("void setPixel(const std::size_t x, const std::size_t y, const float zVal, const float "
			"red, const float green, const float blue)") {
		SECTION("Set All Pixels") {
			slm::ColorDepthBuffer test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal					 = -0.5f;
					const std::array<float, 3> color = {0.2f, 0.4f, 0.6f};
					test.setPixel(xVal, yVal, zVal, color[0], color[1], color[2]);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto pixel = test.getPixel(xVal, yVal);
					const auto zVal	 = pixel.first;
					const auto color = pixel.second;
					helpers::checkValues(zVal, -0.5f);
					helpers::checkValues(color[0], 0.2f);
					helpers::checkValues(color[1], 0.4f);
					helpers::checkValues(color[2], 0.6f);
				}
			}
		}
		SECTION("Ignore Pixels Behind") {
			slm::ColorDepthBuffer test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal					 = -0.5f;
					const std::array<float, 3> color = {0.2f, 0.4f, 0.6f};
					test.setPixel(xVal, yVal, zVal, color[0], color[1], color[2]);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal					 = -0.6f;
					const std::array<float, 3> color = {1.0f, 1.0f, 1.0f};
					test.setPixel(xVal, yVal, zVal, color[0], color[1], color[2]);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto pixel = test.getPixel(xVal, yVal);
					const auto zVal	 = pixel.first;
					const auto color = pixel.second;
					helpers::checkValues(zVal, -0.5f);
					helpers::checkValues(color[0], 0.2f);
					helpers::checkValues(color[1], 0.4f);
					helpers::checkValues(color[2], 0.6f);
				}
			}
		}
		SECTION("Don't Ignore Pixels In Front") {
			slm::ColorDepthBuffer test{defaultWindow};

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal					 = -0.5f;
					const std::array<float, 3> color = {0.2f, 0.4f, 0.6f};
					test.setPixel(xVal, yVal, zVal, color[0], color[1], color[2]);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto zVal					 = -0.4f;
					const std::array<float, 3> color = {1.0f, 1.0f, 1.0f};
					test.setPixel(xVal, yVal, zVal, color[0], color[1], color[2]);
				}
			}

			for (std::size_t yVal = 0; yVal < 50; yVal++) {
				for (std::size_t xVal = 0; xVal < 50; xVal++) {
					const auto pixel = test.getPixel(xVal, yVal);
					const auto zVal	 = pixel.first;
					const auto color = pixel.second;
					helpers::checkValues(zVal, -0.4f);
					helpers::checkValues(color[0], 1.0f);
					helpers::checkValues(color[1], 1.0f);
					helpers::checkValues(color[2], 1.0f);
				}
			}
		}
	}
	SECTION("std::pair<float, std::array<float, 3>> getPixel(const std::size_t x, const "
			"std::size_t y) const") {
		SECTION("Check Specific Pixel") {
			slm::ColorDepthBuffer test{defaultWindow};

			test.setPixel(1, 0, -0.5f, 1.0f, 0.8f, 0.6f);

			const auto pixel = test.getPixel(1, 0);
			const auto zVal	 = pixel.first;
			const auto color = pixel.second;
			helpers::checkValues(zVal, -0.5f);
			helpers::checkValues(color[0], 1.0f);
			helpers::checkValues(color[1], 0.8f);
			helpers::checkValues(color[2], 0.6f);
		}
	}
	SECTION("void printPPMImage() const") {}
}