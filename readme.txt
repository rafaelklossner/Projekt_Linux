
# Das Firefly muss gemountet sein, solte das nicht der fall sein

sudo mount -t nfs 192.168.2.100:/

# Überprüfbar mit 

/opt/embedded/firefly/rootfs

ls -l

# dieser Ordner sollte nicht leer sein

# Es wird eine ssh verbidnugn zum Friefly benötigt

ssh 192.168.2.100

# der x-Server muss ausgeschaltet werden

/usr/local/bin/xdown.sh

# oder einfach

xdown.sh

# Der Nutzer benötigt Zugrifsrechte für die ic2 Schnittstelle falls diese nochnicht vorhanden sind

sudo usermod -a -G i2c student

# möglicherweise ist es nötig das Terminal nochmal zu schliessen und neu zu öffnen damit alles übernommen wird

# üperprüfbar mit 

groups

# application ausführbar mit

./qt5/ColorSensing 

