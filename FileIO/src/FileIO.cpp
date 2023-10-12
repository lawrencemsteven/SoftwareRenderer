#include "FileIO.h"


namespace FileIO {

	std::optional<std::string> readFile(const std::filesystem::path& path) {
		std::ifstream fileStream{path};

		// Read From File
		if (!fileStream.is_open()) {
			std::cout << "Could not read file!" << std::endl;
			return std::nullopt;
		}

		std::string line;
		std::string file_data;

		while (!fileStream.eof()) {
			line.clear();
			std::getline(fileStream, line);
			file_data.append(std::move(line) + "\n");
		}

		return file_data;
	}

}