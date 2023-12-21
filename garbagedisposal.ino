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
  pinMode(12, OUTPUT); //Relay and its status LED
  pinMode(13, OUTPUT); //Green LED (HIGH = off, LOW = on)
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(0) == inverted) {
    if (pressed) return;
    pressed = true;
    pressedTime = millis();
    digitalWrite(13, HIGH);
  }
  else {
    if (pressed) {
      if ((millis()  - pressedTime) > minInvertDelay) inverted = !inverted;
      else if ((millis()  - pressedTime) > minReleaseDelay) {
        digitalWrite(12, HIGH);
        activated = true;
        activationTime = millis();
      }
    }
    pressed = false;
    digitalWrite(13, LOW);
  }

  if (activated && ((millis() - activationTime) > duration)) {
    digitalWrite(12, LOW);
    activated = false;
  }
}
