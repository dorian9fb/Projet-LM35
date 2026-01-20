# Rapport Projet LM35

---

## *Introduction*

L'objectif de ce projet est de concevoir un système de surveillance de température en utilisant un capteur LM35, une carte ESP-32, une Raspberry Pi et le protocole MQTT.

Les données seront transmises au Raspberry Pi via Mosquitto, stockées dans une base de données SQLite, et affichées en temps réel via NodeRED. Vous devrez également mettre en place des alertes et documenter votre travail.


## *Acquisition et Transmission des données*

Dans cette partie nous allons abordée comment nous avons récupérer et afficher les données du capteur sur un écran via MQTT
Tout d'abord on vient connecté la carte ESP32 au capteur LM35 avec alimentation en 3.3 V et sortie analogique A2 :

<p align="center"> <img src="Montage.png"  width="400"></p>
<p align="center"><em>Figure 1 : Branchement entre la carte ESP32 et le capteur LM35</em></p>

Par la suite on intègre le programme Arduino dans la carte ESP-32 afin de récupérer les valeurs du capteurs en mV et les convertir en degrés puis on vient publier les données dans un topic ici (/RodolpheDorian/temperature) avec une connection Wifi que l'on renseigne dans le programme.
 
<p align="center"> <img src="Programme.png"  width="800"></p>
<p align="center"><em>Figure 2 : Programme Arduino</em></p>

Sur la Raspberry Pi, on vient tout d'abord installé Node-red à partir de cette commande :
```bash
bash <(curl -sL https://github.com/node-red/linux-installers/releases/latest/download/update-nodejs-and-nodered-deb)
```
Puis on exécute cette commande dans le terminal de la Raspberry Pi et on vient faire un "contrôle + clic" sur l'adresse IP, ce qui ouvre directement une page Node-red dans le moteur de recherche.
```bash
node-red-start 
```
>[!IMPORTANT]
>Dans la page Node-red on renseigne le nom de domaine (centreia.fr) et le nom du topic (/RodolpheDorian/temperature), on vient ajouter une jauge et un graphique permettant de visualiser les données dans une interface :

<p align="center"> <img src="Node.png"  width="600"></p>
<p align="center"><em>Figure 3 : Interface Node-red</em></p>

Après avoir déployé le programme dans Node-red on exécute dans un nouvel onglet ce lien : 
```bash
http://<hostname>:1880/ui # Avec hostname l'IP de notre interface Node-red ici 127.0.0.1
```
On obtient alors cette interface :

<p align="center"> <img src="Gauge.png"  width="600"></p>
<p align="center"><em>Figure 3 : Jauge et Graphique</em></p>