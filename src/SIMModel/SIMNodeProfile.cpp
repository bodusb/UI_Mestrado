///////////////////////////////////////////////////////////
//  SIMNodeProfile.cpp
//  Implementation of the Class SIMNodeProfile
//  Created on:      08-out-2013 13:42:22
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMNodeProfile.h"

#include "SIMModelNode.h"


SIMNodeProfile::SIMNodeProfile(){

}



SIMNodeProfile::~SIMNodeProfile(){

}



int SIMNodeProfile::GetID(){

	return ID;
}


void SIMNodeProfile::SetID(int newVal){

	ID = newVal;
}


string SIMNodeProfile::GetName(){

	return Name;
}


void SIMNodeProfile::SetName(string newVal){

	Name = newVal;
}


string SIMNodeProfile::GetAcronym(){

	return Acronym;
}


void SIMNodeProfile::SetAcronym(string newVal){

	Acronym = newVal;
}


string SIMNodeProfile::GetUniqueCode(){

	return UniqueCode;
}


void SIMNodeProfile::SetUniqueCode(string newVal){

	UniqueCode = newVal;
}


string SIMNodeProfile::GetFilename(){

	return Filename;
}


void SIMNodeProfile::SetFilename(string newVal){

	Filename = newVal;
}


