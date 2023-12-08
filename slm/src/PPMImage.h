#pragma once

#include "Primitive.h"

namespace slm {

	//////////////
	// PBMImage //
	//////////////

	class PPMImage {
	public:
		PPMImage(const slm::AxisAlignedBox2u& outputWindow);

		void setColorResolution(const uint32_t colorResolution);
		uint32_t getColorResolution();
		void setPixel(const std::size_t x, const std::size_t y, const float red, const float green,
					  const float blue);
		const std::array<float, 3>& getColor(const std::size_t x, const std::size_t y) const;

		friend std::ostream& operator<<(std::ostream& os, const PPMImage& image) {
			os << "P3\n"
			   << image.m_width << " " << image.m_height << "\n"
			   << image.m_colorResolution << "\n";
			for (std::size_t yVal = 0; yVal < image.m_height; yVal++) {
				for (std::size_t xVal = 0; xVal < image.m_width; xVal++) {
					const auto color = image.getColor(xVal, yVal);
					os << static_cast<uint32_t>(color[0] * image.m_colorResolution) << " "
					   << static_cast<uint32_t>(color[1] * image.m_colorResolution) << " "
					   << static_cast<uint32_t>(color[2] * image.m_colorResolution) << " ";
				}
				os << "\n";
			}

			return os;
		}

	private:
		std::vector<std::array<float, 3>> m_pixels{};
		uint32_t m_width{};
		uint32_t m_height{};
		uint32_t m_colorResolution{20};

		std::size_t getLocation(const std::size_t x, const std::size_t y) const;
	};




	/////////////////
	// DepthBuffer //
	/////////////////

	class DepthBuffer {
	public:
		DepthBuffer(const slm::AxisAlignedBox2u& outputWindow);

		void setZVal(const std::size_t x, const std::size_t y, const float zVal);
		float getZVal(const std::size_t x, const std::size_t y) const;

	private:
		std::vector<float> m_zVals{};
		uint32_t m_width{};
		uint32_t m_height{};

		std::size_t getLocation(const std::size_t x, const std::size_t y) const;
	};




	//////////////////////
	// ColorDepthBuffer //
	//////////////////////

	class ColorDepthBuffer {
	public:
		ColorDepthBuffer(const slm::AxisAlignedBox2u& outputWindow);

		void setPixel(const std::size_t x, const std::size_t y, const float zVal, const float red,
					  const float green, const float blue);
		std::pair<float, std::array<float, 3>> getPixel(const std::size_t x, const std::size_t y) const;

		void printPPMImage() const;

	private:
		DepthBuffer m_depthBuffer;
		PPMImage m_ppmImage;
	};
}