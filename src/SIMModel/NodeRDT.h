///////////////////////////////////////////////////////////
//  NodeRDT.h
//  Implementation of the Class NodeRDT
//  Created on:      06-set-2013 14:20:03
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_0AF3BCA1_7947_41dd_B0E8_505D565F7C46__INCLUDED_)
#define EA_0AF3BCA1_7947_41dd_B0E8_505D565F7C46__INCLUDED_

#include "ofPoint.h"
#include "ofVec3f.h"

#include "SIMOperationalModeObject.h"
#include "SIMParameterOperationalMode.h"

class NodeRDT
{

public:	
	
	void	setPlace(ofPoint value) { this->place = value;};
	void	setAuxPlace(ofPoint value) { this->auxPlace = value;};
	void	setOpen(bool value) { open = value;};
	void	setSelect(bool value) { selected = value;};

	void	setRad(double value) { rad = value;};
	void	setOutRad(double value) { out_rad = value;};

	ofPoint getPlace() { return this->place;};
	ofPoint getAuxPlace() { return this->auxPlace;};
	bool isOpen() { return this->open;};
	bool isSelected() { return this->selected;};

	double getRad() { return rad;};
	double getOutRad() { return out_rad;};
	

	appearType getAppearTypeFromOM();

	
	NodeRDT();
	virtual ~NodeRDT();

	SIMModelNode *myModel;

private:

	
	double rad;
	double out_rad;
	ofPoint place;
	ofVec3f auxPlace;
	bool open;
	bool selected;

};
#endif // !defined(EA_0AF3BCA1_7947_41dd_B0E8_505D565F7C46__INCLUDED_)
