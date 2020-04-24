#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Display.h"
#include "Model.h"

class GameManager : public MouseListener {
public:

	GameManager();

	Camera& getCamera() { return cam; }

private:

	void onMouseMotion(double, double) override;
	void onMousePress(int button, int x, int y) override;
	void onMouseRelease(int button, int x, int y) override;
	void onMouseWheel(double) override;

	glm::vec3 rayPlaneCol(glm::vec3 orig, glm::vec3 dir, glm::vec3 normal, glm::vec3 planePt);

	Model selector;

	Display* display = nullptr;
	Camera cam;
	float sensitivity = 0.004f;
	bool middleMouse = false;

};