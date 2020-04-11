#include <iostream>
#include <time.h>

#include "Evt_Display.h"
#include "GameDisplay.h"
#include "Camera.h"
#include "Image.h"
#include "Button.h"

Display* g_display = nullptr;

void OnButton() {
	
	//g_display->setFullscreen(!g_display->isFullscreen());
}

int main() {

	srand(clock()); //Enable random number gens
	
	GameDisplay display(800, 450, "Industry");
	long long lastFrame = clock();
	long long thisFrame = 0;

	Camera cam;
	Camera guiCam;

	display.setAmbientColor(0, 0.5, 1);
	display.setResizable(true);
	g_display = &display;
	Texture tex("textures/missing.png");
	Button btn(tex);
	btn.setCallback(OnButton);
	btn.setRelSize(0, 0);
	btn.setAbsSize(100, 100);

	while (display.isOpen()) {

		/* Frame updates */
		thisFrame = clock();
		Evt_Display::sendFrame((double)(thisFrame - lastFrame) / 1000.0);
		lastFrame = thisFrame;

		/* Draw Geometry */
		display.gBuffer.bind();
		display.gBuffer.setViewMat(cam.getViewMatrix());
		Evt_Display::sendDrawGeometry(display.gBuffer);
		/* Draw 3D GUI */
		display.gBuffer.setViewMat(guiCam.getViewMatrix());
		glDisable(GL_DEPTH_TEST);
		Evt_Display::sendDraw3DGUI(display.gBuffer);
		/* Draw 2D GUI */
		display.gBuffer.setGUI(true);
		display.gBuffer.setViewMat(glm::mat4());
		Evt_Display::sendDrawGUI(display.gBuffer);
		glEnable(GL_DEPTH_TEST);
		display.gBuffer.setGUI(false);
		/* Apply lighting */
		display.lightShader.bind();
		display.lightShader.setCameraPos(cam.getPos());
		display.lightShader.drawQuad();
		/* Apply post effects */
		display.postProcessor.bind();
		display.postProcessor.drawQuad();

		/* Swap buffers */
		display.update();

	}
	return 0;

}