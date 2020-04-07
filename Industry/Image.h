#pragma once

#include "Texture.h"
#include "Evt_Display.h"

class Image : public DisplayListener {
public:

	Image(Texture);

	void onDrawGUI(GBuffer&) override;

private:

	Transform trans;
	Texture tex;
	float relPos[2] = { 0.0f };
	float absPos[2] = { 0.0f };

};