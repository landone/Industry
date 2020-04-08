#include "Button.h"

Button::Button(Texture tex) : Image(tex) {



}

void Button::onMouseRelease(int button, int x, int y) {

	float point[2];
	point[0] = x * pxToScr[0] - 1.0f;
	point[1] = y * -pxToScr[1] + 1.0f;
	if (changed) {
		calcTrans();
	}
	glm::vec3 pos = trans.GetPos();
	glm::vec3 scale = trans.GetScale();
	if ((abs(point[0] - pos.x) < scale.x) && (abs(point[1] - pos.y) < scale.y)) {
		callback();
	}

}

void Button::setCallback(void(*f)()) {

	callback = f;

}