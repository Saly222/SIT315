
const uint8_t BTN_PIN = 2;  // Define the button pin number
const uint8_t LED_PIN = 13; // Define the LED pin number


uint8_t buttonPrevState = LOW; // Variable to store previous button state (initialized as LOW)
uint8_t ledState = LOW;        // Variable to store LED state (initialized as LOW)


void setup()
{

  pinMode(BTN_PIN, INPUT_PULLUP); // Set BTN_PIN as input with internal pull-up resistor
 
  pinMode(LED_PIN, OUTPUT);       // Set LED_PIN as output
 
  Serial.begin(9600);             // Start serial communication at 9600 baud rate

  attachInterrupt(digitalPinToInterrupt(BTN_PIN), toggleButton_ISR, CHANGE); // Attach interrupt to BTN_PIN
}

void loop()
{

}

void toggleButton_ISR() {
  ledState = !ledState;                  // Toggle the LED state
  digitalWrite(LED_PIN, ledState);       // Update the actual LED based on the new state
  
 
  Serial.print(buttonPrevState);         // Print previous button state
  Serial.print(ledState);                // Print current LED state
  Serial.println("");                    // Print a newline for formatting
  
  buttonPrevState = digitalRead(BTN_PIN); // Update buttonPrevState with current button state
}
