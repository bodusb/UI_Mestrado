///////////////////////////////////////////////////////////
//  SatView.cpp
//  Implementation of the Class SatView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SatView.h"

#include "EQState.h"
#include "SSState.h"
#include "SatState.h"
#include "ViewState.h"

#include "..\SIMModel\SIMModelNode.h"
#include "iAction.h"
#include "ModelControl.h"
#include "iScreen.h"

#include "..\SIMModel\SIMNodeProfile.h"

SatView::SatView(){
	cam.setFarClip(10000); 

	this->stateList.push_back(new SatState());
	this->stateList.push_back(new SSState());
	this->stateList.push_back(new EQState());

	this->actualState = this->stateList.at(0);

	//ofLogVerbose() << "test actual: "<< actualState->name;

	vector<ViewState*>::iterator vs;

	for(vs = this->stateList.begin(); vs != this->stateList.end(); vs++){
		(*vs)->mySatview = this;
	}

	showSat = false;
}

SatView::~SatView(){

}

void SatView::draw(){

	//ofLogVerbose("[DRAW]") << " draw sat view";

	//this->actualState->draw();

	// Draw satellite with pivot into satellite center
	//ofLogVerbose("[SATSTATE]") << "---> Drawing SatState";

	//set start point to draw
	SIMModelNode* start = this->myScreen->myAction->modelController->getNode("RB");
	//ofLogVerbose() << "--->" << start->profile.GetName();

	this->cam.begin(this->vp->place);
	//ofDrawAxis(100);
		//ofEnableDepthTest();
	//	glEnable(GL_DEPTH_TEST);
	//	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);

		//ofDisableAlphaBlending();
			
			this->recursiveDraw(start);
		
			//ofEnableAlphaBlending();
		
	//	ofDisableBlendMode();
	//	glDisable(GL_DEPTH_TEST);
		//ofDisableDepthTest();
		
	this->cam.end();

	
	ofSetColor(ofColor::green);

	
	if(this->myScreen->myAction->actualClosestObject != NULL )

		if(this->myScreen->myAction->closestObjectType ==  nodeType::ntSUBSYSTEM)
			ofDrawBitmapString( ((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->profile.GetAcronym(), 
			((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->model3D->getAuxPlace());

			

}

void SatView::executeAction(){

}

void SatView::selectingAction(){
	//this->actualState->selectingAction();
	//this->myScreen->myAction->addTolog("[SATSELECT]"," Looking for action in sat view");
	// select the closest node and send to action

	//only action if its on main view --- for now.
	if(this->vp->name == "main"){

		this->nearestDistance = 0;
		this->nearestIndex = 0;

		SIMModelNode* s = this->myScreen->myAction->modelController->getNode("RB"); //call sat rb

		SIMModelNode* nearestNode = this->findNearestObjectToAction(s);

		if( this->myScreen->myAction->actualClosestObject != NULL){
			//this->myScreen->myAction->actualClosestObject = nearestNode;
			//this->myScreen->myAction->closestObjectType = nearestNode->profile.GetNodeType();
			this->myScreen->myAction->message += ((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->profile.GetUniqueCode();

			/*this->myScreen->myAction->addTolog("[SATSELECT]", " SELECTING: " + 
				((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->profile.GetAcronym());*/

			((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->model3D->setSelected(true);
		}
	}
}

void SatView::panelEvent(ofxUIEventArgs& e){

}

void SatView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("Sat Context Panel", OFX_UI_FONT_LARGE)); 

	this->panel->addSpacer(5);

	ofxUIToggle *b = new ofxUIToggle("Show Sat",&this->showSat,dim,dim,dim,dim,OFX_UI_FONT_LARGE);
	
	panel->addWidgetDown(b);


	this->panel->addSpacer(5);
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &SatView::panelEvent); 
}

void SatView::recursiveDraw(SIMModelNode* start){

	//if a leaf returns
	if(start == NULL) return;

	//ofLogVerbose("[VIEWSTATE]") << "Recursive draw at: " << start->profile.GetAcronym();

	//if doesnt have a 3d models, doesnt draw
	if(start->model3D != NULL){
		if(start->model3D->isLoaded()){
			//ofLogVerbose() << "Request to draw:" << start->profile.GetAcronym();

			if(start->profile.GetNodeType() != ntSATELLITE || this->showSat)
				start->model3D->draw();
		}
	}
	if( start->nodeList.empty() )  return;

	vector<SIMModelNode*>::iterator itN;
	//ofLogVerbose("[VIEWSTATE]") << "Recursive going for more";

	for( itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
		recursiveDraw((*itN));
}

// retorning infinit NULL ------ correct this.
SIMModelNode* SatView::findNearestObjectToAction(SIMModelNode* start){

	if(start!=NULL){ 
		if(start->model3D!=NULL){

			start->model3D->setSelected(false);
			start->model3D->setAuxPlace( this->cam.worldToScreen(start->model3D->getPivot()));

			float distance = start->model3D->getAuxPlace().distance( this->myScreen->myAction->actual.position);
			//cout<<start->acronym;
			//cout<<endl<<start->acronym<<" - "<<start->auxPlace<<" -Distance "<<distance<<" -nearestD:"<<this->nearestDistance;
			//start->distMouse = distance;
			if( (this->nearestIndex == 0 || distance < this->nearestDistance) ) {
				this->nearestDistance = distance;
				if( distance < 150 && ( (start->profile.GetNodeType() == ntSUBSYSTEM) || (start->profile.GetNodeType() == ntEQUIPMENT)) ){
					this->myScreen->myAction->actualClosestObject = start;
					this->myScreen->myAction->closestObjectType = start->profile.GetNodeType();

				}
				//	this->nearestPoint = cur;
				/*	cout<<"----------------"<<
				endl<<nearestNode->acronym<<" - "<<this->nearestDistance;*/
			}
			nearestIndex++;
		}


		vector<SIMModelNode*>::iterator itNode;
		for(itNode = start->nodeList.begin(); itNode != start->nodeList.end(); itNode++){
			findNearestObjectToAction((*itNode));
		}

	}
	return NULL;
}