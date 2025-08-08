//compile
//g++ -g -O3 -fPIC -Wall -std=c++20 -c -o main.o main.cpp;
//g++ -g -O3 -fPIC -Wall -std=c++20 -c -o sonnen_position.o sonnen_position.cpp;
//g++ -g -O3 -fPIC -Wall -std=c++20 -c -o spa.o spa.c;
//g++ -g -O3 -fPIC -Wall -std=c++20 -c -o wetter_daten.o wetter_daten.cpp;
//g++ -g -O3 -fPIC -Wall -std=c++20 -c -o photovoltaic_forecast.o photovoltaic_forecast.cpp;
//openssl pkeyutl -verify -pubin -inkey scoring_pub_key.pem -rawin -in scoring.o -sigfile scoring.o.sig 
//link
//g++ -O2 -flto -fPIC -Wall -o vorhersage main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o -lm -lcurl

//execute
//./vorhersage 2025 12 21 13.37532 52.51860 270.62;
//./vorhersage $(date -d "today" +"%Y %m %d") 13.37532 52.51860 270.62;

using namespace std;

#include <cmath>
#include "spa.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <iomanip>
#include <chrono>




int aktuelle_stunde = -1;


int jahr = -1;
int monat = -1;
int tag = -1;
double longitude;
double latitude;
double azimut_soll;
double azimut_ist;
string azimut_uhrzeit;


vector<double> bewolkung_vec;

vector<double> diffuse_radiation;

vector<double> score_vec;

int main(int argc, char *argv[]) 
{
	
	auto jetzt = std::chrono::system_clock::now();
	time_t zeit = std::chrono::system_clock::to_time_t(jetzt);
	tm* lokal = std::localtime(&zeit);




	aktuelle_stunde = lokal->tm_hour;

	jahr = atoi(argv[1]);


	monat = atoi(argv[2]);
	tag = atoi(argv[3]);


	longitude = stod(argv[4]);
	latitude = stod(argv[5]);
	azimut_soll = stod(argv[6]);

	

	void sonnen_position();
	sonnen_position();

	void wetter_daten();
	wetter_daten();

	void photovoltaic_forecast();
	photovoltaic_forecast();

	
	void scoring();
	scoring();
	

	double top_score = -1;
	int top_zeit = -1;
	
	for (int i = 0; i < score_vec.size(); i++)
	{

				
		if (top_score < score_vec[i])
		{
			top_score = score_vec[i];
			top_zeit = i;
		}
	}
	

	cout<<"Um "<<top_zeit<<" Uhr ist die beste Zeit zum Stromverbrauch"<<endl;

	return(0);
}

