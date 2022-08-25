/*
 * MIT License
 * 
 * Copyright 2021 Manuel Domínguez Dorado <ingeniero@ManoloDominguez.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the 
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to 
 * permit persons to whom the Software is furnished to do so, subject to 
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _NODEMCU_MQTT_SECURE_CONNECTION_H_
#define _NODEMCU_MQTT_SECURE_CONNECTION_H_

#include <MQTTClient.h> // https://github.com/256dpi/arduino-mqtt --> MIT
#include <MQTT.h> // https://github.com/256dpi/arduino-mqtt --> MIT
#include <ESP8266WiFi.h> // https://github.com/esp8266/Arduino --> LGPL-2.1-or-later
#include <ESP8266mDNS.h> // https://github.com/arduino/esp8266/blob/master/libraries/ESP8266mDNS  --> LGPL-2.1-or-later
#include <ArduinoOTA.h> // https://github.com/jandrassy/ArduinoOTA --> LGPL-2.1-only
#include <WiFiClientSecure.h> // https://bearssl.org/ --> MIT
//#include <Time.h> // https://github.com/PaulStoffregen/Time
#include <time.h>
#include <TZ.h>
#include <Arduino.h>
#include <nodemcu-mqtt-secure-connection-config.h>
#include <work-controller.h>

class MqttSecureConnection {
private:
    const unsigned long MAX_UNSIGNED_LONG = 4294967295; // Max millis() before starting at 0.
	const int EPOCH_01_01_2021 = 1609459200; // Millis from January 1st, 2021
    BearSSL::WiFiClientSecure _tlsConnection;
    MQTTClient _mqttClient;
    WorkController _ntpController;
    unsigned long _lastMillisNTP;
    String _upTime;
    bool _gracefulDisconnect;
	bool _otaStatus;
	String _otaHostname;
	int _latestNTPEpoch;
    
    void publishMQTTUpTime();
    String measureTime();
    void setupWiFi();
    void setupNTPTime();
    void setupOTA();
    void setupMQTT(MQTTClientCallbackSimple onMessageCallbackFunction);
    String getDeviceID();
    String getSubTopic();
    String getPubTopic();
    String getLWTPubTopic();
    String getUptimePubTopic();
    void mqtt_connect();
    void checkConnectivity();
    void checkMQTT();
    void onMessageReceived(String &topic, String &payload);
    void publishMQTTMessage(String messageToPublish);
    void printIfSerial(String txt);
    void printlnIfSerial(String txt);
    void printlnIfSerial();
public:
    MqttSecureConnection();
    void publish(String messageToPublish);
    void debug(String messageToPublish);
    void setupConnection();
    void setupConnection(MQTTClientCallbackSimple onMessageCallbackFunction);
    void setupConnection(MQTTClientCallbackSimple onMessageCallbackFunction, String otaHostname);
    void keepConnection();
    void gracefulDisconnect();
	void setOTAStatus(bool otaStatus);
};

#endif
