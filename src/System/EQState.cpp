///////////////////////////////////////////////////////////
//  EQState.cpp
//  Implementation of the Class EQState
//  Created on:      06-set-2013 14:20:20
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "EQState.h"

#include "SatView.h"
#include "ViewState.h"
#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"
#include "..\SIMModel\SIMModelNode.h"
#include "..\SIMModel\Node3D.h"

EQState::EQState(){
	this->name = "eqstate";
}



EQState::~EQState(){

}


void EQState::draw(){
	ofLogVerbose() << "EQState" << this->mySatview->name;

	this->mySatview->cam.begin(this->mySatview->vp->place);

		ofDrawAxis(100);

	this->mySatview->cam.end();
}

void EQState::handle(){

}