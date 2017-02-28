///////////////////////////////////////////////////////////
//  ModelControl.cpp
//  Implementation of the Class ModelControl
//  Created on:      06-set-2013 14:20:06
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ModelControl.h"

#include "..\SIMModel\SIMModelParameter.h"
#include "..\SIMModel\SIMParameterValue.h"
#include "..\SIMModel\SIMParameterOperationalMode.h"
#include "..\SIMModel\SIMOperationalModeObject.h"

#include "..\SIMModel\COMInterface.h"




//#include "NodeA.h"
//#include "NodeInfo.h"
//
//#include "nParam.h"
//#include "OperationalMode.h"
//#include "OperationaModeObject.h"
//#include "TLE.h"
//#include "Value.h"
//
//#include "Node3D.h"
//#include "NodeRDT.h"
//#include "NodePositions.h"
//#include "NodeGUI.h"
//
//
ModelControl::ModelControl(){


	//load model
	this->loadModel("model/earth.xml",NULL);

	ofLogVerbose("[LOADMODEL]") << " -------------> ACTUAL HEAD:" << this->actualHead->profile.GetAcronym();
	
	//Calculate RDT
	this->calculateRadius3D(this->model);
	this->calculatePositions(this->model);

	simulatorStatus = simStatus::ssDISCONNECTED;

	test = "modelController";

	this->simLink = new COMInterface();
	simLink->myModel = this;
}

ModelControl::~ModelControl(){

}
//
void ModelControl::calculateRadius3D(SIMModelNode *start){

	if(!start->nodeRDT->isOpen()) return;
	
	if( start->nodeList.empty()){
		start->nodeRDT->setOutRad(20);
		start->nodeRDT->setRad( 0 );
		return;
	}
	
	vector<SIMModelNode*>::iterator itNode;

	double inner_sum = 0;
	double max_child_radius = 0;

	for(itNode = start->nodeList.begin(); itNode != start->nodeList.end(); itNode++){
		this->calculateRadius3D((*itNode));
		inner_sum += (*itNode)->nodeRDT->getOutRad();
		if( max_child_radius < (*itNode)->nodeRDT->getOutRad()) max_child_radius = (*itNode)->nodeRDT->getOutRad();
	}
	inner_sum *= 2;

	/*cout<<endl<<"Inner Sum:"<<inner_sum<<" - and max child radius:"<<max_child_radius;*/
	if(inner_sum < 2*PI*max_child_radius){
		start->nodeRDT->setRad(max_child_radius);
		//cout<<" -- using:"<<no->rad<<" - MAX";
	} else {
		start->nodeRDT->setRad(inner_sum/(2*PI));
		//cout<<" -- using:"<<no->rad<<" - INN";
	}

	start->nodeRDT->setOutRad(start->nodeRDT->getRad() + max_child_radius);

	//cout<<endl<<" -rad:"<<no->rad<<" -out_rad:"<<no->out_rad;

}

void ModelControl::calculatePositions(SIMModelNode *start){
	
	//	cout<<endl<<"Node:"<<no->id<<"ofPoint:"<<no->place<<" - size:"<<no->children.size();
	if(!start->nodeRDT->isOpen()) return;

	if( start->nodeList.empty()) return;
	int i = 0;
	vector<SIMModelNode*>::iterator itNode,aux;
	float angle = 0;
	float earlier_rad = 0;
	for(itNode = start->nodeList.begin(); itNode != start->nodeList.end(); itNode++){
		//(*itNode)->place = no->place + ofPoint(no->rad*cos(i*(2*PI/no->children.size())),no->rad*sin(i*(2*PI/no->children.size())),10);

		angle +=  (*itNode)->nodeRDT->getOutRad() /start->nodeRDT->getRad() + earlier_rad;	

		(*itNode)->nodeRDT->setPlace( start->nodeRDT->getPlace() + ofPoint(start->nodeRDT->getRad()*cos(angle),start->nodeRDT->getRad()*sin(angle),50) );

		earlier_rad =  (*itNode)->nodeRDT->getOutRad() /start->nodeRDT->getRad() ;		

		//
		//		earlier_rad = (*itNode)->out_rad/no->rad;

		/*	angle += atan((*itNode)->out_rad/no->rad);
		aux = itNode++;
		if((*aux) != NULL ) angle += atan((*aux)->out_rad/no->rad); */

		i++;
		this->calculatePositions((*itNode));
	}



}

