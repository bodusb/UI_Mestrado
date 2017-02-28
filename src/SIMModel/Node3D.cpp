///////////////////////////////////////////////////////////
//  Node3D.cpp
//  Implementation of the Class Node3D
//  Created on:      06-set-2013 14:20:04
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "Node3D.h"

#include "SIMModelNode.h"
#include "SIMOperationalModeObject.h"
#include "SIMParameterOperationalMode.h"


Node3D::Node3D(){
	this->myModel = NULL;
}

Node3D::~Node3D(){
	this->pivotSat = ofPoint(0);
	this->scl = ofVec3f(0);

	this->visible = true;
	this->selected = false;
	this->hasModel = false;

}

void Node3D::draw(){
	if( this->hasModel == true){
		//ofLogVerbose("[NODE3D]") << " hasModel";
		//if(visible){
			//ofLogVerbose("[NODE3D]") << " Draw - model :"<< this->name;

			ofPushMatrix();
			ofPushView();
				// / glEnable(GL_DEPTH_TEST);   //shows completely dark without thi
				// / glEnable(GL_LIGHTING);  // disappears without this
				//glEnable(GL_LIGHT0);

				this->applySatPivot();		// apply pivot
			

			
				//ofSetColor(255, 255, 255, 255);
				//string x = this->name;
				//ofEnableAntiAliasing();
			
				ofScale(this->scl.x,this->scl.y,this->scl.z);
				//if(selected == true) ofScale(2,2,2);	// Apply selected change
				this->model.createLightsFromAiModel();
				//ofSetColor(ofColor::blue);
				if (selected == true) {

		//					ofEnableDepthTest();
		glEnable(GL_DEPTH_TEST);
	//	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);

				switch(getAppearTypeFromOM()){
						case appearType::aptOFF: ofSetColor(ofColor::beige,80);break;// ofLogVerbose("[NODE3D]") << " OFF ";
						case appearType::aptFAILURE: ofSetColor(ofColor::red,80);break;// ofLogVerbose("[NODE3D]") << " FAILURE "; break;
						case appearType::aptFUNCTIONAL: ofSetColor(ofColor::green,80);break;//ofLogVerbose("[NODE3D]") << " FUNCTIONAL "; break;
						case appearType::aptSTANDBY: ofSetColor(ofColor::blue,80);break;// ofLogVerbose("[NODE3D]") << " STANDBY "; break;
						default: ofSetColor(ofColor::darkGray,50);break;// ofLogVerbose("[NODE3D]") << " Default ";break;
						};
					this->model.drawFaces();


					ofSetLineWidth(1);
						switch(getAppearTypeFromOM()){
						case appearType::aptOFF: ofSetColor(ofColor::white);break;// ofLogVerbose("[NODE3D]") << " OFF ";
						case appearType::aptFAILURE: ofSetColor(ofColor::lightSalmon);break;// ofLogVerbose("[NODE3D]") << " FAILURE "; break;
						case appearType::aptFUNCTIONAL: ofSetColor(ofColor::lightGreen);break;//ofLogVerbose("[NODE3D]") << " FUNCTIONAL "; break;
						case appearType::aptSTANDBY: ofSetColor(ofColor::lightBlue);break;// ofLogVerbose("[NODE3D]") << " STANDBY "; break;
						default: ofSetColor(ofColor::lightGray);break;// ofLogVerbose("[NODE3D]") << " Default ";break;
						};
						this->model.drawWireframe();


					//ofLogVerbose("[NODE3D]") << " ---- FACES ";

						//ofDisableAlphaBlending();
		glDisable(GL_DEPTH_TEST);
		//ofDisableDepthTest();

				} else {

					glEnable(GL_DEPTH_TEST);
					ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
					ofSetLineWidth(1);
						switch(getAppearTypeFromOM()){
						case appearType::aptOFF: ofSetColor(ofColor::white,40);break;// ofLogVerbose("[NODE3D]") << " OFF ";
						case appearType::aptFAILURE: ofSetColor(ofColor::red);break;// ofLogVerbose("[NODE3D]") << " FAILURE "; break;
						case appearType::aptFUNCTIONAL: ofSetColor(ofColor::lightGreen,40);break;//ofLogVerbose("[NODE3D]") << " FUNCTIONAL "; break;
						case appearType::aptSTANDBY: ofSetColor(ofColor::lightBlue,40);break;// ofLogVerbose("[NODE3D]") << " STANDBY "; break;
						default: ofSetColor(ofColor::lightGray,40);break;// ofLogVerbose("[NODE3D]") << " Default ";break;
						};

						//this->model.createLightsFromAiModel();
						this->model.drawWireframe();
						//ofLogVerbose("[NODE3D]") << " ---- WIREFRAME ";




					ofDisableBlendMode();
					glDisable(GL_DEPTH_TEST);
				}


				//ofDisableAntiAliasing();
				// / glDisable(GL_LIGHTING);
				// / glDisable(GL_DEPTH_TEST);
			ofPopView();
			ofPopMatrix();
	//	}
	}
}

