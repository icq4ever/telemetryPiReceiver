#pragma once
#include "ofMain.h"

#define EXPORT_WIDTH	1200
#define EXPORT_HEIGHT	1200

class Canvas {
public:
	Canvas();
	~Canvas();

	void pushPolyline(ofPoint p);
	void pushPolyline(float x, float y, float z);
	void updateCarPosition(float x, float y, float z, float heading);
	void draw(float x, float y);
	void updateFbo(float pedal);
	void clearLayout();

	void exportFBO(string fileName);

	ofPoint  car2DPosition;
	ofPolyline circuitLayout;
	ofFbo fbo;
	ofPixels pixels;
	ofImage exportImage;
	
	int carHeadingDegree;
	bool bDrawLayoutOn = false;
	bool bDraw = false;
	ofColor paint;

	// particle class
};

