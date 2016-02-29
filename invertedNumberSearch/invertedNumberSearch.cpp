// invertedNumberSearch.cpp : This program is meant to find then
// record a pattern I noticed back in high school while messing
// around on a calculator
// If you take a number, reverse it but keeping the same sign
// (so -123 reversed is -321), then 
// subtract the reverse from the original number, and repeat
// in that same manner, three things can happen:
//*************
// 1. if the number is less than two digits, you just get zero, as
//		you can't really reverse a single digit
// 2. the number eventually, after bouncing around a while, becomes zero
//		notably, it seems the last digit before zero is always composed
//		of '9's and '0's
// 3. the number eventually becomes reduced to cycling through 4 digits:
//		a, b, -a, -b, (where a and -a, and b and -b are the same magnitude,
//		but opposite signs)
//*************
// The goal is to record:
//-conditions 1 and 2 in the same file, with 
//	-the index of the current number out of all processed numbers
//	-the index of the current number out of all the cond 1 & 2 nums
//	-the progression to zero (history)
//	-the number itself and the digit preceding zero
//-condition 3 in a seperate file,
//	-the index of the current number out of all processed numbers
//	-the index of the current number out of all the cond 3 nums
//	-the progression to zero (history)
//	-the 'cycle' of a, b, -a, -b

//#include "stdafx.h"
#include <iostream>

using namespace std;

// reverse number takes an int, and returns
// a reversal of that int while also keeping
// the same sign (i.e -123 becomes -321)
int reverseNumber(int num)
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
		reverseNum	=	reverseNum * 10;
		reverseNum	+=	num % 10;
		num			/=	10;
	}

	return reverseNum * sign;
}

int main()
{
	cout << reverseNumber(-5021) << "\n";

    return 0;
}

