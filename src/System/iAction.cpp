///////////////////////////////////////////////////////////
//  iAction.cpp
//  Implementation of the Class iAction
//  Created on:      06-set-2013 14:19:56
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "iAction.h"

#include "mouseClick.h"

#include "iScreen.h"
#include "iView.h"
#include "LogView.h"

#include "..\SIMModel\SIMModelNode.h"
#include "..\SIMModel\NodeRDT.h"
#include "..\SIMModel\NodePositions.h"
#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMNodeProfile.h"
#include "..\SIMModel\NodeGUI.h"
#include "..\System\ModelControl.h"

iAction::iAction(){
	this->somePanelVisible = false;

	this->startClick.view = NULL;
	this->endClick.view = NULL;
	this->actual.view = NULL;	


	followingCurrentTime = false;
	connection = false;
	run = false;
	doStep = false;

	doAlarm = false;
	// we are running the systems commands
	// in a sperate thread so that it does
	// not block the drawing
	// startThread();

	//this->currentTime = "";

	// pass the action link to all node GUIs

	collide.loadSound("sounds/click.mp3");
	collide.setVolume(0.4f);



	alarm.loadSound("sounds/alarm.mp3");
	alarm.setVolume(0.4f);

	this->simulatedDate.Year = 0;
	this->simulatedDate.Month = 0;
	this->simulatedDate.Day = 0;
	this->simulatedDate.Hour = 0;
	this->simulatedDate.Min = 0;
	this->simulatedDate.Sec = 0;

}



iAction::~iAction(){
	// stop the thread on exit
	//  waitForThread(true);
}



bool iAction::hasDrag(){

	if(this->startClick.position.squareDistance(this->endClick.position) > 20) return true;
	return false;
}


bool iAction::hasHold(int threshold){

	if( this->endClick.time - this->startClick.time > threshold) return true;
	return false;
}


void iAction::selectingAction(int v_button, ofPoint v_position){

	vector<iView*>::iterator views;
	this->actualClosestObject = NULL;
	this->closestObjectType = 0;

	//if a panel is visible 
	if(this->somePanelVisible == true){

		//check if mouse is over the panel
		if(this->actualPanel->getRect()->inside(v_position)){
			//cout<<endl<<action->actualGUI->getRect()->getHeight()<<" - "<<action->actualGUI->getRect()->getWidth();
			//disable all views mouse actions
			for(views = this->m_iScreen->iviewList.begin(); views != this->m_iScreen->iviewList.end(); views++) 
				(*views)->cam.disableMouseInput();
			this->message = this->actualPanel->getName();	
		}  
	}
	else{

		int otherAboveMain = 0;
		this->actual.view = NULL;
		//verify which view the mouse is over
		for(views = this->m_iScreen->iviewList.begin(); views != this->m_iScreen->iviewList.end(); views++) 
			//if(){	//check if the mouse is over something differente from the main viewplace
				if((*views)->vp != NULL){
					if( (*views)->vp->name != "main" && (*views)->vp->place.inside(v_position)){
						this->actual.set(-1,v_position,(*views));
						(*views)->cam.enableMouseInput();
						//->>>>>>>>>>>>>>>>>>>>>>>>>>>>>> selectionAction
						(*views)->selectingAction();
						this->message = (*views)->name;
						//if(this->actualClosestObject != NULL) collide.play(); 
						//break;
					} else {
						(*views)->cam.disableMouseInput();
					}
				}
				if( this->actual.view == NULL ){
					// if any of the views were found probably is over the main view
					// search who is in main
					for(views = this->m_iScreen->iviewList.begin(); views != this->m_iScreen->iviewList.end(); views++) 
						if((*views)->vp != NULL){
							if((*views)->vp->name == "main"){
								this->actual.set(-1,ofPoint(v_position),(*views));
								(*views)->cam.enableMouseInput();
								//->>>>>>>>>>>>>>>>>>>>>>>>>>>>>> selectionAction
								(*views)->selectingAction();
								//if(this->actualClosestObject != NULL) collide.play();
								this->message = (*views)->name;
							}
						}
				}
	}
}

void iAction::startAction(int v_button, ofPoint v_position){

	if( this->actual.view != NULL ){
		this->startClick.set(v_button, v_position,this->actual.view);
		this->startClick.closestObject = this->actualClosestObject;
		this->startClick.closestObjectType = this->closestObjectType;
	}

	//this->addTolog("[INTERFACE]"," start action at: " + this->startClick.view->name);
}

