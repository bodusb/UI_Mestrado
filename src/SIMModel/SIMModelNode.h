///////////////////////////////////////////////////////////
//  SIMModelNode.h
//  Implementation of the Class SIMModelNode
//  Created on:      08-out-2013 13:42:24
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_08376B93_1DA3_498a_B8AA_6E633A8A3330__INCLUDED_)
#define EA_08376B93_1DA3_498a_B8AA_6E633A8A3330__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#include "SIMNodeProfile.h"
#include "SIMModelParameter.h"
//#include "SIMEnvironment.h"
#include "SIMParameterOperationalMode.h"

#include "Node3D.h"
#include "NodeGUI.h"
#include "NodePositions.h"
#include "NodeRDT.h"

class SIMModelNode
{
public:
	SIMModelNode();
	virtual ~SIMModelNode();


	
	SIMNodeProfile profile;
	vector<SIMModelParameter*> paramList;
	vector<SIMModelNode*> nodeList;
	vector<string> expressionList;
	
	ofxXmlSettings xml;

	//SIMEnvObject *ModelEnv;

	void setFather(SIMModelNode *v_father) { this->Father = v_father;};
	SIMModelNode *getFather() { return this->Father;};

	//void doEvaluationRound(double currentJD);
	NodePositions *myEarthPosition;
	NodeRDT		*nodeRDT;			// rdt info
	Node3D		*model3D;			// 3d models
	NodeGUI		*nodeGUI;			// information panel

	SIMModelParameter* getParam(string value);
	SIMParameterOperationalMode* getOM();

	SIMModelNode* getNode(string v_uniqueCode);
	SIMModelNode* findNode(SIMModelNode* start,string v_uniqueCode);
	SIMModelNode* findNode(SIMModelNode* start,SIMModelNode* desired);
private:
	SIMModelNode *Father;


};

#endif // !defined(EA_08376B93_1DA3_498a_B8AA_6E633A8A3330__INCLUDED_)
