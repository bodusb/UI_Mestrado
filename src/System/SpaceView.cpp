///////////////////////////////////////////////////////////
//  SpaceView.cpp
//  Implementation of the Class SpaceView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SpaceView.h"

#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"
#include "..\SIMModel\SIMModelNode.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMNodeProfile.h"
#include "..\SIMModel\NodePositions.h"

#include "..\SIMModel\SIMModelParameter.h"
#include "..\SIMModel\SIMParameterProfile.h"
#include "..\SIMModel\SIMParameterValue.h"
#include "..\SIMModel\SIMParameterOperationalMode.h"


SpaceView::SpaceView(){
	cam.setFarClip(300000); 
	cam.setDistance(20000);

}


SpaceView::~SpaceView(){

}


void SpaceView::draw(){

	cam.begin(this->vp->place);

	//ofDrawAxis(8000);


	ofPushView();
	ofPushMatrix();

	ofEnableDepthTest();
	glEnable(GL_DEPTH_TEST);
	ofEnableAlphaBlending();

	this->drawSUN();

	this->drawGlobe();

	this->drawGS();

	this->drawSats();


	// DRAW GUIDES HELPs


	ofDisableAlphaBlending();
	glDisable(GL_DEPTH_TEST);
	ofDisableDepthTest();

	ofPopMatrix();
	ofPopView();

	cam.end();

}


void SpaceView::executeAction(){

}


void SpaceView::selectingAction(){
	// select the closest sat or gs and send to action			---> later check iPoints

	//only action if its on main view --- for now.
	if(this->vp->name == "main"){



		this->nearestDistance = 0;
		nearestIndex = 0;
		int i = 0;

		//verifify if mouse is over a ground station or sat (both first order bellow the earth node)

		vector<SIMModelNode*>::iterator s;
		for( s = this->myScreen->myAction->modelController->model->nodeList.begin(); s != this->myScreen->myAction->modelController->model->nodeList.end(); s++){


			(*s)->myEarthPosition->auxPlace = cam.worldToScreen((*s)->myEarthPosition->rectangularToDraw);		// adjust the camera to the screen 

			if( (*s)->model3D != NULL )
				if( (*s)->model3D->isLoaded())
					(*s)->model3D->setSelected(false);

			float distance = (*s)->myEarthPosition->auxPlace.distance(this->myScreen->myAction->actual.position);	// get distance from mouse location
			if((i==0 || distance < nearestDistance)) {		
				nearestDistance = distance;
				nearestPoint = (*s)->myEarthPosition->auxPlace;
				nearestIndex = i;
				if( distance < 150 ) { 
					this->myScreen->myAction->actualClosestObject = (*s);
					this->myScreen->myAction->closestObjectType = (*s)->profile.GetNodeType();
					this->myScreen->myAction->message += (*s)->profile.GetUniqueCode();
					if( (*s)->model3D != NULL )
						if( (*s)->model3D->isLoaded())
							(*s)->model3D->setSelected(true);
					//	ofLogVerbose() << " -------- CLOSEST OBJECT ON SPACE VIEW:" << (*s)->profile.GetAcronym();

				}

			}
			i++;

		}

	}
}




void SpaceView::drawGlobe(){

	SIMModelNode* earth = this->myScreen->myAction->modelController->model;
	double eR = ((SIMParameterValue*)earth->getParam("EARad"))->getValue(); 

	//ofLogVerbose("[INTERFACE]") << "HERE";
	//ofEnableSeparateSpecularLight();
	//Draw earth
	ofPushMatrix();
	//ofPushView();
	//ofPushStyle();



	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);

	//ofRotateX(-90);
	ofRotateZ(180);

	ofSetColor(ofColor::blue);
	ofNoFill();
	ofSphere(eR);

	//ofScale(25,25,25); 
	ofSetColor(ofColor::white);
	ofFill();
	earth->model3D->setSelected(true);
	earth->model3D->drawDefault();

	//ofDisableSeparateSpecularLight();


	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);

	//ofPopStyle();
	//ofPopView();
	ofPopMatrix();

}


