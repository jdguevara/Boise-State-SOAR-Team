Author: Garrett Wells
Date: 11/23/2017

This directory contains my version of the project that is optimized for speed. The only major differences between this
code and the code in the main project folder are listed below.

	1) Only 100 data points are collected. This is for testing purposes to prevent an infinite data collection loop.

	2) Several global variables are initialized but the major changes can be found in the writeToCSV() function.
	This function contains details explaining the code and suggested improvements.


Additional Resources:

	If we pursue writing to a file in bytes we will need a converter method to read the data in bytes and convert
	to a csv/text file. 

	To do this I have included a bare bones commandline app, one_byte.java, to do this. It almost deffinetly does not
	work but outlines how to read the data out of the file and convert it to text. Should provide a base to work off of.

Hope this is helpful.
