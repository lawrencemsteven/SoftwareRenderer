#include "FileIO.h"

namespace FileIO {

	std::optional<std::string> readFile(const std::filesystem::path& path) {
		FileReader fileReader{path};

		// Read From File
		if (!fileReader.hasContents()) {
			return std::nullopt;
		}

		std::string line;
		std::string file_data;

		while (fileReader.hasContents()) {
			line.clear();
			line = fileReader.readNextLine();
			file_data.append(std::move(line) + "\n");
		}

		return file_data;
	}

}