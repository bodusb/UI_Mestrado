///////////////////////////////////////////////////////////
//  SystemView.h
//  Implementation of the Class SystemView
//  Created on:      06-set-2013 14:19:54
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_CC051172_DE28_4f0c_8066_3ED188F18EA8__INCLUDED_)
#define EA_CC051172_DE28_4f0c_8066_3ED188F18EA8__INCLUDED_

#include "iView.h"

class SystemView : public iView
{

public:
	SystemView();
	virtual ~SystemView();

	void draw();
	void executeAction() {};
	void selectingAction() {};

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void guiEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

	void resizeView();
	void startView();

private:

	ofxUICanvas *gui;
	ofxUILabelToggle *status;
	ofxUILabelToggle *run;
	ofxUILabelToggle *step;

	ofxUILabelToggle *verbose;
	bool verbo;

};
#endif // !defined(EA_CC051172_DE28_4f0c_8066_3ED188F18EA8__INCLUDED_)

