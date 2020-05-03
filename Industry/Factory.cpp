#include "Factory.h"

Factory::Factory() {

	mdl.setModel("models/DefaultFactory.obj");
	mdl.setPos(glm::vec3(4, 0, -2));

	test.setModel("models/Boiler.obj");
	test.setPos(glm::vec3(4, 0, -2));

}