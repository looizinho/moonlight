#include "defines.h"
#include <ArduinoJson.h>
#include <WebSockets2_Generic.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

using namespace websockets2_generic;

WebsocketsClient client;
bool clientIsConnected = NULL;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
  (void)data;

  if (event == WebsocketsEvent::ConnectionOpened) {
    Serial.println("Connnection Opened");
    // Send a message
    DynamicJsonDocument doc(1024);
    doc["from"] = ARDUINO_BOARD;
    doc["name"] = BOARD_NAME;
    doc["message"] = "Hello from ESP";
    doc["dateTime"] = millis();
    String output;
    serializeJson(doc, output);
    client.send(output);
    clientIsConnected = true;
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    Serial.println("Connnection Closed");
    clientIsConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    Serial.println("Got a Ping!");
  } else if (event == WebsocketsEvent::GotPong) {
    Serial.println("Got a Pong!");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial && millis() < 5000)
    ;

  Serial.print("\nStart Minimal-ESP8266-Client on ");
  Serial.println(ARDUINO_BOARD);
  Serial.println(WEBSOCKETS2_GENERIC_VERSION);

  // Connect to wifi
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No Wifi!");
    return;
  }

  Serial.print("Connected to Wifi, Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);

  // run callback when messages are received
  client.onMessage(onMessageCallback);

  // run callback when events are occuring
  client.onEvent(onEventsCallback);

  // Connect to server
  // client.connect(websockets_server_host, websockets_server_port, "/microcontrollers");
  client.setAuthorization(client_login, client_password);
  client.connect(websockets_server_host);
  
  // Send a ping
  client.ping();
}

void loop() {
  client.poll();
  if (clientIsConnected == false) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
    Serial.println("Trying to connect...");
    client.connect(websockets_server_host);
  }
}