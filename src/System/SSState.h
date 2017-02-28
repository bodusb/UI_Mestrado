///////////////////////////////////////////////////////////
//  SSState.h
//  Implementation of the Class SSState
//  Created on:      06-set-2013 14:20:18
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_8343F919_09E0_4c6b_9352_52208F3A79B6__INCLUDED_)
#define EA_8343F919_09E0_4c6b_9352_52208F3A79B6__INCLUDED_

#include "ViewState.h"

class SSState : public ViewState
{

public:
	SSState();
	virtual ~SSState();

	void draw();
	void executeAction() {};
	void selectingAction() {};
	void handle();

};
#endif // !defined(EA_8343F919_09E0_4c6b_9352_52208F3A79B6__INCLUDED_)
