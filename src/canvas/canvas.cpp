#include "canvas.h"

canvas::canvas()
{
}


canvas::~canvas()
{
}

void canvas::pushPolyline(ofPoint p) {
	circuitLayout.addVertex(p);
}

void canvas::pushPolyline(float x, float y) {
	circuitLayout.addVertex(x, y);
}

void canvas::draw(float x, float y) {
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	circuitLayout.draw();
	ofPopStyle();
	ofPopMatrix();
}

void canvas::clearLayout() {
	circuitLayout.clear();
}