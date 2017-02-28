///////////////////////////////////////////////////////////
//  iScreen.h
//  Implementation of the Class iScreen
//  Created on:      06-set-2013 15:50:42
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_C0EE7A69_5D83_469c_8077_114767581F12__INCLUDED_)
#define EA_C0EE7A69_5D83_469c_8077_114767581F12__INCLUDED_

#include "ofxXmlSettings.h"
#include "iView.h"

class iAction;

class iScreen
{

public:
	iScreen();
	virtual ~iScreen();
	vector<iView *> iviewList;
	iAction *myAction;

	void updateViews();
	void drawBackgrounds();
	void draw();

	iView* getView(string name);

	void swapViews(iView *start, iView *target);

private:
	ofxXmlSettings XML;

void readViewInfo(iView *v, int i);

	

};
#endif // !defined(EA_C0EE7A69_5D83_469c_8077_114767581F12__INCLUDED_)
