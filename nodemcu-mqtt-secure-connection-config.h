/*
  MIT License
  
  Copyright 2021 Manuel Domínguez Dorado <ingeniero@ManoloDominguez.com>

  Permission is hereby granted, free of charge, to any person obtaining 
  a copy of this software and associated documentation files (the 
  "Software"), to deal in the Software without restriction, including 
  without limitation the rights to use, copy, modify, merge, publish, 
  distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to 
  the following conditions:
  
  The above copyright notice and this permission notice shall be included 
  in all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _NODEMCU_MQTT_SECURE_CONNECTION_CONFIG_H_
#define _NODEMCU_MQTT_SECURE_CONNECTION_CONFIG_H_

// WiFi
const char WIFI_SSID[] = "MECNET";
const char WIFI_PASS[] = "%m4n010y313n4%c14v3%2016%";
const int WIFI_ATTEMPTS_BEFORE_RESETTING_ON_CONNECT = 15;
const int WIFI_ATTEMPTS_BEFORE_RESETTING_ON_RECONNECT = 30;

// MQTT
// MQTT BROKER CONFIG
const char MQTT_HOST[] = "192.168.1.20";
const int MQTT_PORT = 8883;
// MQTT CONNECTION CONFIG
const char MQTT_USER[] = ""; // leave blank if no credentials used
const char MQTT_PASS[] = ""; // leave blank if no credentials used
const unsigned int MIN_TLS_VERSION = BR_TLS12; // one of BR_TLS10, BR_TLS11, BR_TLS12
const unsigned int MAX_TLS_VERSION = BR_TLS12; // one of BR_TLS10, BR_TLS11, BR_TLS12
static const char MQTT_BROKER_CA_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDqTCCApGgAwIBAgIUA191U5uqRoCwNDZqMgXq23rmEU0wDQYJKoZIhvcNAQEL
BQAwZDERMA8GA1UEAwwITWkgQ2FzYSAxITAfBgNVBAoMGHd3dy5tYW5vbG9kb21p
bmd1ZXouY29tIDEsMCoGCSqGSIb3DQEJARYdaW5nZW5pZXJvQG1hbm9sb2RvbWlu
Z3Vlei5jb20wHhcNMjEwMjI3MTkyNDE1WhcNMzEwMjI1MTkyNDE1WjBkMREwDwYD
VQQDDAhNaSBDYXNhIDEhMB8GA1UECgwYd3d3Lm1hbm9sb2RvbWluZ3Vlei5jb20g
MSwwKgYJKoZIhvcNAQkBFh1pbmdlbmllcm9AbWFub2xvZG9taW5ndWV6LmNvbTCC
ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALGcVhXuBhT1K5akseE6pIND
mTseS34jicNVABbLBCcsdr6kP7C1ppajrWN570dqYyMw+bnvDYlVF1Cv/mKq48y1
vgn9w2vv+gRw4qFD6JJ3USQ81cOKsJMtsCsGTxvfjSb3yU4mbQgxQy6407a6SuoK
sFky/Wt1TDRWka9OpUOKxk6Zpe6gDZaUElzBuo4oTa6D4j72Sl0/7LsFDUk8M7zU
q/F7t94mHDeLE71HLuptRET6kuOsDNOPjs2C4WHNt/B8hc5hZha5lHbNigbJ/lJL
vYTTe45/qxEYYbBd2eYnWADCx5nnILSpUmpuBVonYkYUxJtu9i17Ao9N/pNb/scC
AwEAAaNTMFEwHQYDVR0OBBYEFMrLkGR/TURg4Jq73n0B4Fg08P3sMB8GA1UdIwQY
MBaAFMrLkGR/TURg4Jq73n0B4Fg08P3sMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZI
hvcNAQELBQADggEBACaZaYx8RliQIwoKX0WCGVu9tYiIzhHhGBt/yivlC9WSlwiq
fvUe9vikc08vq2zg4sLinljEEFKO/SWsdHX/jMPX9J60H7hcOEL3fov2omgMXbpi
w206LTmskWlf323AZL+j+ABcJZY9LJ+1SVPNJca8AL/rLXoZqxxmJb/2aqGTN9OM
ej4+u4KFEbllxNyUHVpuMYmhbMmuSumcUHVSfPfQRFOo3o8v8IYJ8tJvkwOys+P8
CJsp1/ztj+lfiSsyezhADbtlmAkx72rp6LCaCY2I3JPHVrmakN8xHT84KP9RUmj6
+WWS7aY4TTdLX/rc0zJv591uDDBXe98z/g4NvDg=
-----END CERTIFICATE-----
)EOF";
const int MQTT_KEEPALIVE = 5; // seconds
const int MQTT_CLEAN_SESSION = true;
const int MQTT_NOT_CLEAN_SESSION = false;
// MQTT_TIMEOUT is the timeout(in milliseconds) used by all
// MQTT commands, that return a boolean, before ending
// with due to not being able to perform the operation.
const int MQTT_TIMEOUT = 2000; // milliseconds
// MQTT CLIENT, PUBLISH AND SUBSCRIBE CONFIG
const char MQTT_CLIENT_PREFIX[] = "nodemcu";
const char MQTT_SUB_TOPIC_ROOT[] = "devices/todevice";
const char MQTT_PUB_TOPIC_ROOT[] = "devices/fromdevice";
const char MQTT_UPTIME_PUB_TOPIC_ROOT[] = "devices/uptime";
const int MQTT_PUB_QOS = 2;
const int MQTT_SUB_QOS = 2;
const bool MQTT_RETAINED = true;
const bool MQTT_NOT_RETAINED = false;
// MQTT LAST WILL AND TESTAMENT CONFIG
const char MQTT_LWT_TOPIC_ROOT[] = "devices/fromdevice";
const char MQTT_LWT_MESSAGE[] = "El dispositivo se ha desconectado";
const bool MQTT_LWT_RETAINED = true;
const bool MQTT_LWT_NOT_RETAINED = false;
const int MQTT_LWT_PUB_QOS = 2;

// DATA PUBLISH FREQUENCY
const int DATA_PUBLISH_INTERVAL = 5000;

// Period of time before synchronizing again
// the time via NTP.
const unsigned long NTP_SYNCHRONIZATION_PERIOD = 21600000; // 21600000 milliseconds (6 hours).

#endif
 
