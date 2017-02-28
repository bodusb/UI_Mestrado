///////////////////////////////////////////////////////////
//  SIMParameterValue.cpp
//  Implementation of the Class SIMParameterValue
//  Created on:      08-out-2013 14:24:00
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMParameterValue.h"

#include "SIMModelNode.h"

SIMParameterValue::SIMParameterValue(){

	this->profile.SetType(paramType::ptDATAVALUE);




}


SIMParameterValue::~SIMParameterValue(){

}


double SIMParameterValue::getValue(){
	return Value;
}


void SIMParameterValue::setValue(double newVal){
	Value = newVal;
	fValue = newVal;
}


double SIMParameterValue::getMinThreshold(){

	return MinThreshold;
}


void SIMParameterValue::setMinThreshold(double newVal){
	MinThreshold = newVal;
}


double SIMParameterValue::getMaxThreshold(){
	return MaxThreshold;
}


void SIMParameterValue::setMaxThreshold(double newVal){
	MaxThreshold = newVal;
}


void SIMParameterValue::loadParameter(SIMModelNode *n,SIMModelParameter *param){
	// enters with the xml pointing inside the parameter
	SIMParameterValue *p = (SIMParameterValue*)param;

	// read parameter profile
	this->profile.readProfile(n);

	// Read Type
	string auxType = n->xml.getValue("DataType","ERROR");
	for(;;){
		if(auxType == "TELECOMMAND")			p->setDataType(paramDataValueTypes::dtTELECOMMAND); break;
		if(auxType == "TELEMETRY")				p->setDataType(paramDataValueTypes::dtTELEMETRY); break;
		if(auxType == "OUTPUTPARAMETER")		p->setDataType(paramDataValueTypes::dtOUTPUTPARAMETER); break;
		if(auxType == "THERMALPOWER")			p->setDataType(paramDataValueTypes::dtTHERMALPOWER); break;
		if(auxType == "COMMUNICATIONPOWER")		p->setDataType(paramDataValueTypes::dtCOMMUNICATIONPOWER); break;
		if(auxType == "ELECTRICPOWER")			p->setDataType(paramDataValueTypes::dtELECTRICPOWER); break;
		if(auxType == "SWITCH")					p->setDataType(paramDataValueTypes::dtSWITCH); break;
		if(auxType == "SIMULATIONHELPER")		p->setDataType(paramDataValueTypes::dtSIMULATIONHELPER); break;
		if(auxType == "USERDEFINED")			p->setDataType(paramDataValueTypes::dtUSERDEFINED); break;
		p->setDataType(paramDataValueTypes::dtERROR);break;
	}
	ofLogVerbose("[PARAMETERVALUE]") << "DataType: " << auxType;

	// Value will come from simulator
	//// Read Value Data
	p->setValue(n->xml.getValue("initialValue",0.0));
	p->setMaxThreshold(n->xml.getValue("MaxThreshold",0.0));
	p->setMinThreshold(n->xml.getValue("MinThreshold",0.0));
	p->SetValueUnit(n->xml.getValue("ValueUnit","UNITERROR"));
	ofLogVerbose("[PARAMETERVALUE]") << "Initial Value: " << Value;

	//// ADD VARIABLE TO PARSER
	//n->GetMathParser()->addVariable(p->profile.GetAcronymCBERS(),this->getValueVariable());

}


string SIMParameterValue::GetValueUnit(){

	return ValueUnit;
}


void SIMParameterValue::SetValueUnit(string newVal){

	ValueUnit = newVal;
}



void SIMParameterValue::makeParamPanel(ofxUIScrollableCanvas *v_panel){
	/*
	Value: XXX - XXX
	Value w/range
	Log
	Axis
	MovingGraph
	*/

	v_panel->addSpacer(5);
	//v_panel->addWidgetDown(new ofxUILabel("Value: " + this->profile.GetName() + " - " + this->profile.GetUniqueCode(), OFX_UI_FONT_MEDIUM)); 
	v_panel->addWidgetDown(new ofxUILabel(this->profile.GetName() + " (" + this->profile.GetUniqueCode() + ")", OFX_UI_FONT_MEDIUM)); 

	//v_panel->addWidgetDown(this->sliderValue);
	v_panel->addWidgetDown(new ofxUINumberDialer(this->MinThreshold,this->MaxThreshold,&this->fValue,2,this->profile.GetUniqueCode()+"dialer",OFX_UI_FONT_MEDIUM));
	v_panel->addWidgetRight(new ofxUILabel(this->GetValueUnit() + "  ",OFX_UI_FONT_MEDIUM));

	v_panel->addWidgetRight(new ofxUILabelToggle(60,5,&this->collectChange,"Change", OFX_UI_FONT_MEDIUM));
	v_panel->addWidgetRight(new ofxUILabelToggle(60,5,&this->onGraph,"Graph", OFX_UI_FONT_MEDIUM));

	//v_panel->addWidgetDown(new ofxUIMovingGraph(5, 120,&this->value, 256, this->min, this->max, "MOVING GRAPH"));

}