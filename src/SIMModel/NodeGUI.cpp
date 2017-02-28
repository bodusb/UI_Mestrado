///////////////////////////////////////////////////////////
//  NodeGUI.cpp
//  Implementation of the Class NodeGUI
//  Created on:      06-set-2013 14:20:02
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "NodeGUI.h"

#include "..\SIMModel\SIMModelNode.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMNodeProfile.h"
#include "..\SIMModel\NodePositions.h"

#include "..\SIMModel\SIMModelParameter.h"
#include "..\SIMModel\SIMParameterProfile.h"
#include "..\SIMModel\SIMParameterValue.h"
#include "..\SIMModel\SIMParameterOperationalMode.h"





NodeGUI::NodeGUI(){

}



NodeGUI::~NodeGUI(){

}



void NodeGUI::panelEvent(ofxUIEventArgs& e){
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	string parent = e.widget->getParent()->getName();

	ofLogVerbose("[OM PANEL CHANGES]") << name << " - " << ofToString(kind) << " - Parent:" << parent;

	if( kind == OFX_UI_WIDGET_BUTTON){
		ofxUIButton *b = (ofxUIButton*) e.widget;
		if( b->getValue()){


		// find node son and close this panel and open his

		SIMModelNode *aux = this->myNode->getNode(name);

		if ( aux != NULL) {
			this->myAction->actualPanel->setVisible(false);
			this->myAction->actualPanel = NULL;

			aux->nodeGUI->setContextPanel();
			aux->nodeGUI->setPanelVisible(true);
			this->myAction->actualPanel = aux->nodeGUI->getPanel();
			this->myAction->somePanelVisible = true;
		}

		}
	//	this->changeOMto(name);
	////	if(kind == 	OFX_UI_WIDGET_TOGGLE){
	////		ofxUIRadio *radio = (ofxUIRadio*) e.widget;
	////		ofLogVerbose("[OM PANEL CHANGES]") <<  this->profile.GetUniqueCode() << " - " << radio->getActive()->getName();
	////	}
	}


}


void NodeGUI::setContextPanel(){


	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	
	panel = new ofxUIScrollableCanvas(0, 0, 300, ofGetHeight());  
	panel->setName(this->myNode->profile.GetAcronym() + "panel");

	//panel->setTheme(OFX_UI_THEME_HACKER);
	//panel->
	panel->setColorBack(ofxUIColor(ofColor::darkBlue));
	panel->setScrollAreaToScreen();
    panel->setScrollableDirections(false, true);

	panel->addWidgetDown(new ofxUILabel("Object Context Panel", OFX_UI_FONT_LARGE)); 

	//Create the profile structure
	this->makeProfile();

	//Create parameter structure
	this->makeParameter();

	//Create sons structure
	this->makeSons();

	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &NodeGUI::panelEvent); 

}


void NodeGUI::makeProfile(){	
	// ---------------------
	// XXXXX Profile
	// Name : XXXX
	// Acronym : XXXX - CBERS Acronym : XXXX
	// Of: XXXX


	this->panel->addSpacer(5);

	// Create Profile

	string type;

	switch(this->myNode->profile.GetNodeType()){
	case nodeType::ntEARTH: {type = "Earth"; break; }
	case nodeType::ntGROUNDSTATION: {type = "Ground Station"; break; }
	case nodeType::ntSATELLITE: {type = "Satellite"; break; }
	case nodeType::ntSUBSYSTEM: {type = "Subsystem"; break; }
	case nodeType::ntEQUIPMENT: {type = "Equipment"; break; }
	case nodeType::ntINTERESTPOINT: {type = "Interesting Point"; break; }
	default: break;	};


	this->panel->addWidgetDown(new ofxUILabel(type + " Profile", OFX_UI_FONT_LARGE)); 
	this->panel->addWidgetDown(new ofxUILabel("Name: " + this->myNode->profile.GetName(), OFX_UI_FONT_MEDIUM)); 
	this->panel->addWidgetDown(new ofxUILabel("Acronym: " + this->myNode->profile.GetAcronym() + " - UNIQUE CODE: " + this->myNode->profile.GetUniqueCode(), OFX_UI_FONT_MEDIUM)); 

	string father;

	switch(this->myNode->profile.GetNodeType()){
	case nodeType::ntSUBSYSTEM: 
	case nodeType::ntEQUIPMENT: {
		father = this->myNode->getFather()->profile.GetAcronym(); 
		this->panel->addWidgetDown(new ofxUILabel("Of: " + father, OFX_UI_FONT_MEDIUM)); 
		break; 
								 
								 }
	default: break;	};


	this->panel->addSpacer(5);
}


void NodeGUI::makeParameter(){

	this->panel->addSpacer(5);
	
	this->panel->addWidgetDown(new ofxUILabel("Parameters:", OFX_UI_FONT_LARGE)); 

	vector<SIMModelParameter*>::iterator p;

	for (p = this->myNode->paramList.begin() ; p != this->myNode->paramList.end() ; p++){

		(*p)->makeParamPanel(this->panel);

	}

	this->panel->addSpacer(5);
}

void NodeGUI::makeSons(){

	this->panel->addSpacer(5);

	switch(this->myNode->profile.GetNodeType()){
	case nodeType::ntSATELLITE: this->panel->addWidgetDown(new ofxUILabel("Subsystems:", OFX_UI_FONT_LARGE)) ; break;
	case nodeType::ntGROUNDSTATION: this->panel->addWidgetDown(new ofxUILabel("Subsystems:", OFX_UI_FONT_LARGE)) ; break;
	case nodeType::ntSUBSYSTEM: this->panel->addWidgetDown(new ofxUILabel("Equipments:", OFX_UI_FONT_LARGE)); break;
	case nodeType::ntEQUIPMENT: this->panel->addWidgetDown(new ofxUILabel("Components:", OFX_UI_FONT_LARGE)); break;
	default: break;	};

	vector<SIMModelNode*>::iterator sons;
	bool x;
	for(sons = this->myNode->nodeList.begin();sons != this->myNode->nodeList.end(); sons++){
		this->panel->addWidgetDown(new ofxUILabel((*sons)->profile.GetAcronym() + " [" + (*sons)->profile.GetUniqueCode() + "] - ", OFX_UI_FONT_SMALL));
			// change 3d view or focus
			//ofxUIButton *auxB = new ofxUIButton("SEE 3D",false,16,16);
			//auxB->setName((*sons)->profile.GetUniqueCode() + "Button_see3D");
			//this->panel->addWidgetRight(auxB);
			// Change panel
			ofxUIButton *auxB = new ofxUIButton("SEE INFO",false,16,16);
			auxB->setName((*sons)->profile.GetUniqueCode());
			this->panel->addWidgetRight(auxB);
	}

	this->panel->addSpacer(5);

}