#pragma once

#include "Machine.h"
#include "Model.h"

class Factory {
public:

	Factory();

	/* Get list of machines allowed in this factory */
	const std::vector<MACHINES>& getMachineTypes() { return machineTypes; }
	/* Raycast to position selector. */
	void raycast(glm::vec3 orig, glm::vec3 dir);
	/* Attempt to put machine on selected space */
	bool putMachine(MACHINES);
	/* Attempt to remove selected machine */
	bool removeMachine();
	/*
	Return pointer to selected machine.
	Possibly null pointer.
	*/
	Machine* getSelection(int* index = nullptr);

private:

	/* Building range boundary data */
	struct BuildRange {
		int dim[2]; //Dimensions (x,z)
		int pos[3]; //Position (x,y,z)
		Machine** machines;
	};

	Model mdl;
	Model selector;
	int selectedRange = -1;

	std::vector<BuildRange> ranges;
	std::vector<MACHINES> machineTypes;

};