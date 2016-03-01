#include "outputHandler.h"

#include <limits>
//needed to get max int size
//we want to find as many possible
//of these number combos as possible
//#include <math.h>
#include <iostream>

using namespace std;

//basic constructor
outputHandler::outputHandler()
{
	//find this compiler's max int size
	largestNum = INT_MAX;
	//largestNum = 100000;

	//counters
	numsProcessed = 0; //total processed numbers
	normProcessed = 0; //total terminal (non-looping) reversals processed
	loopProcessed = 0; //total looping reversals processed

	//debug vars
	//used to check for 'reversal cycles'
	debugCount = 0;

	//instantly start the search
	startSearch();
}

int outputHandler::reverseNumber(int num)
{
	int sign = 1;
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}

	//this segment taken from:
	//http://fahad-cprogramming.blogspot.com/2013/12/reverse-number-in-c-program-code.html
	int reverseNum = 0;
	while (num > 0)
	{
		reverseNum = reverseNum * 10;
		reverseNum += num % 10;
		num /= 10;
	}

	return reverseNum * sign;
}

// starts searching through and sorting
// ints to see how they reverse
int outputHandler::startSearch() {
	for (int start = 0; start < largestNum; start++, numsProcessed++)
	{
		// set some initial values
		int num = start;

		// while num != 0
		// AND the history doesn't suggest we're
		// in a loop
		while( num && !hist.checkForLoop() )
		{
			num -= reverseNumber(num);
		}
	}

	return 0;
}


outputHandler::History::History()
	{
		for (int i = 0; i < 4; i++)
			histArr[i] = 0;
		histSize = 0;
	}

	//pushes data onto the History list & array
	//returns true if successful
bool outputHandler::History::pushData(int data)
	{
		//add data to list
		histList.push_back(data);

		//add data to histArray
		if (histSize < 4) {
			// if the array isn't filled yet
			// insert data in the next open slot
			histArr[histSize] = data;
			histSize++;

			return true;
		}
		else {
			//otherwise, the data needs to be shifted
			//back, and the oldest data deleted from 
			//histArr
			for (int i = 0; i < 2; i++)
				histArr[i] = histArr[i++];
			histArr[3] = data;

			return true;
		}

	}	

	// checks to see if there is a reversal loop
	//
	// Checks the History array's first and last
	// elems, making sure they are legit values
	// (the array is initially populated w/ NAN)
	// as well as if they are the same size but w/
	// opposite signs (meaning this is will loop)
	// and if they are, return true, false otherwise
bool outputHandler::History::checkForLoop()
	{
		// return true if there is at least four
		// entries in the History
		// AND if the first and last entries in the
		// History array match in magnitude but have
		// opposite signs
		return (((histArr[0] == (histArr[3] * -1))
			&& histSize > 3)) ?
			true :
			false;
	}


