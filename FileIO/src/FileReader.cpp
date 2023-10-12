#include "FileReader.h"

namespace FileIO {

	FileReader::FileReader(std::filesystem::path path) {
		m_fileStream = std::ifstream(path);

		if (!m_fileStream.is_open()) {
			std::cerr << "Could not read file!" << std::endl;
		}

		m_hasContents = true;
		checkForContent();
	}

	std::string FileReader::readNextLine() {
		if (!m_hasContents) {
			return "";
		}

		std::string line;

		std::getline(m_fileStream, line);

		checkForContent();

		return std::move(line);
	}

	bool FileReader::hasContents() const {
		return m_hasContents;
	}

	void FileReader::checkForContent() {
		if (m_fileStream.eof()) {
			m_hasContents = false;
		}
	}

}