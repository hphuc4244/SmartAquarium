#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//TODO: ESP32 MQTT user config
const char* ssid = "TCHC"; // Wifi SSID
const char* password = "12345689@"; // Wifi Password
const char* subTopic_caloc = "ToNguyenHoangPhuc_Led_caloc";
const char* subTopic_canho = "ToNguyenHoangPhuc_Led_canho";
const char* subTopic_nguon_A = "ToNguyenHoangPhuc_nguon_A";
const char* subTopic_nguon_B = "ToNguyenHoangPhuc_nguon_B";

const int LED_pin_caloc = 16; // LEd pin
const int LED_pin_canho = 14; // LEd pin
const int LED_pin_nguon_1 = 12; // LEd pin
const int LED_pin_nguon_2 = 13; // LEd pin
//AskSensors MQTT config
const char* mqtt_server = "ab76f209f2aa4b76b0944f485bcbd488.s1.eu.hivemq.cloud";
const char *mqtt_username = "hphuc4244";
const char *mqtt_password = "hphuc4244";
unsigned int mqtt_port = 8883;

WiFiClientSecure askClient; 
// WiFiClient askClient;
PubSubClient client(askClient);

void setup() {
  Serial.begin(115200);
  Serial.println("*****************************************************");
  Serial.println("********** Program Start : ESP32 controls LED with AskSensors over MQTT");
  Serial.println("Set LED as output");
  pinMode(LED_pin_caloc, OUTPUT);   // set led as output
  pinMode(LED_pin_canho, OUTPUT);
  pinMode(LED_pin_nguon_1, OUTPUT);
  pinMode(LED_pin_nguon_2, OUTPUT);
  Serial.print("********** connecting to WIFI : ");
  Serial.println(ssid);
  digitalWrite(LED_pin_caloc, 0);
  digitalWrite(LED_pin_canho, 0);
  digitalWrite(LED_pin_nguon_1, 0);
  digitalWrite(LED_pin_nguon_2, 0);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("->WiFi connected");
  Serial.println("->IP address: ");
  Serial.println(WiFi.localIP());
  askClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (!client.connected()) 
    reconnect();

  client.subscribe(subTopic_caloc);
  client.subscribe(subTopic_canho);
  client.subscribe(subTopic_nguon_A);
  client.subscribe(subTopic_nguon_B);
}

void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == subTopic_caloc) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(LED_pin_caloc, HIGH);
      client.publish("ToNguyenHoangPhuc_Led_trangthai_caloc", "bat");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(LED_pin_caloc, LOW);
      client.publish("ToNguyenHoangPhuc_Led_trangthai_caloc", "tat");
    }
  } else if(String(topic) == subTopic_canho) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(LED_pin_canho, HIGH);
      client.publish("ToNguyenHoangPhuc_Led_trangthai_canho", "bat");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(LED_pin_canho, LOW);
      client.publish("ToNguyenHoangPhuc_Led_trangthai_canho", "tat");
    }
  } else 
  if(String(topic) == subTopic_nguon_A) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("bat den nguon A");
      digitalWrite(LED_pin_nguon_1, HIGH);
      client.publish("ToNguyenHoangPhuc_trangthai_nguon_1", "bat");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(LED_pin_nguon_1, LOW);
      client.publish("ToNguyenHoangPhuc_trangthai_nguon_1", "tat");
    }
  }
  else if(String(topic) == subTopic_nguon_B) {
      Serial.print("Changing output to ");
      if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(LED_pin_nguon_2, HIGH);
      client.publish("ToNguyenHoangPhuc_trangthai_nguon_2", "bat");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(LED_pin_nguon_2, LOW);
      client.publish("ToNguyenHoangPhuc_trangthai_nguon_2", "tat");
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("********** Attempting MQTT connection...");
    // Attempt to connect
    String clientID =  "ESPClient-";
    clientID += String(random(0xffff),HEX);
    if (client.connect(clientID.c_str(), mqtt_username, mqtt_password)) {  
      Serial.println("-> MQTT client connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("-> try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
