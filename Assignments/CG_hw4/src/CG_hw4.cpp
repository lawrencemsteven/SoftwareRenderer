#include "CommandLineParser.h"
#include "slm.h"
#include "SMFInterpreter.h"

int main(const int argc, const char* argv[]) {
	CommandLineParser clp{argc, argv};

	std::string fileName = clp.getValueOr("-f", "hw3_split.ps");
	float scale			 = clp.getValueOr("-s", 1.0f);
	int degreeRotation	 = clp.getValueOr("-r", 0);
	int xTranslation	 = clp.getValueOr("-m", 0);
	int yTranslation	 = clp.getValueOr("-n", 0);
	int winLowX			 = clp.getValueOr("-a", 0);
	int winLowY			 = clp.getValueOr("-b", 0);
	int winUpX			 = clp.getValueOr("-c", 250);
	int winUpY			 = clp.getValueOr("-d", 250);
	int viewLowX		 = clp.getValueOr("-j", 0);
	int viewLowY		 = clp.getValueOr("-k", 0);
	int viewUpX			 = clp.getValueOr("-o", 200);
	int viewUpY			 = clp.getValueOr("-p", 200);

	slm::SMFModel model = slm::SMFInterpreter::interpret(fileName);
}