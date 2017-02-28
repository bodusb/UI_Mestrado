///////////////////////////////////////////////////////////
//  SIMParameterProfile.h
//  Implementation of the Class SIMParameterProfile
//  Created on:      08-out-2013 14:43:01
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_1FDF2E57_0902_41a7_8C63_3A892CAE75A0__INCLUDED_)
#define EA_1FDF2E57_0902_41a7_8C63_3A892CAE75A0__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

enum paramType{		ptDATAVALUE, 
					ptOPERATIONALMODE,
					ptOPERATIONALMODEITEM,
					ptTLE, 
					ptWORKINGSTATE, 
					ptWORKINGSTATEITEM,
					ptEXTERNALEVENT,
					ptERROR
};



enum paramDirection{	pdINPUT, 
						pdOUTPUT, 
						pdINTERNAL,
						pdERROR
};

class SIMModelNode;

class SIMParameterProfile
{

public:
	SIMParameterProfile();
	virtual ~SIMParameterProfile();


	paramType GetType();
	void SetType(paramType newVal);
	string GetName();
	void SetName(string newVal);
	string GetInfo();
	void SetInfo(string newVal);
	int GetID();
	void SetID(int newVal);
	paramDirection GetDirection();
	void SetDirection(paramDirection newVal);
	string GetUniqueCode();
	void SetUniqueCode(string newVal);
	string GetAcronym();
	void SetAcronym(string newVal);


	void readProfile(SIMModelNode * modelNode);

private:

	int					ID;
	string				Name;
	string				Acronym;
	string				UniqueCode;
	string				Info;

	paramType			Type;
	paramDirection		Direction;

};
#endif // !defined(EA_1FDF2E57_0902_41a7_8C63_3A892CAE75A0__INCLUDED_)
