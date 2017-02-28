///////////////////////////////////////////////////////////
//  SIMModelScript.h
//  Implementation of the Class SIMModelScript
//  Created on:      15-out-2013 11:04:20
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_816BF699_641D_4ab4_A0A0_94AFCBF11856__INCLUDED_)
#define EA_816BF699_641D_4ab4_A0A0_94AFCBF11856__INCLUDED_

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "SIMScriptObject.h"


typedef struct simScript{
	string name;
	int id;
	double startingJDTime;
	vector<SIMScriptObject *> objectList;
}simScript;


class SIMModel;
class SIMModelNode;

class SIMModelScript
{

public:	
	
	simScript *currentConfiguration;
	vector<simScript*> scriptList;

	SIMModelScript();
	virtual ~SIMModelScript();
	void readConfiguration(string filename);
	//void applyConfiguration(int id);
	void readScript(string filename);
	void applyScript();
	void addEvent(string eventName, string v_node, string v_param, double v_value);
	void readScript();


	void setMyModel(SIMModel *v_model) { this->myModel = v_model;};

private:

	ofxXmlSettings auxXML;

	bool	configurationError;

	SIMModel *myModel;

	//void SIMModelScript::applyConfigurationRecursively(SIMModelNode *start);


};
#endif // !defined(EA_816BF699_641D_4ab4_A0A0_94AFCBF11856__INCLUDED_)
