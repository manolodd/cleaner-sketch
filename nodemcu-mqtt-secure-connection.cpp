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

#include "nodemcu-mqtt-secure-connection.h"

MqttSecureConnection::MqttSecureConnection() {
  lastMillis = 0;
  lastMillisNTP = 0;
  upTime = "";
}

String MqttSecureConnection::getDeviceID() {
  String rawMAC = WiFi.macAddress();
  String deviceID = String(MQTT_CLIENT_PREFIX);
  deviceID += "-";
  for (int i = 0; i < rawMAC.length(); i++) {
    if (rawMAC[i] != ':') {
      deviceID += rawMAC[i];
    }
  }
  return deviceID;
}

String MqttSecureConnection::getSubTopic() {
  String subTopic = MQTT_SUB_TOPIC_ROOT;
  subTopic += "/";
  subTopic += getDeviceID();
  return subTopic;
}

String MqttSecureConnection::getPubTopic() {
  String pubTopic = MQTT_PUB_TOPIC_ROOT;
  pubTopic += "/";
  pubTopic += getDeviceID();
  return pubTopic;
}

String MqttSecureConnection::getLWTPubTopic() {
  String lwtPubTopic = MQTT_LWT_TOPIC_ROOT;
  lwtPubTopic += "/";
  lwtPubTopic += getDeviceID();
  return lwtPubTopic;
}

String MqttSecureConnection::getUptimePubTopic() {
  String uptimePubTopic = MQTT_UPTIME_PUB_TOPIC_ROOT;
  uptimePubTopic += "/";
  uptimePubTopic += getDeviceID();
  return uptimePubTopic;
}

void MqttSecureConnection::mqtt_connect() {
  char deviceID[getDeviceID().length() + 1];
  char sub_topic[getSubTopic().length() + 1];
  char lwt_topic[getLWTPubTopic().length() + 1];
  getLWTPubTopic().toCharArray(lwt_topic, getLWTPubTopic().length() + 1);
  mqtt_client.setOptions(MQTT_KEEPALIVE, MQTT_CLEAN_SESSION, MQTT_TIMEOUT);
  mqtt_client.setWill(lwt_topic, MQTT_LWT_MESSAGE, MQTT_LWT_NOT_RETAINED, MQTT_LWT_PUB_QOS);
  if (!mqtt_client.connected()) {
    getDeviceID().toCharArray(deviceID, getDeviceID().length() + 1);
    getSubTopic().toCharArray(sub_topic, getSubTopic().length() + 1);
    Serial.print("Connecting to MQTT broker using TLS...");
    if (!mqtt_client.connect(deviceID)) {
      Serial.println(" Unable to connect to the MQTT broker");
      delay(500);
    } else {
      Serial.println(" Connected to the MQTT broker!");
      Serial.print("Subscribing to topic ");
      Serial.print(sub_topic);
      Serial.print("...");
      if (!mqtt_client.subscribe(sub_topic, MQTT_SUB_QOS)) {
        Serial.print(" Unable to subscribe to the topic!");
        delay(500);
      } else {
        Serial.println(" Subscribed to topic!");
      }
    }
  }
}

void MqttSecureConnection::checkConnectivity() {
  int attempts = 0;
  if (!WiFi.isConnected()) {
    Serial.print("Network has been disconnected. Reconnecting...");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
      attempts++;
      if (attempts % 50 == 0) {
        Serial.println();
      }
      if (attempts >= WIFI_ATTEMPTS_BEFORE_RESETTING_ON_RECONNECT) {
        Serial.println();
        Serial.print(" Something extrange happens to the Wifi module. Reseting...");
        delay(2000);
        ESP.reset();
      }
    }
    Serial.println(" Connected again!");
  }
}

void MqttSecureConnection::checkMQTT() {
  checkConnectivity();
  mqtt_connect();
}

void MqttSecureConnection::setupWiFi() {
  int attempts = 0;
  WiFi.hostname(getDeviceID());
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println();
  Serial.println();
  Serial.print("Connecting ");
  Serial.print(WiFi.macAddress());
  Serial.print(" to WiFi ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    attempts++;
    if (attempts >= WIFI_ATTEMPTS_BEFORE_RESETTING_ON_CONNECT) {
      Serial.println();
      Serial.print(" Something extrange happens to the Wifi module. Reseting...");
      delay(2000);
      ESP.reset();
    }
  }
  WiFi.setAutoReconnect(true); // Se conectará automáticamente tras una desconexión
  Serial.println(" Connected!");
}

