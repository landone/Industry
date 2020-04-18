#include "Factory.h"

Factory::Factory() {

	mesh.Load("models/DefaultFactory.obj");
	tex.Load("textures/freeman.png");
	trans.SetPos(glm::vec3(0, -5, 10));

}

void Factory::onDrawGeometry(GBuffer& gbuf) {

	trans.rotate(glm::vec3(0, 0.01, 0));
	gbuf.setTransMat(trans.GetMatrix());
	gbuf.setRotMat(trans.GetRotMatrix());
	tex.bind();
	mesh.draw();

}