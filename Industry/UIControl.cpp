#include "UIControl.h"
#include <iostream>

UIControl::UIControl() {

	background.Load("textures/steel.png");

	rateTab.setTexture(background);
	rateTab.setTiled(true);
	rateTab.setRelPos(1, -1);
	rateTab.setAbsPos(-256, 0);
	rateTab.setRelSize(0, 0);
	rateTab.setAbsSize(256, 48);

	totalTab.setTexture(background);
	totalTab.setTiled(true);
	totalTab.setRelPos(-1, 1);
	totalTab.setRelSize(0, 0);
	totalTab.setAbsPos(0, -48);
	totalTab.setAbsSize(256, 48);

	money.setRelPos(-1, 1);
	money.setRelSize(0, 0);
	money.setAbsPos(0, -48);
	money.setAbsSize(128, 48);
	money.setText("$");

	mainTab.setTexture(background);
	mainTab.setTiled(true);
	mainTab.setRelPos(-1, -1);
	mainTab.setRelSize(0, 0);
	mainTab.setAbsSize(128, 96);

	menu.setTexture(background);
	menu.setTiled(true);
	menu.setRelPos(-1, -1);
	menu.setAbsPos(128, 0);
	menu.setRelSize(0, 0);
	menu.setAbsSize(384, 96);
	menu.setVisibility(false);

	factoryBtn.setTexture(Texture("textures/gear.png"));
	factoryBtn.setRelPos(1, 1);
	factoryBtn.setAbsPos(-64, -64);
	factoryBtn.setRelSize(0, 0);
	factoryBtn.setAbsSize(64, 64);
	factoryBtn.setCallback(factoryCbk, this);

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
	tex.setAbsPos(128, 0);
	tex.setRelSize(0, 0);
	tex.setAbsSize(64 * str.size(), 64);
	tex.setVisibility(false);

}

void UIControl::gearCbk(Button& button, void* data) {

	UIControl& self = (*(UIControl*)data);
	self.menu.setVisibility(!self.menu.getVisibility());
	self.tex.setVisibility(self.menu.getVisibility());

}

void UIControl::factoryCbk(Button& btn, void* data) {

	std::cout << "Pressed\n";

}