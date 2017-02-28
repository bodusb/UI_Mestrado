///////////////////////////////////////////////////////////
//  iView.h
//  Implementation of the Class iView
//  Created on:      06-set-2013 15:48:41
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_4817FA78_45A3_4edf_935A_3BD9E9C03E33__INCLUDED_)
#define EA_4817FA78_45A3_4edf_935A_3BD9E9C03E33__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h" 

#include "iViewport.h"

class iScreen;

class iView
{

public:
	iView();
	virtual ~iView();
	string name;
	ofEasyCam cam;
	int id;

	iScreen *myScreen;

	iViewport *vp;

	virtual void draw() = 0;
	
	virtual void executeAction() = 0;
	virtual void selectingAction() = 0;

	//GUI
	virtual void panelEvent(ofxUIEventArgs &e) = 0;  
	virtual void setContextPanel() = 0;
	
	void setPanelVisible(bool v) { panel->setVisible(v);}
	bool isPanelVisible() { return panel->isVisible();}
	
	ofxUIScrollableCanvas *getPanel() { return panel;};

protected:

	float	nearestDistance;
	int		nearestIndex;
	ofVec3f nearestPoint;
	ofxUIScrollableCanvas *panel;


};
#endif // !defined(EA_4817FA78_45A3_4edf_935A_3BD9E9C03E33__INCLUDED_)
