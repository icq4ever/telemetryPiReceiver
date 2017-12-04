#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	receiver.setup(PORT);
	ofBackground(54);

	rpmFbo.allocate(600, 600, GL_RGBA);
	rpmFbo.begin();
	ofClear(0);
	rpmFbo.end();
	//rpmPixels.allocate(600, 600, OF_PIXELS_RGBA);

	lastCheckedTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	getOSCMessage();


	// save to rpmFbo
	rpmFbo.begin();
	ofPushMatrix();
	//ofSetHexColor(0xFFFFFF);
	ofSetColor(ofColor::green.getLerped(ofColor::red, ofMap(tData.rpm, 8000, staticData.maxRpm, 0, 1)));
	ofNoFill();
	ofTranslate(150, 150);
	ofRotate(ofMap(tData.normalizedCarPosition, 0, 1, 0, 360));
	ofDrawLine(50, 0, ofMap(tData.rpm, 0, staticData.maxRpm, 50, 150), 0);
	ofPopMatrix();
	rpmFbo.end();

	// save to pixel
	//rpmFbo.readToPixels(rpmPixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(54);
	
	ofPushMatrix();
	drawInputStatus(50, 50);
	drawRpmSpeed(400, 50);
	drawLapTimeInformation(50, 300);
	rpmDrawing(300, 300);
	ofPopMatrix();

	ofPushMatrix();
	ofPushStyle();
	ofTranslate(ofGetWidth() * 2 / 3, ofGetHeight() / 2);
	//ofScale(2 / 3, 2 / 3, 2 / 3);
	ofSetLineWidth(3);
	ofSetHexColor(0xFFFFFf);
	layout.draw();
	ofPopStyle();
	ofPopMatrix();
}

void ofApp::getOSCMessage() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// car/track information
		if (m.getAddress() == "/playerInfo/carName")				staticData.carInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerInfo/trackName")				staticData.trackInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerinfo/playerName")				staticData.playerName = m.getArgAsString(0);

		// car info
		if (m.getAddress() == "/carInfo/maxRPM")					staticData.maxRpm = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/maxTorque")					staticData.maxTorque = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/hasDRS")					m.getArgAsInt32(0) == 1 ? staticData.hasDRS = true : staticData.hasDRS = false;
		if (m.getAddress() == "/carInfo/hasERS")					m.getArgAsInt32(0) == 1 ? staticData.hasERS = true : staticData.hasERS = false;

		if (m.getAddress() == "/telemetry/completedLaps")			staticData.completedLaps = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/currentLapTimeMillis")	tData.currentLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/lastLapTimeMillis")		staticData.lastLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/bestLapTimeMillis")		staticData.bestLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/normalizedCarPosition")	tData.normalizedCarPosition = m.getArgAsFloat(0);

		// car status		  
		if (m.getAddress() == "/telemetry/gear")			tData.gear = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/rpms")			tData.rpm = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/speedKmh")		tData.speedKmh = (int)m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/heading")			tData.heading = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/pitch")			tData.pitch = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/roll")			tData.roll = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/carCoordinates/x")	tData.carCoordinates.x = m.getArgAsFloat(0);;
		if (m.getAddress() == "/telemetry/carCoordinates/y")	tData.carCoordinates.y = m.getArgAsFloat(0);;
		if (m.getAddress() == "/telemetry/carCoordinates/z")	tData.carCoordinates.z = m.getArgAsFloat(0);;


		if (m.getAddress() == "/telemetry/accG/x")			tData.accG.x = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/accG/y")			tData.accG.y = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/accG/z")			tData.accG.z = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/velocity/x")		tData.velocity.x = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/velocity/y")		tData.velocity.y = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/velocity/z")		tData.velocity.z = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/tireTemp/fl")		tData.tireTemp.x = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/fr")		tData.tireTemp.y = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/rl")		tData.tireTemp.z = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/rr")		tData.tireTemp.w = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/drsAvailable")	m.getArgAsInt32(0) == 1 ? tData.drsAvailable = true : tData.drsAvailable = false;
		if (m.getAddress() == "/telemetry/drsEnabled")		m.getArgAsInt32(0) == 1 ? tData.drsEnabled = true : tData.drsEnabled = false;


		// control status	  "
		if (m.getAddress() == "/controller/clutch")			tData.clutch = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/brake")			tData.brake = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/throttle")		tData.throttle = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/steerAngle")		tData.steerAngle = m.getArgAsFloat(0);

		// drawing
		//cout << tData.carCoordinates.x << endl;
		if (!(tData.carCoordinates.x == 0 && tData.carCoordinates.y == 0 && tData.carCoordinates.z == 0)) {
			layout.addVertex(tData.carCoordinates.x / 2, tData.carCoordinates.y / 2, tData.carCoordinates.z / 2);
		}
	}
}

