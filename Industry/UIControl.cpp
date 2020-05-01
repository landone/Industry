#include "UIControl.h"

UIControl::UIControl() {

	background.Load("textures/steel.png");
	img.setTexture(background);
	img.setRelPos(-1, -1);
	img.setRelSize(0, 0);
	img.setAbsSize(128, 96);
	img.setTiled(true);

	gear.setTexture(Texture("textures/gear.png"));
	gear.setRelPos(-1, -1);
	gear.setAbsPos(48, 32);
	gear.setRelSize(0, 0);
	gear.setAbsSize(32, 32);
	gear.setCallback(gearCbk, this);

	std::string str = "Test Text";
	tex.setTint(1, 0, 1);
	tex.setText(str);
	tex.setRelPos(-1, -1);
	tex.setRelSize(0, 0);
	tex.setAbsSize(64 * str.size(), 64);

}

void UIControl::gearCbk(Button& button, void* data) {

	UIControl& self = (*(UIControl*)data);
	self.img.setVisibility(!self.img.getVisibility());

	std::string str;
	int size = (rand() % 4) + 4;
	for (int i = 0; i < size; i++) {
		str += (char)(rand() % 256);
	}
	self.tex.setAbsSize(64 * str.size(), 64);
	self.tex.setText(str);

}