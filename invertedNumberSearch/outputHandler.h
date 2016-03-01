#ifndef OUTPUTHANDLER_H
#define OUTPUThANDLER_H

#include <fstream>
#include <list>


using namespace::std;

class outputHandler
{
public:
	outputHandler();

private:
	
	//************
	//vars
	//************
	//counters
	int numsProcessed; //total processed numbers
	int normProcessed; //total terminal (non-looping) reversals processed
	int loopProcessed; //total looping reversals processed

	class History {
	public:
		//constructor
		History();

		bool pushData(int);
		//pushes data onto the History list & array
		//returns true if successful

		// checks to see if there is a reversal loop
		bool checkForLoop();

	private:
		//History
		//an array to hold the 4 most recently processed vals
		//of the currently processed number
		int histArr[4];
		
		int histSize; 
		//a container to hold the entire History of the currently
		//processed number
		std::list<int> histList;
	};
	
	History hist;

	//largest number to search
	int largestNum;
	
	//io obj to save data to file
	ofstream output;

	//************
	//functions
	//************
	// reverse number takes an int, and returns
	// a reversal of that int while also keeping
	// the same sign (i.e -123 becomes -321)
	int reverseNumber(int num);

	// starts searching through and sorting
	// ints to see how they reverse
	int startSearch();

	//************
	//debug 
	//************
	//vars
	//************
	//used to check for 'reversal cycles'
	int debugCount;
	//************
	//functions
	//************


};



#endif // OUTPUTHANDLER_H
