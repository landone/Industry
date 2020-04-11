#include "Image.h"
#include "Display.h"

Image::Image(Texture tex) {

	this->tex = tex;

}

void Image::onDrawGUI(GBuffer& buf) {

	checkChanged();
	tex.bind();
	buf.setTint(tint);
	buf.setRotMat(trans.GetRotMatrix());
	buf.setTransMat(trans.GetMatrix());
	buf.drawQuad();

}

void Image::onResize(int x, int y) {

	calcTrans();

}

void Image::checkChanged() {

	if (changed) {
		changed = false;
		calcTrans();
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

}

void Image::calcTrans() {
	
	glm::vec2 pxToScr = Display::getPixelToScreen();
	trans.SetPos(glm::vec3(relPos[0] + absPos[0] * pxToScr[0], relPos[1] + absPos[1] * pxToScr[1], 0));
	trans.SetScale(glm::vec3((relSz[0] + absSz[0] * pxToScr[0]) * 0.5f, (relSz[1] + absSz[1] * pxToScr[1]) * 0.5f, 0));

}