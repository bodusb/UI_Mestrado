///////////////////////////////////////////////////////////
//  EQState.h
//  Implementation of the Class EQState
//  Created on:      06-set-2013 14:20:19
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_FDDD0991_7722_4343_91F9_0F6D46562259__INCLUDED_)
#define EA_FDDD0991_7722_4343_91F9_0F6D46562259__INCLUDED_

#include "ViewState.h"

class EQState : public ViewState
{

public:
	EQState();
	virtual ~EQState();

	void draw();
	void executeAction() {};
	void selectingAction() {};
	void handle();

};
#endif // !defined(EA_FDDD0991_7722_4343_91F9_0F6D46562259__INCLUDED_)
