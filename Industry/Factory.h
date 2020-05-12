#pragma once

#include "Model.h"

class Factory {
public:

	Factory();

	void raycast(glm::vec3 orig, glm::vec3 dir);

private:

	/* Building range boundary data */
	struct BuildRange {
		float height;
		int min[2];//(x,z)
		int max[2];//(x,z)
	};

	Model mdl;
	Model selector;

	std::vector<BuildRange> ranges;

};