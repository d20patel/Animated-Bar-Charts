// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// TO DO: Nothing for the standard application, just compile and run! However,
// before submitting you need to add your creative component.
//
// Shanon Reckinger
// U. of Illinois, Chicago
// CS 251: Fall 2021
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {
	
  //cout << "Enter filename for Animated Bar Chart: ";
	string filename = "countries.txt";
  //cin >> filename;  // user chooses file for Animated Bar Chart
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
  
  // Uncomment this for creative component
  /*
	int playback_rate;
  cout << "Enter your preferred Playback Rate: ";
  cin >> playback_rate;
  bca.animate(cout, 12, -1, playback_rate);  // prints at the appropriate playback_rate
  */
  
  bca.animate(cout, 12, -1, 0);
  
  return 0;
}
