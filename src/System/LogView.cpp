///////////////////////////////////////////////////////////
//  LogView.cpp
//  Implementation of the Class LogView
//  Created on:      06-set-2013 20:14:41
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "LogView.h"


LogView::LogView(){


	// create the new panel
	//ofLogVerbose() << "HERE";
	gui = new ofxUIScrollableCanvas();
//	gui->setTheme(OFX_UI_THEME_HACKER);
	
//	gui->setColorBack(ofxUIColor::black);
    gui->setScrollAreaToScreen();
    gui->setScrollableDirections(false, true);
	gui->autoSizeToFitWidgets();
	////Set  Profile
	gui->addLabel("Log Context Panel", OFX_UI_FONT_LARGE); 

	//// Set to save into file
	//



}


void LogView::resizeView(){
	
	gui->setPosition(this->vp->place.x, this->vp->place.y);
	gui->setDimensions(this->vp->place.width,this->vp->place.height);

	gui->addLabel("[INTERFACE][" + ofGetTimestampString() + "] - Resized", OFX_UI_FONT_SMALL); 
	ofLogVerbose() << "[INTERFACE][" + ofGetTimestampString() + "] - Resized";
}


LogView::~LogView(){

}





void LogView::draw(){

}


void LogView::executeAction(){

}


void LogView::selectingAction(){

}




void LogView::panelEvent(ofxUIEventArgs& e){

}


void LogView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("Log Context Panel", OFX_UI_FONT_LARGE)); 

	// Set to save into file
	
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &LogView::panelEvent); 
}