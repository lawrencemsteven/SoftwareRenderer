#pragma once

#include "FileIO.h"
#include "Scene.h"

namespace slm::PostscriptInterpreter {

	template <class T>
	Scene<LineT<T>> interpret(const std::filesystem::path& path) {
		FileIO::FileReader fileReader{path};
		Scene<LineT<T>> outputScene{};

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
		while (fileReader.hasContents() && readingData) {
			currentLine.clear();
			currentLine = fileReader.readNextLine();
			if (currentLine.find("Line") != std::string::npos ||
				currentLine.find("line") != std::string::npos) {
				std::istringstream lineStream;
				lineStream.str(currentLine);
				for (int i = 0; i < T::getSize() * 2; i++) {
					std::getline(lineStream, num, ' ');
					lineData[i] = std::stof(num);
				}
				outputScene.addObject(LineT<T>{T{lineData[0], lineData[1]}, T{lineData[2], lineData[3]}});
			}
			if (currentLine.find("%%%END") != std::string::npos) {
				readingData = false;
			}
		}

		return std::move(outputScene);
	}

}