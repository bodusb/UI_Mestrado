///////////////////////////////////////////////////////////
//  SatState.h
//  Implementation of the Class SatState
//  Created on:      06-set-2013 14:20:17
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_5045AE00_FDEA_4ad9_A3D3_D21B9ABD0910__INCLUDED_)
#define EA_5045AE00_FDEA_4ad9_A3D3_D21B9ABD0910__INCLUDED_

#include "ViewState.h"

class SatState : public ViewState
{

public:
	SatState();
	virtual ~SatState();

	void draw();
	void executeAction() {};
	void selectingAction();
	void handle();


protected:


};
#endif // !defined(EA_5045AE00_FDEA_4ad9_A3D3_D21B9ABD0910__INCLUDED_)
