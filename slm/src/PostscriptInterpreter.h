#pragma once

#include "FileIO.h"
#include "Scene.h"
#include "PolygonT.h"

namespace slm::PostscriptInterpreter {

	template <class T>
	Scene<T> interpret(const std::filesystem::path& path) {
		FileIO::FileReader fileReader{path};
		Scene<T> outputScene{};

		bool readingData = false;
		std::string currentLine;
		while (fileReader.hasContents() && !readingData) {
			currentLine.clear();
			currentLine = fileReader.readNextLine();
			if (currentLine.find("%%%BEGIN") != std::string::npos) {
				readingData = true;
			}
		}

		std::string num;
		float lineData[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float pointData[2] = {0.0f, 0.0f};
		PolygonTFactory<T> polygonFactory;
		while (fileReader.hasContents() && readingData) {
			currentLine.clear();
			currentLine = fileReader.readNextLine();
			if (currentLine.find("Moveto") != std::string::npos ||
				currentLine.find("moveto") != std::string::npos) {
				std::istringstream lineStream;
				lineStream.str(currentLine);
				for (int i = 0; i < T::getSize(); i++) {
					std::getline(lineStream, num, ' ');
					pointData[i] = std::stof(num);
				}
				T point{pointData[0], pointData[1]};
				polygonFactory.startNewPolygon();
				polygonFactory.addPoint(std::move(point));
			}
			else if (currentLine.find("Lineto") != std::string::npos ||
					 currentLine.find("lineto") != std::string::npos) {
				std::istringstream lineStream;
				lineStream.str(currentLine);
				for (int i = 0; i < T::getSize(); i++) {
					std::getline(lineStream, num, ' ');
					pointData[i] = std::stof(num);
				}
				T point{pointData[0], pointData[1]};
				polygonFactory.addPoint(std::move(point));
			}
			else if (currentLine.find("Stroke") != std::string::npos ||
					 currentLine.find("stroke") != std::string::npos) {
				outputScene.addPolygon(polygonFactory.exportPolygon());
			}
			else if (currentLine.find("Line") != std::string::npos ||
				currentLine.find("line") != std::string::npos) {
				std::istringstream lineStream;
				lineStream.str(currentLine);
				for (int i = 0; i < T::getSize() * 2; i++) {
					std::getline(lineStream, num, ' ');
					lineData[i] = std::stof(num);
				}
				outputScene.addLine(
					LineT<T>{T{lineData[0], lineData[1]}, T{lineData[2], lineData[3]}});
			}
			if (currentLine.find("%%%END") != std::string::npos) {
				readingData = false;
			}
		}

		return std::move(outputScene);
	}

}