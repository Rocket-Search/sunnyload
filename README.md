# ☀️🧺 Photovoltaik-gestützte Waschmaschinenstartprognose

Dieses Programm ermittelt den **optimalen Startzeitpunkt** für eine Waschmaschine,  
um den Betrieb möglichst vollständig mit Strom aus einer **Photovoltaikanlage (PV-Anlage)** zu decken.  
Als Ergebnis wird der Zeitpunkt mit der voraussichtlich **maximal verfügbaren PV-Leistung** ausgegeben.

---

## 📊 Grundlage der Berechnungen
Die Berechnungen basieren auf:

- 🌞 **Sonnenstandsdaten** (Azimut, Elevation), berechnet mit dem [Solar Position Algorithm (SPA) des NREL](https://midcdmz.nrel.gov/spa/)  
- ☁️ **Bewölkungsdaten** und **DHI-Werte** (Diffuse Horizontal Irradiance) von [Open-Meteo](https://open-meteo.com/) (24h-Vorhersage)  
- 🤖 **KI-gestützter Bewertungsalgorithmus**, entwickelt vom Autor *(nicht unter GPLv3, Weitergabe nur mit Zustimmung)*

---

## 📦 Voraussetzungen

- 📚 `libcurl`  
- 📚 `libpqxx`  
- 🌐 Internetzugriff auf Wetterdaten

---

## 🛠️ Kompilieren
Das Programm **sunnyload** kann durch einfaches Ausführen von:

```bash
make
```
kompiliert werden.

Getestet unter:

    🐧 g++ (GCC) 15.1.1 auf Kernel Linux 6.14.6-300.x86_64
    🍓 g++ (Raspbian 12.2.0-14+rpi1) 12.2.0 auf Kernel Linux 6.6.74+rpt-rpi-v7

▶️ Ausführung

```bash
./sunnyload <Jahr> <Monat> <Tag> <Längengrad> <Breitengrad> <Azimut>
./sunnyload 2025 12 21 13.37532 52.51860 244.46
./sunnyload $(date -d "today" +"%Y %m %d") 13.37532 52.51860 244.46
```

📍 Tipp:
Längen- und Breitengrad sowie Azimut können z. B. über
https://www.sonnenverlauf.de ermittelt werden.


📌 Geplante Erweiterungen (ToDo)

    💰 Einbindung aktueller Strompreisdaten

    📈 Berücksichtigung historischer Verbrauchsdaten des Haushalts

    🔋 Einbezug des Batteriestands der PV-Anlage

    🌅 Integration von Sonnenauf- und -untergangszeiten

    🗄️ Speicherung sämtlicher Daten in einer Datenbank

    🖥️ Entwicklung einer Qt-basierten GUI für Linux

    📊 Datenaufbereitung für Grafana




