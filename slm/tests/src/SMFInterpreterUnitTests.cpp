#include <catch2/catch_test_macros.hpp>

#include "HelperFunctions.h"
#include "SMFInterpreter.h"

////////////////////
// SMFInterpreter //
////////////////////

void checkFaceVertices(const slm::SMFModel& model, const std::size_t faceIdx,
					   const slm::Vec3f expectedVertices[], const slm::Vec3i& vertexIndices) {
	const auto faceVertices = model.getFaceVertices(faceIdx);

	for (std::size_t i = 0; i < 3; i++) {
		helpers::checkValues(*faceVertices[i], expectedVertices[vertexIndices[i] - 1]);
	}
}

TEST_CASE("SMFInterpreter") {
	SECTION("Cube") {
		const std::string filepath =
			static_cast<std::string>(TEST_ASSETS_FOLDER).append("/cube.smf");

		const int32_t expectedVertexCount = 8;
		const int32_t expectedFaceCount	  = 12;
		const slm::Vec3f expectedVertices[expectedVertexCount]{
			{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f},  {0.5f, -0.5f, 0.5f},	 {0.5f, 0.5f, 0.5f},  {-0.5f, 0.5f, 0.5f}};
		const slm::Vec3i expectedFaces[expectedFaceCount]{
			{1, 3, 2}, {1, 4, 3}, {8, 6, 7}, {8, 5, 6}, {1, 8, 4}, {1, 5, 8},
			{2, 7, 6}, {2, 3, 7}, {1, 6, 5}, {1, 2, 6}, {4, 7, 3}, {4, 8, 7}};

		slm::SMFModel test = slm::SMFInterpreter::interpret(filepath);

		helpers::checkValues(test.getVertexCount(), expectedVertexCount);
		helpers::checkValues(test.getFaceCount(), expectedFaceCount);

		for (std::size_t i = 0; i < expectedVertexCount; i++) {
			helpers::checkValues(test.getVertex(i), expectedVertices[i]);
		}

		for (std::size_t i = 0; i < expectedFaceCount; i++) {
			checkFaceVertices(test, i, expectedVertices, expectedFaces[i]);
		}
	}
	SECTION("Cylinder") {
		const std::string filepath =
			static_cast<std::string>(TEST_ASSETS_FOLDER).append("/cylinder.smf");

		const int32_t expectedVertexCount = 20;
		const int32_t expectedFaceCount	  = 32;
		const slm::Vec3f expectedVertices[expectedVertexCount]{
			{0.200000, 0.00000, 1.00000},	  {0.141421, 0.141421, 1.00000},
			{0.00000, 0.200000, 1.00000},	  {-0.141421, 0.141421, 1.00000},
			{-0.200000, 0.00000, 1.00000},	  {-0.141421, -0.141421, 1.00000},
			{0.00000, -0.200000, 1.00000},	  {0.141421, -0.141421, 1.00000},
			{0.200000, 0.00000, 1.00000},	  {0.200000, 0.00000, -1.00000},
			{0.141421, 0.141421, -1.00000},	  {0.00000, 0.200000, -1.00000},
			{-0.141421, 0.141421, -1.00000},  {-0.200000, 0.00000, -1.00000},
			{-0.141421, -0.141421, -1.00000}, {0.00000, -0.200000, -1.00000},
			{0.141421, -0.141421, -1.00000},  {0.200000, 0.00000, -1.00000},
			{0.00000, 0.00000, 1.00000},	  {0.00000, 0.00000, -1.00000}};
		const slm::Vec3i expectedFaces[expectedFaceCount]{
			{1, 2, 19},	  {2, 3, 19},	{3, 4, 19},	  {4, 5, 19},	{5, 6, 19},	  {6, 7, 19},
			{7, 8, 19},	  {8, 9, 19},	{10, 20, 11}, {11, 20, 12}, {12, 20, 13}, {13, 20, 14},
			{14, 20, 15}, {15, 20, 16}, {16, 20, 17}, {17, 20, 18}, {1, 10, 11},  {1, 11, 2},
			{2, 11, 12},  {2, 12, 3},	{3, 12, 13},  {3, 13, 4},	{4, 13, 14},  {4, 14, 5},
			{5, 14, 15},  {5, 15, 6},	{6, 15, 16},  {6, 16, 7},	{7, 16, 17},  {7, 17, 8},
			{8, 17, 18},  {8, 18, 9}};

		slm::SMFModel test = slm::SMFInterpreter::interpret(filepath);

		helpers::checkValues(test.getVertexCount(), expectedVertexCount);
		helpers::checkValues(test.getFaceCount(), expectedFaceCount);

		for (std::size_t i = 0; i < expectedVertexCount; i++) {
			helpers::checkValues(test.getVertex(i), expectedVertices[i]);
		}

		for (std::size_t i = 0; i < expectedFaceCount; i++) {
			checkFaceVertices(test, i, expectedVertices, expectedFaces[i]);
		}
	}
}