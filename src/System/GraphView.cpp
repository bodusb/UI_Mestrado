///////////////////////////////////////////////////////////
//  GraphView.cpp
//  Implementation of the Class GraphView
//  Created on:      06-set-2013 14:20:15
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "GraphView.h"


GraphView::GraphView(){
	//trail.resize(8);
	//curve1.resize(8);


}



GraphView::~GraphView(){

}


void GraphView::draw(){

	ofSetVerticalSync(true);

	//update phase
	t = ofGetElapsedTimef();
	if(trail.size()==0){
		initTime = t;
	}
	t = t - initTime;

	x = t;

	curve1 = sin(t*TWO_PI)*10;

	
		if(x<prevX){
			trail.clear();
		}else{
			trail.addVertex(ofPoint(x,curve1));
		}
	

	prevX = x;




	//drawn phase
	cam.begin(this->vp->place);
	cam.disableMouseInput();
	//cam.setPosition(x,curve1,0);
	ofSetLineWidth(1);
		ofDrawGrid(100);

		ofEnableSmoothing();
		ofCircle(x,curve1,0.5);
		trail.draw();
		ofDisableSmoothing();

		//ofRect(ofGetWidth()-rightMargin+10,rectY,10,y[i]-rectY);

		
	cam.end();
}


void GraphView::executeAction(){

}


void GraphView::selectingAction(){

}






void GraphView::speedChanged(){
	for(unsigned int i=0;i<trail.size();i++){
		trail.clear();
	}
}




void GraphView::panelEvent(ofxUIEventArgs& e){

}


void GraphView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("Graphic Context Panel", OFX_UI_FONT_LARGE)); 
	
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &GraphView::panelEvent); 
}
