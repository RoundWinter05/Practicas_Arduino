int button1 = 5;
int led = 10;

int shortDelay = 200;
int longDelay = 900;


void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //read button input
  int buttonState1 = digitalRead(button1);

  //check the state of the button 1
  if (buttonState1 == LOW) {
    Serial.println("Inicio del SOS");
    // Morse for letter S
    for (int i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }

    // Morse for letter O
    for (int i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      delay(longDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }

    // Morse fir letter S
    for (int i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);


    }

    Serial.println("Inicio del Blink");
    for (int i = 0; i < 7; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }
    Serial.println("Final del blink");
    delay(2000);


    Serial.println("Inicio del Fade");
    for (int j = 0; j <= 7; j++) {
      //Fade in
      for (int i = 0; i <= 255; i++) {
        analogWrite(led, i);
        delay(10);
      }

      //Fade out
      for (int i = 255; i >= 0; i--) {
        analogWrite(led, i);
        delay(10);
      }
    }
    Serial.println("Final del fade");
    delay(2000);
  } 
}