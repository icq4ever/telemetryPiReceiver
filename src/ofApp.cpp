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
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		
		// car/track information
		if (m.getAddress() == "/playerInfo/carName")				carInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerInfo/trackName")				trackInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerinfo/playerName")				playerName = m.getArgAsString(0);
		
		// car info
		if (m.getAddress() == "/carInfo/maxRPM")					maxRpm = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/maxTorque")					maxTorque = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/hasDRS")					m.getArgAsInt32(0) == 1 ? hasDRS = true : hasDRS = false;
		if (m.getAddress() == "/carInfo/hasERS")					m.getArgAsInt32(0) == 1 ? hasERS = true : hasERS = false;

		if (m.getAddress() == "/telemetry/completedLaps")			completedLaps = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/currentLapTimeMillis")	currentLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/lastLapTimeMillis")		lastLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/bestLapTimeMillis")		bestLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/normalizedCarPosition")	normalizedCarPosition = m.getArgAsFloat(0);

		// car status		  
		if (m.getAddress() == "/telemetry/gear")			gear = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/rpms")			rpms = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/speedKmh")		speedKmh = (int)m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/heading")			heading = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/pitch")			pitch = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/roll")			roll = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/carCoorindates/x")	carCoordinatesX = m.getArgAsFloat(0);;
		if (m.getAddress() == "/telemetry/carCoorindates/y")	carCoordinatesY = m.getArgAsFloat(0);;
		if (m.getAddress() == "/telemetry/carCoorindates/z")	carCoordinatesZ = m.getArgAsFloat(0);;

		
		if (m.getAddress() == "/telemetry/accG/x")			accX = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/accG/y")			accY = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/accG/z")			accZ = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/velocity/x")		velocityX = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/velocity/y")		velocityY = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/velocity/z")		velocityZ = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/tireTemp/fl")		tireTempFL = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/fr")		tireTempFR = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/rl")		tireTempRL = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp/rr")		tireTempRR = m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/drsAvailable")	m.getArgAsInt32(0) == 1 ? drsAvailable = true : drsAvailable = false;
		if (m.getAddress() == "/telemetry/drsEnabled")		m.getArgAsInt32(0) == 1 ? drsEnabled = true : drsEnabled = false;

					  
		// control status	  "
		if (m.getAddress() == "/controller/clutch")			clutch = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/brake")			brake = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/throttle")		throttle = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/steerAngle")		steerAngle = m.getArgAsFloat(0);
	}

	// save to rpmFbo
	rpmFbo.begin();
	ofPushMatrix();
	//ofSetHexColor(0xFFFFFF);
	ofSetColor(ofColor::green.getLerped(ofColor::red, ofMap(rpms, 8000, maxRpm, 0, 1)));
	ofNoFill();
	ofTranslate(150, 150);
	ofRotate(ofMap(normalizedCarPosition, 0, 1, 0, 360));
	ofDrawLine(50, 0, ofMap(rpms, 0, maxRpm, 50, 150), 0);
	ofPopMatrix();
	rpmFbo.end();

	// save to pixel
	//rpmFbo.readToPixels(rpmPixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(54);
	
	drawInputStatus(50, 50);
	drawRpmSpeed(400, 50);
	drawLapTimeInformation(50, 300);
	rpmDrawing(300, 300);
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
	ofDrawRectangle(0, ofMap(clutch, 1, 0, 80, 0, true), 20, ofMap(clutch, 1, 0, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::red);
	ofDrawRectangle(0, ofMap(brake, 0, 1, 80, 0, true), 20, ofMap(brake, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofFill();
	ofSetColor(ofColor::green);
	ofDrawRectangle(0, ofMap(throttle, 0, 1, 80, 0, true), 20, ofMap(throttle, 0, 1, 0, 80, true));
	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(0, 0, 20, 80);

	ofTranslate(50, 0);
	ofNoFill();
	ofSetColor(ofColor::white);
	ofPushMatrix();
	ofTranslate(40, 40);
	ofRotate(ofMap(steerAngle, -1, 1, -180, 180));
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
	ofDrawRectangle(0, 10, ofMap(rpms, 0, maxRpm, 0, 400), 20);
	ofNoFill();
	ofSetColor(ofColor::white);
	ofDrawRectangle(0, 10, 400, 20);

	ofDrawBitmapStringHighlight(ofToString(speedKmh) + "Km/h - " + ofToString(rpms, 0) + " RPM", 0, 50);

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

	currentLap = millis2lapT(currentLapTimeMillis);
	lastLap = millis2lapT(lastLapTimeMillis);
	bestLap = millis2lapT(bestLapTimeMillis);
	
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
