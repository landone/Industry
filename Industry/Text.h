#pragma once

#include "Image.h"

class Text : public Image {
public:

	Text();
	Text(std::string);
	~Text();

	void setText(std::string);
	std::string getText() { return text; }
	void setFont(std::string);

private:

	void createTexture();

	Mesh mesh;
	std::string text;
	std::string font;
	/* Personal buffer prevents blocking */
	GLuint buf = 0;

};