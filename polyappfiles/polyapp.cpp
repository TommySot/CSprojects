// Author: Thomas Sotherland
// Due:    4/21/24
// Purpose:This file is used to define our member functions and their constructors so that
//         we can easily use them in our main storeclient.cpp file
#include <iostream>
#include <string>
#include "polyapp.h"

using namespace std;
//=====================Aplliance class member functions======================
//-----------------------Appliance Constructor-----------------------------
Appliance::Appliance(string custName, string manuFact) {
    this->custName = custName;
    this->manuFact = manuFact;
    estCost = 0;
}

//-----------------------Appliance EstimateService-----------------------------
// Starts the estimate cost at zero before any calculations are made
void Appliance::EstimateService() {
    estCost = 0;
}
//-----------------------Appliance printObject-----------------------------
// Prints out customer info and the manufacturer type as well as est cost
void Appliance::printObject() {
    cout << "Customer Name  :" << custName << endl;
    cout << "Manufacture    :" << manuFact << endl;
    cout << "Estimated Cost :" << estCost << endl;
}

//=========================TV class member functions=========================
//-----------------------TV Constructor-----------------------------
TV::TV(string custName, string manuFact, int modelAge)
    : Appliance(custName, manuFact), modelAge(modelAge) {}


//-----------------------TV EstimateService-----------------------------
// Estimates price for client based on the modelAge of the TV
void TV::EstimateService() {
    if (modelAge >= 6)
        estCost = 150;
    else
        estCost = 50;
}

//-----------------------TV printObject-----------------------------
// Prints out TV object type and the model age of the TV
void TV::printObject() {
    cout << "-----TV-------" << endl;
    Appliance::printObject();
    cout << "Model Age     : " << modelAge << endl;
}

//====================VCR class member functions=========================
//-----------------------VCR Constructor-----------------------------
VCR::VCR(string custName, string manuFact, int numTapes)
    : Appliance(custName, manuFact), numTapes(numTapes) {}


//-----------------------VCR EstimateService-----------------------------
// Estimates price for client based on numTapes
void VCR::EstimateService() {
    if (numTapes > 1)
        estCost = 100;
    else
        estCost = 40;
}




//-----------------------VCR printObject-----------------------------
// Prints out vcr object type and num of tape drives
void VCR::printObject() {
    cout << "-----VCR-------" << endl;
    Appliance::printObject();
    cout << "Number of Tape Drives: " << numTapes << endl;
}













