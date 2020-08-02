#include "Machine.h"

const std::string Machine::MACHINE_NAMES[MAX_MACHINES] = {
	"None",
	"Boiler",
	"Pipe"
};

const std::string Machine::MACHINE_DESC[MAX_MACHINES] = {
	"None",
	"Boils water into steam",
	"Transports materials"
};

const MODELS Machine::MACHINE_MODELS[MAX_MACHINES] = {
	MODELS::MODEL_PIPE,
	MODELS::MODEL_BOILER,
	MODELS::MODEL_PIPE
};

const long long Machine::MACHINE_PRICES[MAX_MACHINES] = {
	1,
	1000,
	200
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