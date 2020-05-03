#pragma once

#include "Button.h"
#include "Text.h"

class UIControl {
public:

	UIControl();

private:

	Image rateTab;
	Image totalTab;
	Image mainTab;
	Image menu;
	Button factoryBtn;
	Button gear;
	Text tex;
	Texture background;

	static void gearCbk(Button&, void*);
	static void factoryCbk(Button&, void*);

};