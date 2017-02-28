///////////////////////////////////////////////////////////
//  SIMParameterOperationalMode.cpp
//  Implementation of the Class SIMParameterOperationalMode
//  Created on:      08-out-2013 14:24:01
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMParameterOperationalMode.h"


#include "SIMModelNode.h"


SIMParameterOperationalMode::SIMParameterOperationalMode(){

}

SIMParameterOperationalMode::~SIMParameterOperationalMode(){

}

void SIMParameterOperationalMode::loadParameter(SIMModelNode *n,SIMModelParameter *param){
	// enters with the xml pointing inside the parameter
	SIMParameterOperationalMode *p = (SIMParameterOperationalMode*)param;

	// read parameter profile
	this->profile.readProfile(n);
	
	

	// read possible operational Modes
	if(n->xml.pushTag("Modes")){ // Try to PUSH <Modes> tag
		int modeCount = n->xml.getNumTags("ModeObject");
		for(int i = 0; i < modeCount; i++) {
			if(n->xml.pushTag("ModeObject",i)){ // Try to PUSH <ModeObject tag
				SIMOperationalModeObject *omo  = new SIMOperationalModeObject();

				for(;;){
					if(param->profile.GetType() == paramType::ptOPERATIONALMODE) { 
						omo->profile.SetType(paramType::ptOPERATIONALMODEITEM);break;}
					if(param->profile.GetType() == paramType::ptWORKINGSTATE) { 
						omo->profile.SetType(paramType::ptWORKINGSTATEITEM);break;}
					omo->profile.SetType(paramType::ptERROR);break;
				}

				omo->loadParameter(n,param);
		
				this->omoList.push_back(omo);
				n->xml.popTag();	// POP <ModeObject>
			}
		}
		n->xml.popTag(); // POP <Modes>
	}


	p->SetActiveID(n->xml.getValue("initialValue",0));

	p->SetActive(p->GetActiveID());
	//// ADD VARIABLE TO PARSER
	//n->GetMathParser()->addVariable(p->profile.GetAcronymCBERS(),this->getValueVariable());


}

void SIMParameterOperationalMode::SetActive(int v_id){

	ofLogVerbose("[OPERATIONALMODE]") << "Activate id: " << v_id;

	SIMOperationalModeObject *actualOM = this->getActive();
	bool changed = false;

	vector<SIMOperationalModeObject*>::iterator itOMO;

	for(itOMO = this->omoList.begin(); itOMO != this->omoList.end(); itOMO++){
		if(	(*itOMO)->profile.GetID() == v_id ){ 
			(*itOMO)->SetActive(true);
			this->ActiveID = (*itOMO)->profile.GetID();
			ofLogVerbose("[OPERATIONALMODE]") << "OM Activated:" << (*itOMO)->profile.GetName() << " - " << (*itOMO)->profile.GetAcronym();
			changed = true;
		} else {
			(*itOMO)->SetActive(false);
		}
	}

	if (changed == false){
		actualOM->SetActive(true);
		this->ActiveID = actualOM->profile.GetID();
	}
}

SIMOperationalModeObject * SIMParameterOperationalMode::getActive(){
	
	vector<SIMOperationalModeObject*>::iterator itOMO;

	for(itOMO = this->omoList.begin(); itOMO != this->omoList.end(); itOMO++)
		if(	(*itOMO)->IsActive() ) return (*itOMO);
	return NULL;
}

double SIMParameterOperationalMode::GetActiveID(){

	return ActiveID;
}

void SIMParameterOperationalMode::SetActiveID(double newVal){

	ActiveID = newVal;
}

void SIMParameterOperationalMode::panelEvent(ofxUIEventArgs& e){

	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	string parent = e.widget->getParent()->getName();

	ofLogVerbose("[OM PANEL CHANGES]") << name << " - " << ofToString(kind) << " - Parent:" << parent;

	if( parent == "radio"+this->profile.GetUniqueCode()){
		this->changeOMto(name);
	//	if(kind == 	OFX_UI_WIDGET_TOGGLE){
	//		ofxUIRadio *radio = (ofxUIRadio*) e.widget;
	//		ofLogVerbose("[OM PANEL CHANGES]") <<  this->profile.GetUniqueCode() << " - " << radio->getActive()->getName();
	//	}
	}
}

