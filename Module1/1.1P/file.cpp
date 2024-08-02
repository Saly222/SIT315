const uint8_t BTN_PIN = 2;  // Define the button pin number
const uint8_t LED_PIN = 13; // Define the LED pin number

uint8_t buttonPrevState = LOW; // Variable to store previous button state (initialized as LOW)
uint8_t ledState = LOW;        // Variable to store LED state (initialized as LOW)

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP); // Set BTN_PIN as input with internal pull-up resistor
  pinMode(LED_PIN, OUTPUT);       // Set LED_PIN as output
  Serial.begin(9600);             // Start serial communication at 9600 baud rate
}

void loop() {
  uint8_t buttonCurrState = digitalRead(BTN_PIN); // Read the current state of the button

  // Check if the button state has changed
  if (buttonCurrState != buttonPrevState) {
    // Check if the button is pressed (assuming active-low button)
    if (buttonCurrState == LOW) {
      ledState = !ledState;              // Toggle the LED state
      digitalWrite(LED_PIN, ledState);   // Update the actual LED based on the new state

      // Print the button and LED states
      Serial.print("Button State: ");
      Serial.print(buttonPrevState);
      Serial.print(", LED State: ");
      Serial.println(ledState);
    }
    buttonPrevState = buttonCurrState; // Update buttonPrevState with current button state
  }
}
