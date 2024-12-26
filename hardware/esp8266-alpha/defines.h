#ifndef defines_h
#define defines_h

#if (ESP8266)
  #define BOARD_TYPE      "ESP8266"
#else
  #error This code is intended to run only on the ESP8266 boards ! Please check your Tools->Board setting.
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define DEBUG_WEBSOCKETS_PORT     Serial
// Debug Level from 0 to 4
#define _WEBSOCKETS_LOGLEVEL_     3

const char* ssid = "moto"; //Enter SSID
const char* password = "12345679"; //Enter Password

// const char* websockets_server_host = "192.168.39.132"; //Enter server address
const char* websockets_server_host = "wss://mac.tail17794.ts.net/microcontrollers"; //Enter server address

const char* client_login = "itamar";
const char* client_password = "nanotecc";

#define WEBSOCKETS_PORT     443

const uint16_t websockets_server_port = WEBSOCKETS_PORT; // Enter server port

#endif      //defines_h
