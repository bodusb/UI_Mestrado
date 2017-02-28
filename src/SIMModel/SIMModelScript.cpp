///////////////////////////////////////////////////////////
//  SIMModelScript.cpp
//  Implementation of the Class SIMModelScript
//  Created on:      15-out-2013 11:04:20
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMModelScript.h"

#include "SIMModel.h"
#include "SIMModelNode.h"
#include "SIMNodeProfile.h"
#include "SIMParameterProfile.h"

SIMModelScript::SIMModelScript(){

	currentConfiguration = new simScript();

}

SIMModelScript::~SIMModelScript(){

}

void SIMModelScript::readConfiguration(string v_filename){

	this->configurationError = false;
	
	if( !auxXML.loadFile(v_filename)){
		ofLogError("[LOADCONFIGURATION]")  << "Error on: " << v_filename; 
		this->configurationError = true;
		return;	}


	if(auxXML.pushTag("Configuration")){

		// read the configuration profile
		if(auxXML.pushTag("profile")){
			this->currentConfiguration->name = auxXML.getValue("name","ERROR");
			this->currentConfiguration->startingJDTime = auxXML.getValue("startingTime",-99999);
			auxXML.popTag(); }
		ofLogVerbose() << "*****************************************************************************";
		ofLogVerbose("[LOADCONFIGURATION]") << "Loading configuration: " << this->currentConfiguration->name;

		// read the N parameters 
		if(auxXML.pushTag("parameters")){
			int paramCount = auxXML.getNumTags("parameterValue");
			for( int i = 0; i < paramCount; i++){
				SIMScriptObject *auxSO = new SIMScriptObject();
				auxSO->setNodeName(auxXML.getAttribute("parameterValue","node","ERROR",i));
				auxSO->setParamName(auxXML.getAttribute("parameterValue","parameter","ERROR",i));
				auxSO->setNewValue(auxXML.getValue("parameterValue",-999999,i));
				this->currentConfiguration->objectList.push_back(auxSO);
			}
			auxXML.popTag();
		}
		auxXML.popTag();
	}
	ofLogVerbose() << "*****************************************************************************";
}

//void SIMModelScript::applyConfigurationRecursively(SIMModelNode *start){
//
//	vector<SIMScriptObject*>::iterator itSO;
//	vector<SIMModelNode*>::iterator itN;
//	vector<SIMModelParameter*>::iterator itP;
//
//	//
//	ofLogVerbose("[APPLYCONFIGURATION]") << "Into: " << start->profile.GetUniqueCode();
//
//	//compare this parameters with the configuration list of parameters
//
//	for( itSO = this->currentConfiguration->objectList.begin(); itSO != this->currentConfiguration->objectList.end(); itSO++){
//		if(!(*itSO)->isApplied() && (*itSO)->getNodeName() != "ERROR" && (*itSO)->getParamName() != "ERROR" && (*itSO)->getNewValue() != -999999){
//			//not applied yet and everything is ok!
//			//check if its the correct node
//			if(start->profile.GetUniqueCode() == (*itSO)->getNodeName()){
//				//found node
//				//lets find the parameter
//				for( itP = start->paramList.begin(); itP != start->paramList.end(); itP++){
//					if( (*itP)->profile.GetAcronymCBERS() == (*itSO)->getParamName()){
//						//found you BABY
//						(*itP)->setValueVariable((*itSO)->getNewValue());
//						(*itSO)->Apply();
//						ofLogVerbose("[APPLYCONFIGURATION]") << " Applied: " << (*itSO)->getNodeName() << " - " << (*itSO)->getParamName();
//					}
//				}
//			}
//		}
//	}
//
//
//	// if leaf returns
//	if(start->nodeList.empty()) return;
//
//	// not leaf, call son nodes;
//
//	for( itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
//		this->applyConfigurationRecursively((*itN));
//}

void SIMModelScript::applyConfiguration(int id){
	
	if(this->currentConfiguration == NULL) {
		ofLogError("[APPLYCONFIGURATION]")  << "No Configuration loaded";
		return;
	}

	ofLogVerbose() << "*****************************************************************************";
	ofLogVerbose("[APPLYCONFIGURATION]")  << "Reading from: " << this->currentConfiguration->name; 

	// call recursive validation to seek in each node the desired parameter to configure
	this->applyConfigurationRecursively(this->myModel->getModelHead());

	ofLogVerbose() << "*****************************************************************************";
}

void SIMModelScript::readScript(string filename){

}

void SIMModelScript::applyScript(){

}

void SIMModelScript::addEvent(string eventName, string v_node, string v_param, double v_value){

}

void SIMModelScript::readScript(){

}