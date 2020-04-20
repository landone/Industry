#include <iostream>
#include <time.h>

#include "Evt_Display.h"
#include "GameDisplay.h"
#include "Camera.h"
#include "Image.h"
#include "Button.h"
#include "Factory.h"
#include "GameManager.h"

int main() {

	srand(clock()); //Enable random number gens
	
	GameDisplay display(800, 450, "Industry");

	GameManager gameMan;

	Camera& cam = gameMan.getCamera();
	Camera guiCam;

	display.setAmbientColor(0, 0.5, 1);
	display.setResizable(true);
	Factory fact;

	while (display.isOpen()) {

		/* Update frame listeners */
		Evt_Display::sendFrame();

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