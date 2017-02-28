///////////////////////////////////////////////////////////
//  iAction.h
//  Implementation of the Class iAction
//  Created on:      06-set-2013 14:19:56
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_C3CF9D7C_7128_48d5_9479_7478DFA29356__INCLUDED_)
#define EA_C3CF9D7C_7128_48d5_9479_7478DFA29356__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"

#include "mouseClick.h"

class iScreen;
class ModelControl;
class SIMModelNode;

//
//enum objectTypes {	node = 1, 
//					satellite = 2, 
//					groundStation = 3, 
//					equipment = 4, 
//					parameter = 5, 
//					earth = 6, 
//					subsystem = 7};


typedef struct date{
	float Year;
	float Month;
	float Day;
	float Hour;
	float Min;
	float Sec;
	double JD;
	string stringedDate;
} date;

class iAction
{

public:
	iAction();
	virtual ~iAction();
	iScreen *m_iScreen;

	void		spreadAction();
	void		recursiveSpread(SIMModelNode *start);
	ModelControl *modelController;
	mouseClick startClick;
	mouseClick endClick;
	mouseClick actual;
	bool somePanelVisible;
	ofxUIScrollableCanvas *actualPanel;

	bool hasAudio;
	int audioVolume;

	string message;

	int			closestObjectType;
	void		*actualClosestObject;  // do cast to the objectType --
	//ofVec3f		actualClosestObjectPosition;


	void selectingAction(int v_button, ofPoint v_position);
	void startAction(int v_button, ofPoint v_position);
	void finishAction(int v_button, ofPoint v_position);

	bool hasDrag();
	bool hasHold(int threshold = 100000);

	void drawClosestGuide();

	void addTolog(string context,string value);
	
	date getCurrentDate() { return currentDate;};


	ofxUIScrollableCanvas *logPANEL; 


	date		currentDate;
	date		simulatedDate;
	bool		followingCurrentTime;


	bool		connection;
	bool		run;
	bool		doStep;

	bool		doAlarm;

	ofSoundPlayer  collide;
	ofSoundPlayer  alarm;

	void update();

	int timeCounter;
};
#endif // !defined(EA_C3CF9D7C_7128_48d5_9479_7478DFA29356__INCLUDED_)
