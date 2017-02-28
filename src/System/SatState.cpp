///////////////////////////////////////////////////////////
//  SatState.cpp
//  Implementation of the Class SatState
//  Created on:      06-set-2013 14:20:17
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SatState.h"

#include "SatView.h"
#include "ViewState.h"
#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMNodeProfile.h"
#include "..\SIMModel\NodePositions.h"

#include "..\SIMModel\SIMModelParameter.h"
#include "..\SIMModel\SIMParameterProfile.h"
#include "..\SIMModel\SIMParameterValue.h"
#include "..\SIMModel\SIMParameterOperationalMode.h"



SatState::SatState(){
	this->name = "satstate";

}



SatState::~SatState(){

}

void SatState::draw(){
	// Draw satellite with pivot into satellite center
	//ofLogVerbose("[SATSTATE]") << "---> Drawing SatState";

	//set start point to draw
	SIMModelNode* start = this->mySatview->myScreen->myAction->modelController->getNode("RB");
	//ofLogVerbose() << "--->" << start->profile.GetName();

	this->mySatview->cam.begin(this->mySatview->vp->place);
	
		ofDrawAxis(100);
		 this->recursiveDraw(start);
	


			ofSetColor(ofColor::green);
		 if(this->mySatview->myScreen->myAction->actualClosestObject != NULL )
			 if(this->mySatview->myScreen->myAction->closestObjectType ==  nodeType::ntSUBSYSTEM)
			ofDrawBitmapString( ((SIMModelNode*)this->mySatview->myScreen->myAction->actualClosestObject)->profile.GetAcronym(), 
			((SIMModelNode*)this->mySatview->myScreen->myAction->actualClosestObject)->model3D->getAuxPlace());


	this->mySatview->cam.end();

}

void SatState::handle(){

}


void SatState::selectingAction() {
	// select the closest node and send to action

	//only action if its on main view --- for now.
	if(this->mySatview->vp->name == "main"){

		this->nearestDistance = 0;
		this->nearestIndex = 0;

		SIMModelNode* s = this->mySatview->myScreen->myAction->modelController->getNode("RB"); //call sat rb

		SIMModelNode* nearestNode = this->findNearestObjectToAction(s);

		if( nearestNode != NULL){
			this->mySatview->myScreen->myAction->actualClosestObject = nearestNode;
			this->mySatview->myScreen->myAction->closestObjectType = nodeType::ntSUBSYSTEM;
			this->mySatview->myScreen->myAction->message += nearestNode->profile.GetUniqueCode();
	
		}



	}


}


