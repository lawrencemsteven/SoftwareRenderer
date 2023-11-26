#pragma once

#include "FileIO.h"
#include "slm.h"

namespace slm::SMFInterpreter {

	slm::SMFModel interpret(const std::filesystem::path& path);

}