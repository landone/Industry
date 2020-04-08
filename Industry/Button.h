#pragma once

#include "Image.h"
#include "Evt_Mouse.h"

class Button : public Image, MouseListener {
public:

	Button(Texture);

	void setCallback(void(*f)());

private:

	void onMouseRelease(int, int, int) override;

	void(*callback)() = nullptr;

};