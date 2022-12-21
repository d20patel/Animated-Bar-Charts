// barchartanimate.h
// This file is to contain array of frames that contain bars
// The file contains functions to reads from file and store data
// to appropriate variables of the bars. The final animation is also
// built in this file and then is called in application.cpp
// Creative Component: Change option for Playback Rate has seperate animate()

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h"  // used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int capacity;
    int size;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;
    size_t colours_ind;  // for index in colours map

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
      // initializes appropriate values
      this->barcharts = new BarChart[4];
      this->capacity = 4;
      this->size = 0;
      this->title = title;
      this->xlabel = xlabel;
      this->source = source;
      this->colours_ind = 0;
        
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
      if (barcharts != nullptr) {
        delete[] barcharts;  // clears the memory
      }
        //this->barcharts = nullptr;  // initializes to nullptr
    }
  
    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
      int numRecords;  // total bars in that frame
      string emptyLine, dataLine, lineWord, to_int;  // for reading the line
      string category, name, frame, not_required;
      int value;
      file >> numRecords;  // takes in the number
      getline(file, emptyLine);
      BarChart bc_record(numRecords);  // for storing the bar record
      if (! file.good()) { return; }
      for (int i = 0; i < numRecords; i++) {  // loops numRecords times
        getline(file, frame, ',');  // reads appropriate variables
        getline(file, name, ',');
        getline(file, not_required, ',');
        getline(file, to_int, ',');
        getline(file, category);
        value = stoi(to_int);
        bc_record.setFrame(frame);
        bc_record.addBar(name, value, category); // adds bar to bc_record
        if (colorMap.count(category) == 0) {  // if category doesn't exixt
          colorMap[category] = COLORS[this->colours_ind % 7];  // assigned to appropriate colour
          this->colours_ind += 1;  // increments the colours_ind
        }
      }
      if (this->size == this->capacity) {  // if the size is capacity
        int new_capacity = this->capacity*2;  // doubles the capacity
        BarChart* new_barcharts = new BarChart[new_capacity];
        for (int i = 0; i < this->size; i++) {
          new_barcharts[i] = barcharts[i];  // shifts the elements
        }
        delete[] barcharts;
        barcharts = new_barcharts;  // updates back to this->barcharts
        capacity = new_capacity;  // updates the capacity
      }
      barcharts[this->size] = bc_record;
      this->size += 1;
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
    const string BLACK("\033[1;37m");
    if (endIter == -1) {  // if everything is to be printed
      endIter = this->size;
    }
    for (int i = 0; i < endIter; i++) {  // prints bars calling graph()
      usleep(3*microsecond);
      output << CLEARCONSOLE;
      output << BLACK << this->title << endl;
      output << BLACK << this->source << endl;
      this->barcharts[i].graph(output, colorMap, top);
      output << BLACK << this->xlabel << endl;
      output << "Frame: " << this->barcharts[i].getFrame() << endl;
    }
	}
  
  // Creative Component: Users gets to pick their preferred playback_rate
  // in the animation of bar charts. Called in application.cpp
  // int playback_rate parameter for number entered by user as playback_rate
  void animate(ostream &output, int top, int endIter, int playback_rate) {
		unsigned int microsecond = 50000;
    const string BLACK("\033[1;37m");
    if (endIter == -1) {
      endIter = this->size;
    }
    for (int i = 0; i < endIter; i++) {  // prints bars at playback_rate
      usleep(playback_rate*microsecond);
      output << CLEARCONSOLE;
      output << BLACK << this->title << endl;
      output << BLACK << this->source << endl;
      this->barcharts[i].graph(output, colorMap, top);
      output << BLACK << this->xlabel << endl;
      output << BLACK << "Frame: " << this->barcharts[i].getFrame() << endl;
    }
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() {
        return this->size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i) {       
      if (i < 0 or i >= size) {
        throw out_of_range("BarChartAnimate: i out of bounds");
      }
      return this->barcharts[i];  // returns BarChart element in BarChartAnimate
    }

};
