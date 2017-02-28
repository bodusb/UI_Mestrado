#pragma once

#include "ofMain.h"

#include "System\iScreen.h"
#include "System\iAction.h"
#include "System\ModelControl.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void exit();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void loadSystem();

		iScreen *s;					//	Screen manager
		iAction *action;			//	interaction manager
		ModelControl *controller;	//	Model controller

		ofImage splash;

		bool loaded;
		bool showSplash;
		
};