void SpaceView::drawSUN(){
	
	ofPushMatrix();
		SIMModelNode* earth = this->myScreen->myAction->modelController->model;

		SIMModelParameter *sunX = earth->getParam("EAsunX");
		SIMModelParameter *sunY = earth->getParam("EAsunY");
		SIMModelParameter *sunZ = earth->getParam("EAsunZ");

		float sunRadius = 695500;

		ofPoint sunPos;
		sunPos.x = *sunX->getValueVariable();
		sunPos.y = -*sunY->getValueVariable();
		sunPos.z = *sunZ->getValueVariable();

		ofSetColor(ofColor::lightYellow);
		ofLine(ofPoint(0),sunPos);
		ofSphere(sunPos,sunRadius);

	ofPopMatrix();
}


void SpaceView::drawGS(){

	ofPushMatrix();
	vector<SIMModelNode*>::iterator a;
	//glEnable(GL_DEPTH_TEST);



	SIMModelNode* earth = this->myScreen->myAction->modelController->model;

	for(a = earth->nodeList.begin(); a != earth->nodeList.end();a++){
		if( (*a)->profile.GetNodeType() == nodeType::ntGROUNDSTATION){
			ofFill();


			switch((*a)->nodeRDT->getAppearTypeFromOM()){
			case appearType::aptOFF: ofSetColor(ofColor::beige);break;// ofLogVerbose("[NODE3D]") << " OFF ";
			case appearType::aptFAILURE: ofSetColor(ofColor::red);break;// ofLogVerbose("[NODE3D]") << " FAILURE "; break;
			case appearType::aptFUNCTIONAL: ofSetColor(ofColor::green);break;//ofLogVerbose("[NODE3D]") << " FUNCTIONAL "; break;
			case appearType::aptSTANDBY: ofSetColor(ofColor::gray);break;// ofLogVerbose("[NODE3D]") << " STANDBY "; break;
			default: ofSetColor(ofColor::darkGray);break;// ofLogVerbose("[NODE3D]") << " Default ";break;
			};

			ofLine(ofPoint(0),(*a)->myEarthPosition->rectangularToDraw);
			ofSphere((*a)->myEarthPosition->rectangularToDraw,50);
			//ofDrawBitmapString((*a)->profile.GetUniqueCode(),(*a)->myEarthPosition->rectangularToDraw);
			ofSetColor(ofColor::green);
		}
	}

	if(this->myScreen->myAction->actualClosestObject != NULL )
		if(this->myScreen->myAction->closestObjectType ==  nodeType::ntGROUNDSTATION)
			ofDrawBitmapString( ((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->profile.GetAcronym(), 
			((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->myEarthPosition->rectangularToDraw);



	//glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}

void SpaceView::drawSats(){

	ofPushMatrix();
	vector<SIMModelNode*>::iterator a;
	//glEnable(GL_DEPTH_TEST);

	SIMModelNode* earth = this->myScreen->myAction->modelController->model;

	for(a = earth->nodeList.begin(); a != earth->nodeList.end();a++){
		if( (*a)->profile.GetNodeType() == nodeType::ntSATELLITE){
			// recalculate the sat lat to rec
			(*a)->myEarthPosition->latLongToRectangular();
			//ofDrawAxis(60);
			ofFill();
			ofSetColor(ofColor::lightGray);
			//ofLine(ofPoint(0),(*a)->myEarthPosition->rectangularToDraw);

			SIMModelNode* s = this->myScreen->myAction->modelController->getNode("RB"); //call sat rb
			if ( s == NULL){
				ofBox((*a)->myEarthPosition->rectangularToDraw,10);
			} else {
				s->model3D->setSelected(true);
				ofTranslate((*a)->myEarthPosition->rectangularToDraw);
				s->model3D->draw();
				s->model3D->setSelected(false);
			}
			ofSetColor(ofColor::green);

		}
	}

	if(this->myScreen->myAction->actualClosestObject != NULL )
		if(this->myScreen->myAction->closestObjectType ==  nodeType::ntSATELLITE)
			ofDrawBitmapString( ((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->profile.GetAcronym(), 
			((SIMModelNode*)this->myScreen->myAction->actualClosestObject)->myEarthPosition->rectangularToDraw);

	//glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}


void SpaceView::panelEvent(ofxUIEventArgs& e){

}


void SpaceView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("SpaceView Context Panel", OFX_UI_FONT_LARGE)); 

	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &SpaceView::panelEvent); 
}