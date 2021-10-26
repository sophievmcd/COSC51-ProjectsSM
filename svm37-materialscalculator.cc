/** 
* COSC 051 Fall 2021
* Project #1 Code
* Due on: 29 September 2021* 
* Author: <svm37>
* In accordance with class policies and Georgetown’s Honor Code,
* I certify that, with the exception of the class resources and those
* items noted below, I have neither given nor received any assistance
* on this project.
* Note that you may use without citation any help from our TAs,
* professors, or any code taken from the course textbook.
*///Sophie McDowall

#include <iostream>
#include <iomanip>
#include <cmath> 
using namespace std;

int main() {

 //variables that will be input 
int lengthFeet = 0;
int lengthInches = 0;
int widthFeet = 0;
int widthInches = 0;
int ceilingFeet = 0;
int ceilingInches = 0;
int doorNumber = 0;
int windowNumber = 0;
int windowHeight = 0;
int windowLength = 0;
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

//instructions
  cout << "This program will give an estimate of the flooring and drywall needed for one rectangular room. You will be asked to input the measurements of the room (height, width, and length) in feet and inches, the number of doors (standard size) and the number and size of windows (measured in inches). Please round all measurements up to the nearest inch." << endl;
  cout << endl;
  cout << "The program will output the final number of drywall sheets needed, final number of flooring boxes needed, the cost and weight of the drywall and flooring and the total cost (in dollars) and weight (in pounds). It is assumed that each drywall sheet costs $14.28 and each box of flooring costs $52.12." << endl;
  cout << endl;
  cout << "When asked to input a value, type in the number and hit enter." << endl;
  cout << endl; 

//calculating room length
  cout << "Please input length of room in feet: ";
  cin >> lengthFeet;
  //cout << "Length of room in feet: " << lengthFeet << endl;

  cout << "Please input length of room in inches (remaining after feet): ";
  cin >> lengthInches;
  //cout << "Length of room in inches (remaining after feet): "<< lengthInches << endl;

  roomLength = lengthInches + (lengthFeet * 12);
  //cout << "Length of room in inches: " << roomLength << endl;

//calculating room width
  cout << "Please input width of room in feet: ";
  cin >> widthFeet;
  //cout << "Width of room in feet: " << widthFeet << endl;

  cout << "Please input length of room in inches (remaining after feet): ";
  cin >> widthInches;
  //cout << "Width of room in inches (remaining after feet): " << widthInches << endl;

  roomWidth = widthInches + (widthFeet * 12); 
  //cout << "Width of room in inches: " << roomWidth << endl;

//calculating ceiling height
  cout << "Please input ceiling height in feet: ";
  cin >> ceilingFeet;
  //cout << "Ceiling height in feet: " << ceilingFeet << endl;

 cout << "Please input ceiling height in inches (remaining after feet): ";
  cin >> ceilingInches;
  //cout << "ceiling height in inches (remaining after feet): " << ceilingInches << endl;

  ceilingHeight = ceilingInches + (ceilingFeet * 12);   
  //cout << "Ceiling height in inches: " << ceilingHeight << endl;

//calculating wall area
  cout << "Please input the number of doors: ";
  cin >> doorNumber;
  //cout << "Number of doors: " << doorNumber << endl;
  allDoorArea = doorNumber * DOOR_AREA;
  //cout << "Total area of doors: " << allDoorArea << endl; 

  cout << "Please input the number of windows: ";
  cin >> windowNumber;
  //cout << "Number of windows: " << windowNumber << endl;
  cout << "Please input window height in inches: ";
  cin >> windowHeight;
  //cout << "Window height in inches: " << windowHeight << endl;
  cout << "Please input window length in inches: ";
  cin >> windowLength;
  //cout << "Window length in inches: " << windowLength << endl;
  windowArea = windowHeight * windowLength;
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
  if (wallAndCeilingArea <= 0) {
    cout << "Measurement or input error, run program again and check input values";
    return 0; 
  }

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

//output in a chart
cout << "Amount Needed, Cost, and Weight of Materials: " <<endl;
cout << endl;
cout << "Item" <<setw (14) << "Number" << setw(8) << "Cost" << setw(12
) <<"Weight" << endl;
cout << "Drywall:" << setw(10) << finalSheetNumber << setw(10) << sheetCost << setw(10) << sheetWeight << endl;
cout << "Flooring:" << setw(9) << finalBoxNumber << setw(10) << boxCost << setw(10) << boxWeight << endl;
cout << "Total:" << setw(22) << totalCost << setw(10) << totalWeight << endl;

  return 0;
}