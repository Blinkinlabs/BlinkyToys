#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_SINE);

    ofSoundStreamSetup(0, 1, this, sampleRate, bufferSize, 2);
    
    audioInput = new float[bufferSize];
    fftOutput = new float[fft->getBinSize()];
    logOutputs = new float[maxAverages*fft->getBinSize()];
    averageOutput = new float[fft->getBinSize()];
    currentAverage = 0;
    
    gui.setup("settings");
    gui.add(gain.set("gain", 50, 1, 500));
    gui.add(noiseFloor.set("noiseFloor", .005, 0, .1));
    gui.add(displayFrequencyMin.set("minFrequency", 100, 1, 10000));
    gui.add(displayFrequencyMax.set("maxFrequency", 4000, 1, 10000));
    gui.add(averages.set("averages", 9, 1, maxAverages));
    gui.add(huePhase.set("huePhase", .5, 0, 2*pi));
    gui.add(hueRange.set("hueRange", .01, 0, .5));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(displayFrequencyMax<=displayFrequencyMin) {
        displayFrequencyMax = displayFrequencyMin+1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    
    float cyclesPerBin = sampleRate/bufferSize;
    
    int startingBin = displayFrequencyMin/cyclesPerBin;
    int endingBin = displayFrequencyMax/cyclesPerBin;
    
    int binsOfInterest = endingBin - startingBin;
    
    float binDispalyWidth = ((float)ofGetWidth())/binsOfInterest;
    float binColumnHeight = ofGetHeight();
    
    int verticalBinCount = 10;
    float binHeight = binColumnHeight/verticalBinCount;
    
    for(int i = startingBin; i < endingBin; i++) {
        float value = ((int)(averageOutput[i]*binColumnHeight/binHeight))*binHeight;
        
        ofSetColor(ofColor::fromHsb(ofMap(sin(huePhase + i*hueRange),-1,1,0,255), 255, 255));
        ofDrawRectangle((i-startingBin)*binDispalyWidth, binColumnHeight - value,
                        binDispalyWidth, value);
    }
    
	gui.draw();
}


//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    // store input in audioInput buffer
    memcpy(audioInput, input, sizeof(float) * bufferSize);
    
    fft->setSignal(audioInput);
    memcpy(fftOutput, fft->getAmplitude(), sizeof(float) * fft->getBinSize());

    currentAverage = (currentAverage+1)%averages;
    
    for(int i = 0; i < fft->getBinSize(); i++) {
        logOutputs[currentAverage*fft->getBinSize() + i] = log10(1+(fftOutput[i]-noiseFloor)*gain);
    }

    for(int i = 0; i < fft->getBinSize(); i++) {
        averageOutput[i] = 0;
        for(int average = 0; average < averages; average++) {
            averageOutput[i] += logOutputs[((currentAverage + average)%averages)*fft->getBinSize() + i];
        }
        averageOutput[i] /= averages;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
