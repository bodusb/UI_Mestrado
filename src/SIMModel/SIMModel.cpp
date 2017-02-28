///////////////////////////////////////////////////////////
//  SIMModel.cpp
//  Implementation of the Class SIMModel
//  Created on:      08-out-2013 13:44:27
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMModel.h"

#include "SIMParameterValue.h"
#include "SIMParameterOperationalMode.h"
#include "SIMOperationalModeObject.h"
//#include "SIMParameterExternal.h"



SIMModel::SIMModel(){

	this->correctLoaded = false;
	this->someErrorDetected = false;

	this->simulatingTime = false;

	//this->Environment = new SIMEnvironment();

	this->scriptControl.setMyModel(this);
}

SIMModel::~SIMModel(){

}

void SIMModel::loadModel(string v_filename, SIMModelNode *start){

	SIMModelNode *modelNode = new SIMModelNode();

	if( !modelNode->xml.loadFile(v_filename)) {
		free(modelNode);
		ofLogError("[LOADMODEL]")  << "Error on: " << v_filename; 
		this->someErrorDetected = true;
		return;
	}
	ofLogVerbose() << "*****************************************************************************";
	modelNode->setFather(start);
	if(modelNode->getFather() != NULL) { // if father is a null, means that is the model head (all models have heads)
		ofLogVerbose("[LOADMODEL]") << "Father: " << start->profile.GetName();
		modelNode->getFather()->nodeList.push_back(modelNode);
	} else {
		this->headNode = modelNode;
	}

	ofLogVerbose("[LOADMODEL]") << "Reading: " << v_filename;

	if(modelNode->xml.pushTag("SIMModel")){ // try to PUSH <SIMModel> tag

		// READ PROFILE
		this->readProfile(modelNode);
		ofLogVerbose("[LOADMODEL]") << "Profile teste: "<<modelNode->profile.GetName();

		// READ PARAMETERS
		this->readParameters(modelNode);
		//modelNode->GetMathParser()->ListVar();

		/*double x,y;
		modelNode->GetMathParser()->addVariable("x",&x);
		modelNode->GetMathParser()->addVariable("y",&y);


		modelNode->GetMathParser()->addExpression("x = TD*TD2");
		modelNode->GetMathParser()->addExpression("y = x*2");

		ofLogVerbose() << x << " - " << y;*/

		// revise external parameter links

		// READ RULES
		this->readRuleExpressions(modelNode);
		//modelNode->GetMathParser()->ListExprVar();

		//modelNode->GetMathParser()->evaluateExpressions();

		// READ LINKS
		this->readModelLinks(modelNode);

		ofLogVerbose() << "*****************************************************************************";
		modelNode->xml.popTag();	// POP <SIMModel> tag
	}

	if(this->getModelHead() == modelNode){
		// return to the root, call to resolve extenal links
		//this->validateExternalEvents();


		if( someErrorDetected == false) this->correctLoaded = true;

	}

}

