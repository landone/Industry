#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Display.h"
#include "Model.h"
#include "Factory.h"

class GameManager : public MouseListener {
public:

	GameManager();

	Camera& getCamera() { return cam; }
	Camera& getGUICamera() { return guiCam; }

private:

	void onMouseMotion(double, double) override;
	void onMousePress(int button, int x, int y) override;
	void onMouseRelease(int button, int x, int y) override;
	void onMouseWheel(double) override;

	glm::vec3 rayPlaneCol(glm::vec3 orig, glm::vec3 dir, glm::vec3 normal, glm::vec3 planePt);

	Model selector;
	Factory factory;

	Display* display = nullptr;
	Camera cam;
	Camera guiCam;
	float sensitivity = 0.004f;
	bool middleMouse = false;

};