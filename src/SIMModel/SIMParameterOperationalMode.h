///////////////////////////////////////////////////////////
//  SIMParameterOperationalMode.h
//  Implementation of the Class SIMParameterOperationalMode
//  Created on:      08-out-2013 14:24:01
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_D87AC7A1_353D_4859_AA72_12AAEC387436__INCLUDED_)
#define EA_D87AC7A1_353D_4859_AA72_12AAEC387436__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "SIMParameterValue.h"
#include "SIMModelParameter.h"
#include "SIMOperationalModeObject.h"

class SIMParameterOperationalMode : public SIMModelParameter {

public:
	vector<SIMOperationalModeObject*> omoList;
	SIMParameterOperationalMode();
	virtual ~SIMParameterOperationalMode();

	void SetActive(int v_id);
	SIMOperationalModeObject * getActive();

	void loadParameter(SIMModelNode * modelNode,SIMModelParameter *param);

	double GetActiveID();
	void SetActiveID(double newVal);
	void changeOMto(string value);
	void changeOMto(double value);
	double* getValueVariable() { return &ActiveID;};
	void	setValueVariable(double newValue) {changeOMto(newValue);};
	

	void panelEvent(ofxUIEventArgs& e);
	void makeParamPanel(ofxUIScrollableCanvas *v_panel);

private:
	double ActiveID;

};
#endif // !defined(EA_D87AC7A1_353D_4859_AA72_12AAEC387436__INCLUDED_)

