#pragma once

#include "Texture.h"
#include "Evt_Display.h"

class Image : public DisplayListener {
public:

	Image(Texture);

	void setRelPos(float x, float y);
	void setRelPos(glm::vec2);
	void setAbsPos(float x, float y);
	void setAbsPos(glm::vec2);
	glm::vec2 getRelPos() { return relPos; }
	glm::vec2 getAbsPos() { return absPos; }
	/* Screen position accounting for both relative and absolute */
	glm::vec2 getTruePos();

	void setRelSize(float x, float y);
	void setRelSize(glm::vec2);
	void setAbsSize(float x, float y);
	void setAbsSize(glm::vec2);
	glm::vec2 getRelSize() { return relSz; }
	glm::vec2 getAbsSize() { return absSz; }
	/* Screen size accounting for both relative and absolute */
	glm::vec2 getTrueSize();

	void setTint(float r, float g, float b);
	void setTint(glm::vec3);
	glm::vec3 getTint() { return tint; }

protected:

	void onDrawGUI(GBuffer&) override;
	void onResize(int, int) override;

	/* Calculate trans values */
	void calcTrans();
	/* If trans values changed, calculate them */
	void checkChanged();
	bool changed = false;

	Transform trans;
	Texture tex;

	glm::vec2 relPos;
	glm::vec2 absPos;

	glm::vec2 relSz = glm::vec2(2, 2);
	glm::vec2 absSz;

	glm::vec3 tint = glm::vec3(1, 1, 1);
	bool tinted = false;

};