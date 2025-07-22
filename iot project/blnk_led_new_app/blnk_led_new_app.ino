/*New blynk app project
 * https://srituhobby.com
 */
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "VDX4mu6c6Q3B2K12KDcyJkJ-iFCequkD" //Enter your blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy A14 5G AA96";//Enter your WIFI name
char pass[] = "dhruvilad@21";//Enter your WIFI password


BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  pinMode(D0, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}



/* New Blynk app project
 * https://srituhobby.com
 */

/*#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "whJQFRMxndTjWUdhGCckpLQ5tOQyXT7M" // Enter your Blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy A14 5G AA96";   // Enter your WiFi name
char pass[] = "dhruvilad@21";         // Enter your WiFi password

// Define LED pins
#define LED1 D0   // Controlled by V0
#define LED2 D1   // Controlled by V1
#define LED3 D2   // Controlled by V2

BLYNK_WRITE(V0) {
  digitalWrite(LED1, param.asInt());
}

BLYNK_WRITE(V1) {
  digitalWrite(LED2, param.asInt());
}

BLYNK_WRITE(V2) {
  digitalWrite(LED3, param.asInt());
}

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}*/