void iAction::finishAction(int v_button, ofPoint v_position){


	this->selectingAction(v_button,v_position);

	this->endClick.set(v_button,v_position,this->actual.view);
	this->endClick.closestObject = this->actualClosestObject;
	this->endClick.closestObjectType = this->closestObjectType;
	//ofLogVerbose() << "[INTERFACE] end action at:"<<this->endClick.view->name;

	/*ofSystemAlertDialog("Start:" + ofToString(action->startClick.position.x) + "," + ofToString(action->startClick.position.y)
	+ "End:" + ofToString(action->endClick.position.x) + "," + ofToString(action->endClick.position.y)
	+ " Distance:" + ofToString(action->endClick.position.squareDistance(action->startClick.position)));
	*/

	//if a panel is visible 
	if(this->somePanelVisible == true){

		//check if mouse is over the panel
		//if(this->actualPanel->getRect()->inside(this->startClick.position)){ //|| this->actualPanel->getRect()->inside(this->endClick.position)){
	/*	if( this->actualPanel->getRect()->inside(this->endClick.position)){
		}  else {
			ofLogVerbose("[ACTION]") << "Close Panel : " << this->actualPanel->getName();
			this->actualPanel->setVisible(false);
			this->actualPanel = NULL;
			this->somePanelVisible = false;
		}*/


		if(!this->actualPanel->isHit(this->startClick.position.x,this->startClick.position.y)){
			ofLogVerbose("[ACTION]") << "Close Panel : " << this->actualPanel->getName();
			this->actualPanel->setVisible(false);
			this->actualPanel = NULL;
			this->somePanelVisible = false;
		}


	}
	else{   

		if( this->startClick.closestObject == NULL){

			//doesn´t have a fly over and leaving on different location... do swap views
			if( this->startClick.view->vp->name != this->endClick.view->vp->name){ 

				string aEnd = this->endClick.view->name;
				string aST = this->startClick.view->name;

				if ( aEnd != "systemview" &&  aEnd !=  "logview" && aEnd !=  "timelineview" &&
					 aST != "systemview" &&  aST !=  "logview" && aST !=  "timelineview"){

					ofLogVerbose() << "[INTERFACE][Swap view] "<<this->startClick.view->name<<" <-> "<<this->endClick.view->name;
					this->m_iScreen->swapViews(this->startClick.view,this->endClick.view);
				}
				return;

			} else {
				// might have clicked on log views:
				ofLogVerbose() << "[INTERFACE] -------------------- test logView";
				if (this->endClick.view->name == "logview"){
					this->addTolog( "[INTERFACE]"," -- add logview item");
					
				}

			}

			//doesn't have a fly and leaving on same location... with a hold... call view panel
			if ( this->startClick.view->vp->name == this->endClick.view->vp->name && hasHold(500000)){
				//ofLogVerbose() << "[INTERFACE][OpenPanel] "<<this->startClick.view->name;

				//check if other panel is open
				if(this->somePanelVisible){
					//if open close
					this->actualPanel->setVisible(false);
					this->actualPanel = NULL;
					this->somePanelVisible = false;

				} else {
					//ofSystemAlertDialog("Clicked on somewhere else");
					this->startClick.view->setContextPanel();
					this->startClick.view->setPanelVisible(true);
					this->actualPanel = this->startClick.view->getPanel();
					this->somePanelVisible = true;
				}

				return;
			}

		} else {
			ofLogVerbose("[INTERFACE]") << "god dammit has something... lets deal with it.";
			//ofLogVerbose("[INTERFACE]") << this->startClick.view->name << " requires to open " << ((SIMModelNode*)this->startClick.closestObject)->profile.GetAcronym();

			// THROW OBJECT PANEL
			//check if other panel is open
			if(this->somePanelVisible){
				//if open close
				this->actualPanel->setVisible(false);
				this->actualPanel = NULL;
				this->somePanelVisible = false;
			} else {
				//ofSystemAlertDialog("Clicked on somewhere else");

				switch(this->startClick.closestObjectType){
				case nodeType::ntRDT:
				case nodeType::ntSATELLITE:
				case nodeType::ntGROUNDSTATION:
				case nodeType::ntSUBSYSTEM:
				case nodeType::ntEQUIPMENT:{
					SIMModelNode* aux = (SIMModelNode*)this->startClick.closestObject;

					// is releasing in the same View?!?!
					if( this->endClick.view->name == this->startClick.view->name){

						// OPEN A PANEL OR CALL OBJECT ACTION!!!
						if(aux->nodeGUI != NULL){

							aux->nodeGUI->setContextPanel();
							aux->nodeGUI->setPanelVisible(true);
							this->actualPanel = aux->nodeGUI->getPanel();
							this->somePanelVisible = true;
						}
					} else {
						// not releasing in the same view MAN WHAT NOW???

					}
					break;}
				default: break;	};


			}



			//check if has no end



		}


		//ofSystemAlertDialog("Clicked on " + action->startClick.view->name + " - Released on " + action->endClick.view->name);

		//--------------------------------> action into the view
		//this->startClick.view->doAction(action);

	}


}


