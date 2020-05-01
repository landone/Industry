#pragma once

#include "Button.h"
#include "Text.h"

class UIControl {
public:

	UIControl();

private:

	Image img;
	Button gear;
	Text tex;
	Texture background;

	static void gearCbk(Button&, void*);

};