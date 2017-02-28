///////////////////////////////////////////////////////////
//  SIMModelParameter.h
//  Implementation of the Class SIMModelParameter
//  Created on:      08-out-2013 13:42:21
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_7D4B1537_3B48_4ea6_8491_08ED41F0F5D5__INCLUDED_)
#define EA_7D4B1537_3B48_4ea6_8491_08ED41F0F5D5__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "SIMParameterProfile.h"
#include "ParamGui.h"
//#include "mu\muParser.h"

class SIMModelNode;

class SIMModelParameter
{

public:	
	SIMParameterProfile profile;

	SIMModelParameter();
	virtual ~SIMModelParameter();
	virtual void loadParameter(SIMModelNode * modelNode,SIMModelParameter *param) = 0;

	virtual double* getValueVariable() = 0;
	virtual void	setValueVariable(double newValue) = 0;
	virtual void	makeParamPanel(ofxUIScrollableCanvas *v_panel) = 0;

	void setToCollect(bool value){ collectChange = value;};
	bool getCollectStatus() { return collectChange;};


	void setMyNode(SIMModelNode *newVal) { my_Node = newVal;};
	SIMModelNode * getMyNode() { return my_Node;};

private:

	bool	editable;
	ParamGui *m_ParamGui;

	SIMModelNode* my_Node;

protected:
	bool collectChange;
	bool log;
	bool onGraph;

	vector<double> logValue;
};



#endif // !defined(EA_7D4B1537_3B48_4ea6_8491_08ED41F0F5D5__INCLUDED_)

