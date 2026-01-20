# Rapport Projet LM35

---

## *Introduction*

L'objectif de ce projet est de concevoir un système de surveillance de température en utilisant un capteur LM35, une carte ESP-32, une Raspberry Pi et le protocole MQTT.

Les données seront transmises au Raspberry Pi via Mosquitto, stockées dans une base de données SQLite, et affichées en temps réel via NodeRED. Vous devrez également mettre en place des alertes et documenter votre travail.


## *Acquisition et Transmission des données*

Dans cette partie nous allons abordée comment nous avons récupérer et afficher les données du capteur sur un écran via MQTT
<p align="center">Texte centré</p>
Tout d'abord on vient connecté la carte ESP32 au capteur LM35
<p align="center"> <img src="Montage.png"  width="400"></p>