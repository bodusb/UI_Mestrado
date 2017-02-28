///////////////////////////////////////////////////////////
//  ViewState.cpp
//  Implementation of the Class ViewState
//  Created on:      06-set-2013 14:20:21
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ViewState.h"
#include "iView.h"
#include "SatView.h"

#include "iScreen.h"
#include "iAction.h"
#include "mouseClick.h"

#include "..\SIMModel\SIMModelNode.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMNodeProfile.h"
#include "..\SIMModel\NodePositions.h"

#include "..\SIMModel\SIMModelParameter.h"
#include "..\SIMModel\SIMParameterProfile.h"
#include "..\SIMModel\SIMParameterValue.h"
#include "..\SIMModel\SIMParameterOperationalMode.h"


ViewState::ViewState(){
	

}



ViewState::~ViewState(){

}



void ViewState::recursiveDraw(SIMModelNode* start){

	//if a leaf returns
	if(start == NULL) return;

	//ofLogVerbose("[VIEWSTATE]") << "Recursive draw at: " << start->profile.GetAcronym();

	//if doesnt have a 3d models, doesnt draw
	if(start->model3D != NULL)
		if(start->model3D->isLoaded()){
		//ofLogVerbose() << "Request to draw:" << start->profile.GetAcronym();

		//start->model3D->setPivot(v_pivot);

		start->model3D->draw();
	}

	if( start->nodeList.empty() )  return;

	vector<SIMModelNode*>::iterator itN;
	//ofLogVerbose("[VIEWSTATE]") << "Recursive going for more";
	
	for( itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
			recursiveDraw((*itN));
}



// retorning infinit NULL ------ correct this.
SIMModelNode* ViewState::findNearestObjectToAction(SIMModelNode* start){

	if(start!=NULL){
		if(start->model3D!=NULL){
			
			start->model3D->setAuxPlace( this->mySatview->cam.worldToScreen(start->model3D->getPivot()));

			float distance = start->model3D->getAuxPlace().distance( this->mySatview->myScreen->myAction->actual.position);
			//cout<<start->acronym;
			//cout<<endl<<start->acronym<<" - "<<start->auxPlace<<" -Distance "<<distance<<" -nearestD:"<<this->nearestDistance;
			//start->distMouse = distance;
			if( (this->nearestIndex == 0 || distance < this->nearestDistance) ) {
				this->nearestDistance = distance;
				if(distance < 150){
					this->mySatview->myScreen->myAction->actualClosestObject = start;
					this->mySatview->myScreen->myAction->closestObjectType = nodeType::ntEQUIPMENT;
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