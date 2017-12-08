#include "canvas.h"

Canvas::Canvas()
{
	bDraw = false;
	fbo.allocate(EXPORT_WIDTH, EXPORT_HEIGHT, GL_RGBA);
	pixels.allocate(EXPORT_WIDTH, EXPORT_HEIGHT, GL_RGBA);
	exportImage.allocate(EXPORT_WIDTH, EXPORT_HEIGHT, OF_IMAGE_COLOR_ALPHA);
	exportImage.setUseTexture(false);
	fbo.readToPixels(pixels);
	
	fbo.begin();
	ofClear(0);
	fbo.end();
}


Canvas::~Canvas()
{
}

void Canvas::pushPolyline(ofPoint p) {
	circuitLayout.addVertex(p);
}

void Canvas::pushPolyline(float x, float y, float z) {
	circuitLayout.addVertex(x, y, z);
}

void Canvas::updateCarPosition(float x, float y, float z, float heading) {
	car2DPosition.x = x;
	car2DPosition.y = y;
	car2DPosition.z = z;
	carHeadingDegree = (int)(ofRadToDeg(heading) + 180) % 360;
}

void Canvas::updateFbo(float pedal) {
	fbo.begin();
	//ofClear(0, 0, 0, 0);
	ofPushMatrix();
	ofPushStyle();
	
	
	ofTranslate(EXPORT_WIDTH/2, EXPORT_HEIGHT/2, 0);
	ofColor brushColor = ofColor::red.getLerped(ofColor::green, pedal);
	ofTranslate(car2DPosition.x, car2DPosition.y, car2DPosition.z);
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	ofSetColor(brushColor, 5);
	ofCircle(0,0, 3);
	
	ofDisableBlendMode();
	ofDisableAlphaBlending();
	//glDisable(GL_BLEND);
	ofPopStyle();
	ofPopMatrix();
	
	fbo.end();
}

void Canvas::draw(float x, float y) {

	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	
	fbo.draw(-EXPORT_WIDTH/2, -EXPORT_HEIGHT/2);

	ofSetHexColor(0xFFFFFF);
	ofSetLineWidth(2);
	if(bDrawLayoutOn)	 circuitLayout.draw();

	ofSetHexColor(0xFFFFFF);
	ofFill();
	
	ofPushMatrix();
	ofBeginShape();
	ofTranslate(car2DPosition);
	ofRotate(carHeadingDegree);
	ofVertex(0, -10);
	ofVertex(-5, 10);
	ofVertex(5, 10);
	ofEndShape();
	ofPopMatrix();
	
	//ofDrawCircle(car2DPosition, 5);


	
	
	ofPopStyle();
	ofPopMatrix();
}

void Canvas::clearLayout() {
	circuitLayout.clear();
}

void Canvas::exportFBO(string fileName) {
	fbo.readToPixels(pixels);
	exportImage.setFromPixels(pixels);
	exportImage.saveImage("exportImages/" + fileName + ".png", OF_IMAGE_QUALITY_BEST);
}