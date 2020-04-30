#include <time.h>
#include <iostream>

#include "GameDisplay.h"
#include "GameManager.h"
#include "Image.h"
#include "Text.h"

int main() {

	srand(clock()); //Enable random number gens
	
	GameDisplay display(800, 450, "Industry");

	GameManager gameMan;

	Camera& cam = gameMan.getCamera();
	Camera& guiCam = gameMan.getGUICamera();

	display.setAmbientColor(0, 0.5, 1);
	display.setResizable(true);
	
	std::string str = "r/RoastMe";
	Text tex(str);
	tex.setRelPos(-1, -1);
	tex.setRelSize(0, 0);
	tex.setAbsSize(64 * str.size(), 64);

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