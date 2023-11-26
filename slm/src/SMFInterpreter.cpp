#include "SMFInterpreter.h"

namespace slm::SMFInterpreter {

	std::array<std::string, 3> getStringNumbers(const std::string& line) {
		std::array<std::string, 3> outputNumbers{};

		std::size_t outputCounter = 0;
		bool numFound			  = false;
		std::string num{};

		for (const auto character : line) {
			if (isdigit(character) || character == '.' || character == '-') {
				numFound = true;
				num += character;
			}
			else if ((character == ' ' || character == '\n') && numFound) {
				outputNumbers[outputCounter] = std::move(num);
				num.clear();
				outputCounter += 1;
				if (outputCounter >= 3) {
					return outputNumbers;
				}
			}
		}
		outputNumbers[outputCounter] = std::move(num);

		return outputNumbers;
	}

	std::array<float, 3> getVertexData(const std::string& line) {
		std::array<float, 3> vertexData{};

		const auto splitString = getStringNumbers(line);

		for (std::size_t i = 0; i < 3; i++) {
			vertexData[i] = std::stof(splitString[i]);
		}

		return vertexData;
	}

	std::array<int32_t, 3> getFaceData(const std::string& line) {
		std::array<int32_t, 3> faceData{};

		const auto splitString = getStringNumbers(line);

		for (std::size_t i = 0; i < 3; i++) {
			faceData[i] = std::stoi(splitString[i]);
		}

		return faceData;
	}

	enum class LineType { Vertex, Face };

	struct FirstCharData {
		std::optional<char> firstChar{};
		LineType lineType{};

		bool invalidSMF() const {
			return !firstChar.has_value();
		}
	};

	const FirstCharData getFirstChar(const std::string& line) {
		const auto pos = line.find_first_of("#vVfF");

		if (pos == std::string::npos || line[pos] == '#') {
			return FirstCharData{std::nullopt};
		}

		if (line[pos] == 'v' || line[pos] == 'V') {
			return FirstCharData{line[pos], LineType::Vertex};
		}
		if (line[pos] == 'f' || line[pos] == 'F') {
			return FirstCharData{line[pos], LineType::Face};
		}

		return FirstCharData{std::nullopt};
	}

	slm::SMFModel slm::SMFInterpreter::interpret(const std::filesystem::path& path) {
		FileIO::FileReader fileReader{path};
		SMFModel outputModel{};

		std::string currentLine;
		while (fileReader.hasContents()) {
			currentLine.clear();
			currentLine			 = fileReader.readNextLine();
			const auto firstCharData = getFirstChar(currentLine);

			if (firstCharData.invalidSMF()) {
				continue;
			}

			if (firstCharData.lineType == LineType::Vertex) {
				const auto vertexData = getVertexData(currentLine);
				outputModel.addVertex(vertexData);
			}
			else if (firstCharData.lineType == LineType::Face) {
				const auto faceData = getFaceData(currentLine);
				outputModel.addFace(faceData);
			}
		}

		return outputModel;
	}

}