void ModelControl::updateRDT(SIMModelNode *start){

	this->actualHead = this->findNode(model,start);
	if(actualHead == NULL) {
		actualHead = model;
	}

	calculateRadius3D(actualHead);
	calculatePositions(actualHead);
}


//
//void ModelControl::loadModel(string filename){
//	// Change to a single entrance name
//
//	//load earth - and gs chain
//	this->model = this->loadEarth("earth/earth.xml");
//
//	ofLogVerbose() <<" END OF EARTH LOAD";
//	//ofSystemAlertDialog("Setup earth");
//
//	ofLogVerbose() <<" START OF SAT LOAD";
//	// load satellite chain
//	this->model->nodeList.push_back(this->loadSatellite("rb/cbers.XML"));
//	ofLogVerbose() <<" END OF SAT LOAD";
//
//	this->actualHead = this->model;
//}
//
//NodeA* ModelControl::loadEarth(string filename){
//
//	NodeA* earth = new NodeA;
//	earth->nodeRDT = new NodeRDT();
//
//
//	if( earth->xml.loadFile(filename)){ // try to open file
//		ofLogVerbose() <<"--------------------Earth--------------------------------------";
//		ofLogVerbose() << "Reading: "<<filename;
//
//		//ofSystemAlertDialog("Opened file");
//
//		if(earth->xml.pushTag("earth")){ // try to PUSH <satellite> tag
//
//			// read profile
//			this->readProfile(earth);
//			earth->info->setType(objectTypes::earth);
//
//			ofLogVerbose() << earth->info->name;
//
//
//			// read sim link
//
//			// read model
//			this->readModel(earth);
//
//			// read parameters
//			this->readParameter(earth);
//			ofLogVerbose() << "[INTERFACE][LoadModel] N of parameters:" + ofToString(earth->paramList.size());			
//			
//			// read subsystems
//			if(earth->xml.pushTag("groundstations")){	// Try to Push <groundstations>
//				int ssCount = earth->xml.getNumTags("groundstation");
//				ofLogVerbose() <<"[INTERFACE][LoadModel] Reading groundstation links";
//				for(int i = 0; i< ssCount ; i++){	// Try to PUSH <groundstation>
//
//					if(earth->xml.pushTag("groundstation",i)){
//						string f = earth->xml.getValue("configFileAddress","Missing");
//						if(f != "missing"){
//							NodeA *auxGS = this->loadGroundStation(f);
//							auxGS->nodeFather = earth;
//							earth->nodeList.push_back(auxGS);
//						}
//						earth->xml.popTag(); // POP <groundstation>
//					}
//				} // enf of for to load subsystems
//				
//				
//				earth->xml.popTag(); // POP <groundstations>
//			}
//
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of Ground stations:" + ofToString(earth->nodeList.size());	
//
//			earth->xml.popTag(); // POP <earth>
//
//		}
//	}
//	//ofLogVerbose() <<"******************** end of:"<<earth->info->acronym;
//
//
//
//
//	return earth;
//}
//
//NodeA* ModelControl::loadGroundStation(string filename){
//
//	NodeA* gs = new NodeA;
//	gs->nodeRDT = new NodeRDT();
//	gs->myEarthPosition = new NodePositions();
//	gs->myEarthPosition->myNode = gs;
//
//	if( gs->xml.loadFile(filename)){ // try to open file
//		ofLogVerbose() << "--------------------GroundStation--------------------------------------";
//		ofLogVerbose() << "Reading: "<<filename;
//
//		//ofSystemAlertDialog("Opened file");
//
//		if(gs->xml.pushTag("groundstation")){ // try to PUSH <groundstation> tag
//
//			// read profile
//			this->readProfile(gs);
//			gs->info->setType(objectTypes::groundStation);
//			ofLogVerbose() << gs->info->name;
//
//
//			//// read sim link
//			//// read model
//
//			// read parameters
//			this->readParameter(gs);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of parameters:" + ofToString(gs->paramList.size());					
//			
//			
//
//			gs->xml.popTag(); // POP <groundstation>
//
//		}
//
//
//		gs->myEarthPosition->updatePosition();
//	}
//
//	
//
//	return gs;
//}
//
//NodeA* ModelControl::loadSatellite(string filename){
//	
//	NodeA *sat = new NodeA();
//	sat->nodeRDT = new NodeRDT();
//	sat->myEarthPosition = new NodePositions();
//	sat->myEarthPosition->myNode = sat;
//
//	if( sat->xml.loadFile(filename)){ // try to open file
//		ofLogVerbose() << "[INTERFACE][LoadModel] --------------------Satellite--------------------------------------";
//		ofLogVerbose() << "[INTERFACE][LoadModel] Reading: "<<filename;
//
//		//ofSystemAlertDialog("Opened file");
//
//		if(sat->xml.pushTag("satellite")){ // try to PUSH <satellite> tag
//
//			// read profile
//			this->readProfile(sat);
//			sat->info->setType(objectTypes::satellite);
//			ofLogVerbose() << "[INTERFACE][LoadModel] confirming: "<<sat->info->name;
//
//
//			// read sim link
//			// read model
//			this->readModel(sat);
//			
//
//			// read parameters
//			this->readParameter(sat);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of parameters:" + ofToString(sat->paramList.size());			
//			
//			// read subsystems
//			if(sat->xml.pushTag("subsystems")){	// Try to Push <subsystems>
//				int ssCount = sat->xml.getNumTags("subsystem");
//				ofLogVerbose() << "[INTERFACE][LoadModel] Reading subsystems links"<<sat->xml.getPushLevel();
//				for(int i = 0; i< ssCount ; i++){	// Try to PUSH <subsystem>
//					if(sat->xml.pushTag("subsystem",i)){
//						string f = sat->xml.getValue("configFileAddress","Missing");
//						if(f != "missing"){
//							NodeA *auxSS = this->loadSubsystem(f);
//							auxSS->nodeFather = sat;
//							sat->nodeList.push_back(auxSS);
//						}
//						sat->xml.popTag(); // POP <subsystem>
//					}
//				} // enf of for to load subsystems
//				
//				
//				sat->xml.popTag(); // POP <subsystems>
//			}
//
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of SS:" + ofToString(sat->nodeList.size());	
//
//			sat->xml.popTag(); // POP <satellite>
//
//		}
//		sat->myEarthPosition->updatePosition();
//	}
//	ofLogVerbose() << "[INTERFACE][LoadModel] ******************** end of:"<<sat->info->acronym;
//
//	
//
//	return sat;
//}
//
//NodeA* ModelControl::loadSubsystem(string filename){
//
//	NodeA *ss = new NodeA();
//	ss->nodeRDT = new NodeRDT();
//
//	//ofSystemAlertDialog("Opened file" + this->configFileAddress);
//	if( ss->xml.loadFile(filename)){ // try to open file
//		ofLogVerbose() << "[INTERFACE][LoadModel] --------------------SubSystem--------------------------------------";
//		ofLogVerbose() << "[INTERFACE][LoadModel] Reading:" + filename;
//
//		
//
//		if(ss->xml.pushTag("subsystem")){ // try to PUSH <subsystem> tag
//
//			// read profile
//			this->readProfile(ss);
//			ss->info->setType(objectTypes::subsystem);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Confirming: " + ss->info->name;
//
//			// read parameters
//			this->readParameter(ss);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of parameters:" + ofToString(ss->paramList.size());					
//			
//			// read equipments
//			if(ss->xml.pushTag("equipments")){	// Try to Push <equipments>
//				int ssCount = ss->xml.getNumTags("equipment");
//				ofLogVerbose() << "[INTERFACE][LoadModel] Reading equipments links"<<"PL:"<<ss->xml.getPushLevel();;
//				for(int i = 0; i< ssCount; i++){	// Try to PUSH <equipment>
//					if(ss->xml.pushTag("equipment",i)){
//						NodeA *auxEQ = this->loadEquipment(ss->xml.getValue("configFileAddress","Missing"));
//
//						auxEQ->nodeFather = ss;
//						ss->nodeList.push_back(auxEQ);
//						ss->xml.popTag(); // POP <equipment>
//					}
//				} // enf of for to load subsystems
//				
//				
//				ss->xml.popTag(); // POP <equipments>
//			}
//
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of equipments:" + ofToString(ss->nodeList.size());	
//
//			ss->xml.popTag(); // POP <subsystem>
//
//		}
//	}
//	//ofSystemAlertDialog("Loaded" + this->acronym);
//	//ofLogVerbose() << "[INTERFACE][LoadModel] ******************** end of:"<<ss->info->acronym;
//
//	return ss;
//}
//
//NodeA* ModelControl::loadEquipment(string filename){
//
//	NodeA *eq = new NodeA();
//	eq->nodeRDT = new NodeRDT();
//
//
//	//ofSystemAlertDialog("Opened file" + this->configFileAddress);
//	if( eq->xml.loadFile(filename)){ // try to open file
//		ofLogVerbose() << "[INTERFACE][LoadModel] --------------------Equipment--------------------------------------";
//		ofLogVerbose() << "[INTERFACE][LoadModel] Reading" + filename;
//
//		if(eq->xml.pushTag("equipment")){ // try to PUSH <equipment> tag
//
//			// read profile
//			this->readProfile(eq);
//			eq->info->setType(objectTypes::equipment);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Confirming:" + eq->info->name;
//
//
//			// read model
//			this->readModel(eq);
//
//
//			// read parameters
//			this->readParameter(eq);
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of parameters:" + ofToString(eq->paramList.size());	
//
//
//			// read components
//			if(eq->xml.pushTag("components")){	// Try to Push <components>
//				int eqCount = eq->xml.getNumTags("subsystem");
//				
//				for(int i = 0; i< eqCount; i++){	// Try to PUSH <component>
//					if(eq->xml.pushTag("component",i)){
//
//						eq->xml.popTag(); // POP <component>
//					}
//				} // enf of for to load subsystems
//				
//				
//				eq->xml.popTag(); // POP <components>
//			}
//
//			ofLogVerbose() << "[INTERFACE][LoadModel] Number of components:" + ofToString(eq->nodeList.size());	
//
//			eq->xml.popTag(); // POP <equipment>
//		}
//	}
//	//ofLogVerbose() << "[INTERFACE][LoadModel] ********************";
//	return eq;
//
//}
//



