// barchart.h
// This header file uses bar.h to create an array of bars
// This file contains functions to add bars to the array
// compare bars based on their values using sort
// BarChart has capacity, size, frame, bars as variables

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h"  // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Codio (light/dark mode)
/*
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};
*/
//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;  // size allowed in an array
    int size;  // quantity filled in an array
    string frame;  // for printing one entire frame of animation

 public:
    // default constructor:
    BarChart() {
      this->bars = nullptr;
      this->capacity = 0;
      this->size = 0;
      this->frame = "";
    }
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
      this->bars = new Bar[n];
      this->capacity = n;
      this->size = 0;
      this->frame = "";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
      // sets this to other
      this->bars = new Bar[other.capacity];
      this->capacity = other.capacity;
      this->size = other.size;
      this->frame = other.frame;
      // to assign bars in other bar's values to this->bars
      for (int i = 0; i < other.size; i++) {
        Bar b1(other.bars[i].getName(), other.bars[i].getValue(),
        other.bars[i].getCategory());
        this->bars[i] = b1;  // makes copy
      }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
        delete[] this->bars;
        // sets this to other
        this->capacity = other.capacity;
        this->bars = new Bar[other.capacity];
        this->size = other.size;
        this->frame = other.frame;
        for (int i = 0; i < other.size; i++) {
          Bar b1(other.bars[i].getName(), other.bars[i].getValue(),
          other.bars[i].getCategory());
          this->bars[i] = b1;
        }
        return *this;  // due to the return type
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
      // deletes the array and resets the variables
      delete[] this->bars;
      this->bars = nullptr;
      this->capacity = 0;
      this->size = 0;
      this->frame = "";
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
      clear();  // calls clear() to free memory by BarChart
    }
    // setFrame
    void setFrame(string frame) {
        this->frame = frame;
    }
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
        return this->frame;
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        if (this->size >= this->capacity) {  // if the size reaches capacity
          return false;
        } else {  // adds a new bar to the array with passed variables
          Bar b1(name, value, category);
          this->bars[this->size] = b1;
          this->size++;
          return true;
        }
    }
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return this->size;
    }
    int getCapacity() {
        return this->capacity;
    }
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        if (i < 0 || i >= size) {
          throw out_of_range("BarChart: i out of bounds");
        } else {
          return this->bars[i];  // returns Bar element in BarChart
        }
    }
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
      output << "frame: " << this->frame << endl;
      Bar* sortBars = new Bar[this->size];  // for sorted Bars
      for (int i = 0; i < this->size; i++) {
        Bar b1(this->bars[i].getName(), this->bars[i].getValue(),
        this->bars[i].getCategory());
        sortBars[i] = b1;  // inserts in array for sorting
      }
      sort(sortBars, sortBars + this->size, greater<Bar>());  // sorts by values
      for (int i = 0; i < this->size; i++) {  // for printing to check it works
        Bar b1 = sortBars[i];
        output << b1.getName() << " " << b1.getValue()
        << " " << b1.getCategory() << endl;
      }
      delete[] sortBars;  // frees memory
    }
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
      Bar *sortBars = new Bar[this->size];  // to sort the bars by values
      int lenMax = 60;
      for (int i = 0; i < this->size; i++) {  // sets the bars in sortBars
        Bar b(this->bars[i].getName(), this->bars[i].getValue(),
        this->bars[i].getCategory());
        sortBars[i] = b;
      }
      sort(sortBars, sortBars + this->size, greater<Bar>());  // sorts the bars
      for (int i = 0; i < top; i++) {
        string colour = BLACK;
        if (colorMap.find(sortBars[i].getCategory()) != colorMap.end()) {
          colour = colorMap[sortBars[i].getCategory()];
        }
        if (i != 0) { // determines how many BOXs to print
          double currVal = sortBars[i].getValue()*1.0;
          currVal = currVal/sortBars[0].getValue()*60.0;
          lenMax = currVal;
        }
        string barstr = "";
        for (int i = 0; i < lenMax; i++) {
            barstr += BOX;  // adds the BOXs
        }
        // outputs the BOXs with their Name and Values
        output << colour << barstr << " ";
        output << sortBars[i].getName() << " ";
        output << sortBars[i].getValue() << endl;
      }
      delete[] sortBars;  // frees memory of sortBars
    }
};
