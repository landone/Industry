#include "Image.h"

Image::Image(Texture tex) {

	this->tex = tex;

}

void Image::onDrawGUI(GBuffer& buf) {

	tex.bind();
	buf.setRotMat(trans.GetRotMatrix());
	buf.setTransMat(trans.GetMatrix());
	buf.drawQuad();

}