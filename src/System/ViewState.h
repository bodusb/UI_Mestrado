///////////////////////////////////////////////////////////
//  ViewState.h
//  Implementation of the Class ViewState
//  Created on:      06-set-2013 14:20:21
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_CC7905AE_F29D_401e_B404_63ED6BE939D9__INCLUDED_)
#define EA_CC7905AE_F29D_401e_B404_63ED6BE939D9__INCLUDED_

#include "ofMain.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMModelNode.h"

class SatView;

class ViewState
{

public:
	ViewState();
	virtual ~ViewState();

	virtual void draw() = 0;
	virtual void executeAction() = 0;
	virtual void selectingAction() = 0;
	virtual void handle() = 0;

	SatView *mySatview;

	string name;

protected:

	float	nearestDistance;
	int		nearestIndex;
	ofVec3f nearestPoint;

	void recursiveDraw(SIMModelNode* start);

	SIMModelNode* findNearestObjectToAction(SIMModelNode* start);
	
};
#endif // !defined(EA_CC7905AE_F29D_401e_B404_63ED6BE939D9__INCLUDED_)
   