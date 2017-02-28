///////////////////////////////////////////////////////////
//  ParamView.h
//  Implementation of the Class ParamView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_FEB88DFD_8582_43a9_8035_7DAFEBC2EA38__INCLUDED_)
#define EA_FEB88DFD_8582_43a9_8035_7DAFEBC2EA38__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "iView.h"

class SIMModelNode;

class ParamView : public iView
{

public:
	ParamView();
	virtual ~ParamView();
	
	void executeAction();
	void selectingAction();

	// draw routines
	
	void draw();

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

private:

	void drawRDT(SIMModelNode * start);
	SIMModelNode* findNearestNodeToAction(SIMModelNode* start);


};
#endif // !defined(EA_FEB88DFD_8582_43a9_8035_7DAFEBC2EA38__INCLUDED_)
