///////////////////////////////////////////////////////////
//  mouseClick.cpp
//  Implementation of the Class mouseClick
//  Created on:      06-set-2013 15:30:03
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "mouseClick.h"


mouseClick::mouseClick(){
	this->view = NULL;
	this->button = 0;
	this->position.set(0,0,0);
	this->time = 0;

	this->closestObject = NULL;
	this->closestObjectType = 0;
}



mouseClick::~mouseClick(){

}

void mouseClick::set(int v_button, ofPoint v_position,iView *v){

	button = v_button;
	position = v_position;
	time = ofGetSystemTimeMicros();
	view = v;
}