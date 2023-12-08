#include "PPMImage.h"

namespace slm {

	//////////////
	// PBMImage //
	//////////////

	PPMImage::PPMImage(const slm::AxisAlignedBox2u& outputWindow)
		: m_width{outputWindow.getWidth()},
		  m_height{outputWindow.getHeight()} {
		const auto windowArea					= m_width * m_height;
		const std::array<float, 3> defaultColor = {0.0f, 0.0f, 0.0f};
		m_pixels.resize(windowArea, defaultColor);
	}

	void PPMImage::setColorResolution(const uint32_t colorResolution) {
		m_colorResolution = colorResolution;
	}

	uint32_t PPMImage::getColorResolution() {
		return m_colorResolution;
	}

	void PPMImage::setPixel(const std::size_t x, const std::size_t y, const float red,
							const float green, const float blue) {
		const auto location = getLocation(x, y);
		const std::array<float, 3> colors{red, green, blue};
		m_pixels[location] = colors;
	}

	const std::array<float, 3>& PPMImage::getColor(const std::size_t x, const std::size_t y) const {
		const auto location = getLocation(x, y);
		return m_pixels[location];
	}

	std::size_t PPMImage::getLocation(const std::size_t x, const std::size_t y) const {
		return m_height * (y % m_height) + (x % m_width);
	}




	/////////////////
	// DepthBuffer //
	/////////////////

	DepthBuffer::DepthBuffer(const slm::AxisAlignedBox2u& bufferSize)
		: m_width{bufferSize.getWidth()},
		  m_height{bufferSize.getHeight()} {
		const auto windowArea = m_width * m_height;
		m_zVals.resize(windowArea, -2.0f);
	}

	void DepthBuffer::setZVal(const std::size_t x, const std::size_t y, const float zVal) {
		const auto location = getLocation(x, y);
		m_zVals[location]	= zVal;
	}

	float DepthBuffer::getZVal(const std::size_t x, const std::size_t y) const {
		const auto location = getLocation(x, y);
		return m_zVals[location];
	}

	std::size_t DepthBuffer::getLocation(const std::size_t x, const std::size_t y) const {
		return m_height * (y % m_height) + (x % m_width);
	}




	//////////////////////
	// ColorDepthBuffer //
	//////////////////////

	ColorDepthBuffer::ColorDepthBuffer(const slm::AxisAlignedBox2u& outputWindow)
		: m_depthBuffer{outputWindow},
		  m_ppmImage{outputWindow} {}

	void ColorDepthBuffer::setPixel(const std::size_t x, const std::size_t y, const float zVal,
									const float red, const float green, const float blue) {
		if (zVal > m_depthBuffer.getZVal(x, y)) {
			m_depthBuffer.setZVal(x, y, zVal);
			m_ppmImage.setPixel(x, y, red, green, blue);
		}
	}

	std::pair<float, std::array<float, 3>> ColorDepthBuffer::getPixel(const std::size_t x,
																	  const std::size_t y) const {
		const auto zVal	 = m_depthBuffer.getZVal(x, y);
		const auto color = m_ppmImage.getColor(x, y);
		return std::pair<float, std::array<float, 3>>{zVal, color};
	}

	void ColorDepthBuffer::printPPMImage() const {
		std::cout << m_ppmImage;
	}
}