SIMModelNode* ModelControl::getNode(string v_uniqueCode){
	return findNode(this->model,v_uniqueCode);;
}

SIMModelNode* ModelControl::findNode(SIMModelNode* start,string v_uniqueCode){
	
//	if(start->info != NULL) {
		//ofLogVerbose() << start->info->acronymCBERS << " - " << v_acronymCBERS;
	if(start->profile.GetUniqueCode() == v_uniqueCode) {
			//ofLogVerbose() << "found and returning:"<<start->info->acronymCBERS;
			return start;}
//	}
	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++){
		SIMModelNode* aux = this->findNode((*itN),v_uniqueCode);
		if (aux !=NULL) return aux;
	}

	return NULL;
}

SIMModelNode* ModelControl::findNode(SIMModelNode* start,SIMModelNode* desired){

	if(start == desired) return start;

	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
		this->findNode((*itN),desired);

	return NULL;
}


void ModelControl::read3DModel(SIMModelNode *n){

	// read model
	if(n->xml.pushTag("SIMNodeModel")){ // try to PUSH <model> tag 
		n->model3D = new Node3D();
		n->model3D->setMyModel(n);
		n->model3D->setName(n->xml.getValue("name","Missing Name"));
		n->model3D->setFilename(n->xml.getValue("link","Missing Filename"));
		
		ofLogVerbose("[MODELCONTROL]") << " -------------------------------------------------------- READING : " << n->model3D->getName();

		n->model3D->setRot( ofVec3f(	n->xml.getAttribute("rotation","x",0.0),
										n->xml.getAttribute("rotation","y",0.0),
										n->xml.getAttribute("rotation","z",0.0)));


		n->model3D->setScl(	ofVec3f(	n->xml.getAttribute("scale","x",0.0),
										n->xml.getAttribute("scale","y",0.0),
										n->xml.getAttribute("scale","z",0.0)));

		n->model3D->setPivot(ofPoint(	n->xml.getAttribute("satPivot","x",0.0),
										n->xml.getAttribute("satPivot","y",0.0),
										n->xml.getAttribute("satPivot","z",0.0)));


		n->model3D->loadModel();// Load Model

		n->xml.popTag(); // POP <model>
	} else {
		n->model3D = NULL;
	}


}

