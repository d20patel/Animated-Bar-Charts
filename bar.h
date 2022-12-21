// bar.h
// This header file is for creating a bar
// that contains name, value, category of particular bar
// This bar will then be used in array of bars in barchart.h

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
  private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.
    string name;
    int value;
    string category;

  public:

    // default constructor:
    Bar() {
      name = "";
      value = 0;
      category = "";
    }

    //
    // a second constructor:
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
      this->name = name;
      this->value = value;
      this->category = category;
    }

    // destructor:
    virtual ~Bar() {
      name = "";
      value = 0;
      category = "";
    }

    // getName:
    string getName() {
        return name; 
    }

    // getValue:
    int getValue() {
        return value;
    }

    // getCategory:
	string getCategory() {
        return category; // TO DO:  update this, it is only here so code compiles.
	}

	// operators
  // This allows you to compare two Bar objects
  // Comparison is based on the Bar's value
	bool operator<(const Bar &other) const {
    // if this->value is less than other value
    if(this->value < other.value) {  // returns true
      return true;
    } else {
      return false;
    }
	}
  // same procedure for all operators
	bool operator<=(const Bar &other) const {
    if(this->value <= other.value) {
      return true;
    } else {
      return false;
    }
	}

	bool operator>(const Bar &other) const {
    if(this->value > other.value) {
      return true;
    } else {
      return false;
    }
	}

	bool operator>=(const Bar &other) const {
    if(this->value >= other.value) {
      return true;
    } else {
      return false;
    }
	}
};

