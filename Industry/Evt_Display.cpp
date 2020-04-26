#include "Evt_Display.h"
#include <vector>
#include <algorithm>
#include <time.h>

static std::vector<DisplayListener*> listeners;
static DisplayListener::LayerNode* layerHeads[GUILayer_Front] = { nullptr };
long long Evt_Display::lastFrame = 0;
long long Evt_Display::thisFrame = 0;

DisplayListener::DisplayListener() : myNode{ 0 } {
	listeners.push_back(this);
}

DisplayListener::DisplayListener(const DisplayListener& t) : myNode{ 0 } {
	listeners.push_back(this);
}

DisplayListener::~DisplayListener() {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());
	removeGUILayer();
}

void DisplayListener::setGUILayer(GUILayer mLayer) {

	if (mLayer == layer) {
		return;
	}

	removeGUILayer();
	layer = mLayer;

	/* Append to new list as head */
	if (layer != GUILayer_None) {
		int index = (int)layer - 1;
		myNode.obj = this;
		myNode.next = layerHeads[index];
		myNode.prev = nullptr;
		if (layerHeads[index] != nullptr) {
			layerHeads[index]->prev = &myNode;
		}
		layerHeads[index] = &myNode;
	}

}

void DisplayListener::removeGUILayer() {

	/* Remove from previous list */
	if (layer != GUILayer_None) {
		if (myNode.prev) {
			myNode.prev->next = myNode.next;
		}
		else {
			/* If no prev, we must be head */
			layerHeads[(int)layer - 1] = myNode.next;
		}
		if (myNode.next) {
			myNode.next->prev = myNode.prev;
		}
	}

	layer = GUILayer_None;

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
	for (int i = 0; i < (int)GUILayer_Front; i++) {
		DisplayListener::LayerNode* node = layerHeads[i];
		while (node) {
			node->obj->onDrawGUI(gBuffer);
			node = node->next;
		}
	}
}

void Evt_Display::sendDraw3DGUI(GBuffer& gBuffer) {
	for (int i = 0; i < (int)GUILayer_Front; i++) {
		DisplayListener::LayerNode* node = layerHeads[i];
		while (node) {
			node->obj->onDraw3DGUI(gBuffer);
			node = node->next;
		}
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