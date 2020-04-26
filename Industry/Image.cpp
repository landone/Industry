#include "Image.h"
#include "Display.h"
#include <iostream>

/* Default mesh */
static const std::vector<Vertex> vertices{
	Vertex{ glm::vec3(0,0,0),glm::vec3(0, 0, 1),glm::vec2(0,0) },
	Vertex{ glm::vec3(1,0,0),glm::vec3(0, 0, 1),glm::vec2(1,0) },
	Vertex{ glm::vec3(1,1,0),glm::vec3(0, 0, 1),glm::vec2(1,1) },
	Vertex{ glm::vec3(0,1,0),glm::vec3(0, 0, 1),glm::vec2(0,1) }
};
static const std::vector<GLuint> indices{
	0, 1, 2,
	2, 3, 0
};

Image::Image(Texture tex) {

	this->tex = tex;
	setGUILayer(GUILayer_Middle);
	mesh.Init(vertices, indices);

}

void Image::onDrawGUI(GBuffer& buf) {

	checkChanged();
	tex.bind();
	if (tinted) {
		buf.setTint(tint);
	}
	buf.setRotMat(trans.GetRotMatrix());
	buf.setTransMat(trans.GetMatrix());
	mesh.draw();
	if (tinted) {
		buf.setTint(glm::vec3(1, 1, 1));
	}

}

void Image::setTiled(bool toggle) {

	if (tiled != toggle) {
		tiled = toggle;
		texChanged = true;
	}

}

void Image::onResize(int x, int y) {

	changed = true;
	if (tiled) {
		texChanged = true;
	}

}

void Image::checkChanged() {

	if (changed) {
		changed = false;
		calcTrans();
	}
	if (texChanged) {
		texChanged = false;
		calcTex();
	}

}

glm::vec2 Image::getTruePos() {

	checkChanged();
	return trans.GetPos();

}

glm::vec2 Image::getTrueSize() {

	checkChanged();
	return trans.GetScale();

}

void Image::setRelPos(float x, float y) {

	setRelPos(glm::vec2(x, y));

}

void Image::setRelPos(glm::vec2 pos) {

	relPos = pos;
	changed = true;

}

void Image::setAbsPos(float x, float y) {

	setAbsPos(glm::vec2(x, y));

}

void Image::setAbsPos(glm::vec2 pos) {

	absPos = pos;
	changed = true;

}

void Image::setRelSize(float x, float y) {

	setRelSize(glm::vec2(x, y));

}

void Image::setRelSize(glm::vec2 amt) {

	relSz = amt;
	changed = true;

}

void Image::setAbsSize(float x, float y) {

	setAbsSize(glm::vec2(x, y));

}

void Image::setAbsSize(glm::vec2 amt) {

	absSz = amt;
	changed = true;

}

void Image::setTint(float r, float g, float b) {

	setTint(glm::vec3(r, g, b));

}

void Image::setTint(glm::vec3 color) {

	tint = color;
	tinted = (tint != glm::vec3(1, 1, 1));

}

void Image::calcTrans() {
	
	glm::vec2 pxToScr = Display::getGlobal()->getPixelToScreen();
	trans.SetPos(glm::vec3(relPos[0] + absPos[0] * pxToScr[0], relPos[1] + absPos[1] * pxToScr[1], 0));
	trans.SetScale(glm::vec3(relSz[0] + absSz[0] * pxToScr[0], relSz[1] + absSz[1] * pxToScr[1], 0));

}

void Image::calcTex() {

	glm::vec2 texScale = glm::vec2(1, 1);
	if (tiled) {
		glm::vec2 scrSz = tex.getDimensions() * Display::getGlobal()->getPixelToScreen();
		texScale = glm::vec2(trans.GetScale()) / scrSz;
	}
	mesh.setTextureScale(texScale);

}