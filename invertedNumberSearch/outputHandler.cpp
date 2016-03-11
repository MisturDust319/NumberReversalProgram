#include "outputHandler.h"

#include <limits>
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
outputHandler::outputHandler()
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

	//add column names
	outFile << "Starting number, "
		<< "terminating Processed #, "
		<< "2nd to last #, "
		<< "History" << endl;

	outFile.close();

	//open save file
	outFile.open("loopingNum.csv", std::fstream::out | std::fstream::trunc);
	hist.storeHist(outFile);

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

int outputHandler::reverseNumber(int num)
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
int outputHandler::startSearch() {

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


outputHandler::History::History()
	{
		for (int i = 0; i < HIST_ARRAY_SIZE; i++)
			histArr[i] = 0;
		histSize = 0;
	}

// pushes data onto the History list & array
// returns true if successful
bool outputHandler::History::pushData(int data)
	{

		//temp will hold elem 0 if we need to push
		//it back into the history list
		int temp = 0;
		if (histSize > (HIST_ARRAY_BACK))
		{
			//if the history fills the array,
			//data needs to be pushed into histList
			//temp will store the data to be pushed
			//into histList
			temp = histArr[0];
		}
		//start by pushing all data back one slot
		//in the array
		for (int i = 0; i < HIST_ARRAY_BACK; i++)
			histArr[i] = histArr[i+1];
		histArr[HIST_ARRAY_BACK] = data;
		histSize++;

		//if the history exceeds the array,
		//start pushing data into histList
		if (histSize > HIST_ARRAY_SIZE)
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
				ofstream ioFile("TEMP.csv", ios:: out | ios::app);

				for (; histIter != histList.end();
					histIter++)
				{
					ioFile << histSize << ", " << *histIter << endl;
				}

				//when done, close output file
				ioFile.close();

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

		// when these conditions are met, you know you have a reversal loop
		
		// first, checks should only be possible when enough
		// data is in the array
	if (histSize > HIST_ARRAY_BACK)
	{
		// if the most recent's absolute val is equal to the
		// opposite of the value 2 computations back
		if (histArr[HIST_ARRAY_BACK - 2] == histArr[HIST_ARRAY_BACK] * -1)
			return true;
		// if the most recent's absolute val is equal to the
		// opposite of the value 4 computations back
		else if(histArr[HIST_ARRAY_BACK - 4] == histArr[HIST_ARRAY_BACK] * -1)
			return true;
		else
			return false;
	}
	else
		return false;
}

void outputHandler::History::printHistArr()
{
	for (int i = 0; i < HIST_ARRAY_SIZE; i++)
	{
		cout << "History Array Element: " << i
			<< endl << "Data: " << histArr[i] << endl;
	}
}

void outputHandler::History::clearHist()
{
	for (int i = 0; i < HIST_ARRAY_SIZE; i++)
		histArr[i] = 0;
	histSize = 0;
	// clear histList to prevent data from being
	// carried between old and new calculations
	histList.clear();

	//clear the TEMP.CSV file
	ofstream temp("TEMP.CSV", ios::trunc);
	temp.close();
}

bool outputHandler::History::storeHist(ofstream& saveFile)
{
	ifstream histFile("TEMP.CSV", ios::in);
	if (histFile.is_open())
	{
		//tac the history onto the end of the save file
		//start with the data stored on disk
		//begin with just one item
		//making sure we didn't open to EOF
		if (histFile)
		{
			std::string data;
			histFile >> data;
			saveFile << data;
		}
		//then do the rest, with the proper deliminating char
		while (histFile)
		{
			std::string data;
			histFile >> data;
			saveFile << "; " << data;			
		}

		//then store the data in the history list
		for (std::list<int>::iterator iter = histList.begin();
		iter != histList.end();
			iter++)
		{
			saveFile << "; " << *iter;
		}

		int i = 0;
		if (histSize < 8)
			i = HIST_ARRAY_SIZE - histSize;
		//Store the data in the history array
		for (; i < HIST_ARRAY_SIZE; i++)
		{
			saveFile << "; " << histArr[i];
		}
		
		//add the final newline
		saveFile << endl;

		return true;
	}
	//otherwise, return false
	else
	{
		cerr << "Save File failed to open" << endl;
		return false;
	}
}

int outputHandler::History::getHistArrVal(int index)
{
	return histArr[index];
}