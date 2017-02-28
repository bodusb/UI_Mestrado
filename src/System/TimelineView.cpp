///////////////////////////////////////////////////////////
//  TimelineView.cpp
//  Implementation of the Class TimelineView
//  Created on:      05-set-2013 16:22:49
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "TimelineView.h"

#include "iScreen.h"
#include "iAction.h"
#include "ModelControl.h"


TimelineView::TimelineView(){



}

TimelineView::~TimelineView(){

}

void TimelineView::startView(){

	
	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 

	gui = new ofxUICanvas();

	gui->setTheme(OFX_UI_THEME_HACKER);
	
	//gui->setColorBack(ofxUIColor::black);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
  
	gui->addLabel("Current Time:");
	
	Cyear = gui->addLabel("0000");
	gui->addLabel("/");
	Cmon = gui->addLabel("00");
	gui->addLabel("/");
	Cday = gui->addLabel("00");
	gui->addLabel("  ");
	Chour = gui->addLabel("00");
	gui->addLabel(":");
	Cmin = gui->addLabel("00");
	gui->addLabel(":");
	Csec = gui->addLabel("00");

	//gui->addWidgetLeft( new ofxUILabel("Simulated Time:",OFX_UI_FONT_LARGE));
	gui->addLabel("Simulated Time:");

	Syear = gui->addLabel("0000");
	gui->addLabel("/");
	Smon = gui->addLabel("00");
	gui->addLabel("/");
	Sday = gui->addLabel("00");
	gui->addLabel("  ");
	Shour = gui->addLabel("00");
	gui->addLabel(":");
	Smin = gui->addLabel("00");
	gui->addLabel(":");
	Ssec = gui->addLabel("00");	


	//gui->addWidget( new ofxUILabel("Computer Time:...................................", OFX_UI_FONT_LARGE));
	//gui->addWidget( new ofxUIToggle("[RUN]",false,16,16,0, OFX_UI_FONT_LARGE));  //acertar variavel que envia um passo

	//float year = 2014;
	//float *ptry = &year;
	 //gui->addFPSSlider("FPS");


	//gui->addWidgetLeft( new ofxUILabelDynamic(4,"currentYear",ptry));//this->myScreen->myAction->currentDate.Year));
	/*gui->addWidgetEastOf(  new ofxUILabel("sepYM", " / ", OFX_UI_FONT_MEDIUM),"currentYear");
	gui->addWidgetEastOf( new ofxUILabelDynamic(4,"currentMin",&this->myScreen->myAction->currentDate.Min),"sepYM");
	gui->addWidgetEastOf(  new ofxUILabel("sepMinSec", " / ", OFX_UI_FONT_MEDIUM),"currentMin");
	gui->addWidgetEastOf( new ofxUILabelDynamic(4,"currentSec",&this->myScreen->myAction->currentDate.Sec),"sepMinSec");*/

	//gui->addWidgetEastOf( new ofxUILabel("pcTimer", &this->myScreen->myAction->currentTime, OFX_UI_FONT_MEDIUM),"pcTime");
	//gui->addWidgetEastOf( new ofxUILabel("simTime","SIMC Time: XXXX-XX-XX - XX:XX:XX", OFX_UI_FONT_MEDIUM),"[SCRIPT]");

	//gui->addWidgetEastOf( new ofxUIToggle("[RUN]",false,16,16,0,0),"[CONFIG]");  //acertar variavel que envia um passo
	//gui->addWidgetEastOf( new ofxUIToggle("[SIMC3 Slim]",false,16,16,0,0),"[SCRIPT]");
	//gui->addWidgetEastOf( new ofxUILabelButton("[STEP]",false),"[RUN]"); //acertar variavel que envia um passo

    //gui->addWidgetRight(new ofxUILabel("NUMBER DIALER", OFX_UI_FONT_MEDIUM));
   // gui->addWidgetEastOf(new ofxUINumberDialer(0.000,100.000,1.000,0.01,"dialer",OFX_UI_FONT_MEDIUM),"[SCRIPT]");


	this->resizeView();

	this->myScreen->myAction->addTolog("[TIMELINESTART]", " Times started");
}

