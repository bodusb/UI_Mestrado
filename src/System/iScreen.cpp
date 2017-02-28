///////////////////////////////////////////////////////////
//  iScreen.cpp
//  Implementation of the Class iScreen
//  Created on:      06-set-2013 15:50:42
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "iScreen.h"
#include "iView.h"

#include "SpaceView.h"
#include "ParamView.h"
#include "SatView.h"
#include "GraphView.h"
#include "LogView.h"
#include "SystemView.h"
#include "TimelineView.h"

#include "iViewport.h"



iScreen::iScreen(){

	// start views

	if( XML.loadFile("screen.xml")){
		ofLogVerbose() << "[INTERFACE] Starting views";

		//Read Frames
		XML.pushTag("screen");
		int frameCount = XML.getNumTags("frame");
		for (int i = 0; i < frameCount; i++){
			XML.pushTag("frame",i);
			string name = XML.getValue("name","error");
			ofLogVerbose() <<"[INTERFACE] Configuring: "<<name;

			if(name == "spaceview"){
				SpaceView *v = new SpaceView();
				this->readViewInfo(v,i);
			} 

			if(name == "paramview"){
				ParamView *v = new ParamView();
				this->readViewInfo(v,i);
			} 

			if(name == "satview"){
				SatView *v = new SatView();
				this->readViewInfo(v,i);
			} 

			if(name == "graphview"){
				GraphView *v = new GraphView();
				this->readViewInfo(v,i);
			} 


			if(name == "logview"){
				LogView *v = new LogView();
				this->readViewInfo(v,i);
				v->resizeView();
			} 


			if(name == "systemview"){
				SystemView *v = new SystemView();
				this->readViewInfo(v,i);
				//v->resizeView();
			} 


			if(name == "timelineview"){
				TimelineView *v = new TimelineView();
				this->readViewInfo(v,i);
			} 

		XML.popTag();
		}



		XML.popTag();

	} else {
		ofSystemAlertDialog("Error opening the screen.xml file");
		exit(0);

	}



}

void iScreen::readViewInfo(iView *v,int i){
				v->id = XML.getAttribute("frame","id",0,i);
				v->name = XML.getValue("name","error");
				v->vp = new iViewport();
				v->vp->name = XML.getValue("viewport","");
				v->vp->id = v->id;
				v->vp->setDimensions(XML.getValue("fX",50),XML.getValue("fY",50),
					XML.getValue("fWidth",50),XML.getValue("fHeight",50));
				v->vp->backgroundColor = ofColor(XML.getAttribute("BackgroundColor","r",0),
					XML.getAttribute("BackgroundColor","g",0),XML.getAttribute("BackgroundColor","b",0));
				v->vp->updateViewport();
				this->iviewList.push_back(v);
				v->myScreen = this;
				ofLogVerbose() <<"[INTERFACE] " + v->name +" - ok";
}


iScreen::~iScreen(){

}


void iScreen::updateViews(){

	vector<iView *>::iterator v;

	for( v = this->iviewList.begin(); v!= this->iviewList.end(); v++){
		(*v)->vp->updateViewport();
		if ((*v)->name == "logview") ((LogView*)(*v))->resizeView();
		if ((*v)->name == "systemview") ((SystemView*)(*v))->resizeView();
		if ((*v)->name == "timelineview") ((TimelineView*)(*v))->resizeView();
	}

}


void iScreen::drawBackgrounds(){
	
	vector<iView *>::iterator v;

	for( v = this->iviewList.begin(); v!= this->iviewList.end(); v++){
		
		//ofLogVerbose("[INTERFACE]") << "Draw:" << (*v)->name;

		//Draw background
		(*v)->vp->drawBackground();

		//draw views
		//(*v)->draw();
	}
}

void iScreen::draw(){

	vector<iView *>::iterator v;

	for( v = this->iviewList.begin(); v!= this->iviewList.end(); v++){
		
		//ofLogVerbose("[INTERFACE]") << "Draw:" << (*v)->name;

		//Draw background
		//(*v)->vp->drawBackground();

		//draw views
		(*v)->draw();
	}

}


iView* iScreen::getView(string v_name){

	vector<iView *>::iterator v;

	for( v = this->iviewList.begin(); v!= this->iviewList.end(); v++){
		
		if ( (*v)->name == v_name) return (*v);
	}

	return NULL;
}


void iScreen::swapViews(iView *start, iView *target){

	iViewport *aux = start->vp;
	start->vp = target->vp;
	target->vp = aux;
}