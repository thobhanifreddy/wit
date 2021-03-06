#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BUTTON_PIN 0

const char *ssid = "Neel";
const char *password = "icanfly7";
const char *mqtt_server = "192.168.43.128";
const char *device_id = "tankSide";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(String message, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(message);
  Serial.println("] ");

//  if (message == "PUMPON") {
//    Serial.print("ON");
//    digitalWrite(D0, HIGH);
//  }
//  
//  else if (message == "PUMPOFF") {
//    Serial.print("OFF");
//    digitalWrite(D0, LOW);
//  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(device_id, "cloud_username", "cloud_password"))
    {
      Serial.println("connected");
      digitalWrite(D0, LOW);
      client.subscribe("PUMPOFF");
      client.subscribe("PUMPON");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D6, INPUT);

  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  Serial.println("Connecting to " + (String)ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (client.connected())
  {

  }
  if (!client.connected())
  {
    reconnect();
  }
  while (client.loop()) {
    client.publish("PUMPON","on");
    Serial.println("ON");
    delay(1000 * 10);
    client.publish("PUMPOFF","off");
    Serial.println("OFF");
    delay(1000 * 10);
    //    int val;
    //    val = digitalRead(D6);
    //    if (val == 0) {
    //      digitalWrite(D0, HIGH);
    //    }
    //    else {
    //      digitalWrite(D0, LOW);
    //    }
    //    Serial.println(val);
    //    delay(2000);
  }
}
