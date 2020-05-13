#pragma once

#include "Mesh.h"
#include "Assets.h"
#include "Entity.h"
#include "Evt_Display.h"

class Model : public Entity, public DisplayListener {
public:

	Model();

	void setModel(MODELS);
	void setVisible(bool);

	MODELS getType() { return type; }

private:

	void onDrawGeometry(GBuffer&) override;

	Mesh mesh;
	MODELS type;
	bool visible = true;

};