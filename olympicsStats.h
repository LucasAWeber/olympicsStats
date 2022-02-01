// include and define statements and function prototypes

#include <stdio.h>
#include <string.h>

#define COUNTRIES 10
#define MEDALCAT 3
#define MAX_LENGTH_CNAME 100

typedef struct structCountries
{
    int country [MEDALCAT];
	char countryNames [MAX_LENGTH_CNAME];
    int totalAllCountries;
}structCountries;

void readFromFile (char fName [30], structCountries country [COUNTRIES]);

void findTotalPerCountry (structCountries structCountry [COUNTRIES]);

int findTotalPerMedal (structCountries structCountry [COUNTRIES], int totalAllMedals [MEDALCAT], int * whichMedal);

void hHistogram (structCountries structCountry [COUNTRIES]);

int searchCountry (char countryName [MAX_LENGTH_CNAME], structCountries structCountry [COUNTRIES]);

void rankTopThreeByTotal (structCountries structCountry [COUNTRIES]);

void rankTopThreeByMedal (structCountries structCountry [COUNTRIES]);

int findAllWithNoXMedals (structCountries structCountry [COUNTRIES], int indexMedal, int indexOfCountries [COUNTRIES]);

int findAllWithOnlyXMedals (structCountries structCountry [COUNTRIES], int indexMedal, int indexOfCountries [COUNTRIES]);

int findCountryIndexWithMinOrMaxLength (int minOrMax, structCountries structCountry [COUNTRIES]);
 
void vHistogram (structCountries structCountry [COUNTRIES]);
