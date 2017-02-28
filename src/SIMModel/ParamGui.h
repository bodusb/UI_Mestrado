///////////////////////////////////////////////////////////
//  ParamGui.h
//  Implementation of the Class ParamGui
//  Created on:      06-set-2013 14:20:16
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_39DDAC24_CC7B_41fe_AC6A_B44B3EFFEA42__INCLUDED_)
#define EA_39DDAC24_CC7B_41fe_AC6A_B44B3EFFEA42__INCLUDED_

#include "..\System\iGUI.h"

class ParamGui : public iGUI
{

public:
	ParamGui();
	virtual ~ParamGui();

	
	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();

};
#endif // !defined(EA_39DDAC24_CC7B_41fe_AC6A_B44B3EFFEA42__INCLUDED_)
