// Author: Thomas Sotherland
// Due:    4/21/24
// Purpose:This file is used to define our classes and the datatypes we'll be using in the program
#include <iostream>
#include <string>

using namespace std;
//=========================Appliance class definition=========================
//-----------------------------------------------------------------------
class Appliance {
protected:
    string custName;
    string manuFact;
    double estCost;

public:
    Appliance(string custName, string manuFact);

    // Getter and setter functions for custName, manuFact, estCost

    virtual void EstimateService();
    virtual void printObject();
};




//-----------------------------------------------------------------------
//=========================TV class definition=========================
//-----------------------------------------------------------------------
class TV : public Appliance {
private:
    int modelAge;

public:
    TV(string custName, string manuFact, int modelAge);

    // Getter and setter for modelAge

    virtual void EstimateService() override;
    virtual void printObject() override;
};




//-----------------------------------------------------------------------
//=========================VCR class definition=========================
//-----------------------------------------------------------------------
class VCR : public Appliance {
private:
    int numTapes;

public:
    VCR(string custName, string manuFact, int numTapes);

    // Getter and setter for numTapes

    virtual void EstimateService() override;
    virtual void printObject() override;
};




//-----------------------------------------------------------------------
