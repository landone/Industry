#pragma once

#include "Button.h"
#include "Text.h"
#include "Machine.h"

class UIControl {
public:

	UIControl(void* gameManager);

	/* Display monetary value */
	void setMoney(long long);

	/* Set machine buttons in store */
	void setMachines(const std::vector<MACHINES>&, void(*callback)(MACHINES, void*));

	/* Display machine as selected */
	void showSelection(MACHINES);

	/* Set machine sell callback */
	void setSellCbk(void(*)(void*));

private:

	void* gameManagerPtr = nullptr;

	Image rateTab;
	Image totalTab;
	Text money;
	Image mainTab;
	Image menu;
	Button factoryBtn;
	Button gear;

	struct StoreButton {
		MACHINES index = MACHINES::MACHINE_BOILER;
		Button button;
		Text text;
	};
	StoreButton selectMachine;
	Text selectMachineDesc;
	/* Is select menu in use */
	bool isSelectMenu = false;
	/* Update menu to show correct info */
	void updateMenu();

	std::vector<StoreButton*> machines;
	void (*machineBuyCbk)(MACHINES, void*) = nullptr;
	void (*machineSellCbk)(void*) = nullptr;

	static void gearCbk(Button&, void*);
	static void machineCbk(Button&, void*);
	static void factoryCbk(Button&, void*);
	static void sellCbk(Button&, void*);

};