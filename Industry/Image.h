#pragma once

#include "Texture.h"
#include "Evt_Display.h"

class Image : public DisplayListener {
public:

	Image(Texture);

	void onDrawGUI(GBuffer&) override;

	void setRelPos(float x, float y);
	void setAbsPos(float x, float y);

	void setRelSize(float x, float y);
	void setAbsSize(float x, float y);

private:

	void calcTrans();
	bool changed = false;

	Transform trans;
	Texture tex;

	/* Conversion coeff. for pixels to screen units */
	float pxToScr[2] = { 0.0f };

	float relPos[2] = { 0.0f };
	float absPos[2] = { 0.0f };

	float relSz[2] = { 2.0f };
	float absSz[2] = { 0.0f };

};