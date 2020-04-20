#include "Factory.h"

Factory::Factory() {

	mesh.Load("models/DefaultFactory.obj");
	trans.SetPos(glm::vec3(4, 0, -2));

}

void Factory::onDrawGeometry(GBuffer& gbuf) {

	gbuf.setTransMat(trans.GetMatrix());
	gbuf.setRotMat(trans.GetRotMatrix());
	mesh.draw();

}