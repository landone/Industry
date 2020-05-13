#pragma once

#include "Button.h"
#include "Text.h"

class UIControl {
public:

	UIControl();

	/* Display monetary value */
	void setMoney(long long);

private:

	Image rateTab;
	Image totalTab;
	Text money;
	Image mainTab;
	Image menu;
	Button factoryBtn;
	Button gear;
	Text tex;
	Texture background;

	static void gearCbk(Button&, void*);
	static void factoryCbk(Button&, void*);

};