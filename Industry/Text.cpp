#include "Text.h"
#include "BasicShader.h"

#define DEFAULT_FONT		("textures/fonts/ascii.png")

Text::Text() {

	setMouseLayer(MouseLayer_None);
	font = DEFAULT_FONT;
	BasicShader& shader = (*BasicShader::getGlobal());
	buf = shader.createBuffer();
	tex.setIndex(shader.createTex());

}

Text::Text(std::string str) : Text() {

	setText(str);

}

Text::~Text() {

	glDeleteBuffers(1, &buf);
	tex.unloadThis();

}

void Text::setText(std::string str) {

	text = str;
	createTexture();

}

/* TODO: Optimize and cleanup PLEASE */
void Text::createTexture() {

	GLint prevBound = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevBound);

	/* Set up drawing tools */
	Texture fontTex(font);
	BasicShader& shader = (*BasicShader::getGlobal());
	shader.setBuffer(buf);
	shader.setGLTex(tex.getIndex());
	int len = (int)text.length();
	//float width = fontTex.getDimensions().x / 16.0f * len;
	//float height = fontTex.getDimensions().y / 16.0f;
	float width = 1280, height = 256;
	/* Assume ascii 16*16 character map */
	shader.updateDimensions((int)width, (int)height);
	/* shader.setTint(color); */
	fontTex.bind();
	Mesh mesh;
	mesh.createQuad(false);
	Transform trans;
	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	if (len > 0) {
		trans.SetScale(glm::vec3((1.0f / len) * width / dims[2], 1.0f * height / dims[3], 1));
		for (int i = 0; i < len; i++) {

			trans.SetPos(glm::vec3((-1.0f + i * 1.0f / len + 1) / dims[2] * width - 1, -1, 0));
			shader.setTransMat(trans.GetMatrix());
			char c = text.at(i);
			glm::vec2 bottomLeft((c % 16) / 16.0f, (16 - c / 16) / 16.0f);
			mesh.setQuadTextureCoord(bottomLeft, bottomLeft + glm::vec2(1 / 16.0f, -1 / 16.0f));
			mesh.draw();

		}
	}
	mesh.setQuadTextureCoord(glm::vec2(0, 0), glm::vec2(1, 1));

	glBindFramebuffer(GL_FRAMEBUFFER, prevBound);

}