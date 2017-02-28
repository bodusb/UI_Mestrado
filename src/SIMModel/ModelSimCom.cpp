///////////////////////////////////////////////////////////
//  ModelSimCom.cpp
//  Implementation of the Class ModelSimCom
//  Created on:      13-dez-2013 18:03:59
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ModelSimCom.h"

#include "../System/iAction.h"
#include "../System/ModelControl.h"


ModelSimCom::ModelSimCom(){

//		ofSystemAlertDialog("ModelSIMCOM");

}



ModelSimCom::~ModelSimCom(){

}


bool ModelSimCom::setConnected(bool newVal){

	sender->setup(this->simulatorIP,this->portNumber + 1);
	receiver->setup(this->portNumber);

	// try connection
	ofxOscMessage m;
	
	m.setAddress("/ping");
	m.addStringArg("hello here is iSIMC3");
	sender->sendMessage(m);

	this->myModel->myAction->addTolog("[SOCKET]", ofToString(receiver) + " - sending a ping request to " + this->simulatorIP);

	double counter = ofGetSystemTime();
	//ofSleepMillis(1000);

	while(!connected){
		if(ofGetSystemTime() > counter + 5000) {
			this->myModel->myAction->addTolog("[SOCKET]", "TIME-OUT");
			this->connected = false;
			return false;
		}

		ofLogVerbose() << ".  " + ofToString(counter) + " - " +  ofToString(ofGetSystemTime());

		while(receiver->hasWaitingMessages()){

			ofLogVerbose("[SOCKET]") << "INSIDE THE WAITING MESSAGES";

			// waits for ping answer
			ofxOscMessage ans;
			receiver->getNextMessage(&ans);
			this->myModel->myAction->addTolog("[SOCKET]", "Simulator answer: " + ans.getAddress());

			if(ans.getAddress() == "/pingAns"){
				this->myModel->myAction->addTolog("[SOCKET]", "Simulator answer: " + ans.getArgAsString(0));
				this->connected = true;
				return true;
			} 

		}
	}

//	this->myModel->myAction->addTolog("[SOCKET]", "Simulator answer: " + ans.getAddress() + "Not recognized");
	this->connected = false;
	return false;
}



void ModelSimCom::receiveMessage(){
	

	//this->myModel->myAction->addTolog("[SOCKET]", ofToString(&receiver) );
	if( connected){
		while(receiver->hasWaitingMessages()){
		//	ofLogVerbose("[SOCKET]") << "INSIDE THE WAITING MESSAGES";
			message.clear();
			receiver->getNextMessage(&message);
			this->myModel->myAction->addTolog("[SOCKET]",  ofToString(receiver) + " Simulator answer: " + message.getAddress());
		
		
			if(message.getAddress() == "/paramReadAns"){
				this->handlePARAMREAD();
			}
			if(message.getAddress()=="/stepAns"){
				this->handleSIMSTEP();
			}

			// handle getting random OSC messages here

		}
	}

}


void ModelSimCom::sendMessage(messageType mess){

	if(connected){
		switch(mess){
		case messageType::mtSIMSTEP: {

			// MAKE ONE STEP
			date *aux = &this->myModel->myAction->simulatedDate;

			this->myModel->myAction->addTolog("[SOCKET]"," Handling SIMSTEP message - requested from " + 
				ofToString(aux->Year) + "_" + ofToString(aux->Month) + "_" + ofToString(aux->Day) + "_" + ofToString(aux->Hour) + "_" + ofToString(aux->Min) + "_" + ofToString(aux->Sec));

			message.clear();
			message.setAddress("/simStep");
			message.addIntArg((int)aux->Year);
			message.addIntArg((int)aux->Month);
			message.addIntArg((int)aux->Day);
			message.addIntArg((int)aux->Hour);
			message.addIntArg((int)aux->Min);
			message.addFloatArg(aux->Sec);
			message.addIntArg((int)3);

			sender->sendMessage(message);
			message.clear();

			break;}
		case messageType::mtPARAMREAD: { this->handlePARAMREAD(); break;}
		default: break;
		}
	} else {
		this->myModel->myAction->addTolog("[SOCKET]"," SIMULATOR IS OFF");
		return;
	}

}




bool ModelSimCom::isConnected(){

	return connected;
}
