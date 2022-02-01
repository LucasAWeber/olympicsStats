// reads Olympic country stats from txt file passed in through the command line
// outputs data based on user input
// main function

#include "olympicsStats.h"

int main (int argc, char * argv[]) { // Main function

	// Variables
	structCountries structCountry[COUNTRIES];
	char fName[30];
	int choice;
	int totalAllMedals[MEDALCAT];
	char countryName[MAX_LENGTH_CNAME];
	int indexOfCountries[COUNTRIES];
	int whichMedal;
	int indexMedal = -1;
	int minOrMax = -1;
	int outputReturn;

	strcpy(fName, argv[1]);

	readFromFile(fName, structCountry);

	do {
		// Given options for the user to choose from
		printf ("\nHere is the menu \n\n");
		printf ("1. Display all country names read from file and the total number of medals won by each\n");
		printf ("2.    Function 2 - Find total number of medals won by each country\n");
		printf ("3.    Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
		printf ("4.    Function 4 – Display horizontal histogram\n");
		printf ("5.    Function 5 – Search for a country and return the total number of medals won by it\n");
		printf ("6.    Function 6 – Rank and display top three countries in order of total medals won\n");
		printf ("7.    Function 7 – Rank and display top three countries in order of total gold medals won\n");
		printf ("8.    Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
		printf ("9.    Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
		printf ("10.   Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");
		printf ("11.   Function 11 – Display vertical histogram\n");
		printf ("12.    Exit\n");

		printf ("Enter your choice: ");
		scanf ("%d", &choice);
		printf("\n");

		switch (choice) { // Calls functions and executes code based on users input
		case 1:

			for (int i = 0; i < COUNTRIES; i++)
			{
				printf("Country: %s, Gold = %d, Silver = %d, Bronze %d\n", structCountry[i].countryNames, structCountry[i].country[0], structCountry[i].country[1], structCountry[i].country[2]);
			}
			break;
		case 2:
			findTotalPerCountry(structCountry);
			for (int i = 0; i < COUNTRIES; i++)
			{
				printf("Country %s = %d\n", structCountry[i].countryNames, structCountry[i].totalAllCountries);
			}
			break;
		case 3:
			findTotalPerCountry(structCountry);
			outputReturn = findTotalPerMedal(structCountry, totalAllMedals, &whichMedal);
			printf("Medal = Gold, Total = %d\n", totalAllMedals[0]);
			printf("Medal = Silver, Total = %d\n", totalAllMedals[1]);
			printf("Medal = Bronze, Total = %d\n", totalAllMedals[2]);
			printf("Maximum number of medals = %d in category (", outputReturn);
			if (whichMedal == 0)
			{
				printf("Gold");
			}
			else if (whichMedal == 1)
			{
				printf("Silver");
			}
			else
			{
				printf("Bronze");
			}
			printf(")\n");
			break;
		case 4:
			findTotalPerCountry(structCountry);
			hHistogram(structCountry);
			break;
		case 5:
			findTotalPerCountry(structCountry);
			printf("Searching for which country? ");
			while((getchar()) != '\n');
			scanf("%s", countryName);
			outputReturn = searchCountry(countryName, structCountry);
			if (outputReturn == -1)
			{
				printf("Not found\n");
			}
			else
			{
				printf("Found it - %s has a total of %d medals\n", countryName, outputReturn);
			}
			break;
		case 6:
			findTotalPerCountry(structCountry);
			rankTopThreeByTotal(structCountry);
			break;
		case 7:
			rankTopThreeByMedal(structCountry);
			break;
		case 8:
			indexMedal = -1;
			while (indexMedal < 1 || indexMedal > 3)
			{
				while((getchar()) != '\n');
				printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver, 3 for Bronze? ");
				scanf("%d", &indexMedal);
			}
			outputReturn = findAllWithNoXMedals(structCountry, indexMedal, indexOfCountries);
			printf("Number of countries with no ");
			if (indexMedal == 1)
			{
				printf("Gold");
			}
			else if (indexMedal == 2)
			{
				printf("Silver");
			}
			else if (indexMedal == 3)
			{
				printf("Bronze");
			}
			printf(" medals = %d\n", outputReturn);
			break;
		case 9:
			indexMedal = -1;
			while (indexMedal < 1 || indexMedal > 3)
			{
				while((getchar()) != '\n');
				printf("Which medal do you want to look for - Type 1 for Gold, 2 for Silver, 3 for Bronze? ");
				scanf("%d", &indexMedal);
			}
			outputReturn = findAllWithOnlyXMedals(structCountry, indexMedal, indexOfCountries);
			printf("Number of countries with ONLY ");
			if (indexMedal == 1)
			{
				printf("Gold");
			}
			else if (indexMedal == 2)
			{
				printf("Silver");
			}
			else if (indexMedal == 3)
			{
				printf("Bronze");
			}
			printf(" medals = %d\n", outputReturn);
			for (int i = 0; i < outputReturn; i++)
			{
				printf("%s", structCountry[indexOfCountries[i]].countryNames);
			}
			printf("\n");
			break;
		case 10:
			minOrMax = -1;
			while (minOrMax != 1 && minOrMax != 2)
			{
				while((getchar()) != '\n');
				printf("Do you want min (enter 1) or max (enter 2)? ");
				scanf("%d", &minOrMax);
			}
			outputReturn = findCountryIndexWithMinOrMaxLength(minOrMax, structCountry);
			if (minOrMax == 1)
			{
				printf("The country name with minimum length = %s\n", structCountry[outputReturn].countryNames);
			}
			else if (minOrMax == 2)
			{
				printf("The country name with maximum length = %s\n", structCountry[outputReturn].countryNames);
			}
			break;
		case 11:
			findTotalPerCountry(structCountry);
			vHistogram(structCountry);
			break;
		case 12:

			break;

		default: printf ("That is an invalid choice\n");

		}

	} while (choice != 12); // Exits while loop when user inputs 12


	return 0;
}

