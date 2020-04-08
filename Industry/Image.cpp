#include "Image.h"

Image::Image(Texture tex) {

	this->tex = tex;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	pxToScr[0] = 2.0f / viewport[2];
	pxToScr[1] = 2.0f / viewport[3];

}

void Image::onDrawGUI(GBuffer& buf) {

	if (changed) {
		changed = false;
		calcTrans();
	}
	tex.bind();
	buf.setRotMat(trans.GetRotMatrix());
	buf.setTransMat(trans.GetMatrix());
	buf.drawQuad();

}

void Image::setRelPos(float x, float y) {

	relPos[0] = x;
	relPos[1] = y;
	changed = true;

}

void Image::setAbsPos(float x, float y) {

	absPos[0] = x;
	absPos[1] = y;
	changed = true;

}

void Image::setRelSize(float x, float y) {

	relSz[0] = x;
	relSz[1] = y;
	changed = true;

}

void Image::setAbsSize(float x, float y) {

	absSz[0] = x;
	absSz[1] = y;
	changed = true;

}

void Image::calcTrans() {

	trans.SetPos(glm::vec3(relPos[0] + absPos[0] * pxToScr[0], relPos[1] + absPos[1] * pxToScr[1], 0));
	trans.SetScale(glm::vec3((relSz[0] + absSz[0] * pxToScr[0]) * 0.5f, (relSz[1] + absSz[1] * pxToScr[1]) * 0.5f, 0));

}