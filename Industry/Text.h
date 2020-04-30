#pragma once

#include "Image.h"

class Text : public Image {
public:

	Text();
	Text(std::string);
	~Text();

	void setText(std::string);

private:

	void createTexture();

	std::string text;
	std::string font;
	GLuint buf = 0;

};