void iAction::drawClosestGuide(){

	if(this->actual.view->vp->name == "main"){ // only draw on actual (at now) later draw on start and on end

		//ofLogVerbose() << "----------> TRY TO DRAW CLOSEST GUIDE";
		if(this->actualClosestObject != NULL){
			//ofLogVerbose() << "----------> HAS SOMETHING GOGOGO";
			switch(this->closestObjectType){
			case nodeType::ntRDT:
			case nodeType::ntSATELLITE:
			case nodeType::ntGROUNDSTATION:
			case nodeType::ntSUBSYSTEM:
			case nodeType::ntEQUIPMENT:{
				//ofLogVerbose() << "----------> found type GOGOGO";
				SIMModelNode* aux = (SIMModelNode*)this->actualClosestObject;
				//ofLogVerbose() << "----------> found type cast done" << closestObjectType;
				ofVec3f tempPos;
				switch(this->closestObjectType){
				case nodeType::ntRDT: tempPos = aux->nodeRDT->getAuxPlace(); break;
				case nodeType::ntSATELLITE: tempPos = aux->myEarthPosition->auxPlace; break;
				case nodeType::ntGROUNDSTATION: tempPos = aux->myEarthPosition->auxPlace; break;
				case nodeType::ntEQUIPMENT: tempPos = aux->model3D->getAuxPlace(); break;
				case nodeType::ntSUBSYSTEM: tempPos = aux->model3D->getAuxPlace(); break;
				default: break;	};
				//ofLogVerbose() << "----------> Found related position oh boy";
				//draw a line from pointer to selected object
				ofSetLineWidth(1);
				ofSetColor(ofColor::yellow);
				ofLine(tempPos,this->actual.position);

				//place a circle in the selected element
				ofNoFill();
				ofSetColor(ofColor::red);
				ofSetLineWidth(2);
				ofCircle(tempPos,4);

				break;}
			default: break;

			}

		}
	}

}


void iAction::addTolog(string context, string value){
	this->logPANEL->addLabel(context + " " + value,2);
	ofLogVerbose(context) << value;
	this->logPANEL->autoSizeToFitWidgets();
}


void iAction::update(){

	this->currentDate.Year = ofGetYear();
	this->currentDate.Month = ofGetMonth();
	this->currentDate.Day = ofGetDay();
	this->currentDate.Hour = ofGetHours();
	this->currentDate.Min = ofGetMinutes();
	this->currentDate.Sec = ofGetSeconds();

	if ( this->followingCurrentTime) {

		this->simulatedDate.Year = ofGetYear();
	this->simulatedDate.Month = ofGetMonth();
	this->simulatedDate.Day = ofGetDay();
	this->simulatedDate.Hour = ofGetHours();
	this->simulatedDate.Min = ofGetMinutes();
	this->simulatedDate.Sec = ofGetSeconds();

	}


	// if run  do the step automaticaly
	if(this->run){

		int currTime = this->simulatedDate.Sec;

		if(timeCounter != currTime){

			timeCounter = currTime;
			this->modelController->simLink->sendMessage(messageType::mtSIMSTEP);
		}
	
	}



	// if connect call the queue updates
	if(this->connection){
		//this->addTolog("[iACTION]"," Going to treat queue");
		this->modelController->simLink->receiveMessage();
	}




}


void		iAction::spreadAction(){
	this->recursiveSpread(this->modelController->getModelHead());
}

void		iAction::recursiveSpread(SIMModelNode *start){

	if(start->nodeGUI != NULL){
		start->nodeGUI->setMyAction(this);
	}

	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
		recursiveSpread((*itN));

}