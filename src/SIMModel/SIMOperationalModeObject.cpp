///////////////////////////////////////////////////////////
//  SIMOperationalModeObject.cpp
//  Implementation of the Class SIMOperationalModeObject
//  Created on:      08-out-2013 15:45:19
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMOperationalModeObject.h"

#include "SIMModelNode.h"

SIMOperationalModeObject::SIMOperationalModeObject(){

}



SIMOperationalModeObject::~SIMOperationalModeObject(){

}


void SIMOperationalModeObject::loadParameter(SIMModelNode *n,SIMModelParameter *param){
	// enters with the xml pointing inside the parameter

	this->profile.readProfile(n);
	this->SetActive(false);

	string appType = n->xml.getValue("Appearance","ERROR");
	ofLogVerbose("[OPERATIONALMODE]") << "Appearance: " <<  appType;

	for(;;){
		if(appType == "OFF")		{this->SetAppearance(appearType::aptOFF); break;}
		if(appType == "STANDBY")	{this->SetAppearance(appearType::aptSTANDBY); break;}
		if(appType == "FUNCTIONAL") {this->SetAppearance(appearType::aptFUNCTIONAL); break;}
		if(appType == "FAILURE")	{this->SetAppearance(appearType::aptFAILURE); break;}
		if(appType == "OVERHEATED") {this->SetAppearance(appearType::aptOVERHEATED); break;}
		if(appType == "OVERCOOLED") {this->SetAppearance(appearType::aptOVERCOOLED); break;}
		this->SetAppearance(appearType::aptERROR); break;
	}

}


bool SIMOperationalModeObject::IsActive(){

	return Active;
}


void SIMOperationalModeObject::SetActive(bool newVal){

	Active = newVal;
}


appearType SIMOperationalModeObject::GetAppearance(){

	return Appearance;
}


void SIMOperationalModeObject::SetAppearance(appearType newVal){

	Appearance = newVal;
}