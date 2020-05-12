#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Display.h"
#include "Model.h"
#include "Factory.h"
#include "UIControl.h"

class GameManager : public MouseListener {
public:

	GameManager();

	Camera& getCamera() { return cam; }
	Camera& getGUICamera() { return guiCam; }

	
	/*
	Get collision point of plane and ray
	Return origin if not possible
	*/
	static glm::vec3 rayPlaneCol(glm::vec3 orig, glm::vec3 dir, glm::vec3 normal, glm::vec3 planePt);

private:

	bool onMouseMotion(double, double) override;
	bool onMousePress(int button, int x, int y) override;
	bool onMouseRelease(int button, int x, int y) override;
	bool onMouseWheel(double) override;

	UIControl uiControl;

	Factory factory;

	Display* display = nullptr;
	Camera cam;
	Camera guiCam;
	float sensitivity = 0.004f;
	bool middleMouse = false;

};