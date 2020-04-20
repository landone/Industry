#include "GameManager.h"
#include <iostream>

GameManager::GameManager() {

	cam.setOffset(8.0f);
	cam.rotate(glm::vec3(PI / 4.0f, 0, 0));
	cam.setRotLimit(glm::vec2(0, PI / 2.1f));

}

void GameManager::onMouseMotion(double x, double y) {

	if (middleMouse) {
		cam.rotate(glm::vec3(-y, x, 0) * sensitivity);
	}

}

void GameManager::onMousePress(int button, int x, int y) {

	if (button == 1) {
		middleMouse = true;
	}

}

void GameManager::onMouseRelease(int button, int x, int y) {

	if (button == 1) {
		middleMouse = false;
	}

}

void GameManager::onMouseWheel(double amt) {

	cam.setOffset(cam.getOffset() - amt);

}