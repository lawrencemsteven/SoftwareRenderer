#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "slm.h"
#include "PolygonT.h"

TEST_CASE("Polygon") {
	SECTION("Polygon Clipping Test 1") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{0, 0}, {499, 499}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({200.0f, 100.0f});
		polygonFactory.addPoint({300.0f, 100.0f});
		polygonFactory.addPoint({300.0f, 400.0f});
		polygonFactory.addPoint({200.0f, 400.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.scaleAll(1.5f);

		testScene.clip(viewport);

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 4);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(300, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(150, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(450, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(150, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(450, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(499, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(300, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(499, 2.0f));
	}

	SECTION("Polygon Clipping Test 2") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{0, 0}, {499, 499}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({200.0f, 100.0f});
		polygonFactory.addPoint({300.0f, 100.0f});
		polygonFactory.addPoint({300.0f, 400.0f});
		polygonFactory.addPoint({200.0f, 400.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.translateAll(slm::vec2i{-250, -200});

		testScene.clip(viewport);

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 4);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(200, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(0, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(50, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(0, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(50, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(200, 2.0f));
	}

	SECTION("Polygon Clipping Test 3") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{170, 100}, {270, 400}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({100.0f, 125.0f});
		polygonFactory.addPoint({200.0f, 175.0f});
		polygonFactory.addPoint({300.0f, 125.0f});
		polygonFactory.addPoint({250.0f, 210.0f});
		polygonFactory.addPoint({300.0f, 275.0f});
		polygonFactory.addPoint({225.0f, 275.0f});
		polygonFactory.addPoint({200.0f, 350.0f});
		polygonFactory.addPoint({175.0f, 275.0f});
		polygonFactory.addPoint({100.0f, 275.0f});
		polygonFactory.addPoint({150.0f, 210.0f});
		polygonFactory.addPoint({100.0f, 125.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.clip(viewport);

		testScene.translateAll(slm::vec2i{-170, -100});

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 11);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(175, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(60, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(30, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(75, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(100, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(40, 2.0f));

		CHECK_THAT(polygon[4].x(), Catch::Matchers::WithinAbs(100, 2.0f));
		CHECK_THAT(polygon[4].y(), Catch::Matchers::WithinAbs(76, 2.0f));

		CHECK_THAT(polygon[5].x(), Catch::Matchers::WithinAbs(80, 2.0f));
		CHECK_THAT(polygon[5].y(), Catch::Matchers::WithinAbs(110, 2.0f));

		CHECK_THAT(polygon[6].x(), Catch::Matchers::WithinAbs(100, 2.0f));
		CHECK_THAT(polygon[6].y(), Catch::Matchers::WithinAbs(136, 2.0f));

		CHECK_THAT(polygon[7].x(), Catch::Matchers::WithinAbs(100, 2.0f));
		CHECK_THAT(polygon[7].y(), Catch::Matchers::WithinAbs(175, 2.0f));

		CHECK_THAT(polygon[8].x(), Catch::Matchers::WithinAbs(55, 2.0f));
		CHECK_THAT(polygon[8].y(), Catch::Matchers::WithinAbs(175, 2.0f));

		CHECK_THAT(polygon[9].x(), Catch::Matchers::WithinAbs(30, 2.0f));
		CHECK_THAT(polygon[9].y(), Catch::Matchers::WithinAbs(250, 2.0f));

		CHECK_THAT(polygon[10].x(), Catch::Matchers::WithinAbs(5, 2.0f));
		CHECK_THAT(polygon[10].y(), Catch::Matchers::WithinAbs(175, 2.0f));
	}

	SECTION("Polygon Clipping Test 4") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{0, 0}, {499, 499}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({100.0f, 125.0f});
		polygonFactory.addPoint({200.0f, 175.0f});
		polygonFactory.addPoint({300.0f, 125.0f});
		polygonFactory.addPoint({250.0f, 210.0f});
		polygonFactory.addPoint({300.0f, 275.0f});
		polygonFactory.addPoint({225.0f, 275.0f});
		polygonFactory.addPoint({200.0f, 350.0f});
		polygonFactory.addPoint({175.0f, 275.0f});
		polygonFactory.addPoint({100.0f, 275.0f});
		polygonFactory.addPoint({150.0f, 210.0f});
		polygonFactory.addPoint({100.0f, 125.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.scaleAll(2.0f);

		testScene.clip(viewport);

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 7);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(200, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(250, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(400, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(350, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(499, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(300, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(499, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(499, 2.0f));

		CHECK_THAT(polygon[4].x(), Catch::Matchers::WithinAbs(239, 2.0f));
		CHECK_THAT(polygon[4].y(), Catch::Matchers::WithinAbs(499, 2.0f));

		CHECK_THAT(polygon[5].x(), Catch::Matchers::WithinAbs(300, 2.0f));
		CHECK_THAT(polygon[5].y(), Catch::Matchers::WithinAbs(420, 2.0f));

		CHECK_THAT(polygon[6].x(), Catch::Matchers::WithinAbs(200, 2.0f));
		CHECK_THAT(polygon[6].y(), Catch::Matchers::WithinAbs(250, 2.0f));
	}

	SECTION("Polygon Clipping Test 5") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{200, 100}, {375, 400}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({140.0f, 135.0f});
		polygonFactory.addPoint({390.0f, 185.0f});
		polygonFactory.addPoint({240.0f, 235.0f});
		polygonFactory.addPoint({390.0f, 285.0f});
		polygonFactory.addPoint({140.0f, 335.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.clip(viewport);

		testScene.translateAll(slm::vec2i{-200, -100});

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 7);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(223, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(47, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(175, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(82, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(175, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(90, 2.0f));

		CHECK_THAT(polygon[4].x(), Catch::Matchers::WithinAbs(40, 2.0f));
		CHECK_THAT(polygon[4].y(), Catch::Matchers::WithinAbs(135, 2.0f));

		CHECK_THAT(polygon[5].x(), Catch::Matchers::WithinAbs(175, 2.0f));
		CHECK_THAT(polygon[5].y(), Catch::Matchers::WithinAbs(180, 2.0f));

		CHECK_THAT(polygon[6].x(), Catch::Matchers::WithinAbs(175, 2.0f));
		CHECK_THAT(polygon[6].y(), Catch::Matchers::WithinAbs(188, 2.0f));
	}

	SECTION("Polygon Clipping Test 6") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{275, 100}, {550, 502}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({140.0f, 135.0f});
		polygonFactory.addPoint({390.0f, 185.0f});
		polygonFactory.addPoint({240.0f, 235.0f});
		polygonFactory.addPoint({390.0f, 285.0f});
		polygonFactory.addPoint({140.0f, 335.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.clip(viewport);

		testScene.translateAll(slm::vec2i{-275, -100});

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 6);

		CHECK_THAT(polygon[0].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[0].y(), Catch::Matchers::WithinAbs(208, 2.0f));

		CHECK_THAT(polygon[1].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[1].y(), Catch::Matchers::WithinAbs(62, 2.0f));

		CHECK_THAT(polygon[2].x(), Catch::Matchers::WithinAbs(115, 2.0f));
		CHECK_THAT(polygon[2].y(), Catch::Matchers::WithinAbs(85, 2.0f));

		CHECK_THAT(polygon[3].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[3].y(), Catch::Matchers::WithinAbs(123, 2.0f));

		CHECK_THAT(polygon[4].x(), Catch::Matchers::WithinAbs(0, 2.0f));
		CHECK_THAT(polygon[4].y(), Catch::Matchers::WithinAbs(146, 2.0f));

		CHECK_THAT(polygon[5].x(), Catch::Matchers::WithinAbs(115, 2.0f));
		CHECK_THAT(polygon[5].y(), Catch::Matchers::WithinAbs(185, 2.0f));
	}

	SECTION("Polygon Clipping Test 7") {
		slm::Scene<slm::vec2f> testScene{};
		slm::Viewport<int, 2> viewport{{100, 170}, {435, 270}};

		slm::PolygonTFactory<slm::vec2f> polygonFactory{};
		polygonFactory.addPoint({100.0f, 125.0f});
		polygonFactory.addPoint({200.0f, 175.0f});
		polygonFactory.addPoint({300.0f, 125.0f});
		polygonFactory.addPoint({250.0f, 210.0f});
		polygonFactory.addPoint({300.0f, 275.0f});
		polygonFactory.addPoint({225.0f, 275.0f});
		polygonFactory.addPoint({200.0f, 350.0f});
		polygonFactory.addPoint({175.0f, 275.0f});
		polygonFactory.addPoint({100.0f, 275.0f});
		polygonFactory.addPoint({150.0f, 210.0f});
		polygonFactory.addPoint({100.0f, 125.0f});

		testScene.addPolygon(polygonFactory.exportPolygon());

		testScene.rotateAll(17);

		testScene.clip(viewport);

		testScene.translateAll(slm::vec2i{-100, -170});

		const auto polygon = testScene.getPolygons()[0];

		CHECK(polygon.getNumPoints() == 5);
	}
}