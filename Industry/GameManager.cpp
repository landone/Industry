#include "GameManager.h"
#include <iostream>

GameManager::GameManager() {

	cam.setOffset(8.0f);
	cam.rotate(glm::vec3(PI / 4.0f, 0, 0));
	cam.setRotLimit(glm::vec2(PI / 180.0f, PI / 2.1f));
	cam.setOffsetLimit(glm::vec2(4.0f, 16.0f));
	display = Display::getGlobal();
	selector.setModel("models/Selector.obj", false);
	selector.setVisible(false);

}

bool GameManager::onMouseMotion(double x, double y) {

	if (middleMouse) {
		cam.rotate(glm::vec3(-y, x, 0) * sensitivity);
	}

	return false;

}

bool GameManager::onMousePress(int button, int x, int y) {

	if (button == 0) {
		glm::vec2 pxScr = display->getPixelToScreen();
		/* Screen coordinates */
		glm::vec4 pt(x * pxScr.x - 1, 1 - y * pxScr.y, 1, 1);
		/* Ray coming from camera */
		glm::vec3 ray = glm::normalize(glm::vec3(glm::inverse(cam.getViewMatrix()) * pt));
		glm::vec3 col = rayPlaneCol(cam.getOffsetPos(), ray, glm::vec3(0, 1, 0), glm::vec3());
		col.x = ceilf(col.x);
		col.z = floorf(col.z);
		selector.setPos(col);
		selector.setVisible(true);
	}
	else if (button == 1) {
		middleMouse = true;
		display->relativeCursor(true);
	}
	else if (button == 2) {
		selector.setVisible(false);
	}

	return false;

}

bool GameManager::onMouseRelease(int button, int x, int y) {

	if (button == 1) {
		middleMouse = false;
		display->relativeCursor(false);
	}

	return false;

}

bool GameManager::onMouseWheel(double amt) {

	cam.setOffset(cam.getOffset() - (float)amt);

	return false;

}

glm::vec3 GameManager::rayPlaneCol(glm::vec3 orig, glm::vec3 dir, glm::vec3 normal, glm::vec3 planePt) {

	float step = glm::dot(dir, normal);
	if (step == 0) {
		return glm::vec3();
	}
	/* Distance from plane divided by length of direction */
	float mag = glm::dot(planePt - orig, normal) / step;
	return orig + dir * mag;

}