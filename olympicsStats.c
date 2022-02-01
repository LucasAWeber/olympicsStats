// function definitions

#include "olympicsStats.h"

void readFromFile (char fName [30], structCountries structCountry [COUNTRIES]) // Reads file and saves contents into arrays
{
	FILE *txtFile = fopen(fName, "r");

	for (int i = 0; i < COUNTRIES; i++)
	{
		fscanf(txtFile, "%s", structCountry[i].countryNames);
		for (int j = 0; j < MEDALCAT; j++)
		{
			fscanf(txtFile, "%d", &structCountry[i].country[j]);
		}
	}
}

void findTotalPerCountry (structCountries structCountry [COUNTRIES]) // Finds total number of medals per country
{
	for (int i = 0; i < COUNTRIES; i++)
	{
		structCountry[i].totalAllCountries = 0;
		for (int j = 0; j < MEDALCAT; j++)
		{
			structCountry[i].totalAllCountries += structCountry[i].country[j];
		}
	}
}

int findTotalPerMedal (structCountries structCountry [COUNTRIES], int totalAllMedals [MEDALCAT], int * whichMedal) // Finds total number of medals in each category
{
	int maxVal = 0;
	*whichMedal = 0;

	for (int i = 0; i < MEDALCAT; i++)
	{
		totalAllMedals[i] = 0;
		for (int j = 0; j < COUNTRIES; j++)
		{
			totalAllMedals[i] += structCountry[j].country[i];
		}
		if (totalAllMedals[i] > maxVal)
		{
			maxVal = totalAllMedals[i];
			*whichMedal = i;
		}
	}
	return maxVal;
}

void hHistogram (structCountries structCountry [COUNTRIES]) // Draws a nice graphic to visualize the values (horizontal histogram)
{
	for (int i = 0; i < COUNTRIES; i++)
	{
		printf("%-10s: ", structCountry[i].countryNames);
		for (int j = 0; j < structCountry[i].totalAllCountries; j++)
		{
			printf("*");
		}
		printf(" (%d)\n", structCountry[i].totalAllCountries);
	}
}

int searchCountry (char countryName [MAX_LENGTH_CNAME], structCountries structCountry [COUNTRIES]) // Searches for a country inputted by the user and returns the number of medals that country has (if found)
{
	for (int i = 0; i < COUNTRIES; i++)
	{
		if (strcmp(countryName, structCountry[i].countryNames) == 0)
		{
			return structCountry[i].totalAllCountries;
		}
	}
	return -1;
}

