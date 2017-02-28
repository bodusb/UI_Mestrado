///////////////////////////////////////////////////////////
//  iGUI.h
//  Implementation of the Class iGUI
//  Created on:      06-set-2013 14:19:57
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_831BDCD7_F763_46e7_AEF7_F4CF34D95F77__INCLUDED_)
#define EA_831BDCD7_F763_46e7_AEF7_F4CF34D95F77__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "../System/iAction.h"

class iGUI
{

public:
	iGUI();
	virtual ~iGUI();


	void setPanelVisible(bool v) { panel->setVisible(v);}
	bool isPanelVisible() { return panel->isVisible();}
	//GUI
	virtual void panelEvent(ofxUIEventArgs &e) = 0;  
	virtual void setContextPanel() = 0;

	ofxUIScrollableCanvas *getPanel() { return panel;};

	void setMyAction(iAction *value) { myAction = value;};

protected:
	ofxUIScrollableCanvas *panel;

	iAction *myAction;

};
#endif // !defined(EA_831BDCD7_F763_46e7_AEF7_F4CF34D95F77__INCLUDED_)