void SIMModel::readProfile(SIMModelNode *n){
	// read profile
	if(n->xml.pushTag("SIMNodeProfile")){ // try to PUSH <profile> tag

		n->profile.SetID(n->xml.getValue("id",0));
		n->profile.SetName(n->xml.getValue("name","Name missing"));
		n->profile.SetAcronym(n->xml.getValue("acronym","Acronym missing"));
		n->profile.SetUniqueCode(n->xml.getValue("acronymCBERS","CBERS Acronym missing"));
		n->profile.SetInfo(n->xml.getValue("Info","NOINFO"));

		string auxType = n->xml.getValue("type","error");

		for(;;){
			if(auxType == "EARTH")			{
				n->profile.SetNodeType(ntEARTH); 
				//n->ModelEnv = new SIMEnvEarth();
				//n->ModelEnv->env = this->getModelEnvironment();
				//this->getModelEnvironment()->Earth = n->ModelEnv;
				//n->ModelEnv->linkEnvToModel(n);
				ofLogVerbose("[SIMNodeProfile]") << n->profile.GetName();
				break;}
			if(auxType == "GROUNDSTATION")	{
				n->profile.SetNodeType(ntGROUNDSTATION); 
				//n->ModelEnv = new SIMEnvGroundStation();
				//n->ModelEnv->env = this->getModelEnvironment();
				//this->getModelEnvironment()->gsList.push_back(n->ModelEnv);
				//n->ModelEnv->linkEnvToModel(n);
				break;}
			if(auxType == "INTERESTPOINT")	{n->profile.SetNodeType(ntINTERESTPOINT); break;}
			if(auxType == "SATELLITE")		{
				n->profile.SetNodeType(ntSATELLITE); 
				//n->ModelEnv = new SIMEnvSatellite();
				//n->ModelEnv->env = this->getModelEnvironment();
				//n->ModelEnv->linkEnvToModel(n);
				//this->getModelEnvironment()->satellite = n->ModelEnv;
				break;}
			if(auxType == "SUBSYSTEM")		{n->profile.SetNodeType(ntSUBSYSTEM); break;}
			if(auxType == "EQUIPMENT")		{n->profile.SetNodeType(ntEQUIPMENT); break;}

			n->profile.SetNodeType(ntERROR);break;
		}
		n->xml.popTag(); 
	}
}

void SIMModel::readParameters(SIMModelNode *n){
	// read parameters
	if(n->xml.pushTag("SIMNodeParameters")){ // try to PUSH <parameters> tag
		int paramCount = n->xml.getNumTags("NodeParameter");
		for(int i=0; i<paramCount; i++){

			string auxPType = n->xml.getAttribute("NodeParameter","type","ERROR",i);
			ofLogVerbose("[PARAMETERLOAD]") << auxPType;

			SIMModelParameter *newParam;

			for(;;){ // set the major parameter type
				if(auxPType == "DATAVALUE") { 
					newParam = new SIMParameterValue(); 
					newParam->profile.SetType(paramType::ptDATAVALUE);
					break;
				}
				if(auxPType == "OPERATIONALMODE") {
					newParam = new SIMParameterOperationalMode(); 
					newParam->profile.SetType(paramType::ptOPERATIONALMODE);
					break;
				}
				if(auxPType == "WORKINGSTATE"){
					newParam = new SIMParameterOperationalMode(); 
					newParam->profile.SetType(paramType::ptWORKINGSTATE);
					break;
				}
				/*if(auxPType == "EXTERNALEVENT"){
					newParam = new SIMParameterExternal();
					newParam->profile.SetType(paramType::ptEXTERNALEVENT);
					break;
				}*/
				break;
			}



			if(n->xml.pushTag("NodeParameter",i)){ // Try to PUSH "NodeParameters

				// call polimorfic loader - he will know what to do! trust in the force
				newParam->loadParameter(n,newParam);
				n->xml.popTag();
			}

			n->paramList.push_back(newParam);
		}
		n->xml.popTag();
	}

	ofLogVerbose("[PARAMETERLOAD]") << "Number of parameter read: "<< n->paramList.size();
}

