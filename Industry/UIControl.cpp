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

}

void UIControl::gearCbk(Button& button, void* data) {

	UIControl& self = (*(UIControl*)data);
	self.img.setVisibility(!self.img.getVisibility());

}