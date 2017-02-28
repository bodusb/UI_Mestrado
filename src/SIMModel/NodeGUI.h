///////////////////////////////////////////////////////////
//  NodeGUI.h
//  Implementation of the Class NodeGUI
//  Created on:      06-set-2013 14:20:02
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_B05C9A8D_9B18_4acc_B340_DF2F5B03B3D3__INCLUDED_)
#define EA_B05C9A8D_9B18_4acc_B340_DF2F5B03B3D3__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"
#include "..\System\iGUI.h"


class SIMModelNode;

class NodeGUI : public iGUI
{

public:
	NodeGUI();
	virtual ~NodeGUI();

	virtual void panelEvent(ofxUIEventArgs& e);
	virtual void setContextPanel();


	

	void setMyNode(SIMModelNode *v_node) { myNode = v_node;};
	SIMModelNode* getMyNode() { return myNode;};

private:
	void makeProfile();
	void makeParameter();
	void makeSons();
	SIMModelNode* myNode;

};
#endif // !defined(EA_B05C9A8D_9B18_4acc_B340_DF2F5B03B3D3__INCLUDED_)
