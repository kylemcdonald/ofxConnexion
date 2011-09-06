#include "testApp.h"

void testApp::setup(){
	ofxConnexion::start();
	
	// if you want to get data events, you can add a listener toofxConnexion::connexionEvent
	ofAddListener(ofxConnexion::connexionEvent, this, &testApp::connexionMoved);
	
	glEnable(GL_DEPTH_TEST);
	light.enable();
	light.setPosition(+500, 0, 0);
}

testApp::~testApp() {
	ofxConnexion::stop();
}

void testApp::update(){
}

// get data as soon as it comes in
void testApp::connexionMoved(ConnexionData& data) {
	// this would be a good place to get data from multiple devices
	cout << data.getButton(0) << " " << data.getButton(1) << endl;
	
	// use the button state to set the LED
	ofxConnexion::setLed(data.getButton(0) || data.getButton(1));
}

void testApp::draw(){
	ofBackground(0, 0, 0);	
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 , 0);
	
	// get the most recent data
	ConnexionData& data = ofxConnexion::connexionData;
	
	// some of these things are negative, but might be different
	// depending on how you've configured your space navigator
	ofTranslate(
		data.translation[0],
		data.translation[1],
		-data.translation[2]);
	ofRotateX(-data.rotation[0]);
	ofRotateY(-data.rotation[1]);
	ofRotateZ(data.rotation[2]);
	
	ofSetColor(255);
	ofRotateX(180);
	ofBox(200);
}
