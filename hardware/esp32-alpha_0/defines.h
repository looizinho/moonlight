#ifndef defines_h
#define defines_h

#if !(defined(ESP8266) || defined(ESP32))
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#elif (ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM)
#define BOARD_TYPE "ESP32-S2"
#elif (ARDUINO_ESP32C3_DEV)
#warning Using ESP32-C3 boards
#define BOARD_TYPE "ESP32-C3"
#else
#define BOARD_TYPE "ESP32"
#endif

#ifndef BOARD_NAME
#define BOARD_NAME BOARD_TYPE
#endif

#define DEBUG_WEBSOCKETS_PORT Serial
// Debug Level from 0 to 4
#define _WEBSOCKETS_LOGLEVEL_ 3

#define LED_BUILTIN 2

const char* ssid = "moto";          //Enter SSID
const char* password = "12345679";  //Enter Password

// const char* websockets_server_host = "192.168.39.132"; //Enter server address
const char* websockets_server_host = "wss://mac.tail17794.ts.net/microcontrollers";  //Enter server address

const char* client_login = "itamar";
const char* client_password = "nanotecc";

#define WEBSOCKETS_PORT 443

const uint16_t websockets_server_port = WEBSOCKETS_PORT;  // Enter server port

#endif  //defines_h
