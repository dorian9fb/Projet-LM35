#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

// ================= LED NEOPIXEL (Feather V2) =================
Adafruit_NeoPixel pixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// ----- Fonctions couleurs -----
void ledRouge() {
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();
}

void ledVerte() {
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  pixel.show();
}

void ledBleue() {
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));
  pixel.show();
}

void ledOrange() {
  pixel.setPixelColor(0, pixel.Color(255, 80, 0));
  pixel.show();
}

void ledJaune() {
  pixel.setPixelColor(0, pixel.Color(255, 255, 0));
  pixel.show();
}

void ledOff() {
  pixel.setPixelColor(0, pixel.Color(0, 0, 0));
  pixel.show();
}

// ================= Configuration WiFi =================
const char* ssid = "iPhone de Dorian";
const char* wifi_password = "Dorian0911";

// ================= Configuration MQTT =================
const char* mqtt_server = "centreia.fr";
const char* test_topic  = "RodolpheDorian/temperature";
const char* mqtt_username = "rodolphe";
const char* mqtt_password = "ferrer";
const char* clientID = "BLE";

// ================= WiFi & MQTT =================
WiFiClient wifiClient;
PubSubClient client(wifiClient);

// ================= Connexion MQTT =================
void connect_MQTT() {
  client.setServer(mqtt_server, 1883);

  if (client.connect(clientID)) {
    Serial.println("✅ MQTT connecté");
  } else {
    Serial.println("❌ Échec MQTT");
    ledOrange();
    delay(1000);
  }
}
// ==============Couleur LED ======================
void ledtemp(float degres) {
    if (degres < 20) {
      ledVerte();
      delay(1000);

  } else  {
      ledRouge();
      delay(1000);
  }
}
// ================= SETUP =================
void setup() {
  Serial.begin(9600);

  pixel.begin();
  pixel.setBrightness(20);

  // Démarrage
  ledBleue();
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifi_password);

  Serial.print("Connexion WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    ledJaune();   // WiFi en cours
  }

  Serial.println("\n✅ WiFi connecté");
  Serial.println(WiFi.localIP());

  ledBleue(); // WiFi OK
}

// ================= LOOP =================
void loop() {

  // MQTT
  if (!client.connected()) {
    connect_MQTT();
  }

  client.loop();

  // Lecture ADC
  int raw = analogRead(33);
  float volts = (float)raw * 5 / 4095;
  float degres = volts / 0.01;
  
  String temperature_string = String(degres);

  Serial.println(degres);

  // Envoi MQTT
  if (client.publish(test_topic, temperature_string.c_str())) {
    Serial.println("📨 Température envoyée");
    ledtemp(degres);

  } else {
    Serial.println("⚠️ Erreur envoi MQTT");
    ledOrange();
    delay(1000);
  }

  client.disconnect();
  ledOff();
  delay(10000);
}
