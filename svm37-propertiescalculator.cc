/**
  * Project 3
  * In accordance with the class policies and Georgetown's Honor Code,
  * I certify that I have neither given nor received any assistance
  * on this project with the exceptions of the lecture notes and those
  * items noted below.
  *
  * Any help items (you may omit mentions of the TAs, the professors,
  * the recommended text, or prior years posted solutions):
  *
  *  Description: This program allows users to upload files containing room measurements for different properties, view data, check data for errors, show rooms with errors, and compute materials needed including weight and cost for each room and for all the properties combined. It uses a menu to allow users to select which task they would like to complete. 
  *
  *
  **///svm37

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;

const unsigned int DRYWALL_AREA = 4 * 12 * 8 * 12;
const unsigned int FLOORING_AREA = 23.8 * 12 * 12;
const unsigned int DOOR_AREA = 3 * 12 * 7 * 12;
const double FUDGE = 1.1;
  
const double DRYWALL_COST = 14.28;
const double FLOORING_COST = 52.12;
const double DRYWALL_WEIGHT = 35.27;
const double FLOORING_WEIGHT = 53;

const unsigned int MAX_WALL_LENGTH = 24;
const unsigned int MIN_WALL_LENGTH = 6;
const unsigned int MAX_CEILING_HEIGHT = 14;
const unsigned int MIN_CEILING_HEIGHT = 7;


char get_menu();
int load_property_file(vector<string> & ,vector<string> &,
		       vector<unsigned int> &, vector<unsigned int> &, 
		       vector<unsigned int> &, vector<unsigned int> &, 
		       vector<unsigned int> &, vector<unsigned int> &,
		       vector<unsigned int> &, vector<unsigned int> &,
		       vector<unsigned int> &, vector<unsigned int> &,
		       vector<bool> &, string);

void clear_data(vector<string> & ,vector<string> &,
		vector<unsigned int> &, vector<unsigned int> &, 
		vector<unsigned int> &, vector<unsigned int> &, 
		vector<unsigned int> &, vector<unsigned int> &,
		vector<unsigned int> &, vector<unsigned int> &,
		vector<unsigned int> &, vector<unsigned int> &,
		vector<bool> &);


void show_properties(vector<string>, vector<string>,
		     vector<unsigned int>, vector<unsigned int>, 
		     vector<unsigned int>, vector<unsigned int>, 
		     vector<unsigned int>, vector<unsigned int>,
		     vector<unsigned int>, vector<unsigned int>,
		     vector<unsigned int>, vector<unsigned int>,
		     vector<bool>);
  
void show_errors(vector<string>, vector<string>,
		 vector<unsigned int>, vector<unsigned int>, 
		 vector<unsigned int>, vector<unsigned int>, 
		 vector<unsigned int>, vector<unsigned int>,
		 vector<unsigned int>, vector<unsigned int>,
		 vector<unsigned int>, vector<unsigned int>,
		 vector<bool>);
  
  

void check_errors(vector<string>, vector<string>,
		  vector<unsigned int>, vector<unsigned int>, 
		  vector<unsigned int>, vector<unsigned int>, 
		  vector<unsigned int>, vector<unsigned int>,
		  vector<unsigned int>, vector<unsigned int>,
		  vector<unsigned int>, vector<unsigned int>,
		  vector<bool> &);

void compute_materials(vector<string>, vector<string>,
		       vector<unsigned int>, vector<unsigned int>, 
		       vector<unsigned int>, vector<unsigned int>, 
		       vector<unsigned int>, vector<unsigned int>,
		       vector<unsigned int>, vector<unsigned int>,
		       vector<unsigned int>, vector<unsigned int>,
		       vector<bool>);


