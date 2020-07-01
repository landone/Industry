#include "Factory.h"
#include "GameManager.h"

Factory::Factory() {

	mdl.setModel(MODEL_FACTORY1);
	mdl.setPos(glm::vec3(4, 0, -2));
	BuildRange range;
	range.height = 0;
	range.min[0] = -4;
	range.min[1] = -2;
	range.max[0] = 4;
	range.max[1] = 2;
	ranges.push_back(range);

	selector.setModel(MODEL_SELECTOR);
	selector.setVisible(false);

	machineTypes.push_back(MACHINES::MACHINE_BOILER);
	machineTypes.push_back(MACHINES::MACHINE_BOILER);
	machineTypes.push_back(MACHINES::MACHINE_BOILER);
	machineTypes.push_back(MACHINES::MACHINE_BOILER);

}

void Factory::raycast(glm::vec3 orig, glm::vec3 dir) {

	float lastHeight = -INFINITY;
	glm::vec3 result = orig;
	for (int i = 0; i < ranges.size(); i++) {
		/* Ignore blocked ranges */
		if (ranges[i].height < lastHeight) {
			continue;
		}
		glm::vec3 col = GameManager::rayPlaneCol(orig, dir, glm::vec3(0, 1, 0), glm::vec3(1, ranges[i].height, 1));
		/* If hit possible */
		if (col != orig) {
			/* If hit in range */
			if (col.x <= ranges[i].max[0] && col.x >= ranges[i].min[0] &&
			col.z <= ranges[i].max[1] && col.z >= ranges[i].min[1]) {
				lastHeight = ranges[i].height;
				result = col;
			}
		}
	}
	if (lastHeight > -INFINITY) {
		result.x = ceilf(result.x);
		result.z = floorf(result.z);
		selector.setPos(result);
		selector.setVisible(true);
	}

}