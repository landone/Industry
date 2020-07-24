#include "UIControl.h"
#include <iostream>

UIControl::UIControl() {

	rateTab.setTexture(TEXTURE_UI);
	rateTab.setTiled(true);
	rateTab.setRelPos(1, -1);
	rateTab.setAbsPos(-256, 0);
	rateTab.setRelSize(0, 0);
	rateTab.setAbsSize(256, 48);

	totalTab.setTexture(TEXTURE_UI);
	totalTab.setTiled(true);
	totalTab.setRelPos(-1, 1);
	totalTab.setRelSize(0, 0);
	totalTab.setAbsPos(0, -48);
	totalTab.setAbsSize(256, 48);

	money.setRelPos(-1, 1);
	money.setAbsPos(0, -36);
	money.setFontSize(24);
	money.setText("$000.000");

	mainTab.setTexture(TEXTURE_UI);
	mainTab.setTiled(true);
	mainTab.setRelPos(-1, -1);
	mainTab.setRelSize(0, 0);
	mainTab.setAbsSize(128, 96);

	menu.setTexture(TEXTURE_UI);
	menu.setTiled(true);
	menu.setRelPos(-1, -1);
	menu.setAbsPos(128, 0);
	menu.setRelSize(0, 0);
	menu.setAbsSize(384, 96);
	menu.setVisibility(false);

	factoryBtn.setTexture(TEXTURE_GEAR);
	factoryBtn.setRelPos(1, 1);
	factoryBtn.setAbsPos(-64, -64);
	factoryBtn.setRelSize(0, 0);
	factoryBtn.setAbsSize(64, 64);
	factoryBtn.setCallback(factoryCbk, this);

	gear.setTexture(TEXTURE_GEAR);
	gear.setRelPos(-1, -1);
	gear.setAbsPos(48, 32);
	gear.setRelSize(0, 0);
	gear.setAbsSize(32, 32);
	gear.setCallback(gearCbk, this);

}

void UIControl::setMachines(const std::vector<MACHINES>& list, void(*callback)(MACHINES, void*), void* data) {

	machineBuyCbk = callback;
	machineBuyCbkData = data;

	for (unsigned int i = 0; i < machines.size(); i++) {
		delete machines[i];
	}
	machines.clear();

	bool visible = menu.getVisibility();
	for (unsigned int i = 0; i < list.size(); i++) {

		machines.push_back(new StoreButton);
		StoreButton& item = *machines[i];
		item.index = list[i];
		Button& b = item.button;
		Text& t = item.text;

		b.setTexture(TEXTURES::TEXTURE_GEAR);
		b.setVisibility(visible);
		b.setRelPos(-1, -1);
		b.setAbsPos(128 + (float)i * 96, 16);
		b.setRelSize(0, 0);
		b.setAbsSize(64, 64);
		b.setCallback(machineCbk, this);
		
		t.setVisibility(visible);
		t.setRelPos(-1, -1);
		t.setAbsPos(b.getAbsPos() - glm::vec2(0, 16));
		t.setRelSize(0, 0);
		t.setFontSize(12);
		t.setText(Machine::getName(item.index));

	}

}

void UIControl::gearCbk(Button& button, void* data) {

	UIControl& self = (*(UIControl*)data);
	bool toVis = !self.menu.getVisibility();
	self.menu.setVisibility(toVis);

	for (int i = 0; i < self.machines.size(); i++) {
		self.machines[i]->button.setVisibility(toVis);
		self.machines[i]->text.setVisibility(toVis);
	}

}

void UIControl::machineCbk(Button& button, void* data) {

	UIControl& self = (*(UIControl*)data);

	if (!self.machineBuyCbk) {
		return;
	}

	for (unsigned int i = 0; i < self.machines.size(); i++) {
		if ((&button) == &self.machines[i]->button) {
			self.machineBuyCbk(self.machines[i]->index, self.machineBuyCbkData);
			break;
		}
	}

}

void UIControl::factoryCbk(Button& btn, void* data) {

	UIControl& self = (*(UIControl*)data);

}

void UIControl::setMoney(long long amt) {

	std::string output = "$";
	std::string remain = "";
	char symbol = '\0';
	static const long long BILLION = 1000000000;
	static const long long MILLION = 1000000;
	static const long long GRAND = 1000;
	if (amt >= BILLION) {
		output += std::to_string(amt / BILLION);
		remain = std::to_string((amt % BILLION) / MILLION);
		symbol = 'B';
	}
	else if (amt >= MILLION) {
		output += std::to_string(amt / MILLION);
		remain = std::to_string((amt % MILLION) / GRAND);
		symbol = 'M';
	}
	else if (amt >= GRAND) {
		output += std::to_string(amt / GRAND);
		remain = std::to_string(amt % GRAND);
		symbol = 'K';
	}
	else {
		output += std::to_string(amt);
	}

	if (symbol != '\0') {
		if (remain.size() > 0 && remain != "0") {
			output += ".";
			for (size_t i = remain.size(); i < 3; i++) {
				output += "0";
			}
			output += remain;
		}
		output += symbol;
	}

	money.setText(output);

}