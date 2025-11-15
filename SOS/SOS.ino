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

  //check the state of the button 1 - SOS
  if (buttonState1 == LOW) {
    Serial.println("Boton 1 presionado"); 
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
    Serial.println("Final del SOS");
    delay(2000);
  }
}