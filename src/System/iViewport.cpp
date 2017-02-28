///////////////////////////////////////////////////////////
//  iViewport.cpp
//  Implementation of the Class iViewport
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "iViewport.h"


iViewport::iViewport(){

}



iViewport::~iViewport(){

}


void iViewport::setDimensions(int x, int y, int width, int height){

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


void iViewport::updateViewport(){
	float w = ofGetWidth();
	float h = ofGetHeight();

	this->place.x = (this->x*w)/100;
	this->place.y = (this->y*h)/100;
	this->place.width = (this->width*w)/100;
	this->place.height = (this->height*h)/100;

}


void iViewport::drawBackground(){

	ofPushMatrix();
	ofPushView();
		ofEnableAlphaBlending();
		ofEnableLighting();
		ofFill();
		ofSetLineWidth(2);
		ofSetColor(this->backgroundColor,5);
		//ofSetColor(ofColor::black);
		ofRect(this->place);
		ofNoFill();
		ofSetColor(this->backgroundColor,40);
		//ofSetColor(ofColor::black);
		ofRect(this->place);

		ofDrawBitmapString(this->name,this->place.getTopLeft() + 20);

		ofDisableLighting();
		ofDisableAlphaBlending();
	ofPopView();
	ofPopMatrix();
}