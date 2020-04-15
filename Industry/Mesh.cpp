#include "Mesh.h"
#include <fstream>
#include <map>
#include <iostream>

Mesh& Mesh::Init(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = vertices;
	this->indices = indices;
	indexSize = (GLuint)indices.size();
	setupMesh();
	return *this;
}

void Mesh::Init(GLuint vao, size_t indexSize) {
	this->VAO = vao;
	this->indexSize = (GLuint)indexSize;
}

void Mesh::setQuadTextureCoord(glm::vec2 bottomLeft, glm::vec2 topRight) {

	if (vertices.size() != 4) {//Must be quad
		return;
	}

	vertices[0].texCoord = glm::vec2(bottomLeft.x, topRight.y);
	vertices[1].texCoord = topRight;
	vertices[2].texCoord = glm::vec2(topRight.x, bottomLeft.y);
	vertices[3].texCoord = bottomLeft;
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
	glBindVertexArray(0);

}

void Mesh::setTextureScale(glm::vec2 scale) {
	textureScale.x = scale.x / textureScale.x;
	textureScale.y = scale.y / textureScale.y;
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].texCoord.x *= textureScale.x;
		vertices[i].texCoord.y *= textureScale.y;
	}
	textureScale = scale;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
	glBindVertexArray(0);
}

void Mesh::setupMesh() {
	if (VAO == NULL) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glBindVertexArray(0);
}

void Mesh::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::Load(std::string path) {

	std::ifstream file(path);
	std::string line;

	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> norm;

	std::vector<Vertex> verts;
	std::vector<GLuint> indices;
	GLuint vertCounter = 0;
	std::map<std::string, GLuint> vertMap;
	
	while (std::getline(file, line)) {

		if (line[0] == 'v') {
			switch (line[1]) {
			case 't':
				glm::vec2 muv;
				if (sscanf_s(line.c_str(), "vt %f %f", &muv[0], &muv[1]) == 2) {
					uv.push_back(muv);
				}
				break;
			case 'n':
				glm::vec3 mnorm;
				if (sscanf_s(line.c_str(), "vn %f %f %f", &mnorm[0], &mnorm[1], &mnorm[2]) == 3) {
					norm.push_back(mnorm);
				}
				break;
			default:
				glm::vec3 mpos;
				if (sscanf_s(line.c_str(), "v %f %f %f", &mpos[0], &mpos[1], &mpos[2]) == 3) {
					pos.push_back(mpos);
				}
			}
		}
		else if (line[0] == 'f') {
			unsigned int ind[9];
			if (sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &ind[0], &ind[1], &ind[2],
				&ind[3], &ind[4], &ind[5], &ind[6], &ind[7], &ind[8]) == 9) {

				for (int i = 0; i < 9; i+=3) {

					std::string v;
					v += std::to_string(ind[i]);
					v += '/';
					v += std::to_string(ind[i + 1]);
					v += '/';
					v += std::to_string(ind[i + 2]);

					if (vertMap.find(v) == vertMap.end()) {
						vertMap[v] = vertCounter++;
					}

					indices.push_back(vertMap[v]);

				}

			}
		}

	}
	
	/* Place distinct vertices into array */
	verts.resize(vertCounter);
	std::map<std::string, GLuint>::iterator mapIt;
	for (mapIt = vertMap.begin(); mapIt != vertMap.end(); mapIt++) {
		unsigned int ind[3];
		sscanf_s(mapIt->first.c_str(), "%d/%d/%d", &ind[0], &ind[1], &ind[2]);
		Vertex v;
		v.position = pos[ind[0] - 1];
		v.texCoord = uv[ind[1] - 1];
		v.normal = norm[ind[2] - 1];
		verts[mapIt->second] = v;
	}

	Init(verts, indices);

}