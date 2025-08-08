

# Photovoltaik-gestützte Waschmaschinenstart-Vorhersage

Dieses Programm dient zur Bestimmung des optimalen Zeitpunkts, um eine Waschmaschine mit Strom aus einer Photovoltaikanlage (PV-Anlage) zu betreiben.  
Die Berechnungen basieren auf Sonnenstandsdaten, aktueller Bewölkung und diffuser Solarstrahlung, kombiniert mit einem KI-gestützten Algorithmus.

---

## 1. Funktionsprinzip

### Sonnenstand (Azimut)

- **Grundlage:** optimale Ausrichtung der Sonne zur PV-Anlage.  
- **Datenquelle:** [Sonnenverlauf.de](https://www.sonnenverlauf.de)  
  → Im linken Panel unter „Sonnenrichtung“.  
- **Algorithmus:** NREL’s Solar Position Algorithm (SPA)  
  ([Dokumentation](https://www.nrel.gov/grid/solar-resource/solar-position.html))

### Wetter- und Strahlungsdaten

- **API:** Open-Meteo  
- **Parameter:**  
  - Bewölkungsgrad  
  - Diffuse Solar Radiation (DHI) – Energiemenge, die pro m² durch die Atmosphäre gelangt.

### Optimierungsalgorithmus

- Nutzt alle Eingangsdaten, um den energetisch günstigsten Startzeitpunkt zu bestimmen.

---

## 2. Kompilierung

```bash
# Einzelne Quellcode-Dateien kompilieren
g++ -g -O3 -fPIC -Wall -std=c++20 -c -o main.o main.cpp
g++ -g -O3 -fPIC -Wall -std=c++20 -c -o sonnen_position.o sonnen_position.cpp
g++ -g -O3 -fPIC -Wall -std=c++20 -c -o spa.o spa.c
g++ -g -O3 -fPIC -Wall -std=c++20 -c -o wetter_daten.o wetter_daten.cpp
g++ -g -O3 -fPIC -Wall -std=c++20 -c -o photovoltaic_forecast.o photovoltaic_forecast.cpp

# Signatur prüfen (optional)
openssl pkeyutl -verify -pubin -inkey scoring_pub_key.pem -rawin \
  -in scoring.o -sigfile scoring.o.sig

```
---

## 3. Linken

```bash
g++ -O2 -flto -fPIC -Wall -o vorhersage \
  main.o sonnen_position.o spa.o wetter_daten.o photovoltaic_forecast.o scoring.o \
  -lm -lcurl
```

---

## 4. Ausführen
```bash
./vorhersage <Jahr> <Monat> <Tag> <Longitude> <Latitude> <Sonnen-Azimut>
```
### Beispiele:
 Festes Datum
./vorhersage 2025 12 21 13.37532 52.51860 270.62

 Aktuelles Datum automatisch einfügen
./vorhersage $(date -d "today" +"%Y %m %d") 13.37532 52.51860 270.62

---

## 5. Geplante Erweiterungen (To-Do)

    Einbezug aktueller Strompreise

    Historische Hauslastdaten berücksichtigen

    Batteriestand der PV-Anlage einfließen lassen

    Sonnenauf- und -untergangszeiten einbeziehen

    Speicherung aller Daten in einer Datenbank

    QT-GUI für Linux entwickeln

    Daten für Grafana aufbereiten
