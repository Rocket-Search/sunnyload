





#include "spa.h"

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

extern int jahr;
extern int monat;
extern int tag;
extern double longitude;
extern double latitude;
extern double azimut_soll;
extern double azimut_ist;
extern string azimut_uhrzeit;

void sonnen_position()


{

	
	
	
	
	
	
	
	spa_data spa;

	
	
	
	
	spa.year = jahr;
	
	
	spa.month = monat;
	
	
	spa.day = tag;
	spa.hour        = 0;
	spa.minute      = 0;
	spa.second      = 0;
	
	spa.delta_ut1   = 0;
	
	spa.delta_t     = 70.70870833333333333333;
	
	spa.longitude   = longitude;
	
	
	spa.latitude    = latitude;
	
	spa.elevation   = 114.0;             
	spa.pressure    = 1013.25;
	spa.temperature = 20.0;
	spa.slope       = 0.0;
	spa.azm_rotation = 0.0;
	spa.atmos_refract = 0.5667;			
	spa.function    = SPA_ZA;

    
    for (int hour = 0; hour <= 24; ++hour) 
    {
        for (int minute = 0; minute < 60; ++minute) 
        {
            spa.hour = hour;
            spa.minute = minute;
            spa.second = 0;

            int result = spa_calculate(&spa);
            if (result == 0) 
            {
                
                if (fabs(spa.azimuth - azimut_soll) < 0.2) 
                {
                    
                    
                    azimut_uhrzeit = to_string(hour) + ":" + to_string(minute);
                    
                    azimut_ist = spa.azimuth;
					
					
					break;
                }
            }
            
            
            
            
            
            
        }
    }

    
}
