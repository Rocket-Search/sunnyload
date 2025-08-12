
































































/*
Fehlerbehandlung: try-catch, segv
auf Datumsaufruf NOW als jetztiges Datum als Parameter
#Punkte System für beste Zeit der "waschmaschine". Gewichtungen erheben
Tages verhsage, 6h und 4h
Alle Variable zuvor initialiseren mit -1 oder sonst was und out of range abfangen
#KI Vorschlag algirthmus verwenden/testen. Besser Gewichtung von Sonnenposition ???
Drei alternativ Zeiten außer der top_zeit/top_score anbieten
make file für PRD
spa.delta_t (sonnen_position.cpp) ggf. variable halten
konfiog file für werte lesen
open-meteo 180 Grad azimut Umrechzung für 360 Grad Angabe (237° - 180 = 57)
open-meteo Dachneigung einbeziehen bzw. in Programm Parameter Aufruf
Gewichtungen anpassen (Azimut Zeit ????)
Zeitlänge des Geplanten Stromverbruachs (Waschmaschine ca. 3H) in parameter einbeziehen
bei PRD signature check im code object file einbauen und/oder Lizenzschlüssel hinzufügen.
in SQLlite oder berkleyDB Lokal DB schreiben als postgres alterntive
rrdtool integraion 
*/
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
#include <regex>

using namespace std;




int aktuelle_stunde = -1;
double top_score = -1;
int top_zeit = -1;
string ki_vorschlaege_durchschnts_zeiten;


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


vector<string> ai_models_vec;
string ai_models;
vector<string> ai_models_vorschlag;


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

	
	
	
	
	
	
	
	





	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
	
	
	
	
	
	ai_models_vec = { "llama-3.3-70b-versatile", "llama-3.1-8b-instant", "gemma2-9b-it", "moonshotai/kimi-k2-instruct",};
	
	
	
	for (int i = 0; i < ai_models_vec.size() ; i++)
	{
		ai_models = ai_models_vec[i];
		
		void groq_ai();
		groq_ai();
	}
	
	
	vector<string> ki_uhrzeit_vorschlag;
	for (int i = 0; i < ai_models_vorschlag.size(); i++)
	{
		

		
		std::regex pattern(R"(([01]?[0-9]|2[0-3]):[0-5][0-9])");
		auto words_begin = std::sregex_iterator(ai_models_vorschlag[i].begin(), ai_models_vorschlag[i].end(), pattern);
		auto words_end = std::sregex_iterator();
		
		for (std::sregex_iterator i = words_begin; i != words_end; ++i) 
		{
			std::smatch match = *i;
			
			ki_uhrzeit_vorschlag.push_back(match.str());
		}
		
	}
	
	int wo_ist_doppelpunkt = -1;
	int ki_uhrzeit_stunde = -1;
	int ki_uhrzeit_minute = -1;
	double durchnitszeit = -1;
	for (int i = 0; i < ki_uhrzeit_vorschlag.size(); i++)
	{
		
		wo_ist_doppelpunkt = ki_uhrzeit_vorschlag[i].find(":" );
		ki_uhrzeit_stunde = stoi(ki_uhrzeit_vorschlag[i].substr(0 , wo_ist_doppelpunkt));
		
		ki_uhrzeit_minute = stoi(ki_uhrzeit_vorschlag[i].substr(wo_ist_doppelpunkt + 1, ki_uhrzeit_vorschlag[i].length()));
		
		durchnitszeit = durchnitszeit + ((ki_uhrzeit_stunde*60)+ki_uhrzeit_minute);
		
		
	}
	
	durchnitszeit = durchnitszeit / ki_uhrzeit_vorschlag.size();
	
	
	durchnitszeit = durchnitszeit / 60;
    
    
    double stunden;
    
    double minutenDezimal = modf(durchnitszeit, &stunden) * 60; 

	
    int minuten = static_cast<int>(round(minutenDezimal)); 
    cout<<"Beste Solarenergie nach KI Vorschlag um "<<stunden<<":"<<minuten<<" Uhr"<<endl;
    
    ki_vorschlaege_durchschnts_zeiten.append(to_string((int)stunden) + ":" + to_string((int)minuten));
	
	
	
	
	
	
	
	
	
	
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
	
	
	cout<<"Beste Solarenergie nach lokalen Alghriothmus Vorschlag um "<<top_zeit<<" Uhr"<<endl;
	
	
	
	
/*	
	void write_to_db();
	write_to_db();
*/	
	

	
	
	return(0);
}