/**
 * if(n->xml.pushTag("parameter",i)){ // try to PUSH <parameter> two types of
 * paramters - dataValue or operationalMode  if(n->xml.
 * pushTag("operationalMode")){ // try to PUSH <operationalMode> OperationalMode
 * *auxOM = new OperationalMode(); auxOM->setType(paramType::operationalMode);
 * auxOM->set(i+1,n->xml.getValue("name","Missing OM Name"),"", n->xml.
 * getValue("acronymCBERS","Missim CBERS Acronym")); ofLogVerbose() <<
 * "[INTERFACE][LoadModel][OM] Reading: " + auxOM->acronymCBERS; load list of
 * Modes if(n->xml.pushTag("listOfModes")){	// try to PUSH <listOfModes> int
 * modeCount = n->xml.getNumTags("om"); string oms = ""; for(int j=0;j<modeCount;
 * j++){ if(n->xml.pushTag("om",j)){ // Try to PUSH <om> OperationaModeObject *omo
 * = new OperationaModeObject();  omo->set(j+1,n->xml.getValue("name","Missing OM
 * Name"), n->xml.getValue("acronym","Missing acronym"), n->xml.
 * getValue("acronymCBERS","Missing CBERS Acronym"), n->xml.getValue("info",
 * "Missing OM info"));  switch(n->xml.getValue("appearance",0)){ case 0: omo-
 * >colorMode = ofColor::darkBlue; break;		//off case 1: omo->colorMode = ofColor::
 * blue; break;		//standby case 2: omo->colorMode = ofColor::green; break;
 * 		//acting case 3: omo->colorMode = ofColor::red; break;		//alert default:
 * break; } oms = oms + "-" + omo->acronymCBERS; auxOM->omList.push_back(omo);  n-
 * >xml.popTag(); // POP <om> }  } n->xml.popTag(); // POP <listOfModes>
 * ofLogVerbose() << "[INTERFACE][LoadModel][OM] Read:" + oms; } n->paramList.
 * push_back(auxOM); n->xml.popTag(); // POP <operationalMode> } else { if(n->xml.
 * pushTag("value")){ // try to PUSH <value> Value *v = new Value(); v-
 * >setType(paramType::dataValue); v->set(n->xml.getValue("name","missing"), n-
 * >xml.getValue("datavalue",0.0), n->xml.getValue("max",0.0), n->xml.
 * getValue("min",0.0)); v->acronym = n->xml.getValue("acronym","missing"); v-
 * >acronymCBERS =  n->xml.getValue("acronymCBERS","missing"); ofLogVerbose() <<
 * "[INTERFACE][LoadModel][DV] Reading: " + v->name + ":" + ofToString(v->value);
 * n->paramList.push_back(v); n->xml.popTag(); // POP <value> } else { if(n->xml.
 * pushTag("tle")){ // try to PUSH <tle> TLE *tle = new TLE(); tle-
 * >setType(paramType::tle); tle->set(i+1, n->xml.getValue("name","MISSING"), n-
 * >xml.getValue("acronym","Missing acronym"), n->xml.getValue("acronymCBERS",
 * "Missim CBERS Acronym")); tle->filename = n->xml.getValue("fileAddress",
 * "MISSING"); ofLogVerbose() << "[INTERFACE][LoadModel][TLE] Reading: " + tle-
 * >name + ":" + tle->filename; n->paramList.push_back(tle); n->xml.popTag();	//
 * POP <tle> }  }  }  n->xml.popTag();// POP <parameter> } }  n->xml.popTag(); //
 * POP <parameters> } }
 */
void SIMModel::readRuleExpressions(SIMModelNode *n){
	// Read expressions
	if(n->xml.pushTag("SIMNodeExpressions")){ // Try to push the <SIMNodeExpressions> tag
		int expCount = n->xml.getNumTags("Expression");
		for ( int i =0; i < expCount ; i++ ){
			string exp = n->xml.getValue("Expression","ERROR",i);
			//if(exp != "ERROR") n->GetMathParser()->addExpression(exp);
		}
		n->xml.popTag();
	} else {
		ofLogVerbose("[READEXPRESSION]") << "No expression found on this model";
	}
}

void SIMModel::readModelLinks(SIMModelNode *n){
	// Read expressions
	if(n->xml.pushTag("SIMNodeLinks")){
		int linkCount = n->xml.getNumTags("Link");
		for(int i = 0; i < linkCount; i++)
			loadModel(n->xml.getValue("Link","ERROR",i),n);

	} else {
		ofLogVerbose("[READNODELINKS]") << "No lower links on this model";
	}
}

