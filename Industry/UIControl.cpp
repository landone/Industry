#include "UIControl.h"

UIControl::UIControl() {

	img.setTexture(Texture("textures/steel.png"));
	img.setRelPos(-1, -1);
	img.setRelSize(0, 0);
	img.setAbsSize(128, 96);
	img.setTiled(true);

}