void Node3D::drawDefault(){
	if( this->hasModel == true){
		//ofLogVerbose("[NODE3D]") << " hasModel";
		//if(visible){
			//ofLogVerbose("[NODE3D]") << " Draw - model :"<< this->name;

			ofPushMatrix();
			ofPushView();
				// / glEnable(GL_DEPTH_TEST);   //shows completely dark without thi
				// / glEnable(GL_LIGHTING);  // disappears without this
				//glEnable(GL_LIGHT0);

				this->applySatPivot();		// apply pivot
			

			
				//ofSetColor(255, 255, 255, 255);
				//string x = this->name;
				//ofEnableAntiAliasing();
			
				ofScale(this->scl.x,this->scl.y,this->scl.z);
				//if(selected == true) ofScale(2,2,2);	// Apply selected change
				//this->model.createLightsFromAiModel();
				//ofSetColor(ofColor::blue);
				if (selected == true) {

					ofSetColor(ofColor::white);// ofLogVerbose("[NODE3D]") << " Default ";break;
					this->model.drawFaces();
					//ofLogVerbose("[NODE3D]") << " ---- FACES ";
				} else {

					ofSetColor(ofColor::white,30);// ofLogVerbose("[NODE3D]") << " Default ";break;
					this->model.drawWireframe();
					//ofLogVerbose("[NODE3D]") << " ---- WIREFRAME ";
				}

				//ofDisableAntiAliasing();
				// / glDisable(GL_LIGHTING);
				// / glDisable(GL_DEPTH_TEST);
			ofPopView();
			ofPopMatrix();
		}
}

void Node3D::applySatPivot(){
	ofTranslate(this->pivotSat);
};

bool Node3D::loadModel(){

	ofLogVerbose() << "[INTERFACE][Load3DModel] Loading: "<<this->filename;
	if(this->model.loadModel(this->filename,true)){
		this->model.setScale(scl[0],scl[1],scl[2]);
		ofLogVerbose() << "[INTERFACE][Load3DModel]  - loaded";
		this->hasModel = true;
		return true;
	} else {
		if( this->filename == "Missing Filename" ) {ofLogVerbose() << "[INTERFACE][Load3DModel] - Missing Filename"; 
		this->hasModel = false;
		}
		else {
		ofSystemAlertDialog("Error opening: " + this->filename);
		ofExit(0);
		}
	}
	return false;
}

appearType Node3D::getAppearTypeFromOM(){

	if(this->myModel != NULL){
		
		SIMParameterOperationalMode *om  = this->myModel->getOM();

		if (om != NULL){

			SIMOperationalModeObject *omo = om->getActive();

			if(omo != NULL){
				return omo->GetAppearance();
			}


		}




	}

	return appearType::aptERROR;
}