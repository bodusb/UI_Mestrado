///////////////////////////////////////////////////////////
//  SSState.cpp
//  Implementation of the Class SSState
//  Created on:      06-set-2013 14:20:18
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SSState.h"

#include "SatView.h"
#include "ViewState.h"
#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"
#include "..\SIMModel\SIMModelNode.h"
#include "..\SIMModel\Node3D.h"

SSState::SSState(){
	this->name = "ssstate";
}



SSState::~SSState(){

}

void SSState::draw(){
	ofLogVerbose() << "SSState";
	
	this->mySatview->cam.begin(this->mySatview->vp->place);

	ofDrawGridPlane(100);

	
	this->mySatview->cam.end();
}

void SSState::handle(){

}