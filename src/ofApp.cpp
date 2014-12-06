#include "ofApp.h"
using namespace ofxCv;

void ofApp::setup() {
    ofSetVerticalSync(true);
    
    //Setup for tracker
	cam.initGrabber(640, 480);
	tracker.setup();
    
    // load in sounds:
    TOEIC.loadSound("sounds/TOEIC_sample.mp3");
    
    // the fft needs to be smoothed out, so we create an array of floats
    // for that purpose:
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    /*
    //Setup for audio part
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    
    soundStream.listDevices();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    //Setup SoundStream:
    //ofSoundStreamSetup(int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers)
    
    //nOutput Is the number of output channels that your computer supports. Usually this will be two: left and right.
    //nInputs - Is the number of input channels that your system uses. sampleRate - Is usually 44,100 kHz, or CD quality, though you may want to make it higher or lower depending on the needs of your application.
    //bufferSize - Is the size of the buffer that your system supports. At the time of writing this book, on any operating system, its probably 256 values.
    //nBuffers - Is the number of buffers that your system will create and swap out. The more buffers, the faster your computer will write information into the buffer, but the more memory it will take up. You should probably use two for each channel that youre using.
    
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    */

}

void ofApp::update() {
	
    //Camera update frames
    cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
    
    //Update Facial info
    mouthHeight = tracker.getGesture(tracker.MOUTH_HEIGHT);
    mouthWidth = tracker.getGesture(tracker.MOUTH_WIDTH);
    jawOpenness = tracker.getGesture(tracker.JAW_OPENNESS);
    
    //Updates sound engine every frame
    ofSoundUpdate();
}

void ofApp::draw() {
    
	ofSetColor(255);

	cam.draw(0, 0);
    tracker.draw();
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    //float mouthHeight = tracker.getGesture(tracker.MOUTH_HEIGHT);
    if (mouthHeight >= 1.4) {//mouse is open
        mouthIsOpen = 1;
        if (!TOEIC.getIsPlaying()){
            TOEIC.play();
        }
        else {
            TOEIC.setPaused(false);
        }
    }
    else //mouse is closed
    {
        mouthIsOpen = 0;
        if (TOEIC.getIsPlaying()) {
            TOEIC.setPaused(true);
        }
    }
    
    //display mouth related informations
    shwoFacialInfo();
    
    
    /*
    // draw the fft resutls:
    ofSetColor(255,255,255,255);
    
    float width = (float)(5*128) / nBandsToGet;
    for (int i = 0;i < nBandsToGet; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofRect(100+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
    }
    
    //audioDrawChannels();
     */
    
    
}

void ofApp::shwoFacialInfo()
{
    ofSetColor(80,80,80);
    ofRect(660,320,384,160);//(x,y,w,h)
    ofSetColor(255,255,255);
    
    ofDrawBitmapString("The mouth is:", 670, 350);
    ofDrawBitmapString(mouthIsOpen ? "YES" : "NO", 850, 350);
    ofDrawBitmapString("The Mouth Height is: ",670,390);
    ofDrawBitmapString(ofToString(mouthHeight),850,390);
    ofDrawBitmapString("The Mouth Width is: ",670,410);
    ofDrawBitmapString(ofToString(mouthWidth),850,410);
    ofDrawBitmapString("The Jaw Openness is: ",670,430);
    ofDrawBitmapString(ofToString(jawOpenness),850,430);
}

void ofApp::audioDrawChannels()
{
    ofSetColor(225);
    ofDrawBitmapString("AUDIO INPUT EXAMPLE", 32, 32);
    ofDrawBitmapString("press 's' to unpause the audio\n'e' to pause the audio", 31, 92);
    
    ofNoFill();
    
    // draw the left channel:
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(32, 170, 0);
    
        ofSetColor(225);
        ofDrawBitmapString("Left Channel", 4, 18);
    
        ofSetLineWidth(1);
        ofRect(0, 0, 512, 200);
    
        ofSetColor(245, 58, 135);
        ofSetLineWidth(3);
    
            ofBeginShape();
                for (unsigned int i = 0; i < left.size(); i++){
                    ofVertex(i*2, 100 -left[i]*180.0f);
                }
            ofEndShape(false);
    
        ofPopMatrix();
    ofPopStyle();
    
    // draw the right channel:
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(32, 370, 0);
    
        ofSetColor(225);
        ofDrawBitmapString("Right Channel", 4, 18);
    
        ofSetLineWidth(1);
        ofRect(0, 0, 512, 200);
    
        ofSetColor(245, 58, 135);
        ofSetLineWidth(3);
    
            ofBeginShape();
            for (unsigned int i = 0; i < right.size(); i++){
            ofVertex(i*2, 100 -right[i]*180.0f);
            }
        ofEndShape(false);
    
        ofPopMatrix();
    ofPopStyle();
    
    // draw the average volume:
    ofPushStyle();
        ofPushMatrix();
        ofTranslate(565, 170, 0);//move the origin of the coordiante
    
        ofSetColor(225);
        ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
        ofRect(0, 0, 400, 400);
    
        ofSetColor(245, 58, 135);
        ofFill();
        ofCircle(200, 200, scaledVol * 190.0f);
    
        //lets draw the volume history as a graph
        ofBeginShape();
        for (unsigned int i = 0; i < volHistory.size(); i++){
            if( i == 0 ) ofVertex(i, 400);
        
            ofVertex(i, 400 - volHistory[i] * 70);
        
            if( i == volHistory.size() -1 ) ofVertex(i, 400);
        }
        ofEndShape(false);
    
        ofPopMatrix();
    ofPopStyle();
    
    drawCounter++;
    
    ofSetColor(225);
    string reportString = "buffers received: "+ofToString(bufferCounter)+"\ndraw routines called: "+ofToString(drawCounter)+"\nticks: " + ofToString(soundStream.getTickCount());
    ofDrawBitmapString(reportString, 32, 589);
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;//even numbers in input array are samples for left channel
        right[i]	= input[i*2+1]*0.5; // This means odd numbers in input array are for right channel
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}


void ofApp::keyPressed(int key) {
    if(key == 'r') {
		tracker.reset();
	}
}