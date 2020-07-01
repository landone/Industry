#include "Machine.h"

const std::string Machine::MACHINE_NAMES[MAX_MACHINES] = {
	"Boiler"
};

const std::string Machine::MACHINE_DESC[MAX_MACHINES] = {
	"Generates electricity"
};

Machine::Machine(MACHINES type) {

	this->type = type;

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