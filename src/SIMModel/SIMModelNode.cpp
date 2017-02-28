///////////////////////////////////////////////////////////
//  SIMModelNode.cpp
//  Implementation of the Class SIMModelNode
//  Created on:      08-out-2013 13:42:24
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "SIMModelNode.h"


SIMModelNode::SIMModelNode(){

}



SIMModelNode::~SIMModelNode(){

}


SIMModelParameter* SIMModelNode::getParam(string value){
	//ofLogVerbose() << "search param for:"<<  value;
	vector<SIMModelParameter*>::iterator itP;

	for(itP = this->paramList.begin(); itP != this->paramList.end(); itP++){
	//	ofLogVerbose() << "look["<<(*itP)->profile.GetUniqueCode()<<"]";
		if( (*itP)->profile.GetUniqueCode() == value) return (*itP);
	}
	return NULL;
}

SIMParameterOperationalMode* SIMModelNode::getOM(){
	//ofLogVerbose() << "search param for:"<<  value;
	vector<SIMModelParameter*>::iterator itP;

	for(itP = this->paramList.begin(); itP != this->paramList.end(); itP++){
	//	ofLogVerbose() << "look["<<(*itP)->profile.GetUniqueCode()<<"]";
		if( (*itP)->profile.GetType() == paramType::ptOPERATIONALMODE)
			return (SIMParameterOperationalMode*)(*itP);
	}
	return NULL;
}


//
////---------------------------------------------------------------------------
//// Factory function for creating new parser variables
//// This could as well be a function performing database queries.
//mu::value_type* SIMModelNode::AddVariable(const mu::char_type *a_szName, void *a_pUserData)
//{
//  // I don't want dynamic allocation here, so i used this static buffer
//  // If you want dynamic allocation you must allocate all variables dynamically
//  // in order to delete them later on. Or you find other ways to keep track of 
//  // variables that have been created implicitely.
//  static mu::value_type afValBuf[100];  
//  static int iVal = -1;
//
//  ++iVal;
//
//  mu::console() << _T("Generating new variable \"") 
//                << a_szName << std::dec << _T("\" (slots left: ")
//                << 99-iVal << _T(")")
//                << _T(" User data pointer is:") 
//                << std::hex << a_pUserData <<endl;
//  afValBuf[iVal] = 0;
//
//  if (iVal>=99)
//    throw mu::ParserError( _T("Variable buffer overflow.") );
//  else
//    return &afValBuf[iVal];
//}
//
//
//
//
//void	SIMModelNode::doEvaluationRound(double currentJD){
//
//
//	//// PROCESS THIS ( only if going down
//	//if( this->nodeList.empty() == false){
//	//ofLogVerbose("[EVALUATIONROUND]") << "down: " << this->profile.GetAcronymCBERS();
//	//this->GetMathParser()->evaluateExpressions();
//	//}
//
//
//	//// CALL SONS
//	//vector<SIMModelNode*>::iterator itN;
//	//for( itN = this->nodeList.begin(); itN != this->nodeList.end(); itN++ ){
//	//	// the evaluation does 2 round calculations, it calculates from root->leaf, than from leaf->root
//	//	(*itN)->doEvaluationRound(currentJD);
//	//}
//	//
//	//// PROCESS THIS AGAIN
//	//ofLogVerbose("[EVALUATIONROUND]") << "up: " << this->profile.GetAcronymCBERS();
//	//this->GetMathParser()->evaluateExpressions();
//
//
//}




SIMModelNode* SIMModelNode::getNode(string v_uniqueCode){
	return findNode(this,v_uniqueCode);;
}

SIMModelNode* SIMModelNode::findNode(SIMModelNode* start,string v_uniqueCode){
	
//	if(start->info != NULL) {
		//ofLogVerbose() << start->info->acronymCBERS << " - " << v_acronymCBERS;
	if(start->profile.GetUniqueCode() == v_uniqueCode) {
			//ofLogVerbose() << "found and returning:"<<start->info->acronymCBERS;
			return start;}
//	}
	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++){
		SIMModelNode* aux = this->findNode((*itN),v_uniqueCode);
		if (aux !=NULL) return aux;
	}

	return NULL;
}

SIMModelNode* SIMModelNode::findNode(SIMModelNode* start,SIMModelNode* desired){

	if(start == desired) return start;

	vector<SIMModelNode*>::iterator itN;

	for(itN = start->nodeList.begin(); itN != start->nodeList.end(); itN++)
		this->findNode((*itN),desired);

	return NULL;
}
