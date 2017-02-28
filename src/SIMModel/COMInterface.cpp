///////////////////////////////////////////////////////////
//  SIMInterface.cpp
//  Implementation of the Class COMInterface
//  Created on:      13-dez-2013 19:06:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "COMInterface.h"

#include "SIMModelNode.h"
#include "../System/iAction.h"
#include "../System/ModelControl.h"
#include "../SIMModel/SIMModelNode.h"
#include "../SIMModel/SIMModelParameter.h"

COMInterface::COMInterface(){
	this->connected = false;
	this->portNumber = 9000;
	this->simulatorIP = "localhost";


	receiver = new ofxOscReceiver();
	sender = new ofxOscSender();

	//ofSystemAlertDialog("COMINTERFACE");

}



COMInterface::~COMInterface(){



}






void COMInterface::handleSIMCONTROL(){

}


void COMInterface::handleSIMSTEP(){

	this->myModel->myAction->addTolog("[SOCKET]", "Simulator answer: " + ofToString(message.getArgAsString(0)));
	message.clear();

	// DO READ
		
	this->handlePARAMREAD();
	this->recursiveRead(this->myModel->getModelHead());



}


void COMInterface::handleSIMCONFIG(){

}


void COMInterface::handlePARAMCHANGE(){

}


void COMInterface::handlePASSPREDICTION(){

}


void COMInterface::handleSUNPREDICTION(){

}




void COMInterface::recursiveRead(SIMModelNode* start){

	if(!isConnected()) return;

	vector<SIMModelParameter*>::iterator itP;

	for(itP = start->paramList.begin(); itP != start->paramList.end(); itP++){
		
	//	this->myModel->myAction->addTolog("[SOCKET]","Request to read " + start->profile.GetUniqueCode() + ":" + (*itP)->profile.GetUniqueCode());


		message.clear();
		message.setAddress("/simParamRead");
		message.addStringArg(start->profile.GetUniqueCode());
		message.addStringArg((*itP)->profile.GetUniqueCode());
		// SEND MESSAGE
		sender->sendMessage(message);
		
	}


	// IN BETWEEN READINGS UPDATE POSITION
	if(start->profile.GetNodeType() == nodeType::ntGROUNDSTATION )
			start->myEarthPosition->updatePosition();
	if(start->profile.GetNodeType() == nodeType::ntSATELLITE )
			start->myEarthPosition->updatePosition();



	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++){
		recursiveRead((*itN));
	}


}


void COMInterface::handlePARAMREAD(){

	//this->myModel->myAction->addTolog("[SOCKET]"," Handling PARAMREAD message");

	SIMModelNode *auxN = this->myModel->getNode(message.getArgAsString(0));

	if(auxN != NULL){

		SIMModelParameter *auxP = auxN->getParam(message.getArgAsString(1));

		if(auxP != NULL){
		//	this->myModel->myAction->addTolog("[SOCKET]",message.getArgAsString(0)+":"+message.getArgAsString(1)+"="+ofToString(message.getArgAsFloat(2)));
			auxP->setValueVariable(message.getArgAsFloat(2));
		//	this->myModel->myAction->addTolog("[SOCKET]",auxN->profile.GetUniqueCode()+":"+auxP->profile.GetUniqueCode()+"="+ofToString(*auxP->getValueVariable()));

		} else {
			this->myModel->myAction->addTolog("[SOCKET]"," PARAMREAD error node");
		}
	} else {
		this->myModel->myAction->addTolog("[SOCKET]"," PARAMREAD error param");
	}
	 
}


void COMInterface::handleSCRIPTADD(){

}


void COMInterface::handleSCRIPTCONTROL(){

}


void COMInterface::handleSCRIPTLIST(){

}


void COMInterface::handleSCRIPTREMOVE(){

}