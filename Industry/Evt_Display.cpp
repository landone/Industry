#include "Evt_Display.h"
#include <vector>
#include <algorithm>
#include <time.h>

static std::vector<DisplayListener*> listeners;
long long Evt_Display::lastFrame = 0;
long long Evt_Display::thisFrame = 0;

DisplayListener::DisplayListener() {
	listeners.push_back(this);
}

DisplayListener::DisplayListener(const DisplayListener& t) {
	listeners.push_back(this);
}

DisplayListener::~DisplayListener() {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());
}

void Evt_Display::sendFrame() {

	if (lastFrame == 0) {
		lastFrame = clock();
	}

	thisFrame = clock();
	double delta = (double)(thisFrame - lastFrame) / 1000.0;
	lastFrame = thisFrame;

	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onFrame(delta);
	}

}

void Evt_Display::sendDrawGUI(GBuffer& gBuffer) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDrawGUI(gBuffer);
	}
}

void Evt_Display::sendDraw3DGUI(GBuffer& gBuffer) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDraw3DGUI(gBuffer);
	}
}

void Evt_Display::sendDrawGeometry(GBuffer& gBuffer) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDrawGeometry(gBuffer);
	}
}

void Evt_Display::sendResize(int x, int y) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		listeners[i]->onResize(x, y);
	}
}