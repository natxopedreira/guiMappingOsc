#pragma once
#include "ofxUi.h"
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void creaGui();
        void guiEvent(ofxUIEventArgs &e);
		void keyPressed  (int key);
		
    
    ofxUICanvas *gui, *gui2, *gui3;
    ofxOscSender sender;
    vector<string> drawModes;
    vector<string> shadingModes;
    vector<string> parsearInt;
};