void ofApp::drawInputStatus(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	ofSetHexColor(0x000000);
	ofDrawRectangle(0, 0, 288, 100);

	ofDrawBitmapStringHighlight("INPUT STATUS \nclutch / brake / throttle / steer  ", 4, 110);
	
	// draw Clutch
	ofTranslate(40, 10);
	ofSetColor(ofColor::blue);
	ofDrawRectangle(0, ofMap(tData.clutch, 1, 0, 80, 0, true), 20, ofMap(tData.clutch, 1, 0, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::red);
	ofDrawRectangle(0, ofMap(tData.brake, 0, 1, 80, 0, true), 20, ofMap(tData.brake, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::green);
	ofDrawRectangle(0, ofMap(tData.throttle, 0, 1, 80, 0, true), 20, ofMap(tData.throttle, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofNoFill();
	ofSetColor(ofColor::white);
	ofPushMatrix();
	ofTranslate(40, 40);
	ofRotate(ofMap(tData.steerAngle, -1, 1, -180, 180));
	//cout << steerAngle << endl;
	ofDrawLine(0, -40, 0, -30);
	ofDrawCircle(0, 0, 40);
	ofDrawCircle(0, 0, 30);
	ofDrawLine(-30, 0, 30, 0);
	ofDrawLine(0, 0, 0, 30);
	ofPopMatrix();
	ofPopStyle();
	ofPopMatrix();
}
void ofApp::drawRpmSpeed(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	
	ofFill();
	ofSetColor(ofColor::black);
	ofDrawRectangle(0, 10, 400, 20);
	ofSetColor(ofColor::lightGreen);
	ofDrawRectangle(0, 10, ofMap(tData.rpm, 0, staticData.maxRpm, 0, 400), 20);
	ofNoFill();
	ofSetColor(ofColor::white);
	ofDrawRectangle(0, 10, 400, 20);

	ofDrawBitmapStringHighlight(ofToString(tData.speedKmh) + "Km/h - " + ofToString(tData.rpm, 0) + " RPM", 0, 50);

	ofPopStyle();
	ofPopMatrix();
}

timeTemplate ofApp::seconds2lapT(float seconds) {
	timeTemplate t;
	t.min = (int)seconds / 60;
	t.second = (int)seconds % 60;
	t.millisecond = (int)((seconds - (int)seconds) * 100);

	return t;
}

timeTemplate ofApp::millis2lapT(int milliSeconds) {
	timeTemplate t;
	t.millisecond = milliSeconds % 1000;
	t.second = (milliSeconds / 1000) % 60;
	t.min = (milliSeconds / 1000) / 60;

	return t;
}

string ofApp::lapT2String(timeTemplate t) {
	string minStr, secStr, millisStr;
	if (t.min < 10)			minStr = "0" + ofToString(t.min);
	else					minStr = ofToString(t.min);

	if (t.second < 10)		secStr = "0" + ofToString(t.second);
	else					secStr = ofToString(t.second);

	if (t.millisecond < 10)	millisStr = "0" + ofToString(t.millisecond);
	else					millisStr = ofToString(t.millisecond);

	return minStr + ":" + secStr + ":" + millisStr;
}

void ofApp::drawLapTimeInformation(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);

	currentLap = millis2lapT(tData.currentLapTimeMillis);
	lastLap = millis2lapT(staticData.lastLapTimeMillis);
	bestLap = millis2lapT(staticData.bestLapTimeMillis);
	
	//ofDrawBitmapStringHighlight("laptimeSeconds : " + ofToString(millis2lapT(currentLapTimeMillis)., 10, -10);
	ofDrawBitmapStringHighlight("current lapTime : " + lapT2String(currentLap), 10, 10);
	ofDrawBitmapStringHighlight("   last lapTime : " + lapT2String(lastLap), 10, 30);
	ofDrawBitmapStringHighlight("   best lapTime : " + lapT2String(bestLap), 10, 50);
	

	ofPopStyle();
	ofPopMatrix();
}

void ofApp::rpmDrawing(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);

	rpmFbo.draw(0, 0);

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }
