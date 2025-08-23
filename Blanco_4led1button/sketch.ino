// #define BUTTON_PIN 18

// with buttons?
// void setup() {
//   pinMode(LED_PIN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT_PULLUP)
//   Serial.begin(115200);

// }
// void loop() {
//   int buttonState = digitalRead(BUTTON_PIN);

//   if (buttonState == LOW){
//     digitalWrite(LED_PIN, HIGH);
//     Serial.println(("LED ON"));
//   } else {
//     digitalWrite(LED_PIN, LOW);
//     Serial.println("LED OFF");
//   }
//   delay(50);
// }

const int LEDS[] = {12, 14, 27, 26};
const int N = sizeof(LEDS) / sizeof(LEDS[0]);
const int BUTTON_PIN = 18;

bool ledState = false;       
bool lastButtonState = HIGH; 

void setup() {
  for (int i = 0; i < N; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    ledState = !ledState; // flip ON/OFF state

    for (int i = 0; i < N; i++) {
      digitalWrite(LEDS[i], ledState ? HIGH : LOW);
    }
    
    delay(50); 
  }

  lastButtonState = buttonState;
}

