#pragma once

#include "ofxConnexion.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	~ofApp();
	void update();
	void draw();
	
	ofLight light;
	
	void connexionMoved(ConnexionData& data);
};