//void  SIMModel::validateExternalEvents(){
//	ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Starting to resolve the external events";
//
//	vector<SIMModelParameter*> toResolve;
//
//	//CREATE A VECTOR OF Parameters to validate
//	this->collectToResolveExternalEvents(this->getModelHead(),&toResolve);
//
//	ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Amount of External Events to Resolve:" << toResolve.size();
//
//	if( toResolve.size() > 0){
//	//Call recursive validation to seek in each node the desired parameters to link
//	this->resolveExternalEvents(this->getModelHead(),&toResolve);
//
//	// add addres of the external variable to this parser.
//	this->linkExternalEventsToParser(this->getModelHead());
//	}
//
//
//}

//void SIMModel::collectToResolveExternalEvents(SIMModelNode *start,vector<SIMModelParameter*> *extList){
//
//
//	ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Into: " << start->profile.GetAcronymCBERS();
//
//	// read and collect external parameters
//	vector<SIMModelParameter*>::iterator itP;
//	for(itP = start->paramList.begin(); itP != start->paramList.end(); itP++){
//
//		if((*itP)->profile.GetType() == paramType::ptEXTERNALEVENT) {
//			extList->push_back((*itP));
//			SIMParameterExternal *auxResolve = (SIMParameterExternal*)(*itP);
//			ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "ToResolve: " << auxResolve->GetParamName() << " from " << auxResolve->GetNodeName();
//		}
//	}
//
//	// leaf returns
//	if( start->nodeList.empty() ) return;
//
//	// not leaf, call son nodes;
//	vector<SIMModelNode*>::iterator itN;
//	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
//		this->collectToResolveExternalEvents((*itN),extList);
//
//}

//void SIMModel::resolveExternalEvents(SIMModelNode *start,vector<SIMModelParameter*> *extList){
//
//	// read and compare toResolve to start parameters
//	vector<SIMModelParameter*>::iterator toResolve,nodeParam;
//	SIMParameterExternal *auxResolve,*auxNParam;
//	ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Into: " << start->profile.GetAcronymCBERS();
//
//
//	for(toResolve = extList->begin(); toResolve != extList->end() ; toResolve++){
//		auxResolve = (SIMParameterExternal*)(*toResolve);
//		if(!auxResolve->IsReady())
//			if (start->profile.GetAcronymCBERS() == auxResolve->GetNodeName()){ // test if its this node
//				ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Found Node";
//				for ( nodeParam = start->paramList.begin(); nodeParam != start->paramList.end(); nodeParam++){
//					if ( (*nodeParam)->profile.GetAcronymCBERS() == auxResolve->GetParamName()){ // test if its this parameter
//						//if yes I FOUND YOU BABY!
//						ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Found Parameter";
//						auxResolve->setExternalEventLink((*nodeParam));
//						auxResolve->SetReady(true);
//						ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Resolving" << auxResolve->GetParamName() << " from " << auxResolve->GetNodeName();
//					}
//				}
//			}
//
//	}
//
//
//
//	// leaf returns
//	if( start->nodeList.empty() ) return;
//
//	// not leaf, call son nodes;
//	vector<SIMModelNode*>::iterator itN;
//	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
//		this->resolveExternalEvents((*itN),extList);
//}

//void SIMModel::linkExternalEventsToParser(SIMModelNode *start){
//
//	ofLogVerbose("[RESOLVEEXTERNALEVENTS]") << "Into: " << start->profile.GetAcronymCBERS();
//
//	// read and collect external parameters
//	vector<SIMModelParameter*>::iterator itP;
//	for(itP = start->paramList.begin(); itP != start->paramList.end(); itP++){
//
//		if((*itP)->profile.GetType() == paramType::ptEXTERNALEVENT) {
//			//start->GetMathParser()->addVariable((*itP)->profile.GetAcronymCBERS(),(*itP)->getValueVariable());
//		}
//	}
//
//	// leaf returns
//	if( start->nodeList.empty() ) return;
//
//	// not leaf, call son nodes;
//	vector<SIMModelNode*>::iterator itN;
//	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
//		this->linkExternalEventsToParser((*itN));
//
//}

