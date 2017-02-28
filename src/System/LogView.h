///////////////////////////////////////////////////////////
//  LogView.h
//  Implementation of the Class LogView
//  Created on:      06-set-2013 20:14:41
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_5B4A0537_74B9_45cd_9854_B91C2D23017C__INCLUDED_)
#define EA_5B4A0537_74B9_45cd_9854_B91C2D23017C__INCLUDED_

#include "iView.h"

#include "ofMain.h"
#include "ofxUI.h"


class LogView : public iView
{

public:
	LogView();
	virtual ~LogView();

	void draw();
	void executeAction();
	void selectingAction();

	ofxUIScrollableCanvas *getGui() { return gui;};

	void panelEvent(ofxUIEventArgs& e);
	void setContextPanel();

	void resizeView();
private:

	bool saveToFile;
	string filename;
	
	ofxUIScrollableCanvas *gui; 


	vector<string> logHistory;   // [LOG][RT][ST] - EVENT
};
#endif // !defined(EA_5B4A0537_74B9_45cd_9854_B91C2D23017C__INCLUDED_)
