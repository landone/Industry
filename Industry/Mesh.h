#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <vector>
#include <string>
#include "Texture.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	GLint texID;
};

class Mesh {
public:

	~Mesh();

	Mesh() {}
	Mesh(std::vector<Vertex> verts, std::vector<GLuint> indices) {
		Init(verts, indices);
	}

	Mesh& Init(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	bool Load(std::string path);
	void draw();

	void setTextureScale(glm::vec2 scale);
	void setQuadTextureCoord(glm::vec2 bottomLeft, glm::vec2 topRight);

	GLuint getVAO() { return VAO; }

private:

	struct Object {
		std::string name;
		std::string material;
		std::vector<GLuint> indices;
		GLuint texIndex;
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Object> objects;
	std::vector<Texture> textures;

	void setupMesh();
	/* Read MTL file, return vector of material name paired with pathway */
	std::vector<std::pair<std::string, std::string>> ProcessMTL(std::string path);

	glm::vec2 textureScale = glm::vec2(1, 1);
};