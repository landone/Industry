#pragma once

#include "Button.h"

class UIControl {
public:

	UIControl();

private:

	Image img;
	Button gear;
	Texture background;

	static void gearCbk(Button&, void*);

};