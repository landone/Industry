#include "Factory.h"

static const std::vector<Vertex> vertices{
	/*Floor*/
	Vertex{ glm::vec3(0,0,0),glm::vec3(0, 1, 0),glm::vec2(0,0) },
	Vertex{ glm::vec3(0,0,-3),glm::vec3(0, 1, 0),glm::vec2(0,3) },
	Vertex{ glm::vec3(8,0,-3),glm::vec3(0, 1, 0),glm::vec2(8,3) },
	Vertex{ glm::vec3(8,0,0),glm::vec3(0, 1, 0),glm::vec2(8,0) },
	/*Forward Wall*/
	Vertex{ glm::vec3(0,0,0),glm::vec3(0, 0, -1),glm::vec2(0,4) },
	Vertex{ glm::vec3(0,4,0),glm::vec3(0, 0, -1),glm::vec2(0,0) },
	Vertex{ glm::vec3(8,4,0),glm::vec3(0, 0, -1),glm::vec2(8,0) },
	Vertex{ glm::vec3(8,0,0),glm::vec3(0, 0, -1),glm::vec2(8,4) },
	/*Back Wall*/
	Vertex{ glm::vec3(0,0,-3),glm::vec3(0, 0, 1),glm::vec2(0,4) },
	Vertex{ glm::vec3(0,4,-3),glm::vec3(0, 0, 1),glm::vec2(0,0) },
	Vertex{ glm::vec3(8,4,-3),glm::vec3(0, 0, 1),glm::vec2(8,0) },
	Vertex{ glm::vec3(8,0,-3),glm::vec3(0, 0, 1),glm::vec2(8,4) },
	/*Left Wall*/
	Vertex{ glm::vec3(8,0,0),glm::vec3(-1, 0, 0),glm::vec2(0,4) },
	Vertex{ glm::vec3(8,4,0),glm::vec3(-1, 0, 0),glm::vec2(0,0) },
	Vertex{ glm::vec3(8,4,-3),glm::vec3(-1, 0, 0),glm::vec2(3,0) },
	Vertex{ glm::vec3(8,0,-3),glm::vec3(-1, 0, 0),glm::vec2(3,4) },
	/*Right Wall*/
	Vertex{ glm::vec3(0,0,0),glm::vec3(1, 0, 0),glm::vec2(0,4) },
	Vertex{ glm::vec3(0,4,0),glm::vec3(1, 0, 0),glm::vec2(0,0) },
	Vertex{ glm::vec3(0,4,-3),glm::vec3(1, 0, 0),glm::vec2(3,0) },
	Vertex{ glm::vec3(0,0,-3),glm::vec3(1, 0, 0),glm::vec2(3,4) }
};
static const std::vector<GLuint> indices{
	1, 0, 3,
	3, 2, 1,
	4, 5, 6,
	6, 7, 4,
	10, 9, 8,
	8, 11, 10,
	12, 13, 14,
	14, 15, 12,
	18, 17, 16,
	16, 19, 18
};

Factory::Factory() {

	//mesh.Init(vertices, indices);
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