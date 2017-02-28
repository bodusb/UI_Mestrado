///////////////////////////////////////////////////////////
//  SpaceView.h
//  Implementation of the Class SpaceView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_61DCE5BA_B3DF_4022_A9E4_AAF74DA3C8B7__INCLUDED_)
#define EA_61DCE5BA_B3DF_4022_A9E4_AAF74DA3C8B7__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "iView.h"

class SpaceView : public iView
{

public:
	SpaceView();
	virtual ~SpaceView();
	void draw();
	void executeAction();
	void selectingAction();

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

private:
	void drawGlobe();
	void drawGS();
	void drawSats();
	void drawSUN();



};
#endif // !defined(EA_61DCE5BA_B3DF_4022_A9E4_AAF74DA3C8B7__INCLUDED_)
