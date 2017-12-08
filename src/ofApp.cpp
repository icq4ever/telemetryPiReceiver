#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	receiver.setup(PORT);
	ofBackground(0);
	
	headerFont.loadFont("fonts/iosevka-term-ss02-medium.ttf", 48);
	gearFont.loadFont("fonts/iosevka-term-ss02-medium.ttf", 96);
	descFont.loadFont("fonts/iosevka-term-ss02-medium.ttf", 24);
							 
	bigFont1.loadFont("fonts/iosevka-term-ss02-medium.ttf", 600);
	bigFont2.loadFont("fonts/iosevka-term-ss02-medium.ttf", 540);
	bigFont3.loadFont("fonts/iosevka-term-ss02-medium.ttf", 340);
	bigFont3.setLineHeight(320);
	bigFont3.setLetterSpacing(-0.1);

	rpmFbo.allocate(300, 300, GL_RGBA);
	accFbo.allocate(320, 320, GL_RGBA);
	velFbo.allocate(320, 320, GL_RGBA);

	accFbo.begin();
	ofClear(0);
	accFbo.end();

	rpmFbo.begin();
	ofClear(0);
	rpmFbo.end();

	velFbo	.begin();
	ofClear(0);
	velFbo.end();
	//rpmPixels.allocate(600, 600, OF_PIXELS_RGBA);

	lastCheckedTimer = ofGetElapsedTimeMillis();
	canvas.clearLayout();

	bLapStart = false;
	lastTickTimer = ofGetElapsedTimeMillis();
	//lastLapNo = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
	getOSCMessage();
	
	currentLapNo = staticData.completedLaps + 1;
	
	updateRpmFbo();
	updateAccFbo();
	updateVelFbo();
	canvas.updateFbo(ofMap(tData.throttle - tData.brake, -1, 1, 0, 1));

	// save to pixel
	//rpmFbo.readToPixels(rpmPixels);

	if (ofGetElapsedTimeMillis() - lastTickTimer > 2000) {
		playMode++;
		if (playMode > MAX_MODE)	playMode = 0;
		lastTickTimer = ofGetElapsedTimeMillis();
	}

	
}

void ofApp::updateRpmFbo() {
	// save to rpmFbo
	rpmFbo.begin();
	
	ofPushMatrix();
	ofPushStyle();
	
	ofSetColor(ofColor::green.getLerped(ofColor::red, ofMap(tData.rpm, 8000, staticData.maxRpm, 0, 1)));
	ofNoFill();
	ofTranslate(150, 150);
	ofRotate(ofMap(tData.normalizedCarPosition, 0, 1, 0, 360));
	ofDrawLine(50, 0, ofMap(tData.rpm, 0, staticData.maxRpm, 50, 150), 0);
	
	ofPopStyle();
	ofPopMatrix();
	
	rpmFbo.end();
}

void ofApp::updateAccFbo() {
	// save to accFbo
	accFbo.begin();
	
	ofPushMatrix();
	ofPushStyle();
	//ofSetEnable
	ofSetColor(0, 0, 0, 5);
	ofDrawRectangle(0, 0, 320, 320);
	ofTranslate(160, 160);

	//ofBackground(0, 0.2);
	ofSetCircleResolution(200);
	ofSetHexColor(0xFFFFFF);
	ofNoFill();

	ofDrawCircle(0, 0, 50);
	ofDrawCircle(0, 0, 100);
	//ofDrawCircle(0, 0, 150);

	ofFill();
	ofDrawLine(-110, 0, -10, 0);
	ofDrawLine(110, 0, 10, 0);
	ofDrawLine(0, -110, 0, -10);
	ofDrawLine(0, 110, 0, 10);
	ofSetHexColor(0xFFFF00);
	ofDrawBitmapString("2", 35, -5);
	ofDrawBitmapString("4", 85, -5);
	//ofDrawBitmapString("6", 140, 0);

	ofSetHexColor(0xFF0000);
	ofDrawCircle(ofMap(tData.accG.x, -6, 6, -150, 150), ofMap(tData.accG.z, -6, 6, -150, 150), 5);
	
	ofPopStyle();
	ofPopMatrix();

	accFbo.end();
}