void SIMParameterOperationalMode::makeParamPanel(ofxUIScrollableCanvas *v_panel){
	/*
	Operational Mode: XXX - XXX
	TP, TC, TE values
	Avaiable OMs
	Change/log/axis
	*/

		v_panel->addSpacer(5);
		//title
		v_panel->addWidgetDown(new ofxUILabel(this->profile.GetName() + " - " + this->profile.GetUniqueCode(), OFX_UI_FONT_MEDIUM)); 
		//values

		//Avaiable OMS
		vector<string> omStrings; 
		vector<SIMOperationalModeObject*>::iterator itOMO;
		for( itOMO = this->omoList.begin(); itOMO != this->omoList.end(); itOMO++)
			omStrings.push_back((*itOMO)->profile.GetAcronym());

		ofxUIRadio *r = new ofxUIRadio(20,20,"radio"+this->profile.GetUniqueCode(),omStrings,OFX_UI_ORIENTATION_VERTICAL,OFX_UI_FONT_MEDIUM);
		r->activateToggle(this->getActive()->profile.GetAcronym());
		v_panel->addWidgetDown(r);
		// -> create the handlePANEL Change to this. -- ok
		// set selected


	v_panel->addWidgetDown(new ofxUILabelToggle(60,5,&this->collectChange,"Apply Change", OFX_UI_FONT_MEDIUM));
	v_panel->addWidgetRight(new ofxUILabelToggle(60,5,&this->onGraph,"See on Graph", OFX_UI_FONT_MEDIUM));


		ofAddListener(v_panel->newGUIEvent, this, &SIMParameterOperationalMode::panelEvent); 

}

void SIMParameterOperationalMode::changeOMto(string value){

	ofLogVerbose("[OPERATIONALMODE]") << "Activate OM: " << value;

	SIMOperationalModeObject *actualOM = this->getActive();
	bool changed = false;


	vector<SIMOperationalModeObject*>::iterator itOMO;

	for(itOMO = this->omoList.begin(); itOMO != this->omoList.end(); itOMO++){
		if(	(*itOMO)->profile.GetAcronym() == value ){ 
			(*itOMO)->SetActive(true);
			this->ActiveID = (*itOMO)->profile.GetID();
			ofLogVerbose("[OPERATIONALMODE]") << "OM Activated:" << (*itOMO)->profile.GetName() << " - " << (*itOMO)->profile.GetAcronym();
			changed = true;

		} else {
			(*itOMO)->SetActive(false);
		}
	}

	if (changed == false){
		actualOM->SetActive(true);
		this->ActiveID = actualOM->profile.GetID();
	}

	if(actualOM->GetAppearance() == appearType::aptFAILURE){
		ofSoundPlayer alarm;

		alarm.loadSound("sounds/alarm.mp3");
		alarm.setVolume(0.3f);
		alarm.play(); 
	}

}

void SIMParameterOperationalMode::changeOMto(double value){

	ofLogVerbose("[OPERATIONALMODE]") << "Activate OM: " << value;

	SIMOperationalModeObject *actualOM = this->getActive();
	bool changed = false;


	vector<SIMOperationalModeObject*>::iterator itOMO;

	for(itOMO = this->omoList.begin(); itOMO != this->omoList.end(); itOMO++){
		if(	(*itOMO)->profile.GetID() == value ){ 
			(*itOMO)->SetActive(true);
			this->ActiveID = (*itOMO)->profile.GetID();
			ofLogVerbose("[OPERATIONALMODE]") << "OM Activated:" << (*itOMO)->profile.GetName() << " - " << (*itOMO)->profile.GetAcronym();
			changed = true;

		} else {
			(*itOMO)->SetActive(false);
		}
	}

	if (changed == false){
		actualOM->SetActive(true);
		this->ActiveID = actualOM->profile.GetID();
	}


	if(actualOM->GetAppearance() == appearType::aptFAILURE){
		ofSoundPlayer alarm;

		alarm.loadSound("sounds/alarm.mp3");
		alarm.setVolume(0.3f);
		alarm.play(); 
	}

}