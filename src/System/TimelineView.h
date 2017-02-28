///////////////////////////////////////////////////////////
//  TimelineView.h
//  Implementation of the Class TimelineView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_67515864_C1BF_4361_A765_1B5CB175B035__INCLUDED_)
#define EA_67515864_C1BF_4361_A765_1B5CB175B035__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "iView.h"

class TimelineView : public iView
{

public:
	TimelineView();
	virtual ~TimelineView();

	void draw();
	void executeAction() {};
	void selectingAction() {};

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

	void resizeView();
	void startView();

private:

	ofxUICanvas *gui;

	ofxUILabel *Cyear;
	ofxUILabel *Cmon;
	ofxUILabel *Cday;
	ofxUILabel *Chour;
	ofxUILabel *Cmin;
	ofxUILabel *Csec;

	ofxUILabel *Syear;
	ofxUILabel *Smon;
	ofxUILabel *Sday;
	ofxUILabel *Shour;
	ofxUILabel *Smin;
	ofxUILabel *Ssec;



};
#endif // !defined(EA_67515864_C1BF_4361_A765_1B5CB175B035__INCLUDED_)
