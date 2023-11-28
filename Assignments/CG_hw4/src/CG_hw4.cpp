#include "CommandLineParser.h"
#include "slm.h"
#include "SMFInterpreter.h"

int main(const int argc, const char* argv[]) {
	CommandLineParser clp{argc, argv};

	std::string fileName = clp.getValueOr("-f", std::string{""});
	uint32_t viewLowX	 = clp.getValueOr("-j", 0u);
	uint32_t viewLowY	 = clp.getValueOr("-k", 0u);
	uint32_t viewUpX	 = clp.getValueOr("-o", 500u);
	uint32_t viewUpY	 = clp.getValueOr("-p", 500u);

	float PRPx = clp.getValueOr("-x", 0.0f);
	float PRPy = clp.getValueOr("-y", 0.0f);
	float PRPz = clp.getValueOr("-z", 1.0f);

	float VRPx = clp.getValueOr("-X", 0.0f);
	float VRPy = clp.getValueOr("-Y", 0.0f);
	float VRPz = clp.getValueOr("-Z", 0.0f);

	float VPNx = clp.getValueOr("-q", 0.0f);
	float VPNy = clp.getValueOr("-r", 0.0f);
	float VPNz = clp.getValueOr("-w", -1.0f);

	float VUPx = clp.getValueOr("-Q", 0.0f);
	float VUPy = clp.getValueOr("-R", 1.0f);
	float VUPz = clp.getValueOr("-W", 0.0f);

	float uMin = clp.getValueOr("-u", -0.7f);
	float vMin = clp.getValueOr("-v", -0.7f);
	float uMax = clp.getValueOr("-U", 0.7f);
	float vMax = clp.getValueOr("-V", 0.7f);

	bool parallelProjection = clp.getExists("-P");

	slm::SMFModel model = slm::SMFInterpreter::interpret(fileName);

	slm::AxisAlignedBox2u viewport{viewLowX, viewLowY, viewUpX, viewUpY};

	slm::ViewVolume viewVolume{};
	viewVolume.setProjectionReferencePoint({PRPx, PRPy, PRPz});
	viewVolume.setViewReferencePoint({VRPx, VRPy, VRPz});
	viewVolume.setViewPlaneNormal({VPNx, VPNy, VPNz});
	viewVolume.setViewUpVector({VUPx, VUPy, VUPz});
	viewVolume.setVRCMinMaxUV(uMin, vMin, uMax, vMax);
	viewVolume.setParallelProjection(parallelProjection);

	slm::Scene scene{};

	scene.convertModel(viewVolume, model, viewport);

	scene.clip(viewport);

	scene.printPostscript(viewport);
}