void ModelControl::loadModel(string v_filename, SIMModelNode *start){

	SIMModelNode *modelNode = new SIMModelNode();
	modelNode->nodeRDT = new NodeRDT();
	modelNode->nodeRDT->myModel = modelNode;

	modelNode->myEarthPosition = new NodePositions();
	modelNode->myEarthPosition->myNode = modelNode;

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
		this->model = this->headNode;
		this->actualHead = this->model;
		//ofLogVerbose("[LOADMODEL]") << " -------------> ACTUAL HEAD:" << this->actualHead->profile.GetAcronym();
	}

	ofLogVerbose("[LOADMODEL]") << "Reading: " << v_filename;

	if(modelNode->xml.pushTag("SIMModel")){ // try to PUSH <SIMModel> tag

		// READ PROFILE
		this->readProfile(modelNode);
		ofLogVerbose("[LOADMODEL]") << "Profile teste: "<<modelNode->profile.GetName();


		// READ MODEL
		this->read3DModel(modelNode);

		  
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


		if(modelNode->profile.GetNodeType() == nodeType::ntGROUNDSTATION )
			modelNode->myEarthPosition->updatePosition();
		if(modelNode->profile.GetNodeType() == nodeType::ntSATELLITE )
			modelNode->myEarthPosition->updatePosition();



	}

	if(this->getModelHead() == modelNode){
		// return to the root, call to resolve extenal links
		//this->validateExternalEvents();


		if( someErrorDetected == false) this->correctLoaded = true;

	}

}

