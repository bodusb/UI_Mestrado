///////////////////////////////////////////////////////////
//  SIMModel.h
//  Implementation of the Class SIMModel
//  Created on:      08-out-2013 13:44:27
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_55B2DBE0_B719_435a_9982_7798DC188371__INCLUDED_)
#define EA_55B2DBE0_B719_435a_9982_7798DC188371__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
//#include "ofxSpacetrack.h"

#include "SIMModelNode.h"
//#include "SIMEnvironment.h"
#include "SIMModelScript.h"

class SIMParameterExternal;

class SIMModel{

public:
	
	SIMModel();
	~SIMModel();

	void				loadModel(string v_filename,SIMModelNode *start);
	void				doEvaluationRound();

	SIMModelNode		*getModelHead(){return this->headNode;};
	bool				isModelCorrectLoaded() { return this->correctLoaded;};
	//SIMEnvironment		*getModelEnvironment() { return this->Environment;}

	//Setup simulation time (realTime, simulatedTime)
	bool				isSimulatingTime() { return this->simulatingTime;};
	void				setToSimulateTime(bool v_sim) {this->simulatingTime = v_sim; };

	double				getCurrentJD() { return this->currentSimTimeJD;};
	void				setCurrentJD(double newVal) { this->currentSimTimeJD = newVal;};
	//YMD					getCurrentYMD() {return this->currentSimTimeYMD;};
	//void				setCurrentYMD(YMD newVal);
//	void				setTimezone(int value){this->timezone = value; this->Environment->getProp()->setTimezone(0);};
	int					getTimezone() {return this->timezone;};

	// set parameter change
	void				changeParameterValue(string nodeName, string paramName, double newValue);
	void				changeParameterValue(SIMModelParameter * param, double newValue);

	// request parameter value
	double				requestParameterValue(string nodeName, string paramName);
	double				requestParameterValue(SIMModelParameter * v_param);
	SIMModelParameter	*requestParameter(string nodeName, string paramName);

	SIMModelScript		scriptControl;
	

private:
	SIMModelNode		*headNode;
//	SIMEnvironment		*Environment;
	bool				correctLoaded;
	bool				someErrorDetected;



	bool				simulatingTime;
	int					timezone;
	//YMD					currentSimTimeYMD;
	double				currentSimTimeJD;

	void				readProfile(SIMModelNode *v_modelNode); // READ PROFILE
	void				readParameters(SIMModelNode *v_modelNode); // READ PARAMETERS
	void				readRuleExpressions(SIMModelNode *v_modelNode); // READ RULES
	void				readModelLinks(SIMModelNode *v_modelNode); // READ LINKS

	//void				validateExternalEvents(); //validate external event parameters

	//void				collectToResolveExternalEvents(SIMModelNode *start,vector<SIMModelParameter*> *extList);
	//void				resolveExternalEvents(SIMModelNode *start,vector<SIMModelParameter*> *extList);
	//void				linkExternalEventsToParser(SIMModelNode *start);

	//void				doModelEvaluationRound(SIMModelNode *start, double currentJD); // do the model update

};
#endif // !defined(EA_55B2DBE0_B719_435a_9982_7798DC188371__INCLUDED_)
