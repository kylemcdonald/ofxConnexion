#include "ofApp.h"

void ofApp::setup(){
	ofxConnexion::start();
	
	// if you want to get data events, you can add a listener toofxConnexion::connexionEvent
	ofAddListener(ofxConnexion::connexionEvent, this, &ofApp::connexionMoved);
    
    ofBackground(0);
    ofEnableDepthTest();
	light.enable();
	light.setPosition(+500, +500, +500);
}

void ofApp::exit() {
	ofxConnexion::stop();
}

void ofApp::update(){
}

// get data as soon as it comes in
void ofApp::connexionMoved(ConnexionData& data) {
	// this would be a good place to get data from multiple devices
	cout << data.getButton(0) << " " << data.getButton(1) << endl;
	
	// use the button state to set the LED
	ofxConnexion::setLed(data.getButton(0) || data.getButton(1));
}

void ofApp::draw(){
    
    ofEnableLighting();
    ofPushMatrix();
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 , 0);
	
	// get the most recent data
	ConnexionData& data = ofxConnexion::connexionData;
	
	// some of these things are negative, but might be different
    // depending on how you've configured your space navigator
    ofTranslate(
                data.position[0],   // TX
                data.position[2],   // TY
                data.position[1]);  // TZ
    
    ofRotateX(-data.rotation[0]);   // RX
    ofRotateY(-data.rotation[2]);   // RY
	ofRotateZ(-data.rotation[1]);   // RZ
	
	ofSetColor(255);
	ofRotateX(180);
	ofDrawCone(100, 200);
    
    ofPopMatrix();
    
    //-
    
    ofDisableLighting();
    
    ofPushStyle();
    ofSetColor(255);
    
    stringstream ss;
    ss << endl;
    ss << "POSITION" << endl;
    ss << "data.position[0] : " << data.position[0] << endl;
    ss << "data.position[2] : " << data.position[2] << endl;
    ss << "data.position[1] : " << data.position[1] << endl;
    ss << endl;
    
    ss << "ROTATION" << endl;
    ss << "data.rotation[0] : " << data.rotation[0] << endl;
    ss << "data.rotation[2] : " << data.rotation[2] << endl;
    ss << "data.rotation[1] : " << data.rotation[1] << endl;
    ss << endl;
    
    ofDrawBitmapString(ss.str().c_str(), 10, 20);
    ofPopStyle();
}
