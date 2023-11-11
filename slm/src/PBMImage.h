#pragma once

namespace slm {

	class PBMImage {
	public:
		enum class Colors : bool { WHITE = 0, BLACK = 1 };

		PBMImage()
			: PBMImage(501, 501) {}
		PBMImage(uint32_t width, uint32_t height) {
			m_width	 = width;
			m_height = height;
			m_image	 = new std::vector<Colors>(m_width * m_height, Colors::WHITE);
		}
		~PBMImage() {
			delete m_image;
		}
		PBMImage(const PBMImage&)			 = delete;
		PBMImage(PBMImage&&)				 = default;
		PBMImage& operator=(const PBMImage&) = delete;
		PBMImage& operator=(PBMImage&&)		 = default;

		uint32_t getWidth() const {
			return m_width;
		}
		uint32_t getHieght() const {
			return m_height;
		}

		void printImage() const {
			std::cout << "P1\n" << m_width << " " << m_height << std::endl;

			uint32_t counter = 0;

			for (std::size_t i = m_height; i > 0; i--) {
				for (std::size_t j = 0; j < m_width; j++) {
					std::cout << static_cast<bool>(m_image->at(convert2DTo1D(
										 static_cast<uint32_t>(j), static_cast<uint32_t>(i-1))))
								  << " ";
					counter += 1;
					if (counter >= 30) {
						std::cout << "\n";
						counter = 0;
					}
				}
				counter = 0;
				std::cout << "\n";
			}
		}

		void setPixel(uint32_t x, uint32_t y, Colors color) {
			m_image->at(convert2DTo1D(x, y)) = color;
		}

	private:
		uint32_t m_width{};
		uint32_t m_height{};
		std::vector<Colors>* m_image;

		uint32_t convert2DTo1D(uint32_t x, uint32_t y) const {
			return y * m_height + x;
		}
	};

}