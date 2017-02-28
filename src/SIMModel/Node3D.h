///////////////////////////////////////////////////////////
//  Node3D.h
//  Implementation of the Class Node3D
//  Created on:      06-set-2013 14:20:04
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_F875A6C6_EE20_43b7_A3D5_3E11667870D3__INCLUDED_)
#define EA_F875A6C6_EE20_43b7_A3D5_3E11667870D3__INCLUDED_

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxAssimpModelLoader.h"
#include "SIMOperationalModeObject.h"
#include "SIMParameterOperationalMode.h"

class SIMModelNode; 

class Node3D
{

public:
	Node3D();
	virtual ~Node3D();
	void draw();
	void drawDefault();
	bool loadModel();
	
	void setFilename(string value) { this->filename = value;};
	void setName(string value) { this->name = value;};
	void setPivot(ofPoint value) { this->pivotSat = value;};
	void setRot(ofVec3f value) { this->rot = value;};
	void setScl(ofVec3f value) { this->scl = value;};
	void setAuxPlace(ofVec3f value) { this->auxPlace = value;};
	void setVisible(bool value) { this->visible = value;};
	void setSelected(bool value) { this->selected = value;};
	void setTransparency(bool value) { this->transparency = value;};

	void setAppearance( appearType v_operational) { this->opColor = v_operational;};
	void setTemperature( appearType v_temperature) { this->tempColor = v_temperature;};


	ofxAssimpModelLoader *getModel() { if(hasModel) return &this->model; return NULL;};
	string getFilename() { return this->filename;};
	string getName() { return this->name;};
	ofVec3f getAuxPlace() {return this->auxPlace;};
	ofPoint getPivot() { return pivotSat;};


	bool isVisible() {return this->visible;};
	bool isLoaded() {return this->hasModel;};
	bool isSelected() {return this->selected;};
	bool isTransparent() {return this->transparency;};

	void setMyModel(SIMModelNode *newVal) { myModel = newVal;};
	SIMModelNode *getMyModel() {return myModel;};
	

private:

	SIMModelNode *myModel;

	appearType getAppearTypeFromOM();

	void applySatPivot();

	ofxAssimpModelLoader model;
	bool hasModel;
	appearType opColor;
	appearType tempColor;

	string filename;
	string name;
	ofPoint pivotSat;

	ofVec3f rot;
	ofVec3f scl;
	ofVec3f auxPlace;

	bool visible;
	bool selected;
	bool transparency;
};
#endif // !defined(EA_F875A6C6_EE20_43b7_A3D5_3E11667870D3__INCLUDED_)
