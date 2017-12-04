#pragma once
#include "ofMain.h"

class canvas
{
public:
	canvas();
	~canvas();

	void pushPolyline(ofPoint p);
	void pushPolyline(float x, float y);
	void draw(float x, float y);
	void clearLayout();

	ofPolyline circuitLayout;
	ofFbo fbo;
};