int main(){
  // property name vector
  vector<string> property;
  // room name vector
  vector<string> room;
  // length of room wall 1 feet vector
  vector<unsigned int> wall1_ft;
  // length of room wall 1 inches vector
  vector<unsigned int> wall1_in;
  // length of room wall 2 feet vector
  vector<unsigned int> wall2_ft;
  // length of room wall 2 inches vector
  vector<unsigned int> wall2_in; 
  // height of room ceiling feet vector
  vector<unsigned int> ceiling_ft;
  // height of room ceiling inches vector
  vector<unsigned int> ceiling_in;
  // room door count vector
  vector<unsigned int> door_count;
  // room window count vector
  vector<unsigned int> window_count;
  // room window height inches vector
  vector<unsigned int> window_height;
  // room window width inches vector
  vector<unsigned int> window_width;
  // bools that indicate if there is an error in that room vector
  vector<bool> error;

char selection = ' ';
string filename = "";
int lines = 0;
bool exit = false;
bool loadProp = false;
bool errorCheck = false;
bool deleteData = false;
bool errorsInData = false;

while (!exit){

selection = get_menu();

if (selection == 'L' || selection == 'l'){
  cout << "Enter name of property file to load: ";
  cin >> filename;
  lines = load_property_file(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error, filename);

  cout << "Loaded " << lines << " lines from " << filename << "." << endl;

  loadProp = true;
}

if (selection == 'S' || selection == 's') {
  if (!loadProp){
    cout << "No files loaded." << endl;
  }
  else {
  show_properties(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
  }
}

if (selection == 'E' || selection == 'e'){
  if (!loadProp){
    cout << "No files loaded." << endl;
  }
  else {
  check_errors(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
  
  errorCheck = true;

  for (int i=0; i<room.size();i++){
    if (error.at(i)){
      errorsInData = true;
    }
  }
  }
}

if (selection == 'X' || selection == 'x'){
  if (!loadProp){
    cout << "No files loaded." << endl;
  }
  else if (!errorCheck){
      cout << "Errors cannot be shown until data is checked for errors." << endl;
    }
    else {
    show_errors(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
  }
}

if (selection == 'C' || selection == 'c'){
  if (!loadProp){
    cout << "No files loaded." << endl;
  }
  else if (!errorCheck){
    cout << "Please check for errors before computing materials." << endl;
  }
  else if (errorsInData) {
    cout << "****************************************************************************" << endl << "CAUTION! The data loaded from files is known to contain errors." << endl << "Lines with errors will be excluded from computation." << endl << "Please address errors before making purchases based on this data." << endl << "****************************************************************************";

    compute_materials(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);

    cout << "**** REMINDER: This data contains errors and should be corrected before being used to place orders." << endl;
  }
  else {
    compute_materials(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
  }
}

if (selection == 'D' || selection == 'd'){
  clear_data(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);

  deleteData = true;
}

if (selection == 'Q' || selection == 'q'){
  exit = true;
}

}
  return 0;
}

// Prints the menu and then gets the user's menu choice, which is returned as
// a character type.
// It should clear any extra input that comes so that multiple menu choices can
// be made over time
char get_menu(){

char selection = ' ';
string filename = "";

cout << endl;
cout << setw(32) << "Load a property file     L" << endl;
cout << setw(32) << "Show all loaded properties     S" << endl;
cout << setw(32) << "Check data for errors     E" << endl;
cout << setw(32) << "Show rooms with errors     X" << endl;
cout << setw(32) << "Compute materials needed     C" << endl;
cout << setw(32) << "Delete all data     D" << endl;
cout << setw(32) << "Exit the program     Q" << endl;
cout << endl;
cout << "Please enter your choice: ";
cin >> selection;

  // fake return for the compiler
  return selection;
}

// This function takes as input the vectors for storage and a string
// that contains a filename. The filename is passed as a parameter
// the function must not ask the user for it.
// It will open the file of the given name and load each line from the
// file into the vectors. It returns a count of how many rooms were loaded
// from the file.
// It initializes the error vector as it reads lines, setting the value to false
// as no errors have been detected yet.
// In the event the file in unable to be opened, it prints an error message and
// returns a count of zero.
// This function only loads data; it DOES NOT do any error checking
// You may expect the file to be properly formatted and to have no type errors
int load_property_file(vector<string> & property,
		       vector<string> & room,
		       vector<unsigned int> & wall1_ft,
		       vector<unsigned int> & wall1_in, 
		       vector<unsigned int> & wall2_ft,
		       vector<unsigned int> & wall2_in, 
		       vector<unsigned int> & ceiling_ft,
		       vector<unsigned int> & ceiling_in,
		       vector<unsigned int> & door_count,
		       vector<unsigned int> & window_count,
		       vector<unsigned int> & window_height,
		       vector<unsigned int> & window_width,
		       vector<bool> & error,
		       string filename){

 //variables to read into
  string propertyAddress = "";
  string roomName = "";
  int wall1Ft = 0;
  int wall1In = 0;
  int wall2Ft = 0;
  int wall2In = 0;
  int ceilingFt = 0;
  int ceilingIn = 0;
  int doorCount = 0;
  int windowCount = 0;
  int windowHeight = 0;
  int windowWidth = 0;
  int roomCount = 0;


  //open file
  ifstream inputFile;
  inputFile.open(filename.c_str());

  //output error if it fails to find file
  if (!inputFile){
  cout << "Error: file not found." << endl;
  return 0;
  }

  //read each value from the file into variables add to correct vector
  getline(inputFile, propertyAddress);
  while (inputFile >> roomName>> wall1Ft >> wall1In >> wall2Ft >> wall2In >> ceilingFt >> ceilingIn >> doorCount >> windowCount >> windowHeight >> windowWidth) {

   //cout << "Address: " << propertyAddress << endl << "Room: " << roomName << endl << " " << wall1Ft << " " << wall1In << " " << wall2Ft << " " << wall2In <<  " " << ceilingFt << " " << ceilingIn << " " << doorCount <<  " " << windowCount << " " << windowHeight << " " << windowWidth << endl;

  property.push_back(propertyAddress);
  room.push_back(roomName);
  wall1_ft.push_back(wall1Ft);
  wall1_in.push_back(wall1In);
  wall2_ft.push_back(wall2Ft);
  wall2_in.push_back(wall2In);
  ceiling_ft.push_back(ceilingFt);
  ceiling_in.push_back(ceilingIn);
  door_count.push_back(doorCount);
  window_count.push_back(windowCount);
  window_height.push_back(windowHeight);
  window_width.push_back(windowWidth);
  error.push_back(false);

//count lines read
  roomCount++;
 } 

  // Fake return so it can compile
  return roomCount;  
}


// Clear data erases all data in all vectors.
// When done, the vectors should be empty and have a size of zero.
void clear_data(vector<string> & property,
		vector<string> & room,
		vector<unsigned int> & wall1_ft,
		vector<unsigned int> & wall1_in, 
		vector<unsigned int> & wall2_ft,
		vector<unsigned int> & wall2_in, 
		vector<unsigned int> & ceiling_ft,
		vector<unsigned int> & ceiling_in,
		vector<unsigned int> & door_count,
		vector<unsigned int> & window_count,
		vector<unsigned int> & window_height,
		vector<unsigned int> & window_width,
		vector<bool> & error) {

    property.clear();
    room.clear();
    wall1_in.clear();
    wall1_ft.clear();
    wall2_ft.clear();
    wall2_in.clear();
    ceiling_ft.clear();
    ceiling_in.clear();
    door_count.clear();
    window_count.clear();
    window_height.clear();
    window_width.clear();
    error.clear();
}

// This function prints out all data currently in the vectors in a neat
// and aligned format. See the sample output from Clay's program as a model
void show_properties(vector<string>  property,
		     vector<string>  room,
		     vector<unsigned int>  wall1_ft,
		     vector<unsigned int>  wall1_in, 
		     vector<unsigned int>  wall2_ft,
		     vector<unsigned int>  wall2_in, 
		     vector<unsigned int>  ceiling_ft,
		     vector<unsigned int>  ceiling_in,
		     vector<unsigned int>  door_count,
		     vector<unsigned int>  window_count,
		     vector<unsigned int>  window_height,
		     vector<unsigned int> window_width,
		     vector<bool> error) {

//output chart header
cout << setw(20) << "Property" << setw(15) << "Room" << setw(8) << "W1 FT" << setw(8) << "W1 IN" << setw(8) << "W2 FT" << setw(8) << "W2 IN" << setw(8) << "C FT" << setw(8) << "C IN" << setw(8) << "Doors" << setw(8) << "Wndws" << setw(8) << "WDW H" << setw(8) << "WDW W" << setw(8) << "ERR" << endl;

for (int i=0; i < room.size(); i++) {
  cout << setw(20) << property.at(i) << setw(15) << room.at(i) << setw(8) << wall1_ft.at(i) << setw(8) << wall1_in.at(i) << setw(8) << wall2_ft.at(i) << setw(8) << wall2_in.at(i) << setw(8) << ceiling_ft.at(i) << setw(8) << ceiling_in.at(i) << setw(8) << door_count.at(i) << setw(8) << window_count.at(i) << setw(8) << window_height.at(i) << setw(8) << window_width.at(i) << setw(8) << error.at(i) << endl;
}

	  
}

// This function prints out ONLY the data that is known to have an error
// The format should be the same as the show_properties function.
// If no errors are present in any room, it should print a message
// saying there were no errors found.
void show_errors(vector<string>  property,
		 vector<string>  room,
		 vector<unsigned int>  wall1_ft,
		 vector<unsigned int>  wall1_in, 
		 vector<unsigned int>  wall2_ft,
		 vector<unsigned int>  wall2_in, 
		 vector<unsigned int>  ceiling_ft,
		 vector<unsigned int>  ceiling_in,
		 vector<unsigned int>  door_count,
		 vector<unsigned int>  window_count,
		 vector<unsigned int>  window_height,
		 vector<unsigned int> window_width,
		 vector<bool> error) {

bool totalErrors = false;
bool headerOutput = false;

for (int i=0; i < room.size(); i++ ) {
  if (error.at(i) == true){

  if (headerOutput == false){
    cout << setw(20) << "Property" << setw(15) << "Room" << setw(8) << "W1 FT" << setw(8) << "W1 IN" << setw(8) << "W2 FT" << setw(8) << "W2 IN" << setw(8) << "C FT" << setw(8) << "C IN" << setw(8) << "Doors" << setw(8) << "Wndws" << setw(8) << "WDW H" << setw(8) << "WDW W" << setw(8) << "ERR" << endl;
    headerOutput = true;
    }

    totalErrors = true;

    cout << setw(20) << property.at(i) << setw(15) << room.at(i) << setw(8) << wall1_ft.at(i) << setw(8) << wall1_in.at(i) << setw(8) << wall2_ft.at(i) << setw(8) << wall2_in.at(i) << setw(8) << ceiling_ft.at(i) << setw(8) << ceiling_in.at(i) << setw(8) << door_count.at(i) << setw(8) << window_count.at(i) << setw(8) << window_height.at(i) << setw(8) << window_width.at(i) << setw(8) << error.at(i) << endl;
    }
  }

if (totalErrors == false) {
  cout << "No errors found in any rooms." << endl;
  
}

}
  
// This function processes all data and looks for errors.
// In the event of an unrecoverable error, it prints a message
// describing the error and sets the corresponding value in the error
// vector to true.
// In the event of a recoverable error, it asks the user if the error should
// be considered an error or not and accept input back from the user.
// If the user says it should be an error, it sets the corresponding portion
// of the error vector to true; otherwise, it sets it or leaves it false.
// User over-rideable errors are:
//
// * Wall length less than 6 feet
// * Wall length greater than 24 feet.
// * Ceiling height more than 14 feet
// * Ceiling height less than 7 feet
// 
// Unrecoverable errors are:
// 
// * Inches measurements less than 0 or greater than 11 for a length that also includes feet, such as wall length or ceiling height
// * Windows missing measurements - the window count is zero but the measurements have a value
// * Windows missing counts - the measurements are not zero but the window count is zero
// * Door and windows area being greater than the wall area for any particular room.
// In no case should an error cause termination of the program, it should only
// cause the appropriate place in the error vector to be marked true
void check_errors(vector<string>  property,
		  vector<string>  room,
		  vector<unsigned int>  wall1_ft,
		  vector<unsigned int>  wall1_in, 
		  vector<unsigned int>  wall2_ft,
		  vector<unsigned int>  wall2_in, 
		  vector<unsigned int>  ceiling_ft,
		  vector<unsigned int>  ceiling_in,
		  vector<unsigned int>  door_count,
		  vector<unsigned int>  window_count,
		  vector<unsigned int>  window_height,
		  vector<unsigned int> window_width,
		  vector<bool> & error){

char userOverride = ' ';

for (int i=0; i < room.size(); i++) {

  //unrecoverable errors
  if (wall1_in.at(i) > 11) {
    cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - inches for wall 1 are above 11." << endl;
    error.at(i) = true;
  }

  if (wall2_in.at(i) > 11) {
    cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - inches for wall 2 are above 11." << endl;
    error.at(i) = true;
  }
  
  if (ceiling_in.at(i) > 11) {
    cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - inches for wall 2 are above 11." << endl;
    error.at(i) = true;
  }

  if ((window_count.at(i) = 0) && ((window_height.at(i) != 0) || (window_width.at(i) != 0))) {
     cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - there are window measurements but no window count." << endl;
     error.at(i) = true;
  }

  if (window_count.at(i) > 0){
    if ((window_width.at(i) == 0) && (window_height.at(i) == 0)) {
      cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - window count but no window measurements." << endl;
      error.at(i) = true;
      }
   else if ((window_width.at(i) == 0) || (window_height.at(i) == 0)) {
      cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - window count but only one window measurement." << endl;
     }
  }

  //door area and window area greater than wall area
    //calculate wall area
    int wall1Width = 0;
    int wall2Width = 0;
    int ceilingHeight = 0;
    int wallArea = 0;
    int windowAndDoorArea = 0;

    wall1Width = wall1_in.at(i) + (wall1_ft.at(i)*12);
    wall2Width = wall2_in.at(i) + (wall2_ft.at(i)*12);
    ceilingHeight = ceiling_in.at(i) + (ceiling_ft.at(i)*12);
    wallArea = (wall1Width * ceilingHeight * 2) + (wall2Width * ceilingHeight * 2);

    //calculate door and window area
    windowAndDoorArea = (DOOR_AREA * door_count.at(i)) + (window_count.at(i) * window_height.at(i) * window_width.at(i));

    //compare wall area to door and window area
  if (windowAndDoorArea > wallArea) {
    cout << "Unrecoverable error in property " << property.at(i) << " in room: " << room.at(i) << " - window and door area is greater than wall area." << endl;
      error.at(i) = true;
      }

  //recoverable errors
  if (wall1_ft.at(i) < 6) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - wall 1 length is less than 6 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'Y') || (userOverride = 'y')){
      error.at(i) = false;
      }
    else if ((userOverride = 'N') || (userOverride = 'n')) {
      error.at(i) = true;
      }
    }

  if (wall2_ft.at(i) < 6) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - wall 2 length is less than 6 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'n') || (userOverride = 'N')){
      error.at(i) = true;
      }
    }

  if ((wall1_ft.at(i) > 24) || (wall1_ft.at(i) == 24 && wall1_in.at(i) > 0)) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - wall 1 length is greater than 24 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'n') || (userOverride = 'N')){
      error.at(i) = true;
      }
    }

  if ((wall2_ft.at(i) > 24) || (wall2_ft.at(i) == 24 && wall2_in.at(i) > 0)) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - wall 2 length is greater than 24 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'n') || (userOverride = 'N')){
      error.at(i) = true;
      }
    }

  if (ceiling_ft.at(i) < 7) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - ceiling height is less than 7 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'n') || (userOverride = 'N')){
      error.at(i) = true;
      }
    }

  if ((ceiling_ft.at(i) > 14) || (ceiling_ft.at(i) == 14 && ceiling_in.at(i) > 0)) {
    cout << "Error in property " << property.at(i) << " in room: " << room.at(i) << " - ceiling height is greater than 14 ft." <<endl;
    cout << "Do you want to override this error? (Y/N)";
    cin >> userOverride;
    if ((userOverride = 'n') || (userOverride = 'N')){
      error.at(i) = true;
      }
    }

}

}

