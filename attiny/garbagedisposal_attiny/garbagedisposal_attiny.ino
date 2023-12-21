//GLOBAL VARS
bool inverted = false;
bool pressed = false;
bool activated = false;
unsigned long pressedTime = 0;
unsigned long activationTime = 0;

//CONSTANTS
const unsigned long duration = 7000;
const unsigned long minReleaseDelay = 50;
const unsigned long minInvertDelay = 10000;

void setup() {
  pinMode(0, INPUT_PULLUP); //Push button (HIGH = off, LOW = on)
  pinMode(2, OUTPUT); //Relay and its status LED
  pinMode(3, OUTPUT); //Green LED (HIGH = off, LOW = on)
}

void loop() {
  if (activated && ((millis() - activationTime) > duration)) {
    digitalWrite(2, LOW);
    activated = false;
  }

  if (digitalRead(0) == inverted) { //Pedal pressed
    if (pressed) return;
    pressed = true;
    pressedTime = millis();
    digitalWrite(3, HIGH);
    //Serial.print("PRESSED: ");
    //Serial.println(inverted);
  }
  else if (pressed) { //Pedal released
    if ((millis()  - pressedTime) > minInvertDelay) {
      inverted = !inverted;
      //Serial.println("INVERTED");
    }
    else if ((millis()  - pressedTime) > minReleaseDelay) {
      digitalWrite(2, HIGH);
      activated = true;
      activationTime = millis();
    }
    //Serial.println("RELEASED");
    pressed = false;
    digitalWrite(3, LOW);
  }
}