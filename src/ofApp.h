#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "ofxGui.h"

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
    
        void audioReceived(float* input, int bufferSize, int nChannels);
    
    private:
    	const int bufferSize = 256;
        const int sampleRate = 44100;
        const int maxAverages = 100;
    
        ofParameter<int> displayFrequencyMin;
        ofParameter<int> displayFrequencyMax;

        ofParameter<int> averages;
    
        ofParameter<float> gain;
        ofParameter<float> noiseFloor;

        ofParameter<float> huePhase;
        ofParameter<float> hueRange;
    
        ofxPanel gui;
    
        ofxFft* fft;
    
        float* audioInput;
        float* fftOutput;
        float* logOutputs;
        float* averageOutput;
    
        int currentAverage;
};
