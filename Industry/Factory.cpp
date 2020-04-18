#include "Factory.h"

Factory::Factory() {

	mesh.Load("models/DefaultFactory.obj");
	trans.SetPos(glm::vec3(0, -5, 10));

}

void Factory::onDrawGeometry(GBuffer& gbuf) {

	trans.rotate(glm::vec3(0, 0.01, 0));
	gbuf.setTransMat(trans.GetMatrix());
	gbuf.setRotMat(trans.GetRotMatrix());
	mesh.draw();

}