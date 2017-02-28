///////////////////////////////////////////////////////////
//  mouseClick.h
//  Implementation of the Class mouseClick
//  Created on:      06-set-2013 15:30:02
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_B40EB4B4_49A8_4f4a_B014_91C1E113B8DD__INCLUDED_)
#define EA_B40EB4B4_49A8_4f4a_B014_91C1E113B8DD__INCLUDED_

#include "ofMain.h"
#include "ofPoint.h"

class iView;

class mouseClick
{

public:
	mouseClick();
	virtual ~mouseClick();
	ofPoint position;
	int button;
	unsigned long long time;
	iView *view;


	int			closestObjectType;
	void		*closestObject;  // do cast to the objectType --


	void set(int v_button, ofPoint v_position,iView *v);

};
#endif // !defined(EA_B40EB4B4_49A8_4f4a_B014_91C1E113B8DD__INCLUDED_)
