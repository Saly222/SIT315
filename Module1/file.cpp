const int sensorPin = A0;  // Pin connected to the photoresistor
const int ledPin = LED_BUILTIN;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Print a message to the serial monitor
  Serial.println("System initialized.");
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);
  
  // Print the sensor value to the serial monitor
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  
  // Check if the sensor value is below a certain threshold
  if (sensorValue < 500) {  // Adjust the threshold as needed
    // Low light detected, turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("Low light detected: LED is ON");
  } else {
    // Sufficient light, turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("Sufficient light: LED is OFF");
  }
  
  // Add a short delay before the next loop
  delay(500);
}
