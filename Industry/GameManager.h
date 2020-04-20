#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"

class GameManager : public MouseListener {
public:

	GameManager();

	Camera& getCamera() { return cam; }

private:

	void onMouseMotion(double, double) override;
	void onMousePress(int button, int x, int y) override;
	void onMouseRelease(int button, int x, int y) override;
	void onMouseWheel(double) override;

	Camera cam;
	float sensitivity = 0.004f;
	bool middleMouse = false;

};