void ofApp::updateVelFbo() {
	// save to accFbo
	velFbo.begin();
	
	ofPushMatrix();
	ofPushStyle();
	
	//ofSetEnable
	ofSetColor(0, 0, 0, 5);
	ofDrawRectangle(0, 0, 320, 320);
	ofTranslate(160, 160);

	//ofBackground(0, 0.2);
	ofSetCircleResolution(200);
	ofSetHexColor(0xFFFFFF);
	ofNoFill();

	ofDrawCircle(0, 0, 50);
	ofDrawCircle(0, 0, 100);
	//ofDrawCircle(0, 0, 150);

	ofFill();
	ofDrawLine(-110, 0, -10, 0);
	ofDrawLine(110, 0, 10, 0);
	ofDrawLine(0, -110, 0, -10);
	ofDrawLine(0, 110, 0, 10);
	ofSetHexColor(0x00FFFF);
	ofDrawBitmapString("100", 35, -5);
	ofDrawBitmapString("100", 85, -5);
	//ofDrawBitmapString("6", 140, 0);

	ofSetHexColor(0x00FFFF);
	ofDrawCircle(ofMap(tData.velocity.x, -100, 100, -150, 150), ofMap(tData.velocity.z, -100, 100, -150, 150), 5);

	ofPopStyle();
	ofPopMatrix();

	velFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(54);

	//drawHeaders(50, 100);

	//drawStaticData(50, ofGetHeight() - 180);
	//
	//drawGearNo(50, 200);
	//drawRpmSpeed(180, 200);

	//drawLapTimeInformation(50, 350);
	//drawInputStatus(50, ofGetHeight() - 350);

	//accDrawing(300, 300);
	////velDrawing(700, 300);
	//rpmDrawing(700, 300);


	//if (!bLapStart) {
	//	ofPushMatrix();
	//	ofPushStyle();
	//
	//	//ofRectangle box = descFont.getStringBoundingBox("OUTLAP"
	//	ofRectangle box = descFont.getStringBoundingBox("OUTLAP", 0.f, 0.f);
	//	ofFill();
	//	ofTranslate(ofGetWidth() * 2 / 3, ofGetHeight() / 2);
	//	ofSetHexColor(0x000000);
	//	ofSetRectMode(OF_RECTMODE_CENTER);
	//	box.scale(1.1, 1.5);
	//	ofDrawRectangle(box);
	//	ofSetHexColor(0xFFFFFF);
	//	descFont.drawString("OUTLAP", 0, -34, 0, 0, UL2_TEXT_ALIGN_CENTER | UL2_TEXT_ALIGN_V_TOP);
	//	
	//	ofPopStyle();
	//	ofPopMatrix();
	//}
	//
	//canvas.draw(ofGetWidth() * 2 / 3, ofGetHeight() / 2);

	switch (playMode) {
		case 0:
			drawGearNumber();
			break;
		case 1:
			drawRPMText();
			break;
		case 2:
			drawKPHText();
			break;
		case 3:
			drawLapProgressPercentage();
			break;
		case 4:
			drawLapTime();
			break;
		case 5:
			drawInput();
			break;
		case 6:
			drawRPMGraphic();
			break;
		default:
			break;

	}

	//drawGearNumber();
	////drawRPMText();
	//drawKPHText();
	//drawLapProgressPercentage();
	//drawLapTime();

}

