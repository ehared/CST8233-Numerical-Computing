
/************************************************************************************************************************
	Filename:			Ass2.c
	Version:			1.0
	Student Name:		Mahad Hared
	Student #:			040911519
	Course:				CST 8233 - Numerical Computing
	Section:			310
	Lab Section:		313
	Assignment:			1
	Assignment name:	Moore’s Law
	Due Date:			November 15, 2019
	Submission Date:	November 15, 2019
	Professor:			Hala Own
	Lab Instructor:		Hala Own
*************************************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // need this to get the line identification
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* global variables */
typedef enum { FALSE = 0, TRUE } BOOL;
double a, b, sumX, sumY, sumXY, sumX2;	

/* function declarations */
void readFile(int* recs);
void calcRegression(int recs);
void extrapolation();

/************************************************************************************************************************
	Function name:				main()
	Purpose:					main function

	Function InParameters:		none
	Funcstion OutParameters:	int - 0 for successful execution
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
int main() {

	BOOL running = TRUE;
	int records = 0;				/* count of data points */
	char selection;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Menu
	while (running) {
		printf("LEAST_SQUARES LINEAR REGRESSION\n\n");
		printf("MENU\n");
		printf("1: Exponential Fit\n");
		printf("2: Quit\n");
		scanf(" %c", &selection);
		switch (selection) {
		case '1':
			readFile(&records);
			calcRegression(records);
			extrapolation();
			break;
		case '2': 
			printf("The program will now close."); 
			running = FALSE;
			break; // exit program
		default: printf("Please enter a valid option.\n");
		}
	}
	return 0;
}
/************************************************************************************************************************
	Function name:				readFile(int* size)
	Purpose:					Reads input from a file and assigns the global variables to be used in calculating 
								exponential regression

	Function InParameters:		number of records in the file
	Funcstion OutParameters:	void
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
void readFile(int* recs) {

	FILE* fp;
	char buff[200], filename[50];
	int n = 0;
	int row = 0;
	double x = 0;
	double y = 0;

	printf("Please enter the name of the file to open : "); /* take user input for the name of the file to open */
	scanf("%s", &filename);

	fp = fopen(filename, "r"); /* open file */
	if (fp == NULL) { /* check if the file is null */
		printf("ERROR: could not open file.\n");
		printf("Program will now close....\n"); 
		exit(0); /* exit the program if no file is found */
		return;
	}
	while (fgets(buff, 200, fp) != NULL) {  /* print file content to screen */
		printf("%s", buff);
		/* track number of records in the file */
		n++;
	}
	
	printf("\nThere are %d records\n\n", --n);
	rewind(fp); /* reset position of file pointer */
	
	while (fgets(buff, 200, fp) != NULL) {
		if (row > 0) { /* skip header of text file , assumption: the first row is always a header*/
			sscanf(buff, "%lf %lf", &x, &y);
			sumX += x;    /* calculate the sums to be used in exponential regression */
			sumY += log(y);
			sumXY += x * log(y);
			sumX2 += pow(x, 2);
		}
		row++;
	}
	*recs = n;
	fclose(fp); /* close the file */

}
/************************************************************************************************************************
	Function name:				calcRegression(int* size)
	Purpose:					To calculate the a and b constants of a exponential regression

	Function InParameters:		int size = the number of records
	Funcstion OutParameters:	void
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
void calcRegression(int size) {

	double numerator;
	double denominator;
	double aZero;
	double yMean = sumY / size;
	double xMean = sumX / size;

	/* calculate a and b constants */
	numerator = (size * sumXY) - (sumX * sumY);
	denominator = (size * sumX2) - (pow(sumX, 2));
	b = numerator / denominator; /* a1 */
	aZero = yMean - (b * (xMean - 1970));  /* a0 */
	a = exp(aZero); /* A */

	printf("Linear Regression Fit: transistor count = %.3e * exp(%.3e * (year-1970))\n", a, b);

}
/************************************************************************************************************************
	Function name:				extrapolation()
	Purpose:					To calculate extrapolation

	Function InParameters:		none
	Funcstion OutParameters:	void
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
void extrapolation() {
	BOOL RUNNING = TRUE;
	char choice;
	double year;
	double transCount = 0; /* transistor count */
	double exponent = 0;
	double rOfChange = 0;
	/* Extrapolation Menu */
	while (RUNNING) {
		printf("\nMENU\n");
		printf("1: Extrapolation\n");
		printf("2: Quit\n");
		scanf(" %c", &choice);
		switch (choice) {
		case '1':
			printf("Please enter the year to extrapolate to: ");
			scanf("%lf", &year);
			while (getchar() != '\n'); // clears scanf buffer

			/* calculate transistor count */
			exponent = (double)(b * (year - 1970)); 
			transCount = a * exp(exponent);
			rOfChange = transCount * b; /* rate of count increase */

			printf("Year: %.0lf\n", year);
			printf("transistor count = %.3e\n", transCount);
			printf("rate of count increase = %.3e transistors/year\n", rOfChange);
			break;
		case '2': 
			RUNNING = FALSE;
			printf("\n");
			break; /* exit loop */
		default: printf("Please enter a valid option.\n");
		}
	}
}