///////////////////////////////////////////////////////////
//  SatView.h
//  Implementation of the Class SatView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_A8F94DC5_ACC6_4da0_842F_71A3F3208262__INCLUDED_)
#define EA_A8F94DC5_ACC6_4da0_842F_71A3F3208262__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "iView.h"
#include "ViewState.h"

#include "..\SIMModel\Node3D.h"
#include "..\SIMModel\SIMModelNode.h"



class SatView : public iView
{

public:	
	SatView();
	virtual ~SatView();
	void draw();
	void executeAction();
	void selectingAction();
	
	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();


private:

	bool showSat;

	vector<ViewState*> stateList;
	ViewState *actualState;
	ViewState *m_ViewState;



    float	nearestDistance;
	int		nearestIndex;
	ofVec3f nearestPoint;

	void recursiveDraw(SIMModelNode* start);

	SIMModelNode* findNearestObjectToAction(SIMModelNode* start);

};
#endif // !defined(EA_A8F94DC5_ACC6_4da0_842F_71A3F3208262__INCLUDED_)
