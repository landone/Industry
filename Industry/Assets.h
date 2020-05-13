#pragma once

#include "Mesh.h"

enum MODELS {
	MODEL_BOILER,
	MODEL_PIPE,
	MODEL_SELECTOR,
	MODEL_FACTORY1,
	MAX_MODELS
};

class Assets {
public:

	static void LoadAll();
	/* Copy cached mesh */
	static void mesh(MODELS, Mesh&);

private:

	static void LoadMeshes();
	static Mesh meshes[MAX_MODELS];
	static const std::string MODEL_FOLDER;
	static const std::string MODEL_PATHS[MAX_MODELS];
	static const std::string MODEL_EXT;
	static bool MODEL_IS_CULL[MAX_MODELS];

};