void MqttSecureConnection::setupNTPTime() {
  // NTP (Required to use TPLS 1.2)
  // I prefer to use UTC time without offset and use it
  // in the backend as needed.
  const int ZONE_OFFSET = 0;  // Seconds. No offset. UTC time instead.
  const int DAY_LIGHT_OFFSET_SEC = 0; // Seconds. No daylight offset. Plain UTC time instead.
  const int EPOCH_01_01_2021 = 1609459200; // Millis from January 1st, 2021
  const char NTP_SERVER_1[] = "0.es.pool.ntp.org";
  const char NTP_SERVER_2[] = "pool.ntp.org";
  const char NTP_SERVER_3[] = "time.nist.gov";
  checkConnectivity();
  Serial.print("Synchronizing time via NTP");
  configTime(ZONE_OFFSET, DAY_LIGHT_OFFSET_SEC, NTP_SERVER_1, NTP_SERVER_2, NTP_SERVER_3);
  // This loop is needed because is common that some attempts to retrieve
  // current time return errors. So we can assure that once the returned
  // time is greater than 01/01/2021 00:00:00 is because the correct one
  // is retrieved. Put the epoch value you need but always a past one.
  while (time(nullptr) < EPOCH_01_01_2021) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Synchronized!");
}

void MqttSecureConnection::setupMQTT(MQTTClientCallbackSimple onMessageCallbackFunction) {
  checkConnectivity();
  BearSSL::X509List x509_ca_cert(MQTT_BROKER_CA_CERT);
  tlsConnection.setTrustAnchors(&x509_ca_cert);
  tlsConnection.setInsecure();
  tlsConnection.setSSLVersion(MIN_TLS_VERSION, MAX_TLS_VERSION);
  mqtt_client.begin(MQTT_HOST, MQTT_PORT, tlsConnection);
  if (onMessageCallbackFunction) {
    mqtt_client.onMessage(onMessageCallbackFunction);
  }
  mqtt_connect();
}

void MqttSecureConnection::publishMQTTMessage(String messageToPublish) {
  char pub_topic[getPubTopic().length() + 1];
  char message[messageToPublish.length() + 1];
  getPubTopic().toCharArray(pub_topic, getPubTopic().length() + 1);
  messageToPublish.toCharArray(message, messageToPublish.length() + 1);
  if (WiFi.isConnected() && mqtt_client.connected()) {
    if (!mqtt_client.publish(pub_topic, message, MQTT_NOT_RETAINED, MQTT_PUB_QOS)) {
      Serial.println("Cannot publish right now");
    } else {
      Serial.print("Publishing [");
      Serial.print(message);
      Serial.print("] to ");
      Serial.print(pub_topic);
      Serial.print("...");
      Serial.println(" Published!");
    }
  } else {
    Serial.println("Disconnected from MQTT broker. Cannot publish right now.");
    checkMQTT();
  }
}

void MqttSecureConnection::publish(String messageToPublish) {
  checkConnectivity();
  if (isTimeToPublish()) {
    publishMQTTMessage(messageToPublish);
  }
}

void MqttSecureConnection::publishMQTTUpTime() {
  char pub_topic[getUptimePubTopic().length() + 1];
  char message[upTime.length() + 1];
  getUptimePubTopic().toCharArray(pub_topic, getUptimePubTopic().length() + 1);
  upTime.toCharArray(message, upTime.length() + 1);
  if (WiFi.isConnected() && mqtt_client.connected()) {
    if (!mqtt_client.publish(pub_topic, message, MQTT_RETAINED, MQTT_PUB_QOS)) {
      Serial.println("Cannot publish right now");
    } else {
      Serial.print("Publishing [");
      Serial.print(message);
      Serial.print("] to ");
      Serial.print(pub_topic);
      Serial.print("...");
      Serial.println(" Published!");
    }
  } else {
    Serial.println("Disconnected from MQTT broker. Cannot publish right now.");
    checkMQTT();
  }
}

bool MqttSecureConnection::isTimeToPublish() {
  unsigned long currentMillis;
  unsigned long period;
  currentMillis = millis();
  if (currentMillis < lastMillis) {
    period = MAX_UNSIGNED_LONG - lastMillis + currentMillis;
  } else {
    period = currentMillis - lastMillis;
  }
  if (period >= DATA_PUBLISH_INTERVAL) {
    lastMillis = millis();
    return true;
  }
  return false;
}

bool MqttSecureConnection::isTimeToSynchronizeTime() {
  unsigned long currentMillis;
  unsigned long period;
  currentMillis = millis();
  if (currentMillis < lastMillisNTP) {
    period = MAX_UNSIGNED_LONG - lastMillisNTP + currentMillis;
  } else {
    period = currentMillis - lastMillisNTP;
  }
  if (period >= NTP_SYNCHRONIZATION_PERIOD) {
    lastMillisNTP = millis();
    return true;
  }
  return false;
}

String MqttSecureConnection::measureTime() {
  time_t currentTime = time(nullptr);
  return String(currentTime);
}

void MqttSecureConnection::setupConnection(MQTTClientCallbackSimple onMessageCallbackFunction) {
  Serial.begin(115200);
  delay (1000);
  setupWiFi();
  setupNTPTime();
  upTime = measureTime();
  setupMQTT(onMessageCallbackFunction);
  publishMQTTUpTime();
}

void MqttSecureConnection::keepConnection() {
  if (isTimeToSynchronizeTime()) {
    setupNTPTime();
  }
  // Receive data if needed and maintain MQTT connection
  mqtt_client.loop();
  delay(10);
}
