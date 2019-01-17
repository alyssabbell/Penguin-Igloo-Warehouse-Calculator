/*
Name: Alyssa Bell
Date: September 12th, 2017
Project: Penguin Warehouse

Purpose/Description: This program caculates the volume of ice cubes, and then determines how much the warehouse
must be to efficiently store the ice without much wasted space.

Error Checking: Checks for correct input file

Assumptions: The input file only contains numerical values, and that all lines in the input file are in the
same exact format

Summary of Methds:
calcBoxVolLiters() - this method takes in the l/w/h of each ice cube and calculates the volume of each cube in liters,
and adds the total volume of the ice cubes in liters

calcPools() - this method calculates the amount of Olympic-sized pools that can be filled with the
volume in liters of stored ice(using their total volume)

calcWarehouse() - this method takes in the array of cubes and sorts them from largest to smallest,
and determines how large the warehouse must be in centimeters

*/

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cmath>
#include "ItemType.h"


const int POOL_SIZEL = 2500000;
const int ARRAY_SIZE = 1000;
ItemType volArray[ARRAY_SIZE];
ItemType volStruct{};

using namespace std;

// Function Prototypes
float calcBoxVolLiters(/* IN */ItemType volArray[],/* IN */ int i, /* IN & OUT */float& totalCubeVol);
int calcPools(/* IN */float totalCubeVol);
void calcWarehouse(ItemType volArray[], float& finalW, float& finalH, float& totalL);

void main()
{
	ifstream din;

	din.open("ice.txt");

	int tempLength;
	int tempHeight;
	int tempWidth;
	char junkChar;
	// this holds the running tally of the volume of the cubes
	float totalCubeVol = 0;
	// counter variable to pass to helper function
	int i = 0;
	float finalW = 0;
	float finalH = 0;
	float totalL = 0;


	// check for input file
	if (!din)
	{
		cout << "File was not found. Please check your filename or directory." << endl;
	}
	// priming read
	din >> tempLength >> junkChar;


	// read through file while data is present
	while (din)
	{
		// read input lines and break up to lenght, width, and height
		din >> tempWidth >> junkChar >> tempHeight;
		volStruct.length = (float)tempLength;
		volStruct.width = (float)tempWidth;
		volStruct.height = (float)tempHeight;

		// store struct values into array
		volArray[i].length = volStruct.length;
		volArray[i].width = volStruct.width;
		volArray[i].height = volStruct.height;


		// call function to send volume calculation
		volStruct.volumeLiters = calcBoxVolLiters(volArray, i, totalCubeVol);
		volArray[i].volumeLiters = volStruct.volumeLiters;

		i++;
		din >> tempLength >> junkChar;
	}


	din.close();

	cout << "The data file has been processed." << endl << endl;

	// final sum of volume of all cubes in liters
	cout << "The total volume of the cubes is " << setprecision(12) << totalCubeVol << endl << endl;

	
	cout << "The amount of pools that you can fill: " << calcPools(totalCubeVol) << endl << endl;

	// this function call changes the array by reference
	calcWarehouse(volArray, finalW, finalH, totalL);

	cout << "In order to fit all of the ice cubes, the warehouse must be " << finalW << "cm x " << finalH << "cm x " << totalL <<"cm" << endl;
}


/*
pre: length width and height all have values that are greater than 0
post : the total volume of all ice cubes has been calculated and sent back to main
purpose : the purpose of this function is to take in the array, calculate the volume based on the array values
and then return the value to be inserted into the struct & array and run a tally of the total vol
of the ice cubes
*/
float calcBoxVolLiters(/* in */ItemType volArray[], /* in */int i, /* in & out*/ float& totalCubeVol)
{
	float vol = volArray[i].length * volArray[i].width * volArray[i].height;
	//vol = 
	vol = vol *.001;

	totalCubeVol = totalCubeVol + vol;

	return vol;
}


