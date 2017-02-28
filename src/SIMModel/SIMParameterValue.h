///////////////////////////////////////////////////////////
//  SIMParameterValue.h
//  Implementation of the Class SIMParameterValue
//  Created on:      08-out-2013 14:24:00
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_C119D413_F944_4801_88EC_38419D3CE669__INCLUDED_)
#define EA_C119D413_F944_4801_88EC_38419D3CE669__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "SIMModelParameter.h"

enum paramDataValueTypes{
					dtTELECOMMAND, 
					dtTELEMETRY, 	
					dtOUTPUTPARAMETER,
					dtTHERMALPOWER, 
					dtCOMMUNICATIONPOWER, 
					dtELECTRICPOWER, 
					dtSWITCH,
					dtSIMULATIONHELPER,
					dtUSERDEFINED,
					dtERROR
};

class SIMParameterValue : public SIMModelParameter
{

public:
	SIMParameterValue();
	virtual ~SIMParameterValue();

	paramDataValueTypes getDataType() {return dataType;};
	void	setDataType(paramDataValueTypes newVal){ dataType = newVal;};
	double getValue();
	double* getValueVariable() { return &Value;};
	void	setValueVariable(double newValue) {  logValue.push_back(this->Value); this->Value = newValue; this->fValue = newValue;};
	void setValue(double newVal);
	double getMinThreshold();
	void setMinThreshold(double newVal);
	double getMaxThreshold();
	void setMaxThreshold(double newVal);
	void loadParameter(SIMModelNode * modelNode,SIMModelParameter *param);
	string GetValueUnit();
	void SetValueUnit(string newVal) ;

	double newUserValue;


	void makeParamPanel(ofxUIScrollableCanvas *v_panel);


private:
	paramDataValueTypes dataType;
	double Value;
	float fValue;
	double MinThreshold;
	double MaxThreshold;
	string ValueUnit;

	ofxUISlider *sliderValue;

	

};
#endif // !defined(EA_C119D413_F944_4801_88EC_38419D3CE669__INCLUDED_)
