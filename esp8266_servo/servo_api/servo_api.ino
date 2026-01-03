// Connects esp8266 with ServoMotorSG90
// To test it curl -X POST http://192.168.188.64/api/servo \
//                -H "Content-Type: application/json" \
//                -d '{"servoPosition":0}'

//www.elegoo.com
//2018.12.19
#include <Servo.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

Servo myservo;

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

long servoPosition = 90;
long newServoPosition = 0;

AsyncWebServer server(80);

// Define Static IP Settings
IPAddress local_IP(192,168,188,65);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,0,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress secondaryDNS(8,8,4,4);

void setup(){
  myservo.attach(2);
  myservo.write(90);// move servos to center position -> 90°

  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(5000);
  // Connect to Wi-Fi
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
    Serial.println("Static IP failed to configure.");
  }
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/api/servo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(servoPosition).c_str());
  });

  server.on(
    "/api/servo",
    HTTP_POST,
    [](AsyncWebServerRequest *request) {},  // onRequest (not used)
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, data);

      if (error) {
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
      }

      if (!doc.containsKey("servoPosition")) {
        request->send(400, "application/json", "{\"error\":\"Missing servoPosition\"}");
        return;
      }

      long pos = doc["servoPosition"];

      // Optional safety limits
      pos = constrain(pos, 0, 180);

      servoPosition = pos;
      newServoPosition = 1;

      request->send(200, "application/json", "{\"status\":\"ok\"}");
    }
  );

  // Start server
  server.begin();
}

void loop(){
  if (newServoPosition == 1){
    myservo.write(servoPosition);
    newServoPosition = 0;
  }
}
