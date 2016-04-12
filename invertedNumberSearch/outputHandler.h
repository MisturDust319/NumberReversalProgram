#ifndef OUTPUTHANDLER_H
#define OUTPUThANDLER_H

#include <fstream>
#include <list>


#define HIST_ARRAY_SIZE 8
#define HIST_ARRAY_BACK HIST_ARRAY_SIZE-1


using namespace::std;

class OutputHandler
{
public:
	OutputHandler();

private:
	
	//************
	//vars
	//************
	//counters
	int numsProcessed; //total processed numbers
	int normProcessed; //total terminating (non-looping) reversals processed
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

		//prints histArr
		void printHistArr();

		//clears history files and resets histSize
		void clearHist();

		//grabs history stored disk AND mem in order
		//and stores it in the oppropriate file
		bool storeHist(ofstream&);

		//gets a value from history array at index
		//provided
		int getHistArrVal(int);

	private:
		//History
		//an array to hold the 4 most recently processed vals
		//of the currently processed number
		int histArr[HIST_ARRAY_SIZE];
		//histSize tracks how much data has been pushed into history
		int histSize;

		//a container to hold the entire History of the currently
		//processed number
		std::list<int> histList;
	};
	
	//an instance of the embedded History class
	History hist;

	//largest number to search
	int largestNum;
	

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
	//int debugCount;
	//************
	//functions
	//************


};



#endif // OUTPUTHANDLER_H
