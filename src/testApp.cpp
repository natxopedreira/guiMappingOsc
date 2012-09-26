#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    creaGui();
    ofBackground(10, 10, 10);
    ofEnableAlphaBlending();
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
}
//--------------------------------------------------------------
void testApp::creaGui(){
    float dim = 16;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 510-xInit;
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    gui->setDrawBack(false);
    
    gui->addWidgetDown(new ofxUILabel("APERANCE", OFX_UI_FONT_MEDIUM));
    gui->addSlider("scale", 1.0, 25.0, 1, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("backgroundColor", .0, 255.0, .0, length-xInit, dim, OFX_UI_FONT_SMALL);
    
    vector<string> drawModes; 
	drawModes.push_back("faces");
	drawModes.push_back("fullWireframe");
	drawModes.push_back("outlineWireframe");
    drawModes.push_back("occludedWireframe");
    gui->addSpacer(length-xInit, 1);
    gui->addRadio("DRAW MODE", drawModes, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    vector<string> shadingModes; 
	shadingModes.push_back("none");
	shadingModes.push_back("lights");
	shadingModes.push_back("shader");
    gui->addSpacer(length-xInit, 1);
    gui->addRadio("SHADING", shadingModes, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    gui->addSpacer(length-xInit, 1);
    gui->addWidgetDown(new ofxUILabel("HIGHLIGHT", OFX_UI_FONT_MEDIUM));
    gui->addToggle("highlight", true, dim, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("highlightPosition", 0.0, 1.0, 0.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("highlightOffset", 0.0, 1.0, 0.1, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSpacer(length-xInit, 1);
    gui->addButton("saveCalibration", false, dim, dim, OFX_UI_FONT_SMALL);
    gui->addSpacer(length-xInit, 1);
    gui->addSlider("slowLerpRate", 0, .01, .001, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("fastLerpRate", 0.0, 1.0, 1, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("lineWidth", (int)1, (int)8, (int)2, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addToggle("useSmoothing", true, dim, dim, OFX_UI_FONT_SMALL);
    
    gui2 = new ofxUICanvas(length+xInit+2, 0, length+xInit, ofGetHeight());
    gui2->setDrawBack(false);
    gui2->addWidgetDown(new ofxUILabel("CALIBRATION", OFX_UI_FONT_MEDIUM));
    gui2->addSlider("aov", 50, 100, 80, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_aspect_ratio", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_k1", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_K2", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_K3", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_zero_tangent_dist", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_principal_point", false, dim, dim, OFX_UI_FONT_SMALL);
    
    gui2->addSpacer(length-xInit, 1);
    gui2->addWidgetDown(new ofxUILabel("RENDER", OFX_UI_FONT_MEDIUM));
    gui2->addToggle("setupMode", true, dim, dim, OFX_UI_FONT_SMALL);
    
    
    gui2->addSlider("screenPointSize", 1.0, 16.0, 2.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("selectedPointSize", 1.0, 16.0, 8.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("selectionRadius", 1.0, 32.0, 12.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSpacer(length-xInit, 1);
    gui2->addToggle("useFog", false, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("fogNear", 0.0, 1000.0, 200.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("fogFar", 0.0, 2500.0, 1850, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSpacer(length-xInit, 1);
    gui2->addToggle("randomLighting", false, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lightX", -1000, 1000, 200, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lightY", -1000, 1000, 400, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lightZ", -1000, 1000, 800, length-xInit, dim, OFX_UI_FONT_SMALL);
    /*
     panel.addToggle("setupMode", true);
     panel.addSlider("scale", 1, .1, 25);
     panel.addSlider("backgroundColor", 0, 0, 255, true);
     panel.addMultiToggle("drawMode", 3, variadic("faces")("fullWireframe")("outlineWireframe")("occludedWireframe"));
     panel.addMultiToggle("shading", 0, variadic("none")("lights")("shader"));
     panel.addToggle("saveCalibration", false);
     
    
     panel.addToggle("highlight", false);
     panel.addSlider("highlightPosition", 0, 0, 1);
     panel.addSlider("highlightOffset", .1, 0, 1);
     
     
     panel.addSlider("aov", 80, 50, 100);
     panel.addToggle("CV_CALIB_FIX_ASPECT_RATIO", true);
     panel.addToggle("CV_CALIB_FIX_K1", true);
     panel.addToggle("CV_CALIB_FIX_K2", true);
     panel.addToggle("CV_CALIB_FIX_K3", true);
     panel.addToggle("CV_CALIB_ZERO_TANGENT_DIST", true);
     panel.addToggle("CV_CALIB_FIX_PRINCIPAL_POINT", false);
     
     
     panel.addSlider("lineWidth", 2, 1, 8, true);
     panel.addToggle("useSmoothing", false);
     panel.addToggle("useFog", false);
     panel.addSlider("fogNear", 200, 0, 1000);
     panel.addSlider("fogFar", 1850, 0, 2500);
     panel.addSlider("screenPointSize", 2, 1, 16, true);
     panel.addSlider("selectedPointSize", 8, 1, 16, true);
     panel.addSlider("selectionRadius", 12, 1, 32);
     panel.addSlider("lightX", 200, -1000, 1000);
     panel.addSlider("lightY", 400, -1000, 1000);
     panel.addSlider("lightZ", 800, -1000, 1000);
     panel.addToggle("randomLighting", false);
     */
    
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}