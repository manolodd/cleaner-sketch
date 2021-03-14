#include <nodemcu-mqtt-secure-connection.h>
#include <nodemcu-mqtt-secure-connection-config.h>


// Create an object of type MqttSecureConnection. This object
// includes the needed logic to connect to a WiFi network,
// auto-reconnect if it is disconnected, connect via TLS to
// a MQTT broker, reconnect to the MQTT broker if needed, 
// synchronize the time using a set of three NTP servers
// and keep this synchronization along the time. It support
// TLS 1.0, TLS 1.1, TLS 1.2 and MQTT with QoS0, QoS1 and QoS2.
// Everything is done automatically by using only two or
// three methods. Logs are dumped to Serial.

MqttSecureConnection internet;


// Create a function to handle incoming MQTT messages if you
// want your sketch to subscribe to a MQTT topic. The function
// signature has to be as in this example. The content could 
// be whatever you want.
void onMessageReceived(String &topic, String &payload) {
  Serial.print("Se ha recibido un mensaje en el topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(payload);
}

// This is a dummy function. Your sketch will do the work
// in the way you think is better.
String doAnyWork() {
  time_t currentTime = time(nullptr);
  return String(currentTime);
}


void setup() {
// Start your MqttSecureConnection object at the beginning of 
// the setup() function. You can pass nullptr as an argument
// if you are not going to subscribe to any MQTT topic and,
// therefore, you have not defined a callback function. Or
// if you have created a function in charge of handling 
// incoming messages coming from a subscribed topic, then
// you should specify it here.
//
//  internet.setupConnection(nullptr);
  internet.setupConnection(onMessageReceived);
}

void loop() {
  // Do work. And do it the way you want as you think better
  // fits your needs.
  String workResult = doAnyWork();

  // Whenever you have a result you want to publish, do it
  // usgin the publish() method of your MqttSecureConnection
  // object. It will be published only if is time to publish
  // as configured in the MqttSecureConnection class. So
  // you don't have to write here the typical check
  // if (millis() - lastMillis > 10000)...
  internet.publish(workResult);

  // At the end of loop(), put always a call to the 
  // keepConnection() method of MqttSecureConnection. It will
  // maintain MQTT connectin in a dood state, and also do
  // some checks.
  internet.keepConnection();
}
