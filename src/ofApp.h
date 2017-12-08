#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
//#include "canvas.h"
#include "ofxTrueTypeFontUL2.h"

#define PORT 9000
#define recInterval 100
#define MAX_MODE 7

struct timeTemplate {
	int min;
	int second;
	int millisecond;

};

struct TstaticData {
	string carInfo;
	string trackInfo;
	string playerName;

	// car info
	float maxTorque;
	float maxRpm;
	bool hasDRS;
	bool hasERS;

	int lastLapTimeMillis;
	int bestLapTimeMillis;
	int completedLaps;
};

struct telemetryData {
	int gear;
	int rpm;
	int speedKmh;
	int drsAvailable;
	int drsEnabled;

	float heading;	// heading of the car on world coord
	float pitch;	// pitch of the car on world coord
	float roll;		// roll of the car on world coord
	ofVec3f carCoordinates;		// car position on world coord(x,y,z)
	ofVec3f accG;
	ofVec3f velocity;
	ofVec4f tireTemp;

	float throttle;
	float brake;
	float clutch;
	float steerAngle;

	float normalizedCarPosition;
	float currentLapTimeMillis;
	
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	ofxOscReceiver receiver;
	void getOSCMessage();

	// osc save
	int64_t lastCheckedTimer;


	// draw telemetry functions
	void drawHeaders(int x, int y);
	void drawStaticData(int x, int y);
	void drawInputStatus(int x, int y);
	void drawRpmSpeed(int x, int y);
	void drawLapTimeInformation(int x, int y);
	void drawGearNo(int x, int y);

	timeTemplate seconds2lapT(float seconds);
	timeTemplate millis2lapT(int milliSeconds);

	string lapT2String(timeTemplate t);

	timeTemplate currentLap;
	timeTemplate lastLap;
	timeTemplate bestLap;

	ofFbo rpmFbo;
	ofFbo accFbo;
	ofFbo velFbo;

	void updateRpmFbo();
	void updateAccFbo();
	void updateVelFbo();
	void rpmDrawing(int x, int y);
	void accDrawing(int x, int y);
	void velDrawing(int x, int y);

	//canvas drawingCanvas;

	TstaticData staticData;
	telemetryData tData;
	//ofPolyline layout;
	//Canvas canvas;
	
	//ofxTrueTypeFontUL2 headerFont;
	//ofxTrueTypeFontUL2 gearFont;
	//ofxTrueTypeFontUL2 descFont;
	ofxTrueTypeFontUL2 bigFont1;
	ofxTrueTypeFontUL2 bigFont2;
	ofxTrueTypeFontUL2 bigFont3;
	ofxTrueTypeFontUL2 bigFont4;

	// current Lap Count
	int currentLapNo = -1;
	int lastLapNo = -1;
	bool bLapStart = false;

	// map zoom value
	//float zoomValue = 3.f / 4.f;

	uint64_t lastTickTimer;

	int playMode = 0;

	void drawGearNumber();
	void drawRPMText();
	void drawKPHText();
	void drawLapProgressPercentage();
	void drawLapTime();
	void tireTemperature();
	void drawInput();
	void drawRPMGraphic();
	void greenFrag();
};

