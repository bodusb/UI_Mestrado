///////////////////////////////////////////////////////////
//  SIMInterface.h
//  Implementation of the Class COMInterface
//  Created on:      13-dez-2013 19:06:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_88B5666F_B301_4f57_AFEE_892EDB3A36AE__INCLUDED_)
#define EA_88B5666F_B301_4f57_AFEE_892EDB3A36AE__INCLUDED_

#include "ModelSimCom.h"
#include "ofxOsc.h"

class SIMModelNode;
class SIMModelParameter;

class COMInterface : public ModelSimCom
{

public:
	COMInterface();
	virtual ~COMInterface();


private:
	virtual void handleSIMCONTROL();
	virtual void handleSIMSTEP();
	virtual void handleSIMCONFIG();
	virtual void handlePARAMCHANGE();
	virtual void handlePASSPREDICTION();
	virtual void handleSUNPREDICTION();

	void recursiveRead(SIMModelNode* start);
	virtual void handlePARAMREAD();
	virtual void handleSCRIPTADD();
	virtual void handleSCRIPTCONTROL();
	virtual void handleSCRIPTLIST();
	virtual void handleSCRIPTREMOVE();

};
#endif // !defined(EA_88B5666F_B301_4f57_AFEE_892EDB3A36AE__INCLUDED_)