//void SIMModel::doEvaluationRound(){
//	
//
//	// verify the current time; 
//	if( this->isSimulatingTime()){
//
//		this->currentSimTimeJD = this->Environment->getProp()->convertYMDtoJ2000(&this->currentSimTimeYMD);
//
//	} else {
//		// using computer time
//
//		currentSimTimeYMD.year = ofGetYear();
//		currentSimTimeYMD.mon = ofGetMonth();
//		currentSimTimeYMD.day = ofGetDay();
//		currentSimTimeYMD.hr = ofGetHours() + this->timezone;
//		currentSimTimeYMD.minute = ofGetMinutes();
//		currentSimTimeYMD.sec = ofGetSeconds();
//
//		this->currentSimTimeJD = this->Environment->getProp()->convertYMDtoJ2000(&this->currentSimTimeYMD);
//		
//		//jday( ofGetYear(),ofGetMonth(),ofGetDay(),ofGetHours() + this->timezone,ofGetMinutes(),ofGetSeconds(), this->currentSimTimeJD);	//YMD -> JD
//		//this->currentMFE = ( this->currentJ2000 - satrec.jdsatepoch)*1440.0; // JD -> MFE
//
//
//	}
//
//	ofLogVerbose("[EVALUATIONROUND]") << "*************** STARTING: " << this->currentSimTimeJD;
//
//	// evolve environment
//	Environment->doEvaluationRound(this->currentSimTimeJD);
//
//	// evolve model
//	if( !this->isModelCorrectLoaded() ) {
//		ofLogVerbose("[EVALUATIONROUND]") << "Can´t evaluate, model is incorrect";
//		return;
//	} else {
//		this->headNode->doEvaluationRound(this->currentSimTimeJD);
//	}
//	//doModelEvaluationRound(headNode,this->currentSimTimeJD);
//
//}
//
//void SIMModel::doModelEvaluationRound(SIMModelNode *start, double currentJD){
//
//	if( !this->isModelCorrectLoaded() ) {
//		ofLogVerbose("[EVALUATIONROUND]") << "Can´t evaluate, model is incorrect";
//		return;
//	}
//	
//
//	if ( start == NULL ) { // first evaluation round; (only the first-time)
//		start = headNode;
//	}
//
//	// leaf returns
//	if ( start->nodeList.empty() ) {
//		ofLogVerbose("[EVALUATIONROUND]") << "leaf" << start->profile.GetAcronymCBERS();
//		//start->GetMathParser()->evaluateExpressions();
//		return;
//	}
//
//	// not leaf, call son nodes;
//	vector<SIMModelNode*>::iterator itN;
//	for( itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++ ){
//		// the evaluation does 2 round calculations, it calculates from root->leaf, than from leaf->root
//		ofLogVerbose("[EVALUATIONROUND]") << "down" << start->profile.GetAcronymCBERS();
//	//	start->GetMathParser()->evaluateExpressions();
//		this->doModelEvaluationRound((*itN),currentJD);
//		ofLogVerbose("[EVALUATIONROUND]") << "up" << start->profile.GetAcronymCBERS();
//		//start->GetMathParser()->evaluateExpressions();
//	}
//
//
//
//}

//void SIMModel::setCurrentYMD(YMD newVal){
//
//	currentSimTimeYMD.year = newVal.year;
//	currentSimTimeYMD.mon = newVal.mon;
//	currentSimTimeYMD.day = newVal.day;
//	currentSimTimeYMD.hr = newVal.hr;
//	currentSimTimeYMD.minute = newVal.minute;
//	currentSimTimeYMD.sec = newVal.sec;
//
//	this->currentSimTimeJD = this->Environment->getProp()->convertYMDtoJ2000(&this->currentSimTimeYMD);
//
//}

void SIMModel::changeParameterValue(string nodeName, string paramName, double newValue){

}

void SIMModel::changeParameterValue(SIMModelParameter * param, double newValue){

}


double SIMModel::requestParameterValue(string nodeName, string paramName){

	return 0;
}


double SIMModel::requestParameterValue(SIMModelParameter * v_param){

	return 0;
}


SIMModelParameter * SIMModel::requestParameter(string nodeName, string paramName){

	return  NULL;
}