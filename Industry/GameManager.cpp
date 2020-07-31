#include "GameManager.h"
#include "Evt_Keyboard.h"
#include <iostream>

static const long long START_MONEY = 10000;

GameManager::GameManager() {

	cam.setOffset(8.0f);
	cam.rotate(glm::vec3(PI / 4.0f, 0, 0));
	cam.setRotLimit(glm::vec2(PI / 180.0f, PI / 2.1f));
	cam.setOffsetLimit(glm::vec2(4.0f, 10.0f));
	display = Display::getGlobal();
	money = START_MONEY;
	uiControl.setMoney(money);
	uiControl.setMachines(factory.getMachineTypes(), onMachinePurchase, this);

}

void GameManager::onMachinePurchase(MACHINES type, void* data) {

	GameManager& self = *((GameManager*)data);

	long long price = Machine::getPrice(type);
	if (self.purchase(price)) {

		std::cout << "Bought machine type: " << Machine::getName(type) << std::endl;
		if (!self.factory.putMachine(type)) {
			std::cout << "Unable to place machine\n";
		}

	}
	else {
		std::cout << "Unable to purchase machine" << std::endl;
	}

}

bool GameManager::purchase(long long amt) {

	if (amt > money) {
		return false;
	}

	money -= amt;
	uiControl.setMoney(money);

	return true;

}

void GameManager::onFrame(double delta) {

	if (Evt_Keyboard::isKeyDown(KEY::KEY_DOWN)) {
		cam.rotate(glm::vec3(-arrowRotateStrength * delta, 0, 0));
	}
	else if (Evt_Keyboard::isKeyDown(KEY::KEY_UP)) {
		cam.rotate(glm::vec3(arrowRotateStrength * delta, 0, 0));
	}

	if (Evt_Keyboard::isKeyDown(KEY::KEY_RIGHT)) {
		cam.rotate(glm::vec3(0, arrowRotateStrength * delta, 0));
	}
	else if (Evt_Keyboard::isKeyDown(KEY::KEY_LEFT)) {
		cam.rotate(glm::vec3(0, -arrowRotateStrength * delta, 0));
	}

	if (Evt_Keyboard::isKeyDown(KEY::KEY_EQUAL)) {
		cam.setOffset(cam.getOffset() - arrowZoomStrength * delta);
	}
	else if (Evt_Keyboard::isKeyDown(KEY::KEY_MINUS)) {
		cam.setOffset(cam.getOffset() + arrowZoomStrength * delta);
	}

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
		factory.raycast(cam.getOffsetPos(), ray);
	}
	else if (button == 1) {
		middleMouse = true;
		display->relativeCursor(true);
	}
	else if (button == 2) {
		/* Right-click */
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
	/* Perpendicular case */
	if (step == 0) {
		return orig;
	}
	/* Amount of steps until collision */
	float mag = glm::dot(planePt - orig, normal) / step;
	/* Only allow forwards collision */
	if (mag <= 0) {
		return orig;
	}
	return orig + dir * mag;

}