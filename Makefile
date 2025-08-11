TARGET = sunnyload

FILE := scoring.o
SIGFILE  := scoring.o.sig
PUBKEY  := scoring_pub_key.pem#

all: verify $(TARGET)


verify:
	@echo "Prüfe Signatur..."
	@if openssl pkeyutl -verify -pubin -inkey $(PUBKEY) -rawin -in $(FILE) -sigfile $(SIGFILE); then \
	    echo "Signatur OK"; \
	else \
	    echo "Fehler: Signatur ungültig!"; \
	    exit 1; \
	fi


sunnyload: main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o
	g++ -O2 -fPIC -Wall -o sunnyload main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o -lm -lcurl -lpqxx


main.o: main.cpp
	g++ -O2 -fPIC -Wall -std=c++20 -c -o main.o main.cpp

sonnen_position.o: sonnen_position.cpp
	g++ -O2 -fPIC -Wall -std=c++20 -c -o sonnen_position.o sonnen_position.cpp

spa.o: spa.c
	g++ -O2 -fPIC -Wall -std=c++20 -c -o spa.o spa.c
	
wetter_daten.o: wetter_daten.cpp
	g++ -O2 -fPIC -Wall -std=c++20 -c -o wetter_daten.o wetter_daten.cpp
	
photovoltaic_forecast.o: photovoltaic_forecast.cpp
	g++ -O2 -fPIC -Wall -std=c++20 -c -o photovoltaic_forecast.o photovoltaic_forecast.cpp
	
