#pragma once

#include "Clipping.h"
#include "VecT.h"
#include "LineT.h"
#include "PolygonT.h"

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
			return m_lines.size();
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

	private:
		std::vector<LineT<T>> m_lines{};
		std::vector<PolygonT<T>> m_polygons{};
	};

}