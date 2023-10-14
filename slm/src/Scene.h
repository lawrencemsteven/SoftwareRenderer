#pragma once

#include "VecT.h"

namespace slm {

	template <class T>
	class Scene {
	public:
		Scene()	 = default;
		~Scene() = default;

		uint32_t getSize() const {
			return m_objects.size();
		}

		template <class U>
		void translateAll(U amount) {
			for (auto& object : m_objects) {
				object.translate(amount);
			}
		}
		void rotateAll(int degreesCounterClockwise) {
			for (auto& object : m_objects) {
				object.rotate(degreesCounterClockwise);
			}
		}
		void scaleAll(float factor) {
			for (auto& object : m_objects) {
				object.scale(factor);
			}
		}

		template <class T>
		void clip(const T& viewport) {
			// Cohen-Sutherland Clipping Algorithm
			std::vector<std::pair<uint8_t, uint8_t>> pointLocInfo{};
			pointLocInfo.resize(getSize());

			// Classify point Locations
			for (int i = 0; i < getSize(); i++) {
				uint8_t locInfo[2] = {0b0000, 0b0000};
				for (int j = 0; j < 2; j++) {
					if (m_objects[i][j].x() < viewport.getLeft()) {
						locInfo[j] = locInfo[j] | 0b0001;
					}
					else if (m_objects[i][j].x() > viewport.getRight()) {
						locInfo[j] = locInfo[j] | 0b0010;
					}
					if (m_objects[i][j].y() < viewport.getBottom()) {
						locInfo[j] = locInfo[j] | 0b0100;
					}
					else if (m_objects[i][j].y() > viewport.getTop()) {
						locInfo[j] = locInfo[j] | 0b1000;
					}
				}
				pointLocInfo[i].first  = locInfo[0];
				pointLocInfo[i].second = locInfo[1];
			}

			// Remove Outside Lines
			for (int i = 0; i < getSize(); i++) {
				if ((pointLocInfo[i].first & pointLocInfo[i].second) != 0) {
					m_objects.erase(std::next(m_objects.begin(), i));
					pointLocInfo.erase(std::next(pointLocInfo.begin(), i));
					i -= 1;
				}
			}

			// Clip Remaining Lines
			for (int i = 0; i < getSize(); i++) {
				if ((pointLocInfo[i].first & 0b0001) != 0) {
					const auto xPos = viewport.getLeft();
					const auto yPos = m_objects[i].getYAtX(xPos);
					m_objects[i][0].x(xPos);
					m_objects[i][0].y(yPos);
					pointLocInfo[i].first = pointLocInfo[i].first & 0b1110;
				}
				else if ((pointLocInfo[i].first & 0b0010) != 0) {
					const auto xPos = viewport.getRight();
					const auto yPos = m_objects[i].getYAtX(xPos);
					m_objects[i][0].x(xPos);
					m_objects[i][0].y(yPos);
					pointLocInfo[i].first = pointLocInfo[i].first & 0b1101;
				}
				if ((pointLocInfo[i].second & 0b0001) != 0) {
					const auto xPos = viewport.getLeft();
					const auto yPos = m_objects[i].getYAtX(xPos);
					m_objects[i][1].x(xPos);
					m_objects[i][1].y(yPos);
					pointLocInfo[i].second = pointLocInfo[i].second & 0b1110;
				}
				else if ((pointLocInfo[i].second & 0b0010) != 0) {
					const auto xPos = viewport.getRight();
					const auto yPos = m_objects[i].getYAtX(xPos);
					m_objects[i][1].x(xPos);
					m_objects[i][1].y(yPos);
					pointLocInfo[i].second = pointLocInfo[i].second & 0b1101;
				}
				if ((pointLocInfo[i].first & 0b1000) != 0) {
					const auto yPos = viewport.getTop();
					const auto xPos = m_objects[i].getXAtY(yPos);
					m_objects[i][0].x(xPos);
					m_objects[i][0].y(yPos);
					pointLocInfo[i].first = pointLocInfo[i].first & 0b0111;
				}
				else if ((pointLocInfo[i].first & 0b0100) != 0) {
					const auto yPos = viewport.getBottom();
					const auto xPos = m_objects[i].getXAtY(yPos);
					m_objects[i][0].x(xPos);
					m_objects[i][0].y(yPos);
					pointLocInfo[i].first = pointLocInfo[i].first & 0b1011;
				}
				if ((pointLocInfo[i].second & 0b1000) != 0) {
					const auto yPos = viewport.getTop();
					const auto xPos = m_objects[i].getXAtY(yPos);
					m_objects[i][1].x(xPos);
					m_objects[i][1].y(yPos);
					pointLocInfo[i].second = pointLocInfo[i].second & 0b0111;
				}
				else if ((pointLocInfo[i].second & 0b0100) != 0) {
					const auto yPos = viewport.getBottom();
					const auto xPos = m_objects[i].getXAtY(yPos);
					m_objects[i][1].x(xPos);
					m_objects[i][1].y(yPos);
					pointLocInfo[i].second = pointLocInfo[i].second & 0b1011;
				}

				uint8_t locInfo[2] = {0b0000, 0b0000};
				for (int j = 0; j < 2; j++) {
					if (m_objects[i][j].x() < viewport.getLeft()) {
						locInfo[j] = locInfo[j] | 0b0001;
					}
					else if (m_objects[i][j].x() > viewport.getRight()) {
						locInfo[j] = locInfo[j] | 0b0010;
					}
					if (m_objects[i][j].y() < viewport.getBottom()) {
						locInfo[j] = locInfo[j] | 0b0100;
					}
					else if (m_objects[i][j].y() > viewport.getTop()) {
						locInfo[j] = locInfo[j] | 0b1000;
					}
				}
				pointLocInfo[i].first  = locInfo[0];
				pointLocInfo[i].second = locInfo[1];

				if ((pointLocInfo[i].first & pointLocInfo[i].second) != 0) {
					m_objects.erase(std::next(m_objects.begin(), i));
					pointLocInfo.erase(std::next(pointLocInfo.begin(), i));
					i -= 1;
				}
			}
		}

		void addObject(T object) {
			m_objects.push_back(object);
		}

		const T& operator[](std::size_t idx) const {
			return m_objects[idx];
		}

		template <class T>
		void printPostscript(const T& viewport) {
			translateAll(slm::vec2i{-viewport.getLeft(), -viewport.getBottom()});

			std::cout << "%!PS\n\n0.1 setlinewidth\n\n%%BeginSetup\n  << /PageSize ["
					  << viewport.getWidth() << " " << viewport.getHeight()
					  << "] >> setpagedevice\n%%EndSetup\n\n%%%BEGIN\n";
			for (const auto& object : m_objects) {
				std::cout << object.toPostscript();
			}
			std::cout << "0 sg\n%%%END\n";

			translateAll(slm::vec2i{viewport.getLeft(), viewport.getBottom()});
		}

	private:
		std::vector<T> m_objects{};
	};

}