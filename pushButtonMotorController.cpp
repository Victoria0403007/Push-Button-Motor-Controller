
// Pin Assignments
const int BUTTON_PIN = 2;    // Pushbutton input
const int MOTOR_PWM_PIN = 9; // Speed control (PWM)
const int DIR_A = 4;         // H-Bridge direction pin A
const int DIR_B = 5;         // H-Bridge direction pin B

// System Variables
bool isMotorRunning = false;
bool isForward = true;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  
  // Set up pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);

  Serial.println("Pushbutton Motor Controller Ready.");
}

void loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);

  // Check if the button was just pressed (transition from HIGH to LOW)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    
    // Toggle running state
    isMotorRunning = !isMotorRunning;

    // Switch direction every time motor turns ON
    if (isMotorRunning) {
      isForward = !isForward;
    }

    delay(200); // Simple debounce to prevent false multi-clicks
  }

  // Save current button state for the next frame
  lastButtonState = currentButtonState;

  // Apply motor outputs based on system state
  if (isMotorRunning) {
    // Set Direction Pins
    digitalWrite(DIR_A, isForward ? HIGH : LOW);
    digitalWrite(DIR_B, isForward ? LOW : HIGH);
    
    // Set Speed (0 to 255)
    analogWrite(MOTOR_PWM_PIN, 180);

    // Print Telemetry to Serial Monitor
    Serial.print("Status: RUNNING | Direction: ");
    Serial.println(isForward ? "FORWARD" : "REVERSE");
  } else {
    // Stop Motor
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(MOTOR_PWM_PIN, 0);

    Serial.println("Status: STOPPED");
  }

  delay(100); // Short delay to keep serial output stable
}