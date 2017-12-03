#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9000
#define recInterval 100

struct timeTemplate {
	int min;
	int second;
	int millisecond;
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
	string messageAddrHeader = "/telemetry/";


	// player information
	string carInfo;
	string trackInfo;
	string playerName;

	float layoutLength;

	// car info
	float maxTorque;
	float maxRpm;
	bool hasDRS;
	bool hasERS;

	// lap info
	int completedLaps;
	int currentLapTimeMillis;
	int lastLapTimeMillis;
	int bestLapTimeMillis;
	float normalizedCarPosition;

	// car status
	int gear;
	int rpms;
	int speedKmh;
	bool drsAvailable;
	bool drsEnabled;

	float heading, pitch, roll;
	float carCoordinatesX, carCoordinatesY, carCoordinatesZ;
	float accX, accY, accZ;
	float velocityX, velocityY, velocityZ;
	float tireTempFL, tireTempFR, tireTempRL, tireTempRR;

	// controller information
	float throttle;
	float brake;
	float clutch;
	float steerAngle;

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

	vector<int> tele_gears;
	vector<int> tele_rpm;
	vector<int> tele_speed;
	//ofPixels rpmPixels;
};

