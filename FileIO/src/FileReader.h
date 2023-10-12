#pragma once

namespace FileIO {

	class FileReader {
	public:
		FileReader(std::filesystem::path path);
		~FileReader()							 = default;
		FileReader(const FileReader&)			 = delete;
		FileReader(FileReader&&)				 = delete;
		FileReader& operator=(const FileReader&) = delete;
		FileReader& operator=(FileReader&&)		 = delete;

		std::string readNextLine();

		bool hasContents() const;

	private:
		std::ifstream m_fileStream{};
		bool m_hasContents{false};

		void checkForContent();
	};

}