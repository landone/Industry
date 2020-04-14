#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Evt_Display.h"

class Factory : public DisplayListener {
public:

	Factory();

private:

	void onDrawGeometry(GBuffer&) override;

	Mesh mesh;
	Texture tex;
	Transform trans;

};