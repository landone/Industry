#include "Machine.h"

const std::string Machine::MACHINE_NAMES[MAX_MACHINES] = {
	"Boiler",
	"Steam Engine"
};

const std::string Machine::MACHINE_DESC[MAX_MACHINES] = {
	"Boils water into steam",
	"Converts steam to electrical energy"
};

const MODELS Machine::MACHINE_MODELS[MAX_MACHINES] = {
	MODELS::MODEL_BOILER,
	MODELS::MODEL_PIPE
};

const long long Machine::MACHINE_PRICES[MAX_MACHINES] = {
	1000,
	2500
};

Machine::Machine(MACHINES type) {

	this->type = type;
	model.setModel(Machine::getModel(type));

}

std::string Machine::getName(MACHINES type) {

	if (type < 0 || type >= MAX_MACHINES) {
		return "";
	}

	return MACHINE_NAMES[type];

}

std::string Machine::getDescription(MACHINES type) {

	if (type < 0 || type >= MAX_MACHINES) {
		return "";
	}

	return MACHINE_DESC[type];

}

MODELS Machine::getModel(MACHINES type) {

	if (type < 0 || type >= MAX_MACHINES) {
		return (MODELS)0;
	}

	return MACHINE_MODELS[type];

}

long long Machine::getPrice(MACHINES type) {

	if (type < 0 || type >= MAX_MACHINES) {
		return 0;
	}

	return MACHINE_PRICES[type];

}