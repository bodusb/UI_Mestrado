///////////////////////////////////////////////////////////
//  ParamView.cpp
//  Implementation of the Class ParamView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ParamView.h"

#include "..\SIMModel\SIMModelNode.h"
#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\NodeRDT.h"


#include "iScreen.h"

#include "iAction.h"

#include "ModelControl.h"

ParamView::ParamView(){

	cam.setFarClip(100000);
}

ParamView::~ParamView(){

}

void ParamView::draw(){

	ofPushMatrix();
	ofPushView();
	ofPushStyle();

	ofEnableDepthTest();
//	ofEnableAlphaBlending();

	cam.begin(this->vp->place);
		
		//ofDrawGrid();
		this->drawRDT(this->myScreen->myAction->modelController->actualHead);
	cam.end();

//	ofDisableAlphaBlending();
	ofDisableDepthTest();

	ofPopStyle();
	ofPopView();
	ofPopMatrix();
}

void ParamView::drawRDT(SIMModelNode * start){

	if (!start->nodeRDT->isOpen()) return;

	// CALL NODE DRAW
	//ofLogVerbose("[INTERFACE]") << "DRAW NODE RDT" << start->profile.GetAcronym() ;

	//ofSetColor(ofColor::blue);

	switch(start->nodeRDT->getAppearTypeFromOM()){
		case appearType::aptOFF: ofSetColor(ofColor::beige,50);break;// ofLogVerbose("[NODE3D]") << " OFF ";
		case appearType::aptFAILURE: ofSetColor(ofColor::red,50);break;// ofLogVerbose("[NODE3D]") << " FAILURE "; break;
		case appearType::aptFUNCTIONAL: ofSetColor(ofColor::green,50);break;//ofLogVerbose("[NODE3D]") << " FUNCTIONAL "; break;
		case appearType::aptSTANDBY: ofSetColor(ofColor::blue,50);break;// ofLogVerbose("[NODE3D]") << " STANDBY "; break;
		default: ofSetColor(ofColor::darkGray,50);break;// ofLogVerbose("[NODE3D]") << " Default ";break;
	};
	ofNoFill();
	ofSetLineWidth(1);
	ofSphere(start->nodeRDT->getPlace(),5);

	ofSetColor(ofColor::white);
	//ofDrawBitmapString(start->acronym+"-"+ofToString(start->auxPlace)+"-"+ofToString(start->distMouse),start->place);
	ofDrawBitmapString(start->profile.GetAcronym(),start->nodeRDT->getPlace()+5);
	/*ofSetColor(ofColor::lightGray);
	ofSphere(no->place,no->rad);
	ofSetColor(ofColor::lightBlue);
	ofSphere(no->place,no->out_rad);*/
	if(start->nodeList.empty()) return;

	vector<SIMModelNode*>::iterator itNode;

	for(itNode = start->nodeList.begin(); itNode != start->nodeList.end(); itNode++) {
		ofSetColor(ofColor::antiqueWhite);
		ofSetLineWidth(2);
		ofLine(start->nodeRDT->getPlace(),(*itNode)->nodeRDT->getPlace());
		this->drawRDT((*itNode));
		
	}

}

void ParamView::executeAction(){

}

void ParamView::selectingAction(){
	// select the closest node and send to action

	//only action if its on main view --- for now.
	if(this->vp->name == "main"){

		this->nearestDistance = 0;
		nearestIndex = 0;
		SIMModelNode* nearestNode = findNearestNodeToAction(this->myScreen->myAction->modelController->model);

		

	}

}

// retorning infinit NULL ------ correct this.
SIMModelNode* ParamView::findNearestNodeToAction(SIMModelNode* start){

	//cout<<".";
	if(start!=NULL){

		start->nodeRDT->setAuxPlace(this->cam.worldToScreen(start->nodeRDT->getPlace()));
		float distance = start->nodeRDT->getAuxPlace().distance(this->myScreen->myAction->actual.position);
		//cout<<start->acronym;
		//cout<<endl<<start->acronym<<" - "<<start->auxPlace<<" -Distance "<<distance<<" -nearestD:"<<this->nearestDistance;
		//start->distMouse = distance;
		if( (this->nearestIndex == 0 || distance < this->nearestDistance) ) {

			this->nearestDistance = distance;
			if(distance < 150){
				this->myScreen->myAction->actualClosestObject = start;
				this->myScreen->myAction->closestObjectType = nodeType::ntRDT;
			}
			//	this->nearestPoint = cur;
			/*	cout<<"----------------"<<
			endl<<nearestNode->acronym<<" - "<<this->nearestDistance;*/
		}

		nearestIndex++;
		vector<SIMModelNode*>::iterator itNode;
		for(itNode = start->nodeList.begin(); itNode != start->nodeList.end(); itNode++){
			findNearestNodeToAction((*itNode));
		}
	}

	return NULL;
}

void ParamView::panelEvent(ofxUIEventArgs& e){

}

void ParamView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("ParameterView Context Panel", OFX_UI_FONT_LARGE)); 
	
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &ParamView::panelEvent); 
}