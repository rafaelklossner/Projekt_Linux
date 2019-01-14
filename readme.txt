ColorSensing |
-------------

Überblick
---------
Die Applikation ColorSensing dient dem Feststellen des RGB Farbwertes
eines Gegenstandes oder eines Displays. Dazu kann per Knopfdruck eine
Messung gestartet werden. In diesem Projekt wird zum bestimmen der
Farbe der TCS3472 Sensor verwendet. Um die Anwendung zu starten sind
einige Vorarbeiten nötig.

Vorbereitung des Firefly
-------------------------
Um die Applikation in QT zu kompilieren und zu starten, muss
sichergestellt werden, dass das rootfs des Firefly im host
System gemountet ist.

Schritt 1
----------
@host sudo mount -t nfs 192.168.2.100:/ /opt/embedded/firefly/rootfs

Überprüfbar mit: 

@host cd /opt/embedded/firefly/rootfs
@host ls -l

Dieser Ordner sollte das fs des Firefly enthalten.


Schritt 2
----------
Es wird eine ssh Verbindung zum Friefly benötigt um den x-Server
auszuschalten.

@host ssh 192.168.2.100

x-Server ausschalten

@target /usr/local/bin/xdown.sh
oder einfach
@target xdown.sh

blinkender Cursor ausschalten

@target sudo su
@target echo 0 > /sys/class/graphics/fbcon/cursor_blink
@target exit


Schritt 3
----------
Im nächsten Schritt muss sichergestellt werden, dass eine
Zugriffsberechtigung auf das i2c Device vorhanden ist.

Dazu wird im Verzeichnis
@target cd /etc/udev/rules.d

eine Datei i2c.rules erstellt mit
@target sudo nano i2c.rules

in diese wird der folgende Text kopiert
# i2c devices
KERNEL=="i2c-[0-9]*", NAME="i2c/%n", SYMLINK+="%k"
KERNEL=="i2c-0" , GROUP="dialout", MODE="0660"
KERNEL=="i2c-[1-9]*", GROUP="dialout", MODE="0666"


Schritt 4
----------
Da möglicherweise ein Problem mit dem Touch-Treiber des Displays
besteht, muss dieses Modul entfernt werden. Ansosnten tretten
Probleme beim Senden und Empfangen der Sensordaten auf.

@target cd /sys/bus/i2c/drivers/edt_ft5x06
@target sudo su
@target echo -n "4-0038" > unbind
@target exit

um touch Treiber wider zu aktivieren (Schritt überspringen)

@target cd /sys/bus/i2c/drivers/edt_ft5x06
@target sudo su
@target echo -n "4-0038" > bind
@target exit


Ausführen der Applikation
-------------------------
Zunächst wird die Applikation in QT geöffnet. Dazu wird am
besten der Ordner ColorSensing in den Workspace von QT
verschoben. Anschliessend wird QT geöffnet und mit "open project"
wird die Datei ColorSensing.pro im Ordner ColorSensing
ausgewählt.

Anmerkung: 	Um die Applikation für das Firefly zu kompilieren
		muss QT natürlich vorher konfigueriert werden und
		ein Profil dür das Firefly erstellt werden. Dies
		geschieht am besten mit der Anleitung
		"Getting Started with QtCreator" in Session 4
		des Moodle Kurses für das Modul BTE5446
		
		--> Link: https://moodle.bfh.ch/course/view.php?id=18721

Nun wird das Projekt in QT für das Firefly kompiliert. Mit Run kann
die Applikation dann direkt ausgeführt werden.
Die Applikation kann mit dem Befehl

@target ./qt5/ColorSensing 

direkt in der Konsole gastartet werden. Dies bietet den Vorteil,
dass Meldung schneller Angezeigt werden als in der Konsole von
QT.


Bedienung Applikation
-------------------------

Tasten, Knöpfe, LEDs und deren Funktion:

T1 	Start Messurement 	--> 	Startet eine Einzelmessung
T2 	Reset Messurement	--> 	Setzt das Display auf den Ursprünglichen
					zurück
T3 	Umschalttaste Poti	--> 	Dient dem Umschalten zwischen den Einstellungen
					integration time und gain
T4 	Quit			--> 	Beendet die Applikation
P1	Einstellung integration	--> 	Mit dem Poti kann entwder die Integrationszeit
	time und gain			oder der gain eingestellt werden (Umschalten
					mit Taster T3). Die Auswahl wird mit eine
					violetten Rahmen angezeigt.
					Beide Werte bewirken beim erhöhen eine Erhöhung
					der Messempfindlichkeit
L1-L4	Signalisation "running	-->	Lauflicht das alle 5s durchläuft
	application"

Anmerkung: 	Wird die Messempfindlichkeit zu hoch eingestellt
		geraten die rgb Werte in Sättigung (max. 255)
		und die Anzeige der Farbe auf dem Display stimmt
		nicht mehr.
		--> Meldung unter Slider beachten
		Das Einstellen der Werte erfodert etwas
		Fingerspitzengefühl und ist stark von den
		lokalen Lichtverhälnissen abhängig.
		

Für die Tasten T1, T2 und T4 gibt es auf dem Diplay Knöpfe
mit der entsprechenden Beschriftung.

Anmerkung: 	Die Touch-Funktion kann aufgrund des entfernten
		Touch Treibers nicht verwendet werden.

Der Farbsensor befindet sich ungefähr auf der Unterseite des BFH Symbols.
Am besten geeignet sind leuchtende Displays um die Farbe zu erkennen. 
Gegenstände die nicht selber leuchten sind schwieriger zu erfassen

Signalisation der Messung:	red: 	der Farbanteil von rot
				green: 	der Farbanteil von grün
				bleu: 	der Farbanteil von blau
				clear:	gesamte Farbintensität über alle spektren

Es erfolgt auch eine optische Ausgabe der gemessenen Farbe im Quadrat neben dem Quit Button.


Beenden der Applikation
-------------------------
Konsole: 	ctrl-c
QT: 		Rotes Quadrat (Stop)
Firefly: 	T4

