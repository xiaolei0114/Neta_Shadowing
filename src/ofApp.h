#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	//basic methods for OF by default
    void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
    //Objects for face tracking
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    
    //Datas for FaceTracking
    float mouthIsOpen = 0;
    float mouthHeight = 0;
    float mouthWidth  = 0;
    float jawOpenness = 0;
    
    //Use to show the
    //1. mouthHeight
    //2. mouthWidth
    //3. JawOpenness
    void shwoFacialInfo();
    
    
    //Objects for audio processing
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    //Objects for sound player, one per each sound file
    ofSoundPlayer       TOEIC;
    
    float 				* fftSmoothed;
    
    //Methods for sound input
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioDrawChannels();
};
