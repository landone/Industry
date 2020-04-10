#include "Button.h"

Button::Button(Texture tex) : Image(tex) {



}

void Button::onMouseRelease(int button, int x, int y) {

	float point[2];
	point[0] = x * pxToScr[0] - 1.0f;
	point[1] = y * -pxToScr[1] + 1.0f;
	glm::vec2 pos = getTruePos();
	glm::vec2 size = getTrueSize();
	if ((abs(point[0] - pos.x) < size.x) && (abs(point[1] - pos.y) < size.y)) {
		callback();
	}

}

void Button::setCallback(void(*f)()) {

	callback = f;

}