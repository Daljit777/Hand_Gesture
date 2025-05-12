#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Enter Your SSID";
const char* password = "Enter Your Password";

// Correct static IP configuration
IPAddress local_IP(192, 168, 137, 100);
IPAddress gateway(192, 168, 137, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

const int relay1 = D1;
const int relay2 = D2;
const int relay3 = D3;
const int relay4 = D4;

void setup() {
  Serial.begin(115200);

  // Apply static IP settings
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  // Relay endpoints
  server.on("/ON1", []() {
    digitalWrite(relay1, LOW);
    server.send(200, "text/plain", "Relay 1 ON");
  });
  server.on("/OFF1", []() {
    digitalWrite(relay1, HIGH);
    server.send(200, "text/plain", "Relay 1 OFF");
  });

  server.on("/ON2", []() {
    digitalWrite(relay2, LOW);
    server.send(200, "text/plain", "Relay 2 ON");
  });
  server.on("/OFF2", []() {
    digitalWrite(relay2, HIGH);
    server.send(200, "text/plain", "Relay 2 OFF");
  });

  server.on("/ON3", []() {
    digitalWrite(relay3, LOW);
    server.send(200, "text/plain", "Relay 3 ON");
  });
  server.on("/OFF3", []() {
    digitalWrite(relay3, HIGH);
    server.send(200, "text/plain", "Relay 3 OFF");
  });

  server.on("/ON4", []() {
    digitalWrite(relay4, LOW);
    server.send(200, "text/plain", "Relay 4 ON");
  });
  server.on("/OFF4", []() {
    digitalWrite(relay4, HIGH);
    server.send(200, "text/plain", "Relay 4 OFF");
  });

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