void rankTopThreeByTotal (structCountries structCountry [COUNTRIES]) // Ranks the top 3 countries based on total medals
{
	int rank[3] = {0,1,2};
	int maxVal = 0;
	int minVal = 0;
	int temp = 0;

	for (int i = 0; i < COUNTRIES; i++)
	{
		if (structCountry[minVal].totalAllCountries > structCountry[i].totalAllCountries)
		{
			minVal = i;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		maxVal = minVal;
		for (int j = 0; j < COUNTRIES; j++)
		{
			if ((structCountry[j].totalAllCountries > structCountry[maxVal].totalAllCountries) && ((i == 0 && j != rank[1] && j != rank[2]) || (i == 1 && j != rank[2] && j != rank[0]) || (i == 2 && j != rank[0] && j != rank[1])))
			{
				maxVal = j;
			}
		}
		rank[i] = maxVal;
	}
	for (int i = 0; i < 3; i++)
	{
		if (structCountry[rank[0]].totalAllCountries < structCountry[rank[1]].totalAllCountries)
		{
			temp = rank[0];
			rank[0] = rank[1];
			rank[1] = temp;
		}

		if (structCountry[rank[1]].totalAllCountries < structCountry[rank[2]].totalAllCountries)
		{
			temp = rank[1];
			rank[1] = rank[2];
			rank[2] = temp;
		}

		if (structCountry[rank[0]].totalAllCountries < structCountry[rank[2]].totalAllCountries)
		{
			temp = rank[0];
			rank[0] = rank[2];
			rank[2] = temp;
		}
	}

	printf("Rank top three based on total number of medals\n");

	for (int i = 0; i < 3; i++)
	{
		printf("%s (%d)\n", structCountry[rank[i]].countryNames, structCountry[rank[i]].totalAllCountries);
	}
}

void rankTopThreeByMedal (structCountries structCountry [COUNTRIES]) // Ranks top 3 countries based on gold medals
{
	int rank[3] = {0,1,2};
	int maxVal = 0;
	int minVal = 0;
	int temp = 0;

	for (int i = 0; i < COUNTRIES; i++)
	{
		if (structCountry[minVal].country[0] > structCountry[i].country[0])
		{
			minVal = i;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		maxVal = minVal;
		for (int j = 0; j < COUNTRIES; j++)
		{
			if ((structCountry[j].country[0] > structCountry[maxVal].country[0]) && ((i == 0 && j != rank[1] && j != rank[2]) || (i == 1 && j != rank[2] && j != rank[0]) || (i == 2 && j != rank[0] && j != rank[1])))
			{
				maxVal = j;
			}
		}
		rank[i] = maxVal;
	}
	for (int i = 0; i < 3; i++)
	{
		if (structCountry[rank[0]].country[0] < structCountry[rank[0]].country[0])
		{
			temp = rank[0];
			rank[0] = rank[1];
			rank[1] = temp;
		}

		if (structCountry[rank[1]].country[0] < structCountry[rank[2]].country[0])
		{
			temp = rank[1];
			rank[1] = rank[2];
			rank[2] = temp;
		}

		if (structCountry[rank[0]].country[0] < structCountry[rank[2]].country[0])
		{
			temp = rank[0];
			rank[0] = rank[2];
			rank[2] = temp;
		}
	}

	printf("Rank top three based on gold medals\n");

	for (int i = 0; i < 3; i++)
	{
		printf("%s (%d)\n", structCountry[rank[i]].countryNames, structCountry[rank[i]].country[0]);
	}
}

int findAllWithNoXMedals (structCountries structCountry [COUNTRIES], int indexMedal, int indexOfCountries [COUNTRIES]) // Find the number of countries that have no medals of an inputted category
{
	int total = 0;

	for (int i = 0; i < COUNTRIES; i++)
	{
		if (structCountry[i].country[indexMedal-1] == 0)
		{
			indexOfCountries[total] = i;
			total += 1;
		}
	}

	return total;
}

int findAllWithOnlyXMedals (structCountries structCountry [COUNTRIES], int indexMedal, int indexOfCountries [COUNTRIES]) // Finds the countries with only inputted medal ie has gold medals but no silver or bronze
{
	int total = 0;

	for (int i = 0; i < COUNTRIES; i++)
	{
		if ((structCountry[i].country[indexMedal-1] > 1) && ((indexMedal-1 == 0 && structCountry[i].country[1] == 0 && structCountry[i].country[2] == 0) || (indexMedal-1 == 1 && structCountry[i].country[0] == 0 && structCountry[i].country[2] == 0) || (indexMedal-1 == 2 && structCountry[i].country[0] == 0 && structCountry[i].country[1] == 0)))
		{
			indexOfCountries[total] = i;
			total += 1;
		}
	}

	return total;
}

int findCountryIndexWithMinOrMaxLength (int minOrMax, structCountries structCountry [COUNTRIES]) // Finds the country with the smallest strlen() or largest strlen() depending on users input
{
	int minMax = 0;

	if (minOrMax == 1)
	{
		for (int i = 0; i < COUNTRIES; i++)
		{
			if (strlen(structCountry[i].countryNames) < strlen(structCountry[minMax].countryNames))
			{
				minMax = i;
			}
		}
	}
	else if (minOrMax == 2)
	{
		for (int i = 0; i < COUNTRIES; i++)
		{
			if (strlen(structCountry[i].countryNames) > strlen(structCountry[minMax].countryNames))
			{
				minMax = i;
			}
		}
	}

	return minMax;
}

void vHistogram (structCountries structCountry [COUNTRIES]) // Draws a nice graphic to visualize the data (vertical histogram)
{
	int max = 0;
	int width = 0;

	for (int i = 0; i < COUNTRIES; i++)
	{
		if (strlen(structCountry[i].countryNames) > width)
		{
			width = strlen(structCountry[i].countryNames);
		}
	}

	for (int i = 0; i < COUNTRIES; i++)
	{
		for (int j = 0; j < (width / 2); j++)
		{
			printf(" ");
		}
		printf("%d", structCountry[i].totalAllCountries);
		for (int j = 0; j < (width / 2) - 1; j++)
		{
			printf(" ");
		}
		if (structCountry[i].totalAllCountries < 10)
		{
			printf(" ");
		}
		if (structCountry[i].totalAllCountries > max)
		{
			max = structCountry[i].totalAllCountries;
		}
	}

	printf("\n");

	for (int j = 0; j < max; j++)
	{
		for (int i = 0; i < COUNTRIES; i++)
		{
			for (int k = 0; k < (width / 2); k++)
			{
				printf(" ");
			}
			if (max - structCountry[i].totalAllCountries <= j)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
			for (int k = 0; k < (width / 2); k++)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < COUNTRIES; i++)
	{
		for (int k = 0; k < (width / 2) - (strlen(structCountry[i].countryNames) / 2); k++)
		{
			printf(" ");
		}
		if (strlen(structCountry[i].countryNames) % 2 == 0)
		{
			printf(" ");
		}
		printf("%s", structCountry[i].countryNames);
		for (int k = 0; k < (width / 2) - (strlen(structCountry[i].countryNames) / 2); k++)
		{
			printf(" ");
		}
	}

	printf("\n");
}
