#pragma once

#include "Camera.h"
#include "Evt_Mouse.h"
#include "Evt_Display.h"
#include "Display.h"
#include "Model.h"
#include "Factory.h"
#include "UIControl.h"

class GameManager : public MouseListener, public DisplayListener {
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

	static void onMachinePurchase(MACHINES, void*);

	bool purchase(long long);

	bool onMouseMotion(double, double) override;
	bool onMousePress(int button, int x, int y) override;
	bool onMouseRelease(int button, int x, int y) override;
	bool onMouseWheel(double) override;

	virtual void onFrame(double delta) override;

	UIControl uiControl;
	Factory factory;

	long long money;

	Display* display = nullptr;
	Camera cam;
	Camera guiCam;
	float sensitivity = 0.004f;
	float arrowRotateStrength = 1.0f;
	float arrowZoomStrength = 10.0f;
	bool middleMouse = false;

};