#include "Assets.h"

Mesh Assets::meshes[MAX_MODELS];
const std::string Assets::MODEL_FOLDER = "models/";
const std::string Assets::MODEL_EXT = ".obj";
bool Assets::MODEL_IS_CULL[MAX_MODELS] = {
	true,
	false,
	false,
	true
};
const std::string Assets::MODEL_PATHS[MAX_MODELS] = {
	"Boiler",
	"Pipe",
	"Selector",
	"DefaultFactory"
};

Texture Assets::textures[MAX_TEXTURES];
const std::string Assets::TEXTURE_FOLDER = "textures/";
const std::string Assets::TEXTURE_PATHS[MAX_TEXTURES] = {
	"missing.png",
	"steel.png",
	"gear.png",
	"freeman.png"
};

void Assets::LoadAll() {

	LoadMeshes();
	LoadTextures();

}

void Assets::LoadMeshes() {

	for (int i = 0; i < MAX_MODELS; i++) {

		meshes[i].Load(MODEL_FOLDER + MODEL_PATHS[i] + MODEL_EXT, MODEL_IS_CULL[i]);

	}

}

void Assets::LoadTextures() {

	for (int i = 0; i < MAX_TEXTURES; i++) {

		textures[i].Load(TEXTURE_FOLDER + TEXTURE_PATHS[i]);

	}

}

void Assets::mesh(MODELS type, Mesh& dest) {

	if ((int)type >= 0 && type < MAX_MODELS) {
		dest.copy(meshes[type]);
	}

}

Texture Assets::texture(TEXTURES type) {

	if ((int)type < 0 || type >= MAX_TEXTURES) {
		type = TEXTURE_NONE;
	}
	return textures[type];

}