// This function computes the amount of flooring and drywall needed
// for all rooms of all loaded properties, except rooms known to have an error.
// If any error is present in the data, as indicated by any true setting in the
// erro vector, it prints a warning before and after the computation to indicate that the
// output is unreliable.
// The materials computation for each room is the same as in Project 2.
// The output should have headers, appropriate totals, and should be neatly
// formatted in columns.

void compute_materials(vector<string>  property,
		       vector<string>  room,
		       vector<unsigned int>  wall1_ft,
		       vector<unsigned int>  wall1_in, 
		       vector<unsigned int>  wall2_ft,
		       vector<unsigned int>  wall2_in, 
		       vector<unsigned int>  ceiling_ft,
		       vector<unsigned int>  ceiling_in,
		       vector<unsigned int>  door_count,
		       vector<unsigned int>  window_count,
		       vector<unsigned int>  window_height,
		       vector<unsigned int> window_width,
		       vector<bool> error) {
  

//variables that come from vectors
string propertyName = "";
string roomName = "";
int wall1Ft = 0;
int wall1In = 0;
int wall2Ft = 0;
int wall2In = 0;
int ceilingFt = 0;
int ceilingIn = 0;
int doorCount = 0;
int windowCount = 0;
int windowWidth = 0;
int windowHeight = 0;

 

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
  int allPropsSheetNumber = 0;
  int allPropsBoxNumber = 0;
  double allPropsCost = 0;
  double allPropsWeight = 0;
  

//output chart header
cout <<endl;
cout << setw(18) << "Property" << setw(12) << "Room" << setw(18) << "Drywall Sheets" << setw(18) << "Flooring Boxes" << setw(10) << "Cost" << setw(10) << "Weight" << endl;
cout << "--------------------------------------------------------------------------------------";

//run program to calculate all the information

for (int i = 0; i < room.size(); i++){
  if (!error.at(i)){
  propertyName = property.at(i);
  roomName = room.at(i);
  wall1Ft = wall1_ft.at(i);
  wall1In = wall1_in.at(i);
  wall2Ft = wall2_ft.at(i);
  wall2In = wall2_in.at(i);
  ceilingFt = ceiling_ft.at(i);
  ceilingIn = ceiling_in.at(i);
  doorCount = door_count.at(i);
  windowCount = window_count.at(i);
  windowWidth = window_width.at(i);
  windowHeight = window_height.at(i); 

//calculate room length
    roomLength = wall1In + (wall1Ft * 12);
    //cout << "Length of room in inches: " << roomLength << endl;

//calculate room width
    roomWidth = wall2In + (wall2Ft * 12); 
    //cout << "Width of room in inches: " << roomWidth << endl;

//calculate ceiling height
    ceilingHeight = ceilingIn + (ceilingFt * 12); 
    //cout << "Ceiling height in inches: " << ceilingHeight << endl;  

//calculate door and window area
    allDoorArea = doorCount * DOOR_AREA;
    //cout << "Total area of doors: " << allDoorArea << endl;
    windowArea = windowHeight * windowWidth;
    //cout << "Area of individual windows: " << windowArea << endl;
    allWindowArea = windowArea * windowCount;
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
      //cout << "wall and ceiling area: " << wallAndCeilingArea << endl;
      //cout << "drywall area: " << DRYWALL_AREA;
      drywallSheetNumber = ceil (wallAndCeilingArea/static_cast<double>(DRYWALL_AREA)); 
      //cout << "Drywall Sheet Number: " << drywallSheetNumber << endl;
      tenPercentSheetNumber = (drywallSheetNumber/10);
      //cout << "Ten Percent of Sheet Number: " << tenPercentSheetNumber << endl;
      finalSheetNumber = ceil (drywallSheetNumber + tenPercentSheetNumber);
      //cout << "Drywall Sheets Needed: " << finalSheetNumber << endl;

    //calculate flooring boxes needed
      flooringBoxNumber = ceil (floorArea/static_cast<double>(FLOORING_AREA)); 
      //cout << "Flooring Box Number: " << flooringBoxNumber << endl;
      tenPercentBoxNumber = flooringBoxNumber/10;
      //cout << "Ten Percent of Box Number: " << tenPercentBoxNumber << endl;
      finalBoxNumber = ceil (flooringBoxNumber + tenPercentBoxNumber);
      //cout << "Flooring Boxes Needed:" << finalBoxNumber << endl;

    //calculate final sheet and box costs 
      sheetCost = finalSheetNumber * DRYWALL_COST;
      boxCost = finalBoxNumber * FLOORING_COST;
      //cout << "Drywall Cost: " << sheetCost << endl;
      //cout << "Flooring Cost: " << boxCost << endl;

    //calculate final sheet and box weights 
      sheetWeight = finalSheetNumber * DRYWALL_WEIGHT; 
      boxWeight = finalBoxNumber * FLOORING_WEIGHT;
      //cout << "Drywall Weight: " << sheetWeight << endl;
      //cout << "Flooring Weight: " << boxWeight << endl;

    //calculate total cost and weight
      totalCost = sheetCost + boxCost;
      totalWeight = sheetWeight + boxWeight; 
      //cout << "Total Cost: " << totalCost << endl;
      //cout << "Total Weight: " << totalWeight << endl;

    //add to full house totals
    allPropsSheetNumber = allPropsSheetNumber + finalSheetNumber; 
    allPropsBoxNumber = allPropsBoxNumber + finalBoxNumber;
    allPropsCost = allPropsCost + totalCost;
    allPropsWeight = allPropsWeight + totalWeight; 

    //output
        cout << setw (18) << propertyName << setw(12) << roomName << setw (18)<< finalSheetNumber << setw (18) << finalBoxNumber << setw (10) << totalCost << setw (10) << totalWeight;
    }
    }  


//output totals
cout <<endl; 
cout << "--------------------------------------------------------------------------------------"<< endl;
cout << setw (30) << "Total:" << setw (18)<< allPropsSheetNumber << setw(18) << allPropsBoxNumber << setw(10) << allPropsCost << setw (10) << allPropsWeight << endl; 




}



// Below is the scaffolding code Clay used for testing as code was developed
//
// You can use this as you develop each function to test and see if it is working.
// You will need to put the code in main.
// After all the functions are done, then you can build the menu and call functions
// as needed
//
// int lines = load_property_file(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error, "prop1.txt");
//
//  cout << "Read " << lines << " lines" << endl;
//
//  show_properties(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
//
//
//  lines = load_property_file(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error, "prop2.txt");
//
//  cout << "Read " << lines << " lines" << endl;
//
//
//  lines = load_property_file(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error, "prop3.txt");
//
//  cout << "Read " << lines << " lines" << endl;
//
  
//  
//
//  compute_materials(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
//  
// clear_data(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
//  
//  show_properties(property, room, wall1_ft, wall1_in, wall2_ft, wall2_in, ceiling_ft, ceiling_in, door_count, window_count, window_height, window_width, error);
//

