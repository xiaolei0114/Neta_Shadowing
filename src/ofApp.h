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

/**************************************************************************************************
                                  Face Tracking Objects begin
**************************************************************************************************/
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
    void trackerSetUp();
    void shwoFacialInfo();
    
/**************************************************************************************************
                                 Face Tracking Objects end
 **************************************************************************************************/
/**************************************************************************************************
                                 Text Processing Objects start
**************************************************************************************************/
    
    float nextLetterTime;//Time for calculating the time to display the next letter in the substring
    int   lineCount;//Pointer to the current line
    int   letterCount;//Pointer for the next letter to be shown
    string typedLine;
    
    float textDrawX, textDrawY;
    
    // the total width on the line to be drawn
    int strWidth = 0;
    
    vector <string> seussLines;
    
    void textProcessingSetUp();
    //update typedLine, x,y for drawing, strWidth based on lineCount
    void textDrawingInfoUpdate();
    //update the lineCount and Letter Count based the current time and nextLetterTime
    void textUpdateStrPosBasedOnTime(int time);
    //draw the black background rectangular and the texts
    void textDraw();
    
/**************************************************************************************************
                                 Text Processing Objects end
**************************************************************************************************/
    
/**************************************************************************************************
                                 Sound Processing Objects begins
**************************************************************************************************/
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
    void audioSetUp();
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioDrawChannels();
};
