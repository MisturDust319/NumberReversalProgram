#include "outputHandler.h"

#include <limits>
//needed to get max int size
//we want to find as many possible
//of these number combos as possible
#include <cmath>
#include <iostream>

using namespace std;

//basic constructor
outputHandler::outputHandler()
{
	//find this compiler's max int size
	//largestNum = INT_MAX;
	largestNum = 100000;

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
	for (int start = 1012; start < largestNum; start++, numsProcessed++)
	{
		cout << "current #: " << start << endl;
		// set some initial values
		int num = start;
		int reverse = reverseNumber(num);
		//add num and reverses's current val to the data history
		hist.pushData(num);
		if(reverse != 0)
			hist.pushData(reverse);
		// if reverse is 0, num is 0 
		// num is stored before reverse
		//	so this would just be redundant

		// while num != 0
		// AND the history doesn't suggest we're
		// in a loop
		while( num )
		{
			num -= reverse;
			//get the next num & reverse values
			reverse = reverseNumber(num);

			//add num and reverses's current val to the data history
			hist.pushData(num);
			if (reverse != 0)
				hist.pushData(reverse);
			// if reverse is 0, num is 0 
			// num is stored before reverse
			//	so this would just be redundant
			//cout << "num : " << num << endl
			//	<< "reverse : " << reverse << endl;
			
			//check if it looks like we're in a reversal loop
			//if so, break the loop, and save the history
			if (hist.checkForLoop())
			{
				cout << "broke a reversal loop" << endl;
				hist.printHistArr();
				break;
			}
						
			/*
			debugCount++;
			if (debugCount > 1000)
			{
				//if here, we're prob stuck in a loop
				//so print the history and move on
				cout << "breaking & ouputing history\n probably in reversal loop"
					<< endl << "start point : " << start
					<< endl << "debugCount : " << debugCount << endl;
				hist.printHistArr();
				debugCount = 0;
				break;
			}*/
		}
		//reset debug count for each unique number
		//debugCount = 0;
		hist.clearHist();
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
		//histList.push_back(data);
		
		//otherwise, the data needs to be shifted
		//back, and the oldest data deleted from 
		//histArr

		//temp will hold elem 0 if we need to push
		//it back into the history list
		int temp = 0;
		if (histSize == 4)
		{
			//if the history has more than 4 members
			//data needs to be pushed into histList
			//temp will store the data to be pushed
			//into histList
			temp = histArr[0];
		}
		//start by pushing all data back one slot
		//in the array
		for (int i = 0; i < 3; i++)
			histArr[i] = histArr[i+1];
		histArr[3] = data;
		histSize++;

		//if the history exceeds the array,
		//start pushing data into histList
		if (histSize == 4)
		{
			histList.push_back(temp);
			
			//if histList is too big,
			//save it to disk for later retrieval
			if (histList.size() > 64)
			{
				//create iterator for histList
				std::list<int>::iterator histIter =
					histList.begin();

				//open a temporary output file
				//set to append
				output.open("TEMP.csv", ios::app);

				for (; histIter != histList.end();
					histIter++)
				{
					output << histSize << ", " *histIter;
				}

				//when done, close output file
				output.close();

				//clear histList
				histList.clear();

				//return true upon completion
				return true;
			}

			//return true upon completion
			return true;
		}

		//return true upon completion
		return true;
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
		return (((abs(histArr[1]) == abs(histArr[3]))
			&& histSize > 3)) ?
			true :
			false;
		
	}

void outputHandler::History::printHistArr()
{
	for (int i = 0; i < 4; i++)
	{
		cout << "History Array Element: " << i
			<< endl << "Data: " << histArr[i] << endl;
	}
}

void outputHandler::History::clearHist()
{
	for (int i = 0; i < 4; i++)
		histArr[i] = 0;
	histSize = 0;
	//clear & resize histList to keep it
	// under control
	//histList.clear();
	//histList.resize(0);
}