/*
pre: the total volume of the ice cubes has been calculated
post: the amount of Olympic-sized pools to be filled has been calcuted and sent back to main
purpose: This function takes in the total volume of the ice and determines how many pools can be
filled with ice/or water - for this assignment, there is no change in density between water or ice.
The amount of pools that can be filled is sent back to main.
*/
int calcPools(float totalCubeVol)
{

	int poolCount = 0;

	if (totalCubeVol >= POOL_SIZEL)
	{
		while (totalCubeVol >= POOL_SIZEL)
		{
			totalCubeVol = totalCubeVol - POOL_SIZEL;
			poolCount++;
		}
	}

	else
		poolCount = 0;

	return poolCount;

}


/*
pre: the array is unsorted and contains dimensions from input file
post: the array is now sorted from largest ice cube to smallest ice cube
purpose: Takes the ice cubes stored inside the array and arranges them in descending size
and then returns the ordered array
*/

void calcWarehouse(ItemType volArray[], float& finalW, float& finalH, float& totalL)
{
	// these values are all in centimeters
	float tempLength = 0;
	float tempWidth = 0;
	float tempHeight = 0;
	float tempLiters = 0;
	float dim1 = 0;
	float dim2 = 0;
	float dim3 = 0;

	// loop through array and sorting by the largest dimension
	for (int j = 0; volArray[j].length != 0; j++)
	{
		for (int k = j + 1; volArray[k].length != 0; k++)
		{

			if (volArray[k].length > volArray[j].length)
			{

				tempLength = volArray[j].length;
				tempWidth = volArray[j].width;
				tempHeight = volArray[j].height;
				tempLiters = volArray[j].volumeLiters;

				volArray[j].length = volArray[k].length;
				volArray[j].height = volArray[k].height;
				volArray[j].width = volArray[k].width;
				volArray[j].volumeLiters = volArray[k].volumeLiters;

				volArray[k].length = tempLength;
				volArray[k].width = tempWidth;
				volArray[k].height = tempHeight;
				volArray[k].volumeLiters = tempLiters;

			}


			// sorting by width for 2nd largest value
			if (volArray[k].width > volArray[j].width)
			{

				tempLength = volArray[j].length;
				tempWidth = volArray[j].width;
				tempHeight = volArray[j].height;
				tempLiters = volArray[j].volumeLiters;

				volArray[j].length = volArray[k].length;
				volArray[j].height = volArray[k].height;
				volArray[j].width = volArray[k].width;
				volArray[j].volumeLiters = volArray[k].volumeLiters;

				volArray[k].length = tempLength;
				volArray[k].width = tempWidth;
				volArray[k].height = tempHeight;
				volArray[k].volumeLiters = tempLiters;

			}
		}

		// during each iteration of the first for loop above, this will save the largest 3 dimensions
		// the 2 largest out of the 3 will become the finalW and finalH further down
		if (volArray[j].length > dim1)
		{
			dim1 = volArray[j].length;
		}

		if (volArray[j].width > dim2)
		{
			dim2 = volArray[j].width;
		}

		if (volArray[j].height > dim3)
		{
			dim3 = volArray[j].height;
		}

		/* add tallies of smallest dimentions to the finalL here
		   * if the next block placed is smaller than the previous block, it could be
		   placed along the side or above it if there is room so do not count it
		   in finalL
		   */
		if (volArray[j].length <= volArray[j].width && volArray[j].length <= volArray[j].height)
		{
			if (volArray[j].length > volArray[j + 1].length)
			{
				totalL = totalL + volArray[j].length;
			}
		}
		else if (volArray[j].width <= volArray[j].length && volArray[j].width <= volArray[j].height)
		{
			if (volArray[j].width > volArray[j + 1].width)
			{
				totalL = totalL + volArray[j].width;
			}
		}
		else if (volArray[j].height <= volArray[j].length && volArray[j].height <= volArray[j].width)
		{
			if (volArray[j].height > volArray[j + 1].height)
			{
				totalL = totalL + volArray[j].height;
			}
		}
	}

	// saving 2 largest values as the finalW and finalH before calculating the overall length
	// With this data set, the largest block is 1000 x 1000 x 1 - 1000 will become the width and 1000 will
	// become the height
	if (dim1 >= dim2 && dim1 >= dim3)
	{

		finalW = dim1;
	}
	if (dim2 >= dim1 && dim2 >= dim3)
	{
		finalH = dim2;
	}
	if (dim3 >= dim1 && dim3 >= dim2)
	{
		finalH = dim3;
	}


}

