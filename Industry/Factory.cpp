#include "Factory.h"
#include "GameManager.h"

Factory::Factory() {

	mdl.setModel(MODEL_FACTORY1);
	mdl.setPos(glm::vec3(4, 0, -2));

	BuildRange range;
	range.pos[0] = -4;
	range.pos[1] = 0;
	range.pos[2] = -2;
	range.dim[0] = 8;
	range.dim[1] = 4;

	int area = range.dim[0] * range.dim[1];
	range.machines = new Machine*[area];
	for (unsigned int i = 0; i < area; i++) {
		range.machines[i] = nullptr;
	}
	ranges.push_back(range);

	selector.setModel(MODEL_SELECTOR);
	selector.setVisible(false);

	machineTypes.push_back(MACHINES::MACHINE_BOILER);
	machineTypes.push_back(MACHINES::MACHINE_BOILER);
	machineTypes.push_back(MACHINES::MACHINE_STEAM_ENGINE);
	machineTypes.push_back(MACHINES::MACHINE_STEAM_ENGINE);

}

bool Factory::removeMachine() {

	/* If no selection made */
	if (selectedRange == -1 || !selector.isVisible()) {
		return false;
	}

	BuildRange& range = ranges[selectedRange];
	glm::vec3 selectPos = selector.getPos();
	int index = ((int)selectPos.x - range.pos[0]) + ((int)selectPos.z - range.pos[2]) * range.dim[0];

	/* If no machine in place */
	if (range.machines[index] == nullptr) {
		return false;
	}

	delete range.machines[index];
	range.machines[index] = nullptr;
	
	return true;

}

bool Factory::putMachine(MACHINES type) {

	/* If no selection made */
	if (selectedRange == -1 || !selector.isVisible()) {
		return false;
	}

	BuildRange& range = ranges[selectedRange];
	glm::vec3 selectPos = selector.getPos();
	int index = ((int)selectPos.x - range.pos[0]) + ((int)selectPos.z - range.pos[2]) * range.dim[0];

	/* Machine already in place */
	if (range.machines[index] != nullptr) {
		return false;
	}

	Machine& mach = *(new Machine(type));
	range.machines[index] = &mach;
	mach.getModel().setPos(selectPos);

	return true;

}

void Factory::raycast(glm::vec3 orig, glm::vec3 dir) {

	float lastHeight = -INFINITY;
	int lastRange = -1;
	glm::vec3 result = orig;
	for (int i = 0; i < ranges.size(); i++) {
		/* Ignore blocked ranges */
		if ((float)ranges[i].pos[1] < lastHeight) {
			continue;
		}
		glm::vec3 col = GameManager::rayPlaneCol(orig, dir, glm::vec3(0, 1, 0), glm::vec3(1, ranges[i].pos[1], 1));
		/* If hit possible */
		if (col != orig) {
			int max[2] = { ranges[i].pos[0] + ranges[i].dim[0], ranges[i].pos[2] + ranges[i].dim[1] };
			/* If hit in range */
			if (col.x <= max[0] && col.x >= ranges[i].pos[0] &&
			col.z <= max[1] && col.z >= ranges[i].pos[2]) {
				lastHeight = (float)ranges[i].pos[1];
				lastRange = i;
				result = col;
			}
		}
	}
	if (lastRange != -1) {
		result.x = ceilf(result.x);
		result.z = floorf(result.z);
		selector.setPos(result);
		selector.setVisible(true);
		/* Remember selected range index */
		selectedRange = lastRange;
	}
	else {
		selector.setVisible(false);
		selectedRange = -1;
	}

}