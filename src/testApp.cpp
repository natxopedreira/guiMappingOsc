#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(10, 10, 10);
    ofEnableAlphaBlending();
    
    creaGui();
    sender.setup(HOST, PORT);
    
    gui->loadSettings("gui.xml");
    gui2->loadSettings("gui2.xml");
    
    
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
    gui->addSlider("scale", 1, 25, 1, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui->addSlider("backgroundColor", 0, 255, 0, length-xInit, dim, OFX_UI_FONT_SMALL);
    
    parsearInt.push_back("backgroundColor");
     
	drawModes.push_back("faces");
	drawModes.push_back("fullWireframe");
	drawModes.push_back("outlineWireframe");
    drawModes.push_back("occludedWireframe");
    gui->addSpacer(length-xInit, 1);
    gui->addRadio("DRAW MODE", drawModes, OFX_UI_ORIENTATION_VERTICAL, 40, 40);
    gui->addSpacer(length-xInit, 1);
    gui->addToggle("shader", false, 40, 40, OFX_UI_FONT_SMALL);
    gui->addToggle("useLights", false, 40, 40, OFX_UI_FONT_SMALL);
    gui->addToggle("randomLighting", false, 40, 40, OFX_UI_FONT_SMALL);
    gui->addSpacer(length-xInit, 1);
    gui->addToggle("setupMode", true, 40, 40, OFX_UI_FONT_SMALL);
    gui->addToggle("useSmoothing", false, 40, 40, OFX_UI_FONT_SMALL);
    gui->addButton("saveSettings", false, 40, 40, OFX_UI_FONT_SMALL);
    gui->addButton("saveCalibration", false, 40, 40, OFX_UI_FONT_SMALL);
    parsearInt.push_back("lineWidth");
    
    
    gui2 = new ofxUICanvas(length+xInit+2, 0, length+xInit, ofGetHeight());
    gui2->setDrawBack(false);
    gui2->addWidgetDown(new ofxUILabel("CALIBRATION", OFX_UI_FONT_MEDIUM));
    gui2->addSlider("aov", 50, 100, 80, length-xInit, dim, OFX_UI_FONT_SMALL);
    //parsearInt.push_back("aov");
    gui2->addToggle("cv_calib_fix_aspect_ratio", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_k1", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_K2", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_K3", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_zero_tangent_dist", true, dim, dim, OFX_UI_FONT_SMALL);
    gui2->addToggle("cv_calib_fix_principal_point", false, dim, dim, OFX_UI_FONT_SMALL);
    
    gui2->addSlider("screenPointSize", 1.0, 16.0, 2.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("selectedPointSize", 1.0, 16.0, 8.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("selectionRadius", 1.0, 32.0, 12.0, length-xInit, dim, OFX_UI_FONT_SMALL);
    parsearInt.push_back("screenPointSize");
    parsearInt.push_back("selectedPointSize");
    parsearInt.push_back("selectionRadius");
    gui2->addSpacer(length-xInit, 1);

    gui2->addSlider("lightX", -1000, 1000, 200, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lightY", -1000, 1000, 400, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lightZ", -1000, 1000, 800, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSpacer(length-xInit, 1);
    gui2->addSlider("slowLerpRate", 0, .01, .001, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("fastLerpRate", 0.0, 1.0, 1, length-xInit, dim, OFX_UI_FONT_SMALL);
    gui2->addSlider("lineWidth", 1, 8, 2, length-xInit, dim, OFX_UI_FONT_SMALL);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
    

    
}
void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    ofxOscMessage m;
    
    if(e.widget->getKind() == OFX_UI_WIDGET_TOGGLE){

        
        ofxUIToggle *boolValor = (ofxUIToggle *) e.widget;
        bool valor = boolValor->getValue();
        m.setAddress("/mapamoko/"+name+"/");
        m.addIntArg(valor);
    }else if(e.widget->getKind() == OFX_UI_WIDGET_RADIO){
        ofxUIRadio * rv =  (ofxUIRadio *) e.widget;
        vector<ofxUIToggle *> togles = rv->getToggles();
        for(int i = 0; togles.size(); i++){
            bool valor = togles.at(i)->getValue();
            m.setAddress("/mapamoko/"+name+"/");
            m.addIntArg(valor);
        }
    }else if(e.widget->getKind() == OFX_UI_WIDGET_SLIDER_H){
        ofxUISlider *floatValor = (ofxUISlider *) e.widget;
        
        for(int i = 0; i< parsearInt.size(); i++){
            if(name == parsearInt.at(i)){
                int valor = (int)floatValor->getScaledValue();
                m.setAddress("/mapamoko/"+name+"/");
                m.addIntArg(valor);
            }else{
                float valor = floatValor->getScaledValue();
                m.setAddress("/mapamoko/"+name+"/");
                m.addFloatArg(valor);
            }
        }
        

    }else if (e.widget->getKind() == OFX_UI_WIDGET_BUTTON) {
        ofxUISlider *floatValor = (ofxUISlider *) e.widget;
        if(name == "saveSettings"){
            gui->saveSettings("gui.xml");
            gui2->saveSettings("gui2.xml");
        }else{
            int valor = (int)floatValor->getScaledValue();
            m.setAddress("/mapamoko/"+name+"/");
            m.addIntArg(valor);
        }
    }
    
    
    sender.sendMessage(m);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 's'){
        gui->saveSettings("gui.xml");
        gui2->saveSettings("gui2.xml");
    }
}