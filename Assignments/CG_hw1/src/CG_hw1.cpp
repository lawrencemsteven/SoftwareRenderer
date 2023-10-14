#include "CommandLineParser.h"
#include "slm.h"

int main(const int argc, const char* argv[]) {
	CommandLineParser clp{argc, argv};

	std::string fileName = clp.getValueOr("-f", "");
	float scale			 = clp.getValueOr("-s", 1.0f);
	int degreeRotation	 = clp.getValueOr("-r", 0);
	int xTranslation	 = clp.getValueOr("-m", 0);
	int yTranslation	 = clp.getValueOr("-n", 0);
	int viewLowX		 = clp.getValueOr("-a", 0);
	int viewLowY		 = clp.getValueOr("-b", 0);
	int viewUpX			 = clp.getValueOr("-c", 499);
	int viewUpY			 = clp.getValueOr("-d", 499);

	slm::Viewport<int, 2> viewport{{viewLowX, viewLowY}, {viewUpX, viewUpY}};

	slm::Scene<slm::LineT<slm::vec2f>> scene =
		slm::PostscriptInterpreter::interpret<slm::vec2f>(fileName);

	scene.scaleAll(scale);
	scene.rotateAll(degreeRotation);
	scene.translateAll(slm::vec2i{xTranslation, yTranslation});

	scene.clip(viewport);
	scene.printPostscript(viewport);
}