#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Evt_Display.h"

class Factory : public DisplayListener {
public:

	Factory();

private:

	void onDrawGeometry(GBuffer&) override;

	Mesh mesh;
	Transform trans;

};