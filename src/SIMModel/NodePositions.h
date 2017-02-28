///////////////////////////////////////////////////////////
//  NodePositions.h
//  Implementation of the Class NodePositions
//  Created on:      10-set-2013 14:33:18
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_39B54A55_E2C7_4b6a_B53B_F1F40FE424D9__INCLUDED_)
#define EA_39B54A55_E2C7_4b6a_B53B_F1F40FE424D9__INCLUDED_

#include "ofMain.h"

class SIMModelNode;

class NodePositions
{

public:
	NodePositions();
	virtual ~NodePositions();
	double latitude;
	double longitude;
	double altitude;
	ofPoint rectangular;
	ofPoint rectangularToDraw;
	ofVec3f auxPlace;

	SIMModelNode *myNode;

	void updatePosition();
	void updatePosition(double v_lat, double v_long, double v_alt);
	void updatePosition(ofPoint v_rect);
	void latLongToRectangular();

};
#endif // !defined(EA_39B54A55_E2C7_4b6a_B53B_F1F40FE424D9__INCLUDED_)
