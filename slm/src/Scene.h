#pragma once

#include "Clipping.h"
#include "VecT.h"
#include "LineT.h"
#include "PolygonT.h"
#include "PBMImage.h"

namespace slm {

	template <class T>
	class Scene {
	public:
		Scene()	 = default;
		~Scene() = default;

		uint32_t getNumLines() const {
			return m_lines.size();
		}
		uint32_t getNumPolygons() const {
			return m_polygons.size();
		}

		template <class U>
		void translateAll(U amount) {
			for (auto& line : m_lines) {
				line.translate(amount);
			}
			for (auto& polygon : m_polygons) {
				polygon.translate(amount);
			}
		}
		void rotateAll(int degreesCounterClockwise) {
			for (auto& line : m_lines) {
				line.rotate(degreesCounterClockwise);
			}
			for (auto& polygon : m_polygons) {
				polygon.rotate(degreesCounterClockwise);
			}
		}
		void scaleAll(float factor) {
			for (auto& line : m_lines) {
				line.scale(factor);
			}
			for (auto& polygon : m_polygons) {
				polygon.scale(factor);
			}
		}

		template <class U>
		void clip(const U& viewport) {
			for (std::size_t i = 0; i < m_lines.size(); i++) {
				const auto clipped = m_lines[i].clip(viewport);
				if (clipped == ClippingStatus::Outside) {
					m_lines.erase(std::next(m_lines.begin(), i));
					i -= 1;
				}
			}
			for (std::size_t i = 0; i < m_polygons.size(); i++) {
				const auto clipped = m_polygons[i].clip(viewport);
				if (clipped == ClippingStatus::Outside) {
					m_polygons.erase(std::next(m_polygons.begin(), i));
					i -= 1;
				}
			}
		}

		void addLine(LineT<T> line) {
			m_lines.push_back(std::move(line));
		}
		void addPolygon(PolygonT<T> polygon) {
			m_polygons.push_back(std::move(polygon));
		}

		const std::vector<LineT<T>>& getLines() const {
			return m_lines;
		}
		const std::vector<PolygonT<T>>& getPolygons() const {
			return m_polygons;
		}

		template <class U>
		void printPostscript(const U& viewport) {
			translateAll(slm::vec2i{-viewport.getLeft(), -viewport.getBottom()});

			std::cout << "%!PS\n\n0.1 setlinewidth\n\n%%BeginSetup\n  << /PageSize ["
					  << viewport.getWidth() << " " << viewport.getHeight()
					  << "] >> setpagedevice\n%%EndSetup\n\n%%%BEGIN\n";
			for (const auto& line : m_lines) {
				std::cout << line.toPostscript();
			}
			for (const auto& polygon : m_polygons) {
				std::cout << polygon.toPostscript();
			}
			std::cout << "0 setgray\n%%%END\n";

			translateAll(slm::vec2i{viewport.getLeft(), viewport.getBottom()});
		}

		template <class U>
		void printPBM(const U& window, const U& viewport) {
			PBMImage pbmImage{};

			auto newPolygons = getPolygonsConvertedToInts();
			const slm::vec2i firstTranslateAmount{-window.getLeft(), -window.getBottom()};
			const float scaleXAmount{static_cast<float>(viewport.getWidth()) /
									 static_cast<float>(window.getWidth())};
			const float scaleYAmount{static_cast<float>(viewport.getHeight()) /
									 static_cast<float>(window.getHeight())};
			const slm::vec2i secondTranslateAmount{viewport.getLeft(), viewport.getBottom()};

			for (auto& polygon : newPolygons) {
				polygon.translate(firstTranslateAmount);
				polygon.scaleX(scaleXAmount);
				polygon.scaleY(scaleYAmount);
				polygon.translate(secondTranslateAmount);
			}

			// Iterate over each scanline
			slm::LineT<vec2i> scanline{{0, 0}, {static_cast<int>(pbmImage.getWidth() - 1), 0}};
			for (std::size_t pbmVerticalIndex = viewport.getBottom();
				 pbmVerticalIndex <= viewport.getTop(); pbmVerticalIndex++) {

				// Iterate over each polygon
				for (const auto& polygon : newPolygons) {
					std::vector<slm::vec2i> intersectionPoints =
						polygon.lineCollissionPoints(scanline);

					if (intersectionPoints.size() > 0) {
						// Iterate over each intersection
						std::size_t intersectionPointsIndex = 0;
						for (std::size_t pbmHorizontalIndex =
								 intersectionPoints[intersectionPointsIndex].x();
							 pbmHorizontalIndex < viewport.getWidth() - 1; pbmHorizontalIndex++) {
							pbmImage.setPixel(pbmHorizontalIndex, pbmVerticalIndex,
											  PBMImage::Colors::BLACK);
							if (pbmHorizontalIndex > 490) {
								int x = 5;
							}
							// If we hit an intersection point
							if (static_cast<int>(intersectionPointsIndex) < static_cast<int>(intersectionPoints.size()) - 1 &&
								intersectionPoints[intersectionPointsIndex + 1].x() ==
									pbmHorizontalIndex) {
								intersectionPointsIndex += 2;
								if (intersectionPointsIndex < intersectionPoints.size() - 1) {
									pbmHorizontalIndex =
										intersectionPoints[intersectionPointsIndex].x();
								}
								else {
									pbmHorizontalIndex = pbmImage.getWidth();
								}
							}
						}
					}

					scanline.setStart({0, static_cast<int>(pbmVerticalIndex)});
					scanline.setEnd({static_cast<int>(pbmImage.getWidth() - 1),
									 static_cast<int>(pbmVerticalIndex)});
				}
			}

			pbmImage.printImage();
		}

	private:
		std::vector<LineT<T>> m_lines{};
		std::vector<PolygonT<T>> m_polygons{};

		std::vector<PolygonT<slm::vec2i>> getPolygonsConvertedToInts() const {
			std::vector<PolygonT<slm::vec2i>> outPolygons;
			outPolygons.reserve(m_polygons.size());

			for (const auto polygon : m_polygons) {
				PolygonT<slm::vec2i> newPolygon{};
				const auto points = polygon.getPoints();
				for (const slm::vec2f point : points) {
					const int newX = static_cast<int>(point.x());
					const int newY = static_cast<int>(point.y());
					newPolygon.extend(slm::vec2i{newX, newY});
				}
				outPolygons.push_back(newPolygon);
			}

			return outPolygons;
		}
	};

}