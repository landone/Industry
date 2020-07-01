#pragma once

#include "Model.h"

enum MACHINES {
	MACHINE_BOILER,
	MAX_MACHINES
};

class Machine {
public:

	Machine(MACHINES); 

	MACHINES getType() { return type; }
	Model& getModel() { return model; }
	std::string getName() { return getName(type); }
	std::string getDescription() { return getDescription(type); }

	static std::string getName(MACHINES);
	static std::string getDescription(MACHINES);

private:

	MACHINES type;
	Model model;

	static const std::string MACHINE_NAMES[MAX_MACHINES];
	static const std::string MACHINE_DESC[MAX_MACHINES];

};