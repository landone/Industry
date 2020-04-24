#pragma once

#include "Mesh.h"
#include "Entity.h"
#include "Evt_Display.h"

class Model : public Entity, public DisplayListener {
public:

	Model();

	bool setModel(std::string path, bool backfaceCull = true);
	void setVisible(bool);

	std::string getModel() { return mdlPath; }

private:

	void onDrawGeometry(GBuffer&) override;

	Mesh mesh;
	std::string mdlPath;
	bool visible = true;

};