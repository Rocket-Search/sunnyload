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


using namespace std;




int aktuelle_stunde = -1;
double top_score = -1;
int top_zeit = -1;
	

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
	
	
	
	
	
	for (int i = 0; i < score_vec.size(); i++)
	{
		
				
		if (top_score < score_vec[i])
		{
			top_score = score_vec[i];
			top_zeit = i;
		}
	}
	
	
	cout<<"Um "<<top_zeit<<" Uhr Lokalzeit ist die Spitzen Zeit zum Stromverbrauch erreicht"<<endl;
/*	
UNDER CONSTRUCTION

	
	
	void write_to_db();
	write_to_db();
	
*/
	
	
	return(0);
}

