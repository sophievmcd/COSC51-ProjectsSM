//
 // p2.cc
 //
 // COSC 051 Fall 2021
 // Project #2 Code
 // <svm37>
 // In accordance with class policies and Georgetown’s Honor Code,
 // I certify that, with the exception of the class resources and those
 // items noted below, I have neither given nor received any assistance
 // on this project.
 //
 // Note that you may use without citation any help from our TAs,
 // professors, or any code taken from the course textbook.
 //
 

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std; 

int main() {
 
//this currently reads the file, calculates the number of drywall and flooring needed, total cost and weight for each room individually and outputs in chart
//need to calculate totals of sheets, boxes, cost, and weight

//variables to read from the file
string roomName = " ";
int side1Feet = 0;
int side1Inch = 0;
int side2Feet = 0;
int side2Inch = 0;
int ceilingFeet = 0;
int ceilingInch = 0;
int doorNumber = 0;
int windowNumber = 0;
int windowWidth = 0;
int windowHeight = 0;

//other
string overridevalue = " "; 
string N = "N"; 
string Y = "Y"; 
bool error = false; 

 //constants
  const int DOOR_AREA = 3024;
  const double DRYWALL_SHEET_AREA = 4608;
  const double DRYWALL_COST_PER_SHEET = 14.28;
  const double DRYWALL_WEIGHT_PER_SHEET = 35.27;
  const double FLOORING_BOX_AREA = 3427.2;
  const double FLOORING_COST_PER_BOX = 52.12;
  const double FLOORING_WEIGHT_PER_BOX = 53;
  //variables that will be calculated
  int roomLength = 0;
  int roomWidth = 0;
  int ceilingHeight = 0;
  int allDoorArea = 0;
  int windowArea = 0;
  int allWindowArea = 0;
  int floorArea = 0;
  int ceilingArea = 0;
  int wallArea = 0;
  int wallAndCeilingArea = 0;
  double drywallSheetNumber = 0;
  double tenPercentSheetNumber = 0;
  int finalSheetNumber = 0;
  double flooringBoxNumber = 0;
  double tenPercentBoxNumber = 0;
  int finalBoxNumber = 0;
  double sheetCost = 0;
  double boxCost = 0;
  double sheetWeight = 0;
  double boxWeight = 0;
  double totalCost = 0;
  double totalWeight = 0;

// variables for final totals
  int fullHouseSheetNumber = 0;
  int fullHouseBoxNumber = 0;
  double fullHouseCost = 0;
  double fullHouseWeight = 0;
  
string filename = " ";
ifstream inputFile;

//instructions
cout << "This program estimates the amount of drywall and flooring needed to renovate multiple rooms of a house." << endl;
cout << endl;
cout << "This program takes as input a file name for a file of the format: " << endl;
cout << endl;
cout << "<room name> <side 1 ft> <side 1 in> <side 2 ft> <side 2 in> <ceiling ft> <ceiling in> <num doors> <num windows> <window width> <window height>" << endl;
cout << endl;
cout << "If there are errors with the measurements the program will output an error message and will not include the room with errors in the final calculations for materials, cost and weight." << endl; 
cout << endl;

//reading from the file
cout << "Please enter the file name to use: " << endl;
cin >> filename;

inputFile.open(filename.c_str());

//output chart header
cout <<endl;
cout << setw(10) << "Room" << setw(18) << "Drywall Sheets" << setw(18) << "Flooring Boxes" << setw(10) << "Cost" << setw(10) << "Weight" << endl;
cout << "-------------------------------------------------------------------";

//read file and output (only first row)
while (inputFile >> roomName >> side1Feet >> side1Inch >> side2Feet >> side2Inch >> ceilingFeet >> ceilingInch >> doorNumber >> windowNumber >> windowWidth >> windowHeight >> overridevalue){
 
 //set error bool equal to false
  error = false; 

//output everything for the room
//cout << "Room Name: " << roomName << endl;
//cout << "Side 1 Feet: " << side1Feet << endl;
//cout << "Side 1 Inches: " << side1Inch << endl;
//cout << "Side 2 Feet: " << side2Feet << endl;
//cout << "Side 2 Inches: " << side2Inch << endl;
//cout << "Ceiling Feet:  " << ceilingFeet << endl;
//cout << "Ceiling Inches: " << ceilingInch << endl;
//cout << "Number of Doors: " << doorNumber << endl;
//cout << "Number of Windows: " << windowNumber << endl;
//cout << "Window Width: " << windowWidth << endl;
//cout << "Window Height: " << windowHeight << endl;
//cout << "Override Value:" << overridevalue << endl;

//run program to calculate all the information
  //calculating room length
    roomLength = side1Inch + (side1Feet * 12);
    //cout << "Length of room in inches: " << roomLength << endl;

  //calculating room width
    roomWidth = side2Inch + (side2Feet * 12); 
    //cout << "Width of room in inches: " << roomWidth << endl;

  //calculating ceiling height
    ceilingHeight = ceilingInch + (ceilingFeet * 12);   
    //cout << "Ceiling height in inches: " << ceilingHeight << endl;

  //calculating door and window area
    allDoorArea = doorNumber * DOOR_AREA;
    //cout << "Total area of doors: " << allDoorArea << endl; 
    windowArea = windowHeight * windowWidth;
    //cout << "Area of individual windows: " << windowArea << endl;
    allWindowArea = windowArea * windowNumber;
    //cout << "Area of all windows: " << allWindowArea << endl;

  //calculate area of wall and ceiling 
    floorArea = roomLength * roomWidth;
    //cout << "Area of the floor: " << floorArea << endl;
    ceilingArea = roomLength * roomWidth;
    //cout << "Area of the ceiling: " << ceilingArea << endl;
    wallArea = ((roomWidth * ceilingHeight * 2) + (roomLength * ceilingHeight * 2)) - allDoorArea - allWindowArea; 
    //cout << "Area of the wall: " << wallArea << endl;
    wallAndCeilingArea = wallArea + ceilingArea;
    //cout << "Area of wall and ceiling: " << wallAndCeilingArea << endl;
    cout << endl;

    //round to two decimal places
      cout << fixed;
    cout << setprecision(2);

    //calculate drywall sheets needed
      drywallSheetNumber = ceil (wallAndCeilingArea/DRYWALL_SHEET_AREA); 
      //cout << "Drywall Sheet Number: " << drywallSheetNumber << endl;
      tenPercentSheetNumber = (drywallSheetNumber/10);
      //cout << "Ten Percent of Sheet Number: " << tenPercentSheetNumber << endl;
      finalSheetNumber = ceil (drywallSheetNumber + tenPercentSheetNumber);
      //cout << "Drywall Sheets Needed: " << finalSheetNumber << endl;

    //calculate flooring boxes needed
      flooringBoxNumber = ceil (floorArea/FLOORING_BOX_AREA); 
      //cout << "Flooring Box Number: " << flooringBoxNumber << endl;
      tenPercentBoxNumber = flooringBoxNumber/10;
      //cout << "Ten Percent of Box Number: " << tenPercentBoxNumber << endl;
      finalBoxNumber = ceil (flooringBoxNumber + tenPercentBoxNumber);
      //cout << "Flooring Boxes Needed:" << finalBoxNumber << endl;

    //calculate final sheet and box costs 
      sheetCost = finalSheetNumber * DRYWALL_COST_PER_SHEET;
      boxCost = finalBoxNumber * FLOORING_COST_PER_BOX;
      //cout << "Drywall Cost: " << sheetCost << endl;
      //cout << "Flooring Cost: " << boxCost << endl;

    //calculate final sheet and box weights 
      sheetWeight = finalSheetNumber * DRYWALL_WEIGHT_PER_SHEET; 
      boxWeight = finalBoxNumber * FLOORING_WEIGHT_PER_BOX;
      //cout << "Drywall Weight: " << sheetWeight << endl;
      //cout << "Flooring Weight: " << boxWeight << endl;

    //calculate total cost and weight
      totalCost = sheetCost + boxCost;
      totalWeight = sheetWeight + boxWeight; 
      //cout << "Total Cost: " << totalCost << endl;
      //cout << "Total Weight: " << totalWeight << endl;

    //if window missing measurements (window count not zero but measurements are), windows missing counts, (measurements are not zero but count is), door and window area greater than wall area - print message to describe these and stop

    //if override is N
    if (overridevalue == N) {
      if (side1Feet < 6) {
       cout << "Wall length 1 for " << roomName << " of " << side1Feet << " is under minimum of 6 feet."<<endl;
        error = true; 
        }
      if (side2Feet < 6) {
       cout << "Wall length 2 for " << roomName << " of " << side2Feet << " is under minimum of 6 feet."<<endl;
        error = true;  
        }
      if ((side1Feet > 24) || ((side1Feet == 24) && (side1Inch > 0))) {
        cout << "Wall length 1 for " << roomName << " is over maximum of 24 feet."<<endl;
        error = true; 
        }
      if ((side2Feet > 24) || ((side2Feet == 24) && (side2Inch > 0))) {
       cout << "Wall length 2 for " << roomName << " is over maximum of 24 feet."<<endl;
        error = true;  
        }
      if ((ceilingFeet > 14) || ((ceilingFeet == 14) && (ceilingInch > 0))) {
        cout << "Ceiling Height for " << roomName << " is over maximum of 14 feet."<<endl;
        error = true; 
       }
      if (ceilingFeet < 7) {
        cout << "Ceiling Height for " << roomName << " of " << ceilingFeet << " is under minimum of 7 feet."<<endl;
        error = true; 
       }
    }
//    cout << error; 
      if ((overridevalue == N) || (overridevalue == Y)){
        //check negative doors, windows, or window measurements
        if (doorNumber < 0) {  
          cout << "Door Number for " << roomName <<  " cannot be less than 0."<<endl;
          error = true; 
          }
        if (windowNumber < 0) {  
          cout << "Window Number for " << roomName <<  " cannot be less than 0."<<endl;
          error = true; 
          }
        if (windowWidth < 0) {  
          cout << "Window Width for " << roomName <<  " cannot be less than 0."<<endl;
          error = true; 
          }
        if (windowHeight < 0) {  
          cout << "Window Height for " << roomName <<  " cannot be less than 0."<<endl;
          error = true; 
          }
          
        //check inch measurements
        //side 1
       if (side1Inch < 0){
          cout << roomName <<" inch measurements for side 1 of " << side1Inch <<" cannot be less than 0."<<endl;
          error = true; 
         }
        if (side1Inch > 11){
          cout << roomName << " inch measurements for side 1 of " << side1Inch << " cannot be greater than 11."<<endl; 
          error = true; 
          } 
        //side 2
        if (side2Inch < 0){
         cout << roomName <<" inch measurements for side 2 of " << side2Inch << " cannot be less than 0."<<endl;
         error = true;
          }
        if (side2Inch > 11){
          cout << roomName << " inch measurements for side 2 of " << side2Inch << " cannot be greater than 11."<<endl;
          error = true; 
          }
        //ceiling
        if (ceilingInch < 0){
          cout << roomName <<" inch measurements for ceiling height of " << ceilingInch << " cannot be less than 0."<<endl;
          error = true;
          }
        if (ceilingInch > 11){
          cout << roomName << " inch measurements for ceiling height of " << ceilingInch << " cannot be greater than 11."<<endl;
          error = true; 
         }  
        //other possible errors
        //wall area less than door and window area
      if (wallArea <= 0) {
        cout << "Error: " << roomName << " window and door area cannot be greater than wall area"; 
        return 0;
        }
       //no windows but window measurements
      if (windowNumber == 0) {
       if ((windowWidth > 0) || (windowHeight > 0)) {
          cout << "Error: " << roomName << " has no window count but has window measurements.";
          return 0;
          }
        }
     if (windowNumber > 0){
       if ((windowWidth == 0) && (windowHeight == 0)) {
          cout << "Error: " << roomName << " has window count but no window measurements.";
         return 0;
          }
        if ((windowWidth == 0) || (windowHeight == 0)) {
          cout << "Error: " << roomName << " has window count but only one window measurement.";
          return 0;
          }
        }
      }  

    //output data if there are no errors
    if (!error){
        cout << setw (10) << roomName << setw (18)<< finalSheetNumber << setw (18) << finalBoxNumber << setw (10) << totalCost << setw (10) << totalWeight;
        }

    //add to full house totals
    if (!error) {
    fullHouseSheetNumber = fullHouseSheetNumber + finalSheetNumber; 
    fullHouseBoxNumber = fullHouseBoxNumber + finalBoxNumber;
    fullHouseCost = fullHouseCost + totalCost;
    fullHouseWeight = fullHouseWeight + totalWeight; 
    }      
}
//output totals
cout <<endl; 
cout << "-------------------------------------------------------------------"<< endl;
cout << setw (10) << "Total: " << setw (18)<< fullHouseSheetNumber << setw(18) << fullHouseBoxNumber << setw(10) << fullHouseCost << setw (10) << fullHouseWeight << endl; 

 return 0;
 }
