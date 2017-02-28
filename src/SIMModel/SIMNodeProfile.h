///////////////////////////////////////////////////////////
//  SIMNodeProfile.h
//  Implementation of the Class SIMNodeProfile
//  Created on:      08-out-2013 13:42:22
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_B8D73C88_8A8F_4691_B1EA_C8047D25B0AC__INCLUDED_)
#define EA_B8D73C88_8A8F_4691_B1EA_C8047D25B0AC__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

enum nodeType{	ntEARTH,
				ntGROUNDSTATION,
				ntINTERESTPOINT,
				ntSATELLITE,
				ntSUBSYSTEM,
				ntEQUIPMENT,
				ntERROR,
				ntRDT
};


class SIMModelNode;

class SIMNodeProfile
{

public:
	SIMNodeProfile();
	virtual ~SIMNodeProfile();

	void set(int i,string v_name,string v_acro,string v_acroCBERS);
	int GetID();
	void SetID(int newVal);
	string GetName();
	void SetName(string newVal);
	string GetAcronym();
	void SetAcronym(string newVal);
	string GetUniqueCode();
	void SetUniqueCode(string newVal);
	string GetInfo() { return this->Info;};
	void SetInfo(string newVal) { this->Info = newVal;};
	string GetFilename();
	void SetFilename(string newVal);
	nodeType GetNodeType() {return this->NodeType;};
	void SetNodeType(nodeType newVal) { this->NodeType = newVal;};	
	

private:

	int ID;
	string Name;
	string Acronym;
	string UniqueCode;
	string Info;
	string Filename;
	nodeType NodeType;
	
};
#endif // !defined(EA_B8D73C88_8A8F_4691_B1EA_C8047D25B0AC__INCLUDED_)