void TimelineView::draw(){

	// as it is called every refresh, it will be used to update the clock label
	Cyear->setLabel( ofToString(this->myScreen->myAction->currentDate.Year));
	Cmon->setLabel( ofToString(this->myScreen->myAction->currentDate.Month));
	Cday->setLabel( ofToString(this->myScreen->myAction->currentDate.Day));
	Chour->setLabel( ofToString(this->myScreen->myAction->currentDate.Hour));
	Cmin->setLabel( ofToString(this->myScreen->myAction->currentDate.Min));
	Csec->setLabel( ofToString(this->myScreen->myAction->currentDate.Sec));
	
	
//	if(this->myScreen->myAction->followingCurrentTime){
		Syear->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Year));
		Smon->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Month));
		Sday->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Day));
		Shour->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Hour));
		Smin->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Min));
		Ssec->setLabel( ofToString(this->myScreen->myAction->simulatedDate.Sec));
//	} else {


//
	this->resizeView();

}

void TimelineView::panelEvent(ofxUIEventArgs& e){

}

void TimelineView::setContextPanel(){
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	

	//Start the SpaceView Context Panel
	panel = new ofxUIScrollableCanvas(0, 0, 300, ofGetHeight());  
	panel->setTheme(OFX_UI_THEME_HACKER);
	panel->setColorBack(ofxUIColor::black);
	panel->setScrollAreaToScreen();
    panel->setScrollableDirections(false, true);

	  
	//Set Timeline Profile
	panel->addWidgetDown(new ofxUILabel("Timeline Context Panel", OFX_UI_FONT_LARGE)); 


	//if(this->myScreen->myAction->modelController->getSimulatorStatus() == simStatus::

	panel->addWidgetDown(new ofxUILabel("NUMBER DIALER", OFX_UI_FONT_MEDIUM));

	panel->addNumberDialer("simYear",(int)2014,(int)2017,&this->myScreen->myAction->simulatedDate.Year,0);
	//panel->addSlider("simYear",2014,2017,&this->myScreen->myAction->simulatedDate.Year);
	panel->addNumberDialer("simMonth",0,12,&this->myScreen->myAction->simulatedDate.Month,1);

	switch((int)this->myScreen->myAction->simulatedDate.Month){
	case 2: {if(((int)this->myScreen->myAction->simulatedDate.Year % 4)==0 ){
		panel->addSlider("simDay",0,29,&this->myScreen->myAction->simulatedDate.Day); 
			} else {
				panel->addSlider("simDay",0,28,&this->myScreen->myAction->simulatedDate.Day);
			}
			break;}
	case 1:	case 3: case 5: case 7: case 8: case 10: case 12:
		panel->addSlider("simDay",0,31,&this->myScreen->myAction->simulatedDate.Day); break;
	case 4: case 6: case 9: case 11:
		panel->addSlider("simDay",0,30,&this->myScreen->myAction->simulatedDate.Day); break;
	}


	panel->addSlider("simHour",0,23,&this->myScreen->myAction->simulatedDate.Hour);
	panel->addSlider("simMin",0,59,&this->myScreen->myAction->simulatedDate.Min);
	panel->addSlider("simSec",0,59,&this->myScreen->myAction->simulatedDate.Sec);

	
	panel->autoSizeToFitWidgets();

	ofAddListener(panel->newGUIEvent, this, &TimelineView::panelEvent); 
}

void TimelineView::resizeView(){

	gui->autoSizeToFitWidgets();

	gui->setPosition(ofGetWidth()/2 - gui->getRect()->width/2, 10);

	
	//gui->setDimensions(this->vp->place.width,this->vp->place.height);

	//this->myScreen->myAction->addTolog("[INTERFACE]", "[" + ofGetTimestampString() + "] - System View Resized");
	//ofLogVerbose("[INTERFACE]") << "[" +  ofGetTimestampString() + "] - Time View Resized";
}