/************************************************************************************************************************
	Filename:			Ass1.c
	Version:			1.0
	Student Name:		Mahad Hared
	Student #:			040911519
	Course:				CST 8233 - Numerical Computing
	Section:			310
	Lab Section:		313
	Assignment:			1
	Assignment name:	Building Motion Simulation
	Due Date:			September 29, 2019
	Submission Date:	September 29, 2019
	Professor:			Hala Own
	Lab Instructor:		Hala Own
*************************************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // need this to get the line identification
#include <stdio.h>
#include <math.h>

typedef enum { FALSE = 0, TRUE} BOOL;
void evaluateSeries();
/************************************************************************************************************************
	Function name:				main
	Purpose:					main function
									- Calls evaluateSeries function to evaluate a Maclaurin series based on user input
	Function InParameters:		none
	Funcstion OutParameters:	int - 0 for successful execution
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
int main() {
	
	BOOL running = TRUE;
	char selection;
	// Menu
	while (running) {
		printf("Evaluate the Maclaurin Series approximation to exp(-t) * cos(t)\n\n"); // Menu 
		printf("1: Evaluate the series\n");
		printf("2: Quit\n");
		scanf("%c", &selection);
		while (getchar() != '\n'); // clears scanf buffer
		switch (selection) {
		case '1': evaluateSeries(); break;
		case '2': printf("The program will now close.\n"); running = FALSE; break; // exit program
		default: printf("Please enter a valid option.\n");
		}
	}
	return 0;
}
/************************************************************************************************************************
	Function name:				evaluateSeries
	Purpose:					Evaluate Maclaurin Series based on user input
	Function InParameters:		none
	Funcstion OutParameters:	none
	Version:					1.0
	Author:						Eltire Hared
*************************************************************************************************************************/
void evaluateSeries() {
	int nTerms; // number of terms to compute
	double tRange; // range of t in increments
	double t = 0.0;
	double inc;
	double firstTruncTerm = 0.0; 
	double sValue; // series value
	double eValue; // exact value
	double eError; // exact % error
	double tError; // trunc. % error

	 // Table Headings 
	char tHeading[] = "t";
	char series[] = "Series";
	char exactValue[] = "Exact";
	char exactError[] = "Exact % Error";
	char truncError[] = "Trunc. % Error";

	// Display menu options and verify the input is within acceptable range for both # of terms and increments
	printf("Evaluating the series:\n");
	
	// Check to see #terms is between 1 -> 5
	do {
		printf("Please enter the number of terms in the series (max 5 terms): ");
		scanf("%d", &nTerms);
		while (getchar() != '\n'); // clear buffer
	} while (nTerms <= 0 || nTerms >= 6); 

	// Check to see increment value is within (0.0 -> 2.0)
	do {
		printf("Please enter the range of t to evaluate in 10 increments (0.0 < t < +2.0): ");
		scanf("%lf", &tRange);
		while (getchar() != '\n');
	} while (tRange < 0.0 || tRange > 2.0); 

	// Calculate increments based on range inputed by the user
	inc = tRange / 10; 
	
	printf("\n\nMACLAURIN SERIES\n\n");

	// Table Headings, used formating to keep alignment of headers
	printf("%-15s %-15s %-15s %-15s %-15s\n\n",tHeading,series,exactValue,exactError,truncError);

	// f(a) when a = 0, f(0) = 1 series value = 1
	sValue = 1;
	eValue = exp(-t) * cos(t); // exact value = e^(-t) * cos(t) when t = 0
	eError = 100 * (eValue - sValue) / eValue; // Exact % Error = 100  * ( exact value – series value ) / exact value
	tError = 100 * (firstTruncTerm / sValue); // Truncation % Error = 100 * first truncated term / series value.

	printf("%-15e %-15e %-15e %-15e %-15e\n", t, sValue, eValue,eError,tError);

	for (int i = 0; i < 10; i++) { 
		// t increases by increment
		t = t + inc; 
		
		if (nTerms == 1) { 
			// D1 = (-x) -> f(0) - D1(0)
			sValue = 1 - t;
			firstTruncTerm = -t;  // first truncated term -> Remainder R(n+1)
		}
		else if (nTerms == 2) { 
			// D2 = 0 -> f(0) - D1(0) + 0
			sValue = 1 - t;
			// R(3) = ( t ^ 3) / 3
			firstTruncTerm = (t * t * t) / 3;
		}
		else if (nTerms == 3) {
			// D3 = (x^3) / 3  -> f(0) - D1(0) + D3(0)
			sValue = 1 - t + ( ( t * t * t) / 3);
			// R(4) = - ( t ^ 4 ) / 6
			firstTruncTerm = -(t * t * t * t) / 6;
		}
		else if (nTerms == 4) { 
			// D4 = -(x^4)/6  -> f(0) - D1(0) + D3(0) - D4(0)
			sValue = 1 - t + ((t * t * t) / 3) - ((t * t * t * t) / 6);
			// R(5) = ( t ^ 5 ) / 30 
			firstTruncTerm = (t * t * t * t * t) / 30;
		}
		else if (nTerms == 5) { 
			// D5 = (x^5) / 30 -> f(0) - D1(0) + D3(0) - D4(0) + D(5)
			sValue = 1 - t + ((t * t * t) / 3) - ((t * t * t * t) / 6) + ((t * t * t * t * t) / 30);
			// R(6) = ( t ^ 7 ) / 630
			firstTruncTerm = -(t * t * t * t * t * t * t) / 630;
		}

		eValue = exp(-t) * cos(t); // exact value = e^-t * cos(t)
		eError = 100 * (eValue - sValue) / eValue; // calculates Exact % Error
		tError = 100 * (firstTruncTerm / sValue); // calculates Trunc % Error

		// Print Values using formating to keep alignment
		printf("%-15e %-15e %-15e %-15e %-15e \n", t, sValue, eValue, eError, tError);
	}
	
	printf("\n\n");
}