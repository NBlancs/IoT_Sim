const int LEDS[] = {12, 14, 27, 26};
const int BTNS[] = {18, 19, 21, 22};
const int N = 4;

bool ledStates[N] = {false, false, false, false};
bool lastButtonStates[N] = {HIGH, HIGH, HIGH, HIGH};

void setup() {
  for (int i = 0; i < N; i++) {
    pinMode(LEDS[i], OUTPUT);
    pinMode(BTNS[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < N; i++) {
    bool buttonState = digitalRead(BTNS[i]);

    // detect press (HIGH -> LOW transition)
    if (lastButtonStates[i] == HIGH && buttonState == LOW) {
      ledStates[i] = !ledStates[i];  // toggle this LED
      digitalWrite(LEDS[i], ledStates[i] ? HIGH : LOW);
      delay(50); // debounce
    }

    lastButtonStates[i] = buttonState;
  }
}
