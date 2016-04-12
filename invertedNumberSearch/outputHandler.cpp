#include "outputHandler.h"

#include <climits>
//needed to get max int size
//we want to find as many possible
//of these number combos as possible
#include <cmath>
#include <iostream>
#include <sstream>

#define HIST_ARRAY_SIZE 8
#define HIST_ARRAY_BACK HIST_ARRAY_SIZE-1


using namespace std;

//basic constructor
OutputHandler::OutputHandler()
{
	//find this compiler's max int size
	largestNum = INT_MAX;

	//counters
	numsProcessed = 0; //total processed numbers
	normProcessed = 0; //total terminal (non-looping) reversals processed
	loopProcessed = 0; //total looping reversals processed
	
	//Prepare save files by clearing old files &
	// adding column names
	//start with 
	ofstream outFile("terminatingNum.csv", std::fstream::out | std::fstream::trunc);
	hist.storeHist(outFile);

	//add credit & contact info
	outFile << "Data compiled in Stan Slupecki's (github: MisturDust319) 'invertedNumberSearch' program"
		<< endl;

	//add column names
	outFile << "Starting number, "
		<< "terminating Processed #, "
		<< "2nd to last #, "
		<< "History" << endl;

	outFile.close();

	//open save file
	outFile.open("loopingNum.csv", std::fstream::out | std::fstream::trunc);
	hist.storeHist(outFile);

	//add credit & contact info
	outFile << "data compiled in Stan Slupecki's (github: MisturDust319) 'invertedNumberSearch' program"
		<< endl;

	//add column names
	outFile << "Starting number, "
		<< "Looping Processed #, "
		<< "Last " << HIST_ARRAY_SIZE << " numbers, "
		<< "History" << endl;

	outFile.close();
	//debug vars
	//used to check for 'reversal cycles'
	//debugCount = 0;

	//instantly start the search
	startSearch();
}

int OutputHandler::reverseNumber(int num)
{
	// note the sign of the number
	// the return val should have
	// the same sign as the input
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
int OutputHandler::startSearch() {

	//num is used to track the most recent value
	int num;
	//rev is used to track num's reverse
	int rev;

	for (int start = 0; start <= largestNum; start++, numsProcessed++)
	{
		cout << "current #: " << start << endl;
		/*
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
		*/

		//reset the values of num and rev
		//set num to start's val
		num = start;
		rev = 0;

		// while num != 0
		// AND the history doesn't suggest we're
		// in a loop,
		// process down the current starting
		// number
		// note breaking the loop is handled internally
		while( 1 == 1 )
		{
			/*num -= reverse;
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
			*/

			//start by pushing num into history
			hist.pushData(num);

			// if num == 0, then we've reached the end
			// w/o a reversal loop
			if (num == 0)
			{
				/*//debug code

				cout << "Stub: reached 0." << endl
					<< "+++~History~+++" << endl;
				hist.printHistArr();
				cout << "--------------" << endl;
				*/
				
				//increment terminal reversal count
				normProcessed++;

				//open save file
				ofstream outFile("terminatingNum.csv", ios::out | ios::app);
				

				//add column names
				outFile << start << ", "
					<< normProcessed << ", "
					<< hist.getHistArrVal(HIST_ARRAY_BACK - 1) << ", ";

				hist.storeHist(outFile);
				//break the loop to start check for next num
				break;
			}

			//check if it looks like we're in a reversal loop
			//if so, break the loop, and save the history
			else if (hist.checkForLoop())
			{
				//increment the total found reversal loops
				loopProcessed++;
				//open save file
				ofstream outFile("loopingNum.csv", ios::out | ios::app);
				

				outFile << start << ", " << loopProcessed << ", ";

				for (int i = 0; i < HIST_ARRAY_SIZE; i++)
					outFile << hist.getHistArrVal(i) << ";";

				outFile << ", ";

				//store all of history from mem
				hist.storeHist(outFile);

				//close the output file
				outFile.close();

				/* some debug code
				cout << "broke a reversal loop" << endl;
				hist.printHistArr();
				*/

				//break the loop to start check for next num
				break;
			}
			
			// otherwise, keep processing until an endpoint or
			// loop is reached
			else
			{
				//get num's reverse
				rev = reverseNumber(num);
				hist.pushData(rev);

				//subtract rev from num
				num -= rev;

				//..and repeat
			}
		}
		//reset debug count for each unique number
		//debugCount = 0;

		//increment total numbers processed
		numsProcessed++;
		//clear the history
		hist.clearHist();
	}

	return 0;
}


