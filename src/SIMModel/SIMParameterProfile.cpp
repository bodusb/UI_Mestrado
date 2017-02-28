///////////////////////////////////////////////////////////
//  SIMParameterProfile.cpp
//  Implementation of the Class SIMParameterProfile
//  Created on:      08-out-2013 14:43:01
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMParameterProfile.h"

#include "SIMModelNode.h"


SIMParameterProfile::SIMParameterProfile(){

}



SIMParameterProfile::~SIMParameterProfile(){

}


paramType SIMParameterProfile::GetType(){

	return Type;
}


void SIMParameterProfile::SetType(paramType newVal){

	Type = newVal;
}


string SIMParameterProfile::GetName(){

	return Name;
}


void SIMParameterProfile::SetName(string newVal){

	Name = newVal;
}


string SIMParameterProfile::GetInfo(){

	return Info;
}


void SIMParameterProfile::SetInfo(string newVal){

	Info = newVal;
}


int SIMParameterProfile::GetID(){

	return ID;
}


void SIMParameterProfile::SetID(int newVal){

	ID = newVal;
}


paramDirection SIMParameterProfile::GetDirection(){

	return Direction;
}


void SIMParameterProfile::SetDirection(paramDirection newVal){

	Direction = newVal;
}


string SIMParameterProfile::GetUniqueCode(){

	return UniqueCode;
}


void SIMParameterProfile::SetUniqueCode(string newVal){

	UniqueCode = newVal;
}


string SIMParameterProfile::GetAcronym(){

	return Acronym;
}


void SIMParameterProfile::SetAcronym(string newVal){

	Acronym = newVal;
}

void SIMParameterProfile::readProfile(SIMModelNode * n){

	if(n->xml.pushTag("ParameterProfile")){ // try to PUSH <ParameterProfile> tag

		this->SetID(n->xml.getValue("ID",0));
		this->SetName(n->xml.getValue("Name","ERROR"));
		this->SetAcronym(n->xml.getValue("Acronym","ERROR"));
		this->SetUniqueCode(n->xml.getValue("uniqueCode","ERROR"));
		this->SetInfo(n->xml.getValue("Info","NOINFO"));

		ofLogVerbose("[PARAMETERPROFILE]") << "Name: " << this->GetName();

	/*	string direction = n->xml.getValue("Direction","ERROR");
		for(;;){
			if(direction == "INPUT")				this->SetDirection(paramDirection::pdINPUT);break;
			if(direction == "OUTPUT")				this->SetDirection(paramDirection::pdOUTPUT);break;
			if(direction == "INTERNAL")				this->SetDirection(paramDirection::pdINTERNAL);break;
			this->SetDirection(paramDirection::pdERROR);break;
		}
		ofLogVerbose("[PARAMETERPROFILE]") << "Direction: " << direction;*/

		n->xml.popTag(); // pop <ParameterProfile> tag
	}



}