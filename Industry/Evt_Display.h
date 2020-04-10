#pragma once

#include "GBuffer.h"

class DisplayListener {
public:

	DisplayListener();
	DisplayListener(const DisplayListener&);
	~DisplayListener();

protected:

	virtual void onFrame(double delta) {}
	virtual void onDrawGUI(GBuffer&) {}
	virtual void onDraw3DGUI(GBuffer&) {}
	virtual void onDrawGeometry(GBuffer&) {}
	virtual void onResize(int, int) {}

	friend class Evt_Display;

};

class Evt_Display {
public:

	static void sendFrame(double delta);
	static void sendDrawGUI(GBuffer&);
	static void sendDrawGeometry(GBuffer&);
	static void sendDraw3DGUI(GBuffer&);
	static void sendResize(int x, int y);

};