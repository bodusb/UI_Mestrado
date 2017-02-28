///////////////////////////////////////////////////////////
//  SIMScriptObject.h
//  Implementation of the Class SIMScriptObject
//  Created on:      22-out-2013 16:02:59
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_851034E2_D6BC_4f8c_89B7_7839239508B5__INCLUDED_)
#define EA_851034E2_D6BC_4f8c_89B7_7839239508B5__INCLUDED_

#include "ofMain.h"

class SIMScriptObject
{


public:
	SIMScriptObject();
	virtual ~SIMScriptObject();

	void		setNodeName(string v_nodename) { this->NodeName = v_nodename;};
	string		getNodeName() { return this->NodeName;};

	void		setParamName(string v_paramname) { this->ParamName = v_paramname;};
	string		getParamName() { return this->ParamName;};

	void		setID(int v_id) { this->ID = v_id;};
	int			getID() { return this->ID;};

	void		setNewValue(double v_newVal) { this->NewValue = v_newVal;}
	double		getNewValue() { return this->NewValue;};
	
	bool		isApplied() { return this->applied;};
	void		Apply() { this->applied = true;};


private:
	string NodeName;
	string ParamName;
	int ID;
	double NewValue;

	bool applied;

	// link to the desired parameter
};
#endif // !defined(EA_851034E2_D6BC_4f8c_89B7_7839239508B5__INCLUDED_)
