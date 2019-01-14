ColorSensing

# Das Firefly muss gemountet sein, solte das nicht der fall sein

@host sudo mount -t nfs 192.168.2.100:/

# Überprüfbar mit 

@host cd /opt/embedded/firefly/rootfs

@host ls -l

# dieser Ordner sollte nicht leer sein

# Es wird eine ssh verbidnugn zum Friefly benötigt

@host ssh 192.168.2.100

# der x-Server muss ausgeschaltet werden

@target /usr/local/bin/xdown.sh

# oder einfach

@target xdown.sh

# blinkender Cursor ausschalten

@target sudo su
@target echo 0 > /sys/class/graphics/fbcon/cursor_blink
@target exit

# Der Nutzer benötigt Zugrifsrechte für die ic2 Schnittstelle falls diese nochnicht vorhanden sind

@target sudo usermod -a -G i2c student

# möglicherweise ist es nötig das Terminal nochmal zu schliessen und neu zu öffnen damit alles übernommen wird

# üperprüfbar mit 

@target groups

# ungelöstes Problem. Ic2 Sensorauslesung funktioniert nicht immer, wenn das Programm hängen bleibt Bildschirm antippen
# um das problem zu umgehen kann der Touch treiber ausgeschlatet werden so funktionieren aber keine touch funktionen mehr

@target cd /sys/bus/i2c/drivers/edt_ft5x06
@target sudo su
@target echo -n "4-0038" > unbind
@target exit

# um touch treiber wider zu aktivieren

@target cd /sys/bus/i2c/drivers/edt_ft5x06
@target sudo su
@target echo -n "4-0038" > bind
@target exit

# application ausführbar mit

@target ./qt5/ColorSensing 

# Messung starten mit

Display Button Start messurement oder Taster T1

# Messung resetten mit

Display Button Reset messurement oder Taster T2

# Umschalten zwischen integration time und gain (Der momentan ausgewählte wird markiert mit einem blauen Rechteck)

Taster T3

# Verändern der integration time oder gain

Potentiometer P1

# Abstufungen der integration time auf Slider: 	  0 =   2,4	ms
						  3 =  24	ms
						  7 =  50	ms
						 14 = 101 	ms
						 21 = 154 	ms
						100 = 700 	ms

# bei zu grosser Integrationszeit kann Messung nicht richtig verarbeitet werden.

# Abstufung des gain auf Slider: 		  0 =  1x
						  7 =  4x
						 26 = 16x
						100 = 60x

# Der Farbsensor befindet sich ungefähr auf der Unterseite des BFH Symbols
# Am besten geeignet sind leuchtende Displys wie Handydisplays um die Farbe zu erkennen. 
# Gegenstände die nicht selber leuchten sind schwiriger zu erfassen
# Signalisation der Messung:	red: 	der Farbanteil von rot
				green: 	der Farbanteil von grün
				bleu: 	der Farbanteil von blau
				clear:	gesamte Farbintensität über alle spektren

# Es erfolgt auch eine optische Ausgabe der gemessenen Farbe im Quadrat neben dem Quit Button

# application beendbar mit

Button Quit auf Display oder mit Taster T4 oder mit ctrl C 


