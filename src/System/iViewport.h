///////////////////////////////////////////////////////////
//  iViewport.h
//  Implementation of the Class iViewport
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_0C6913C5_A2C9_4e80_8CCF_56E1FBD60DE3__INCLUDED_)
#define EA_0C6913C5_A2C9_4e80_8CCF_56E1FBD60DE3__INCLUDED_

#include "ofMain.h"

class iViewport
{
private:
	int height;
	int width;
	int x;
	int y;


public:
	iViewport();
	virtual ~iViewport();
	void setDimensions(int x, int y, int width, int height);
	void updateViewport();
	void drawBackground();

	ofColor backgroundColor;
	int id;
	string name;
	ofRectangle place;

};
#endif // !defined(EA_0C6913C5_A2C9_4e80_8CCF_56E1FBD60DE3__INCLUDED_)
