#define soil_moisture_pin A0
#define relay_pin 4

void setup() {
  Serial.begin(9600);
  digitalWrite(relay_pin, HIGH);
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  Serial.print("Soil moisture read: ");
  Serial.println(analogRead(soil_moisture_pin));
  delay(5000);
  
  digitalWrite(relay_pin, LOW); // green light is off
  Serial.println("Current flowing for 10 secs...");
  delay(10000);
  digitalWrite(relay_pin, HIGH); // green light is on
  Serial.println("Current NOT flowing");
  delay(1000);
}