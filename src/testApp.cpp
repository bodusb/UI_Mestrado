#include "testApp.h"

#include "System\mouseClick.h"
#include "System\LogView.h"
#include "System\TimelineView.h"
#include "System\SystemView.h"

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel(OF_LOG_SILENT);

	ofLogVerbose("[INTERFACE]") << " Starting interface";

	this->splash.loadImage("GUI/splash1.png");
	this->loaded = false;
	this->showSplash = true;

}

void testApp::exit() {
	delete action;

}


void testApp::loadSystem(){
	// setup model
	this->controller = new ModelControl();

	ofLogVerbose("[INTERFACE]") << "Model OK";
	// setup screen
	s = new iScreen();  // always create the screen before the action !!!!!
	ofSetWindowTitle("Interactive Simulator for CBERS 3 - Iron Release 2");

	ofBackground(ofColor::black);
	ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	GLfloat ambient[] = {0.2, 0.2f, 0.2f, 0.2f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	GLfloat position[] = { 0.5f, 0.5f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHT0);

	ofEnableAlphaBlending();
	ofEnableAntiAliasing();

	// setup userAction

	action = new iAction();

	action->m_iScreen = this->s;  
	action->logPANEL = ((LogView*)s->getView("logview"))->getGui(); // trick to add on the iAction the loglink
	s->myAction = action;


	((SystemView*)s->getView("systemview"))->startView(); // trick to start the view after loaded.
	((TimelineView*)s->getView("timelineview"))->startView(); // trick to start the view after loaded.

	action->modelController = this->controller;
	controller->myAction = action;
	action->spreadAction();

	ofLogVerbose("[INTERFACE]") << " ---------------- Interface started";

}





//--------------------------------------------------------------
void testApp::update(){
	//	ofLogVerbose("[INTERFACE]") << " update";

	if(this->showSplash == false){

		if(this->loaded == true){

			//ofLogVerbose("[INTERFACE]") << "Update";
			// call update all nodes... 

			// collect datas, request simulator etc. etc. 
			action->update();


		} else {
			ofLogVerbose("[INTERFACE]") << " Starting to load the system";
			this->loadSystem();
			loaded = true;
			ofSystemAlertDialog("Setup over");
		}
	} else {
		ofLogVerbose("[INTERFACE]") << " NO SPLASH YET";
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	//ofLogVerbose("[INTERFACE]") << " draw";

	if( showSplash == false) {

		if(this->loaded == true){

			//ofBackgroundGradient(ofColor::black,ofColor::darkGray);

			//ofLogVerbose("[INTERFACE]") << "Start Draw";

			/*ofPushMatrix();
			ofPushStyle();
			ofPushView();
			ofEnableLighting();
			ofEnableAlphaBlending();*/


			//Draw backgrounds
			s->drawBackgrounds();


			//	ofDisableAlphaBlending();
			//	ofDisableLighting();
			//ofPopView();
			//ofPopStyle();
			//ofPopMatrix();


			//Draw Views
			s->draw();
			//ofLogVerbose("[INTERFACE]") << "Views ok";
			s->drawBackgrounds();
			//Draw closest pointer
			action->drawClosestGuide();
			//ofLogVerbose("[INTERFACE]") << "closest pointer ok";

			//	ofSetColor(ofColor::yellow);

			ofSetColor(ofColor::yellow);
			ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, ofGetHeight() - 15);

		}
	} else {

		splash.draw(0,0,ofGetWidth(),ofGetHeight());
		this->showSplash = false;
		ofLogVerbose("[INTERFACE]") << " Splash drawn";
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	if(key == OF_KEY_F11)	
		ofToggleFullscreen();

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

	if(this->loaded)
		action->selectingAction(0,ofPoint(x,y));

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	if(this->loaded)
		action->startAction(button,ofPoint(x,y));

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(this->loaded)
		action->finishAction(button,ofPoint(x,y));
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	if(this->loaded){
		ofLogVerbose("[INTERFACE]") << "[" + ofGetTimestampString() + "] - Resized";
		s->updateViews();
	}
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