void ofApp::getOSCMessage() {
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// car/track information

		if (m.getAddress() == "/playerInfo/carName")				staticData.carInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerInfo/trackName")				staticData.trackInfo = m.getArgAsString(0);
		if (m.getAddress() == "/playerInfo/playerName")				staticData.playerName = m.getArgAsString(0);

		// car info
		if (m.getAddress() == "/carInfo/maxRPM")					staticData.maxRpm = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/maxTorque")					staticData.maxTorque = m.getArgAsFloat(0);
		if (m.getAddress() == "/carInfo/hasDRS")					m.getArgAsInt32(0) == 1 ? staticData.hasDRS = true : staticData.hasDRS = false;
		if (m.getAddress() == "/carInfo/hasERS")					m.getArgAsInt32(0) == 1 ? staticData.hasERS = true : staticData.hasERS = false;

		if (m.getAddress() == "/telemetry/completedLaps")			staticData.completedLaps = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/currentLapTimeMillis")	tData.currentLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/lastLapTimeMillis")		staticData.lastLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/bestLapTimeMillis")		staticData.bestLapTimeMillis = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/normalizedCarPosition") {
			tData.normalizedCarPosition = m.getArgAsFloat(0);
			
			if ((currentLapNo != lastLapNo) && (tData.normalizedCarPosition < 0.02)) {
				lastLapNo = currentLapNo;
				bLapStart = true;
			}
		}

		// car status		  
		if (m.getAddress() == "/telemetry/gear")			tData.gear = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/rpms")			tData.rpm = m.getArgAsInt32(0);
		if (m.getAddress() == "/telemetry/speedKmh")		tData.speedKmh = (int)m.getArgAsFloat(0);

		if (m.getAddress() == "/telemetry/heading")			tData.heading = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/pitch")			tData.pitch = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/roll")			tData.roll = m.getArgAsFloat(0);
		
		//if (m.getAddress() == "/telemetry/carCoordinates/x")	tData.carCoordinates.x = m.getArgAsFloat(0);;
		//if (m.getAddress() == "/telemetry/carCoordinates/y")	tData.carCoordinates.y = m.getArgAsFloat(0);;
		//if (m.getAddress() == "/telemetry/carCoordinates/z")	tData.carCoordinates.z = m.getArgAsFloat(0);;
		if (m.getAddress() == "/telemetry/carCoordinates") {
			tData.carCoordinates.x = m.getArgAsFloat(0);
			tData.carCoordinates.y = m.getArgAsFloat(1);
			tData.carCoordinates.z = m.getArgAsFloat(2);
		}

		//if (m.getAddress() == "/telemetry/accG/x")			tData.accG.x = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/accG/y")			tData.accG.y = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/accG/z")			tData.accG.z = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/accG") {
			tData.accG.x = m.getArgAsFloat(0);
			tData.accG.y = m.getArgAsFloat(1);
			tData.accG.z = m.getArgAsFloat(2);
		}

		//if (m.getAddress() == "/telemetry/velocity/x")		tData.velocity.x = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/velocity/y")		tData.velocity.y = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/velocity/z")		tData.velocity.z = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/velocity") {
			tData.velocity.x = m.getArgAsFloat(0);
			tData.velocity.y = m.getArgAsFloat(1);
			tData.velocity.z = m.getArgAsFloat(2);
		}

		//if (m.getAddress() == "/telemetry/tireTemp/fl")		tData.tireTemp.x = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/tireTemp/fr")		tData.tireTemp.y = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/tireTemp/rl")		tData.tireTemp.z = m.getArgAsFloat(0);
		//if (m.getAddress() == "/telemetry/tireTemp/rr")		tData.tireTemp.w = m.getArgAsFloat(0);
		if (m.getAddress() == "/telemetry/tireTemp") {
			tData.tireTemp.x = m.getArgAsFloat(0);
			tData.tireTemp.y = m.getArgAsFloat(1);
			tData.tireTemp.z = m.getArgAsFloat(2);
			tData.tireTemp.w = m.getArgAsFloat(3);
		}

		if (m.getAddress() == "/telemetry/drsAvailable")	m.getArgAsInt32(0) == 1 ? tData.drsAvailable = true : tData.drsAvailable = false;
		if (m.getAddress() == "/telemetry/drsEnabled")		m.getArgAsInt32(0) == 1 ? tData.drsEnabled = true : tData.drsEnabled = false;


		// control status	  "
		if (m.getAddress() == "/controller/clutch")			tData.clutch = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/brake")			tData.brake = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/throttle")		tData.throttle = m.getArgAsFloat(0);
		if (m.getAddress() == "/controller/steerAngle")		tData.steerAngle = m.getArgAsFloat(0);


		canvas.updateCarPosition(tData.carCoordinates.x * zoomValue, tData.carCoordinates.y * zoomValue, tData.carCoordinates.z * zoomValue, tData.heading);
		// drawing
		//cout << tData.carCoordinates.x << endl;
		if (bLapStart) {
			canvas.pushPolyline(tData.carCoordinates.x * zoomValue, tData.carCoordinates.y * zoomValue, tData.carCoordinates.z * zoomValue);
		}

		
	}
}

void ofApp::drawHeaders(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	string carName, circuitName;
	carName = staticData.carInfo;
	carName.erase(0, 3);
	circuitName = staticData.trackInfo;
	circuitName.erase(0, 3);
	carName = ofToUpper(carName);
	circuitName = ofToUpper(circuitName);

	ofSetHexColor(0x00FFFF);
	headerFont.drawString(carName, 0, 0);
	ofSetHexColor(0x00AAAA);
	headerFont.drawString(circuitName, 0, 60);
	ofPopStyle();
	ofPopMatrix();
}

void ofApp::drawStaticData(int x, int y) {
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x, y);
	ofDrawBitmapStringHighlight(
		"DRIVER NAME : " + staticData.playerName + " \n" +
		"TRACK NAME  : " + staticData.trackInfo + " \n" +
		"CAR INFO    : " + staticData.carInfo + " \n\n" +
		"MAX RPM     : " + ofToString(staticData.maxRpm) + " \n" +
		"MAX TOURQUE : " + ofToString(staticData.maxTorque) + " \n" +
		"HAS DRS     : " + ofToString(staticData.hasDRS) + "\n" +
		"HAS ERS     : " + ofToString(staticData.hasERS) + "\n" + 
		"lap start   : " + ofToString(bLapStart),
		0, 0);
	ofPopStyle();
	ofPopMatrix();
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

