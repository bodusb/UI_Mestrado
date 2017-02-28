///////////////////////////////////////////////////////////
//  NodeRDT.cpp
//  Implementation of the Class NodeRDT
//  Created on:      06-set-2013 14:20:03
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "NodeRDT.h"

#include "SIMModelNode.h"

NodeRDT::NodeRDT(){

	this->open = true;
	this->selected = false;

}



NodeRDT::~NodeRDT(){

}



appearType NodeRDT::getAppearTypeFromOM(){



		SIMParameterOperationalMode *om  = this->myModel->getOM();

		if (om != NULL){

			SIMOperationalModeObject *omo = om->getActive();

			if(omo != NULL){
				return omo->GetAppearance();
			}


		}


	return appearType::aptERROR;
}