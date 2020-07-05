#pragma once

#include "Button.h"
#include "Text.h"
#include "Machine.h"

class UIControl {
public:

	UIControl();

	/* Display monetary value */
	void setMoney(long long);

	/* Set machine buttons in store */
	void setMachines(const std::vector<MACHINES>&, void(*callback)(MACHINES, void*), void* data);

private:

	Image rateTab;
	Image totalTab;
	Text money;
	Image mainTab;
	Image menu;
	Button factoryBtn;
	Button gear;

	struct StoreButton {
		MACHINES index;
		Button button;
		Text text;
	};
	std::vector<StoreButton*> machines;
	void (*machineBuyCbk)(MACHINES, void*) = nullptr;
	void* machineBuyCbkData = nullptr;

	static void gearCbk(Button&, void*);
	static void machineCbk(Button&, void*);
	static void factoryCbk(Button&, void*);

};