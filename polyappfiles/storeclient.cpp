//This file contains a main program to build and display a list
//that utilizes inheritance and polymorphism.
//TV and VCR, which are all derived from
//the same base class Appliance,  Are stored in a vector used to maintain
//the list of appliances in inventory. The vector consists of base class
//pointers to each appliance.
// Author: Thomas Sotherland
// Due:    4/21/24
// Purpose:This program runs our functions created in the other two files and outputs
//         a repair list of customers with info on their device and estimated cost
#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include "polyapp.h"

using namespace std;

Appliance* getAppliance(int code);				     // prototype: creates an appliance
void printList(vector<Appliance*> repairList);      // prototype: prints the list appliances
ifstream infile;									// global file pointer to read data from the input file

int main()
{
        vector<Appliance*> repairList;
		Appliance* AppPtr;
		int code;
		infile.open("repairlist.txt");

		infile >> code; // get a menu code before entering the loop		

		while (code != 3)
		{
			AppPtr = getAppliance(code);
			repairList.push_back(AppPtr); //this adds code to the vector,
										  //the object is dynamically declare
										  //in the heap.
			infile >> code;
		}

		//add a base class object to the end of the list to test your base class functions
		repairList.push_back(new Appliance("END", "TEST"));
		//print the list
		printList(repairList);
		return 0;
}
//-----------------------------------------------------
// Function: getAppliance
// Inputs data for an appliance
// Create a new object based on the type of appliance
// and returns a pointer to that appliance
//-----------------------------------------------------
Appliance* getAppliance(int code)
{
	//Declare the appropriate variables to popluate your object.
	Appliance* nuApp;
	string custName, manuFact;
	int modelAge, numTapes;

	//input those variables to popluate your object.
	infile.ignore();
	getline(infile, custName);
	getline(infile, manuFact);
	//add those variables as arguments to populate your object.
	if (code == 1)
	{
		infile >> modelAge;
		return new TV(custName, manuFact, modelAge);
	}
	else
	{
		infile >> numTapes;
		return new VCR(custName, manuFact, numTapes);
	}
}
//-----------------------------------------------------
// Function: printList
// Prints the list of appliance
//-----------------------------------------------------
void printList(vector<Appliance*> repairList)
{
	cout << "The Repair List :" << endl;
	for (int k = 0; k < repairList.size(); k++)
	{
		cout << "------------------------------------" << endl;
		repairList[k]->EstimateService();   //repairList.at(k)->EstimateService()
		repairList[k]->printObject();		//will also work with vectors
	}
}