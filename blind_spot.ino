#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "hossammekkawy";
const char* password = "12345678";
const char* mqtt_server = "192.168.17.41";

WiFiClient espClient;
PubSubClient client(espClient);

class Ultrasonic {
  int trig, echo;
public:
  Ultrasonic(int t, int e) : trig(t), echo(e) {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
  }

  float readCM() {
    digitalWrite(trig, LOW); delayMicroseconds(2);
    digitalWrite(trig, HIGH); delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long duration = pulseIn(echo, HIGH, 30000);
    return duration ? duration * 0.017 : -1;
  }
};

Ultrasonic u1(18, 19);
Ultrasonic u2(21, 22);

void setup_wifi() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("connecting to MQTT broker...");
    if (client.connect("ESP32Client")) //connect to server
    {  
      Serial.println("connected ");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" - retrying in 2s");
      delay(2000);
    }
  }
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float d1 = u1.readCM();
  delay(50);
  float d2 = u2.readCM();

  String payload = "u1:" + String(d1, 1) + "cm\n
  u2:" + String(d2, 1) + "cm";
  client.publish("ultrasonic/data", payload.c_str());

  Serial.println("Published: ");
  Serial.println(payload);

  delay(2000);
}