void ModelControl::readProfile(SIMModelNode *n){
	// read profile
	if(n->xml.pushTag("SIMNodeProfile")){ // try to PUSH <profile> tag

		n->profile.SetID(n->xml.getValue("id",0));
		n->profile.SetName(n->xml.getValue("name","Name missing"));
		n->profile.SetAcronym(n->xml.getValue("acronym","Acronym missing"));
		n->profile.SetUniqueCode(n->xml.getValue("uniqueCode","Unique Code missing"));
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

		//	// Create Profile Panel
		n->nodeGUI = new NodeGUI();
		n->nodeGUI->setMyNode(n);
	}
}

void ModelControl::readParameters(SIMModelNode *n){
	// read parameters
	if(n->xml.pushTag("SIMNodeParameters")){ // try to PUSH <parameters> tag
		int paramCount = n->xml.getNumTags("NodeParameter");
		for(int i=0; i<paramCount; i++){

			string auxPType = n->xml.getAttribute("NodeParameter","type","ERROR",i);
			ofLogVerbose("[PARAMETERLOAD]") << auxPType;

			SIMModelParameter *newParam;
			//newParam->setMyNode(n);

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
 * auxOM = new OperationalMode(); auxOM->setType(paramType::operationalMode);
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
 * blue; break;		//standby case 2: omo->colorMode = ofColor::green; break; acting
 * case 3: omo->colorMode = ofColor::red; break;		//alert default: break; } oms =
 * oms + "-" + omo->acronymCBERS; auxOM->omList.push_back(omo);  n- >xml.popTag();
 * // POP <om> }  } n->xml.popTag(); // POP <listOfModes> ofLogVerbose() <<
 * "[INTERFACE][LoadModel][OM] Read:" + oms; } n->paramList. push_back(auxOM); n-
 * >xml.popTag(); // POP <operationalMode> } else { if(n->xml. pushTag("value")){
 * // try to PUSH <value> Value *v = new Value(); v- >setType(paramType::
 * dataValue); v->set(n->xml.getValue("name","missing"), n- >xml.
 * getValue("datavalue",0.0), n->xml.getValue("max",0.0), n->xml. getValue("min",0.
 * 0)); v->acronym = n->xml.getValue("acronym","missing"); v- >acronymCBERS =  n-
 * >xml.getValue("acronymCBERS","missing"); ofLogVerbose() <<
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
void ModelControl::readRuleExpressions(SIMModelNode *n){
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

void ModelControl::readModelLinks(SIMModelNode *n){
	// Read expressions
	if(n->xml.pushTag("SIMNodeLinks")){
		int linkCount = n->xml.getNumTags("Link");
		for(int i = 0; i < linkCount; i++)
			loadModel(n->xml.getValue("Link","ERROR",i),n);

	} else {
		ofLogVerbose("[READNODELINKS]") << "No lower links on this model";
	}
}


void ModelControl::updateFromSim(){

	this->simLink->sendMessage(messageType::mtPARAMREAD);

	





}