##SensorWebEnergy


###Descrizione del sistema

Il sistema permette il monitoraggio di impianti di ….
Il device è stato configurato in modo che invii i dati tramite scheda SIM al server ogni N minuti (dove N viene configurato a lato server). I dati inviati sono formattati in una stringa contenente le seguenti informazioni:


![alt tag](https://raw.github.com/loweherz/SensorWebEnergy/master/images/string.jpg)


###Hardware

Il sistema è basato sul dispositivo Seeduino Stalker, il quale è possibile programmarlo facilmente tramite l’IDE di Arduino.


![alt tag](https://raw.github.com/loweherz/SensorWebEnergy/master/images/schema.png)


#####Sensori utilizzati

* DHT22 (link), con questo dispositivo è possibile misurare la temperatura e l’umidità di un ambiente. 

* DIGITAL TEMPERATURE WATERPROOF (link), sfruttano ONE WIRE

* XL MAX SONAR (link), lettura da seriale

* CT SENSOR (link)

* CONTATTI REED

* FLUSSOMETRO


###Sketch

Il software è stato ottimizzato per poter essere eseguito su device con scarsa memoria. Lo sketch mostrato in appendice permette di eseguire la lettura dei sensori sopra citati ed inviare la loro lettura al server dove saranno salvate tali informazioni.

###Web application
