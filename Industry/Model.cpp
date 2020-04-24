#include "Model.h"

Model::Model() {



}

bool Model::setModel(std::string path) {

	if (!mesh.Load(path)) {
		return false;
	}
	mdlPath = path;
	return true;

}

void Model::setVisible(bool toggle) {

	visible = toggle;

}

void Model::onDrawGeometry(GBuffer& gbuf) {

	if (visible) {
		Transform& trans = getTransform();
		gbuf.setTransMat(trans.GetMatrix());
		gbuf.setRotMat(trans.GetRotMatrix());
		mesh.draw();
	}

}