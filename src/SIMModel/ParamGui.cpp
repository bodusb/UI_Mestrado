///////////////////////////////////////////////////////////
//  ParamGui.cpp
//  Implementation of the Class ParamGui
//  Created on:      06-set-2013 14:20:16
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ParamGui.h"


ParamGui::ParamGui(){

}



ParamGui::~ParamGui(){

}



void ParamGui::panelEvent(ofxUIEventArgs& e){

}


void ParamGui::setContextPanel(){
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	

	//Start the SpaceView Context Panel
	panel = new ofxUIScrollableCanvas(0, 0, 300, ofGetHeight());  
	panel->setTheme(OFX_UI_THEME_HACKER);
	panel->setColorBack(ofxUIColor::black);
	panel->setScrollAreaToScreen();
    panel->setScrollableDirections(false, true);

	  
	//Set SpaceView Profile
	panel->addWidgetDown(new ofxUILabel("System Context Panel", OFX_UI_FONT_LARGE)); 
	
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &ParamGui::panelEvent); 
}