****************************************************************************
**~  Author: Stan Slupecki		 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**~  Git Account: MisturDust319	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
****************************************************************************
**~	Program Description	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
****************************************************************************
invertedNumberSearch.cpp : 
This program is meant to find then
record a pattern I noticed back in high school while messing
around on a calculator
If you take a number, reverse it but keeping the same sign
(so -123 reversed is -321), then 
subtract the reverse from the original number, and repeat
in that same manner, three things can happen:

1. if the number is a single, you just get zero, as
		you can't really reverse a single digit
2. the number eventually, after bouncing around a while, becomes zero
		however, it seems the last digit before zero is always composed
		of '9's and '0's
3. the number eventually becomes reduced to cycling through 8 digits:
		a, b, -a, -b, (where a and -a, and b and -b are the same magnitude,
		but opposite signs) and their corresponding reversals, though
		the ordering of these numbers vary
****************************************************************************
**Goals
****************************************************************************
**	~Important (necessary to meet goals)
****************************************************************************
		The goal is to record:
		-conditions 1 and 2 in the same file, with 
			-the index of the current number out of all processed numbers
			-the index of the current number out of all the cond 1 & 2 nums
			-the progression to zero (History)
			-the number itself and the digit preceding zero
		-condition 3 (I call it a 'reversal loop' in a seperate file,
			-the index of the current number out of all processed numbers
			-the index of the current number out of all the cond 3 nums
			-the progression to zero (History)
			-the 'cycle' of a, b, -a, -b and their reversals
****************************************************************************
**	~Other (extra potentially nice features)
****************************************************************************
		-hook up to a PostgreSQL database instead of using CSV text files
****************************************************************************
****************************************************************************