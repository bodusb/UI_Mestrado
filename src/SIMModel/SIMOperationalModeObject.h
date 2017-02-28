///////////////////////////////////////////////////////////
//  SIMOperationalModeObject.h
//  Implementation of the Class SIMOperationalModeObject
//  Created on:      08-out-2013 15:45:19
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_E0318C8A_4F7D_44bb_A2A6_9A2842B53FA1__INCLUDED_)
#define EA_E0318C8A_4F7D_44bb_A2A6_9A2842B53FA1__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"
#include "SIMModelParameter.h"


enum appearType{
	aptOFF,
	aptSTANDBY,
	aptFUNCTIONAL,
	aptFAILURE,
	aptOVERHEATED,
	aptOVERCOOLED,
	aptERROR
};

class SIMModelNode;

class SIMOperationalModeObject : public SIMModelParameter {

public:
	SIMOperationalModeObject();
	virtual ~SIMOperationalModeObject();
	void loadParameter(SIMModelNode * modelNode,SIMModelParameter *param);
	bool IsActive();
	void SetActive(bool newVal);
	appearType GetAppearance();
	void SetAppearance(appearType newVal);

	double* getValueVariable() {return NULL;};
	void	setValueVariable(double newValue) {};

	void makeParamPanel(ofxUIScrollableCanvas *v_panel) {};
private:
	bool Active;
	appearType Appearance;




};
#endif // !defined(EA_E0318C8A_4F7D_44bb_A2A6_9A2842B53FA1__INCLUDED_)
