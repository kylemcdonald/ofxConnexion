#pragma once

#include "ofxConnexion.h"
#include "ofMain.h"

class testApp : public ofBaseApp{

public:
	void setup();
	~testApp();
	void update();
	void draw();
	
	ofLight light;
	
	void connexionMoved(ConnexionData& data);
};

