TARGET = sunnyload

FILES := scoring.o groq_ai.o
SIGFILE := scoring.o.sig groq_ai.o.sig
PUBKEY  := scoring_pub_key.pem

all: verify $(TARGET)

verify:
	@echo "== Prüfe Signaturen mit openssl pkeyutl =="
	@for f in $(FILES); do \
	    sig="$${f}.sig"; \
	    echo "Prüfe $$f ..."; \
	    if ! openssl pkeyutl -verify -pubin -inkey $(PUBKEY) -rawin -in "$$f" -sigfile "$$sig" >/dev/null 2>&1; then \
	        echo "Signaturprüfung fehlgeschlagen: $$f"; \
	        exit 1; \
	    fi; \
	done
	@echo "Alle Signaturen gültig"
	
sunnyload: main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o
	g++ -O3 -fPIC -Wall -o sunnyload main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o groq_ai.o -lm -lcurl -lpqxx

main.o: main.cpp
	g++ -g -O3 -fPIC -Wall -std=c++20 -c -o main.o main.cpp

sonnen_position.o: sonnen_position.cpp
	g++ -g -O3 -fPIC -Wall -std=c++20 -c -o sonnen_position.o sonnen_position.cpp

spa.o: spa.c
	g++ -g -O3 -fPIC -Wall -std=c++20 -c -o spa.o spa.c
	
wetter_daten.o: wetter_daten.cpp
	g++ -g -O3 -fPIC -Wall -std=c++20 -c -o wetter_daten.o wetter_daten.cpp
	
photovoltaic_forecast.o: photovoltaic_forecast.cpp
	g++ -g -O3 -fPIC -Wall -std=c++20 -c -o photovoltaic_forecast.o photovoltaic_forecast.cpp
	