void ofApp::drawGearNo(int x, int y){
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(x,y);
	
	ofFill();
	ofSetColor(ofColor::fromHex(0xFFFFFF));
	string tempG;
	if(tData.gear == 0)				tempG = "R";
	else if (tData.gear == 1)		tempG = "N";
	else							tempG = ofToString(tData.gear - 1);
	
	gearFont.drawString(tempG, 0, 96);
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

	ofDrawBitmapStringHighlight(" current lap no : " + ofToString(currentLapNo), 10, 90);
	ofDrawBitmapStringHighlight("    last lap no : " + ofToString(lastLapNo), 10, 110);
	ofDrawBitmapStringHighlight("  norm position : " + ofToString(tData.normalizedCarPosition), 10, 130);
	

	ofPopStyle();
	ofPopMatrix();
}

void ofApp::rpmDrawing(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);

	rpmFbo.draw(0, 0);

	ofPopMatrix();
}


void ofApp::accDrawing(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);
	accFbo.draw(0, 0);
	ofPopMatrix();
}

void ofApp::velDrawing(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);
	velFbo.draw(0, 0);
	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case 'f' :
		case 'F':
			ofToggleFullscreen();
		break;
		case ' ':
			canvas.clearLayout();
			bLapStart = false;
			break;
		case '/':
			canvas.bDrawLayoutOn = !canvas.bDrawLayoutOn;
			break;
		case 's':
			canvas.fbo.readToPixels(canvas.pixels);
			canvas.exportFBO(staticData.carInfo + "_" + staticData.trackInfo);
			break;
		case OF_KEY_LEFT:
			playMode--;
			if (playMode < 0)	playMode = MAX_MODE;
			break;
		case OF_KEY_RIGHT:
			playMode++;
			if (playMode > MAX_MODE)	playMode = 0;
			break;
		default:
			break;
	}
}

void ofApp::drawGearNumber() {
	string tempG;
	if (tData.gear == 0)			tempG = "R";
	else if (tData.gear == 1)		tempG = "N";
	else							tempG = ofToString(tData.gear - 1);
	bigFont1.drawString(ofToString(tempG), ofGetWidth()/2, ofGetHeight()/2, 0.f, 0.f, UL2_TEXT_ALIGN_CENTER | UL2_TEXT_ALIGN_V_MIDDLE);
}
void ofApp::drawRPMText() {
	bigFont2.drawString(ofToString(tData.rpm), ofGetWidth()-80, ofGetHeight() / 2, 0.f, 0.f, UL2_TEXT_ALIGN_RIGHT | UL2_TEXT_ALIGN_V_MIDDLE);
}

void ofApp::drawKPHText() {
	bigFont1.drawString(ofToString(tData.speedKmh) + "K", ofGetWidth() - 200, ofGetHeight() / 2, 0.f, 0.f, UL2_TEXT_ALIGN_RIGHT | UL2_TEXT_ALIGN_V_MIDDLE);
}
void ofApp::drawLapProgressPercentage() {
	bigFont1.drawString(ofToString((int)(tData.normalizedCarPosition*100)) + "%", ofGetWidth() - 200, ofGetHeight() / 2, 0.f, 0.f, UL2_TEXT_ALIGN_RIGHT | UL2_TEXT_ALIGN_V_MIDDLE);
}
void ofApp::drawLapTime() {
	int intMillis = (int)tData.currentLapTimeMillis % 1000;
	int intSec = ((int)tData.currentLapTimeMillis / 1000) % 60;
	int intMin = ((int)tData.currentLapTimeMillis / 1000) / 60;

	string strMillis, strSec, strMin;

	if (intMillis < 10)			strMillis = "00" + ofToString(intMillis);
	else if (intMillis < 100)	strMillis = "0" + ofToString(intMillis);
	else						strMillis = ofToString(intMillis);
		
	if (intSec < 10)	strSec = "0" + ofToString(intSec);
	else				strSec = ofToString(intSec);

	if (intMin < 10)	strMin = "0" + ofToString(intMin);
	else				strMin = ofToString(intMin);

	bigFont3.drawString(
		strMin + ":" +
		strSec + ":" +
		strMillis, 
		80, 
		ofGetHeight() / 2, 
		0.f, 
		0.f, 
		UL2_TEXT_ALIGN_LEFT | UL2_TEXT_ALIGN_V_MIDDLE
	);
}

void ofApp::drawRPMGraphic() {
	ofPushStyle();
	ofSetCircleResolution(300);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(tData.rpm, 0, staticData.maxRpm* 0.8, 0, 400, true));
	ofPopStyle();
}


void ofApp::tireTemperature() {}

void ofApp::drawInput() {
	ofPushStyle();
	ofSetCircleResolution(300);
	ofSetHexColor(0xFF5555);
	ofDrawCircle(ofGetWidth() / 4, ofGetHeight()/2, ofMap(tData.brake, 0, 1, 0, 400));
	ofSetHexColor(0x55FFFF);
	ofDrawCircle(ofGetWidth() * 3 / 4, ofGetHeight()/2, ofMap(tData.throttle, 0, 1, 0, 400));
	ofPopStyle();
}

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
