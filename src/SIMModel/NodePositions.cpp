///////////////////////////////////////////////////////////
//  NodePositions.cpp
//  Implementation of the Class NodePositions
//  Created on:      10-set-2013 14:33:20
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "NodePositions.h"

#include "SIMModelNode.h"
#include "SIMModelParameter.h"
#include "SIMParameterValue.h"
#include "SIMParameterOperationalMode.h"


NodePositions::NodePositions(){
	this->latitude = 0;
	this->longitude = 0;
	this->rectangular = ofPoint(0);
	this->myNode = NULL;
}



NodePositions::~NodePositions(){

}


void NodePositions::updatePosition(){

	ofLogVerbose() << "Start Update Position of " << this->myNode->profile.GetUniqueCode();

	SIMModelParameter *aux;

	aux = this->myNode->getParam(this->myNode->profile.GetUniqueCode()+"Lat");
	if(aux == NULL) {	ofLogFatalError("[USEPARAMETER]") << "Error on " << this->myNode->profile.GetUniqueCode()+"Lat" ;
						ofSystemAlertDialog("ERROR ACQUIRING " + this->myNode->profile.GetUniqueCode() + "parameter"); exit(0); }
	ofLogVerbose() << aux->profile.GetType() << "-" << (*aux->getValueVariable());
	if(aux != NULL) 
		if(aux->profile.GetType() == paramType::ptDATAVALUE) 
			this->latitude = ((SIMParameterValue*)aux)->getValue();

	ofLogVerbose() << "latitude: " << this->latitude;

	aux = this->myNode->getParam(this->myNode->profile.GetUniqueCode()+"Lon");
	if(aux == NULL) {	ofLogFatalError("[USEPARAMETER]") << "Error on " << this->myNode->profile.GetUniqueCode()+"Lon" ;
						ofSystemAlertDialog("ERROR ACQUIRING " + this->myNode->profile.GetUniqueCode() + "parameter"); exit(0); }
	if(aux != NULL) 
		if(aux->profile.GetType()== paramType::ptDATAVALUE) 
			this->longitude =  ((SIMParameterValue*)aux)->getValue();

	ofLogVerbose() << "longitude: " << this->longitude;

	aux = this->myNode->getParam(this->myNode->profile.GetUniqueCode()+"Alt");
	if(aux == NULL) {	ofLogFatalError("[USEPARAMETER]") << "Error on " << this->myNode->profile.GetUniqueCode()+"Alt" ;
						ofSystemAlertDialog("ERROR ACQUIRING " + this->myNode->profile.GetUniqueCode() + "parameter"); exit(0); }
	if(aux != NULL) 
		if(aux->profile.GetType() == paramType::ptDATAVALUE) 
			this->altitude =  6378.135 + ((SIMParameterValue*)aux)->getValue();			
	
	ofLogVerbose() << "altitude: " << this->altitude;

	this->latLongToRectangular();

	ofLogVerbose() << "end Update Position";

}

void NodePositions::updatePosition(double v_lat, double v_long, double v_alt){
	ofLogVerbose() << "Start Update Position";
	this->altitude = v_alt;
	this->latitude = v_lat;
	this->longitude = v_long;
	this->latLongToRectangular();
	ofLogVerbose() << "end Update Position:" << this->rectangular;
}

void NodePositions::updatePosition(ofPoint v_rect){
	this->rectangular = v_rect;

}




/**
 *    x (in m) = Latitude  * 60 * 1852
 * 
 *    y (in m) =  (PI/180) * cos(Longitude) * ( 637813.7^2 /
 * sqrt( (637813.7 * cos(Longitude))^2 + (635675.23 *
 * sin(Longitude))^2 ) )  <--- from ManoM's link
 * 
 *   z (in m) = Altitude (in m) 
 */
void NodePositions::latLongToRectangular(){

	//float lat = latitude.x + (latitude.y)/60 + (latitude.z)/3600;
	//	if(latitudeDirection == "north") lat *=-1;                           // to adjust originally was south
	//float lon = longitude.x + (longitude.y)/60 + (longitude.z)/3600;
	//	if(longitudeDirection == "west") lon *=-1;

	ofQuaternion latRot, longRot;
	ofVec3f center;
	center = ofVec3f(0,0,altitude);
	
	latRot.makeRotate(latitude, 1, 0, 0);
    longRot.makeRotate(longitude, 0, 1, 0);
	rectangular = latRot * longRot * center;


	this->rectangularToDraw = rectangular;
	this->rectangularToDraw.y *= -1;
	// correct to match with the model

	//rectangular.scale(0.04);
	

	//rectangular.x = lat * 60 * 1852; 
	//rectangular.y = (PI/180) * cos(lon) * ( pow(637813.7,2) / sqrt( pow((637813.7 * cos(lon)),2) + pow((635675.23 * sin(lon)),2) ) );
	
	//rectangular.z = altitude;
	
}