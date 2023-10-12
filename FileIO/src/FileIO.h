#pragma once

#include "FileReader.h"

namespace FileIO {

	std::optional<std::string> readFile(const std::filesystem::path& path);

}
