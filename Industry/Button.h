#pragma once

#include "Image.h"

class Button : public Image {
public:

	Button(Texture);

	void setCallback(void(*f)());

private:

	bool onMouseRelease(int, int, int) override;

	void(*callback)() = nullptr;

};