///////////////////////////////////////////////////////////
//  GraphView.h
//  Implementation of the Class GraphView
//  Created on:      06-set-2013 14:20:15
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_8A5BFA36_A4AA_43af_9814_041130C5E23A__INCLUDED_)
#define EA_8A5BFA36_A4AA_43af_9814_041130C5E23A__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "iView.h"

class GraphView : public iView
{

public:
	GraphView();
	virtual ~GraphView();
	void draw();
	void executeAction();
	void selectingAction();

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

	void speedChanged();

protected:

	float curve1,curve2;
	ofPolyline trail;
	bool showPos;
	float initTime,t;
	float x, prevX;

};
#endif // !defined(EA_8A5BFA36_A4AA_43af_9814_041130C5E23A__INCLUDED_)
