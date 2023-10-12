#include <catch2/catch_test_macros.hpp>

#include "FileIO.h"

TEST_CASE("FileIO") {
	const std::string filePath =
		static_cast<std::string>(TEST_ASSETS_FOLDER).append("/sampleFile.txt");
	const std::string expectedFileContents = "Hello,\n\nThis is a sample file!\n";
	const std::string fileLines[3]		   = {"Hello,", "", "This is a sample file!"};

	SECTION("FileIO Read File") {
		const std::optional<std::string> fileContentsOptional = FileIO::readFile(filePath);
		REQUIRE(fileContentsOptional.has_value());

		const std::string fileContents = fileContentsOptional.value();
		CHECK(fileContents.compare(expectedFileContents) == 0);
	}

	SECTION("File Reader") {
		FileIO::FileReader fileReader{filePath};

		REQUIRE(fileReader.hasContents());

		for (std::string expectedLine : fileLines) {
			CHECK(expectedLine.compare(fileReader.readNextLine()) == 0);
		}

		REQUIRE(!fileReader.hasContents());
	}
}