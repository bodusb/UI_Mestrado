///////////////////////////////////////////////////////////
//  SystemView.cpp
//  Implementation of the Class SystemView
//  Created on:      06-set-2013 14:19:54
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SystemView.h"
#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"

SystemView::SystemView(){
	verbo = true;

}


SystemView::~SystemView(){

}


void SystemView::guiEvent(ofxUIEventArgs& e){

	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	string parent = e.widget->getParent()->getName();

	ofLogVerbose("[SYSTEM CONTROLS PANEL CHANGES]") << name << " - " << ofToString(kind) << " - Parent:" << parent;

	if( name == "runStatus"){
		switch (this->myScreen->myAction->modelController->getSimulatorStatus())
		{
		case simStatus::ssDISCONNECTED: { 

			if ( this->myScreen->myAction->modelController->simLink->setConnected(true)){
			status->setLabelText("STOP"); 
			status->setValue(false);
			this->myScreen->myAction->modelController->setSimulatorStatus(simStatus::ssCONNECTED);
			this->myScreen->myAction->connection = true;
			this->myScreen->myAction->run = false;
			run->setVisible(true);
			step->setVisible(true);
			this->resizeView();
			this->myScreen->myAction->followingCurrentTime = true;
			ofLogVerbose("[SYSTEM CONTROLS PANEL CHANGES]") << "SET TO CONNECTED";
			} 
			break;}

		case simStatus::ssCONNECTED:{ 
			status->setLabelText("START"); 
			status->setValue(false);
			this->myScreen->myAction->modelController->setSimulatorStatus(simStatus::ssDISCONNECTED);
			this->myScreen->myAction->run = false;
			this->myScreen->myAction->connection = false;
			run->setVisible(false);
			step->setVisible(false);
			this->resizeView();
			ofLogVerbose("[SYSTEM CONTROLS PANEL CHANGES]") << "SET TO DISCONNECTED";
			break;}
		case simStatus::ssLOSTCONNECTION: status->setLabelText("LOST CONNECTION");break;
		case simStatus::ssERROR: status->setLabelText("ERROR"); break;
		default:
			break;
		}
	}

	if( name == "stepButton"){
		switch (this->myScreen->myAction->modelController->getSimulatorStatus())
		{
		case simStatus::ssDISCONNECTED: break;
		case simStatus::ssCONNECTED:{ 

			this->myScreen->myAction->modelController->simLink->sendMessage(messageType::mtSIMSTEP);
			this->myScreen->myAction->run = false;
			run->setValue(false);
			step->setValue(false);

			ofLogVerbose("[SYSTEM CONTROLS PANEL CHANGES]") << "SEND SIMULATOR STEP";
			break;}
		case simStatus::ssLOSTCONNECTION: 
		case simStatus::ssERROR: 
		default:
			break;
		}

	}


	if( name == "runButton"){
		switch (this->myScreen->myAction->modelController->getSimulatorStatus())
		{
		case simStatus::ssDISCONNECTED: break;
		case simStatus::ssCONNECTED:{ 

			if( this->myScreen->myAction->run == true) {
				this->myScreen->myAction->run = false;
				run->setValue(false);
			} else {
				this->myScreen->myAction->run = true;
				run->setValue(true);
			}

			ofLogVerbose("[SYSTEM CONTROLS PANEL CHANGES]") << "toogle run";
			break;}
		case simStatus::ssLOSTCONNECTION: 
		case simStatus::ssERROR: 
		default:
			break;
		}
	}
}

void SystemView::startView(){
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
	float length = 255-xInit; 

	gui = new ofxUICanvas();

	gui->setTheme(OFX_UI_THEME_HACKER);

	//gui->setColorBack(ofxUIColor::black);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);


	status = gui->addLabelToggle("runStatus",this->myScreen->myAction->connection);
	run = gui->addLabelToggle("runButton",this->myScreen->myAction->run);
	step = gui->addLabelToggle("stepButton",this->myScreen->myAction->doStep);
	
	run->setVisible(false);
	run->setLabelText("Run");

	step->setVisible(false);
	step->setLabelText("Step");

	this->resizeView();
	ofAddListener(gui->newGUIEvent, this, &SystemView::guiEvent); 



	this->myScreen->myAction->addTolog("[SYSTEMSTART]", " System started");

//	this->verbose = new ofxUILabelToggle(&this->verbo,"verbose",OFX_UI_FONT_LARGE);
//	this->verbose->setLabelText("Verbose");
}


void SystemView::draw(){

	switch (this->myScreen->myAction->modelController->getSimulatorStatus())
	{
	case simStatus::ssDISCONNECTED: status->setLabelText("START"); break;
	case simStatus::ssCONNECTED: status->setLabelText("STOP"); break;
	case simStatus::ssLOSTCONNECTION: status->setLabelText("LOST CONNECTION");break;
	case simStatus::ssERROR: status->setLabelText("ERROR"); break;
	default:
		break;
	}

	this->resizeView();

}


void SystemView::panelEvent(ofxUIEventArgs& e){

	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	string parent = e.widget->getParent()->getName();


	if(name == "verbose"){
		ofxUILabelToggle *aux = (ofxUILabelToggle*)e.widget;

		if(verbo == true){
			verbo = false;
			aux->setValue(false);
			ofSetLogLevel(OF_LOG_SILENT);
			ofLogVerbose("[OM PANEL CHANGES]") << name << " Verbose SILENT ";
	
		} else {
			verbo = true;
			aux->setValue(true);
			ofSetLogLevel(OF_LOG_VERBOSE);
			ofLogVerbose("[OM PANEL CHANGES]") << name << " Verbose ON ";
		}
	}




	ofLogVerbose("[OM PANEL CHANGES]") << name << " - " << ofToString(kind) << " - Parent:" << parent;
}


void SystemView::setContextPanel(){
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
	panel->addWidgetDown(new ofxUILabel("System Context Panel", OFX_UI_FONT_LARGE)); 

	panel->addSpacer();
	// connect
	//panel->addToggle("CONNECTED",false)->setName("simCONNECTION");
	// sim address

	if( this->myScreen->myAction->modelController->getSimulatorStatus() == simStatus::ssDISCONNECTED){

	panel->addTextInput("Address:","localhost")->setName("simADDRESS");
	// sim port
	panel->addTextInput("Port Connection:","9000")->setName("simPORT");

	panel->addSpacer();

	}




	// do a step
	//panel->addButton("STEP",false);

	// run
	//panel->addToggle("RUN",false);

	// time factor
	panel->addSlider("Time multiplier",0,100,1);

	panel->addSpacer();

	

	panel->addWidgetDown(new ofxUILabelToggle(&this->verbo,"verbose",OFX_UI_FONT_LARGE));


	panel->autoSizeToFitWidgets();


	ofAddListener(panel->newGUIEvent, this, &SystemView::panelEvent); 
}

void SystemView::resizeView(){

	gui->autoSizeToFitWidgets();

	gui->setPosition(ofGetWidth()/2 - gui->getRect()->width/2, ofGetHeight()-40);


	//gui->setDimensions(this->vp->place.width,this->vp->place.height);

	//this->myScreen->myAction->addTolog("[INTERFACE]", "[" + ofGetTimestampString() + "] - System View Resized");
	//ofLogVerbose("[INTERFACE]") << "[" +  ofGetTimestampString() + "] - System View Resized";
}