int const button22 = 7;
int const button23 = 23;
int const button24 = 24;
int const button25 = 25;
int const button26 = 26;
int const button27 = 27;
int const button28 = 28;
int const potA0 = A0;

int state22 = LOW;
int state23 = LOW;
int state24 = LOW;
int state25 = LOW;
int state26 = LOW;
int state27 = LOW;
int state28 = LOW;

int const buttonBegin = 24;
int const buttonEnd = 31;

void setup() {
  Serial.begin(230400);

  for(int i = buttonBegin; i < buttonEnd; i++) {
    activateAsButton(i);
  }

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Setup complete");
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  bool pressed = false;
  
 for(int i = buttonBegin; i < buttonEnd; i++) {
    if(checkButton(i)) {
      Serial.println(i);
      pressed = true;
    }
  }

  if(pressed) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}

void activateAsButton(int button) {
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}

boolean checkButton(int button) {
  return digitalRead(button) == LOW;
}

