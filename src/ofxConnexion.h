#pragma once

#include "ofMain.h"
#include "3DconnexionClient/ConnexionClientAPI.h"

class ConnexionData {
public:
	short position[3];
	short rotation[3];
	short deviceId;
	short buttonState;
	
	bool getButton(int button);
    
    // these assume you set the speed to max in the control panel
    ofVec3f getNormalizedPosition();
    ofVec3f getNormalizedRotation();
};

class ofxConnexion {
public:
	static ofEvent<ConnexionData> connexionEvent;
	static ConnexionData connexionData;

	static void start();
	static void stop();
	static void setLed(bool state);
	
protected:
	static UInt16 clientId;
	static void driverHandler(io_connect_t connection, natural_t messageType, void *messageArgument);
};
