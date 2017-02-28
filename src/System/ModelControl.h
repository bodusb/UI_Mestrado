///////////////////////////////////////////////////////////
//  ModelControl.h
//  Implementation of the Class ModelControl
//  Created on:      06-set-2013 14:20:06
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_795130AE_3962_49f5_AF5F_1BCFBADE2C21__INCLUDED_)
#define EA_795130AE_3962_49f5_AF5F_1BCFBADE2C21__INCLUDED_

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "..\SIMModel\SIMModelNode.h"
#include "..\SIMModel\ModelSimCom.h"

enum simStatus{
	ssCONNECTED,
	ssDISCONNECTED,
	ssERROR,
	ssLOSTCONNECTION
};


//class NodeA;
class iAction;

class ModelControl
{

public:

	// LOAD MODEL
	void				loadModel(string v_filename,SIMModelNode *start);
	SIMModelNode		*getModelHead(){return this->headNode;};
	bool				isModelCorrectLoaded() { return this->correctLoaded;};


	SIMModelNode *model;

	SIMModelNode *actualHead;

	ModelControl();
	virtual ~ModelControl();

	void calculateRadius3D(SIMModelNode * start);
	void calculatePositions(SIMModelNode * start);
	void updateRDT(SIMModelNode *start);
	
	iAction *myAction;

	//void loadModel(string filename);

	//NodeA* loadEarth(string filename);
	//NodeA* loadGroundStation(string filename);
	//NodeA* loadSatellite(string filename);
	//NodeA* loadSubsystem(string filename);
	//NodeA* loadEquipment(string filename);

	//void resetHead() { actualHead = model;}

	SIMModelNode* getNode(string v_uniqueCode);
	///

	// control functions

	// set/get time
		//bool				isSimulatingTime() { return this->simulatingTime;};
		//void				setToSimulateTime(bool v_sim) {this->simulatingTime = v_sim; };

		//double				getCurrentJD() { return this->currentSimTimeJD;};
		//void				setCurrentJD(double newVal) { this->currentSimTimeJD = newVal;};
		////YMD					getCurrentYMD() {return this->currentSimTimeYMD;};
		////void				setCurrentYMD(YMD newVal);
		//void				setTimezone(int value){this->timezone = value; this->Environment->getProp()->setTimezone(0);};
		//int					getTimezone() {return this->timezone;};
	// set/get parameter
		// set parameter change
		//void				changeParameterValue(string nodeName, string paramName, double newValue);
		//void				changeParameterValue(SIMModelParameter * param, double newValue);

		//// request parameter value
		//double				requestParameterValue(string nodeName, string paramName);
		//double				requestParameterValue(SIMModelParameter * v_param);
		//SIMModelParameter	*requestParameter(string nodeName, string paramName);
	// set/get future change



	string test;
	ModelSimCom* simLink;
	
	simStatus getSimulatorStatus() { return simulatorStatus;};
	void setSimulatorStatus(simStatus value) {this->simulatorStatus = value; } ;

	void updateFromSim();
	

private:

	// MODEL DATA STRUCTURE
		SIMModelNode		*headNode;
		bool				correctLoaded;
		bool				someErrorDetected;

		void				readProfile(SIMModelNode *v_modelNode); // READ PROFILE
		void				readParameters(SIMModelNode *v_modelNode); // READ PARAMETERS
		void				readRuleExpressions(SIMModelNode *v_modelNode); // READ RULES
		void				readModelLinks(SIMModelNode *v_modelNode); // READ LINKS
		void				read3DModel(SIMModelNode *n);

		SIMModelNode* findNode(SIMModelNode* start, string v_uniqueCode);
		SIMModelNode* findNode(SIMModelNode* start,SIMModelNode* desired);

		//void readProfile(NodeA *n);
		//void readread3DModelModel(NodeA *n);
		//void readParameter(NodeA *n);


		simStatus simulatorStatus;
};
#endif // !defined(EA_795130AE_3962_49f5_AF5F_1BCFBADE2C21__INCLUDED_)
