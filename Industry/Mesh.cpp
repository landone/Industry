#include "Mesh.h"
#include <fstream>
#include <map>

Mesh& Mesh::Init(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = vertices;
	this->indices = indices;
	setupMesh();
	return *this;
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
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
}

bool Mesh::Load(std::string path) {

	std::ifstream file(path);
	if (!file.is_open()) {
		return false;
	}
	std::string line;

	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> norm;

	std::vector<Vertex> verts;
	std::vector<GLuint> indices;
	GLuint vertCounter = 0;
	std::map<std::string, GLuint> vertMap;

	Object curObj;

	
	while (std::getline(file, line)) {

		if (line.size() <= 2) {
			continue;
		}
		if (line[0] == 'v') {

			switch (line[1]) {
			case 't':
				glm::vec2 muv;
				if (sscanf_s(line.c_str(), "vt %f %f", &muv[0], &muv[1]) == 2) {
					uv.push_back(muv);
				}
				else {
					return false;
				}
				break;
			case 'n':
				glm::vec3 mnorm;
				if (sscanf_s(line.c_str(), "vn %f %f %f", &mnorm[0], &mnorm[1], &mnorm[2]) == 3) {
					norm.push_back(mnorm);
				}
				else {
					return false;
				}
				break;
			default:
				glm::vec3 mpos;
				if (sscanf_s(line.c_str(), "v %f %f %f", &mpos[0], &mpos[1], &mpos[2]) == 3) {
					pos.push_back(mpos);
				}
				else {
					return false;
				}
				/* Push object position index lower boundary */
				if (curObj.indices.size() == 0) {
					curObj.indices.push_back((GLuint)pos.size());
				}
			}
		}
		else if (line[0] == 'f') {

			size_t start = 1;
			for (int i = 0; i < 3; i++) {

				/* Get string representing vertex */
				start = line.find_first_not_of(' ', start);
				size_t end = line.find_first_of(' ', start);
				if (start == std::string::npos || (i < 2 && end == std::string::npos)) {
					return false;
				}
				std::string v = line.substr(start, end - start);
				start = end;

				/* Place vertex in map if not found */
				if (vertMap.find(v) == vertMap.end()) {
					vertMap[v] = vertCounter++;
				}
				indices.push_back(vertMap[v]);

			}
		}
		else if (line[0] == 'o') {
			/* If object initialized, save with upper boundary */
			if (curObj.indices.size() > 0) {
				curObj.indices.push_back((GLuint)pos.size());
				objects.push_back(curObj);
				curObj.indices.clear();
			}

			size_t nameStart = line.find_first_not_of(' ', 1);
			if (nameStart == std::string::npos) {
				curObj.name = "";
			}
			else {
				curObj.name = line.substr(nameStart, line.size() - nameStart);
			}

		}

	}

	/* Account for last object */
	if (curObj.indices.size() > 0) {
		curObj.indices.push_back((GLuint)pos.size());
		objects.push_back(curObj);
	}
	/* Middleman obj. vertex recorder */
	std::vector<std::vector<GLuint>> objectVerts;
	objectVerts.resize(objects.size());
	/* Convert map to array */
	verts.resize(vertCounter);
	std::map<std::string, GLuint>::iterator mapIt;
	for (mapIt = vertMap.begin(); mapIt != vertMap.end(); mapIt++) {
		unsigned int ind[3];
		if (sscanf_s(mapIt->first.c_str(), "%d/%d/%d", &ind[0], &ind[1], &ind[2]) != 3) {
			return false;
		}
		/* Convert object indices from position to vertex */
		for (unsigned int i = 0; i < objects.size(); i++) {
			if (ind[0] >= objects[i].indices[0] && ind[0] <= objects[i].indices[1]) {
				objectVerts[i].push_back(mapIt->second);
				break;
			}
		}
		/* Translate indices to 0-based */
		ind[0]--;
		ind[1]--;
		ind[2]--;
		/* Avoid crash due to bad input */
		if ((ind[0] < 0 || ind[0] >= pos.size()) || (ind[1] < 0 || ind[1] >= uv.size()) || (ind[2] < 0 || ind[2] >= norm.size())) {
			return false;
		}
		/* Place vertex into final vector */
		Vertex v;
		v.position = pos[ind[0]];
		v.texCoord = uv[ind[1]];
		v.normal = norm[ind[2]];
		verts[mapIt->second] = v;
	}

	/* Overwrite object vertex arrays */
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i].indices = objectVerts[i];
	}

	Init(verts, indices);
	return true;

}