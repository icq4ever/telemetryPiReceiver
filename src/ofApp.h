#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "canvas.h"

#define PORT 9000
#define recInterval 100

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
	void drawInputStatus(int x, int y);
	void drawRpmSpeed(int x, int y);
	void drawLapTimeInformation(int x, int y);

	// rpmDrawing
	void rpmDrawing(int x, int y);

	timeTemplate seconds2lapT(float seconds);
	timeTemplate millis2lapT(int milliSeconds);

	string lapT2String(timeTemplate t);

	timeTemplate currentLap;
	timeTemplate lastLap;
	timeTemplate bestLap;

	ofFbo rpmFbo;
	//ofPixels rpmPixels;

	canvas drawingCanvas;

	TstaticData staticData;
	telemetryData tData;
	ofPolyline layout;
};

