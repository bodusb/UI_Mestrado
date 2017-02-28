///////////////////////////////////////////////////////////
//  ModelSimCom.h
//  Implementation of the Class ModelSimCom
//  Created on:      13-dez-2013 18:03:59
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_B9B8F0A2_F66D_424d_A845_C5E65672CF9F__INCLUDED_)
#define EA_B9B8F0A2_F66D_424d_A845_C5E65672CF9F__INCLUDED_

#include "ofMain.h"
#include "ofxOsc.h"


enum netComType{	nctINTERFACE,
					nctSIMULATOR,
					nctRDT
};
	
enum messageType{	mtSIMCONTROL,
					mtSIMCONFIG,
					mtSIMSTEP,
					mtSCRIPTCONTROL,
					mtSCRIPTLIST,
					mtSCRIPTADD,
					mtSCRIPTREMOVE,
					mtPARAMREAD,
					mtPARAMCHANGE,
					mtSUNPREDICTION,
					mtPASSPREDICTION
};
	



class ModelControl;

class ModelSimCom
{

public:
	ModelSimCom();
	virtual ~ModelSimCom();

	void receiveMessage();
	void sendMessage(messageType mess);
	
	bool isConnected();
	bool setConnected(bool newVal);


	ModelControl *myModel;
private:
	
	virtual void handleSIMCONTROL() = 0;
	virtual void handleSIMSTEP() = 0;
	virtual void handleSIMCONFIG() = 0;
	virtual void handlePARAMCHANGE() = 0;
	virtual void handlePASSPREDICTION() = 0;
	virtual void handleSUNPREDICTION() = 0;
	virtual void handlePARAMREAD() = 0;
	virtual void handleSCRIPTADD() = 0;
	virtual void handleSCRIPTCONTROL() = 0;
	virtual void handleSCRIPTLIST() = 0;
	virtual void handleSCRIPTREMOVE() = 0;

protected:
	netComType cType;
	messageType mType;

	ofxOscSender *sender;
	ofxOscReceiver *receiver;
	int portNumber;
	string simulatorIP;
	string interfaceIP;
	bool connected;
	ofxOscMessage message;

};
#endif // !defined(EA_B9B8F0A2_F66D_424d_A845_C5E65672CF9F__INCLUDED_)
