int interruptionPin = 2;

int button1 = 5;
int button2 = 6;
int button3 = 7;
int led = 10;

int shortDelay = 200;
int longDelay = 900;

volatile bool interrupt = false;

void setup() {
  pinMode(interruptionPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptionPin), myInterruption, CHANGE);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Lectura de los botones
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  int buttonState3 = digitalRead(button3);

  interrupt = false;

  if (buttonState1 == LOW) {
    Serial.println("Boton 1 presionado");  //Boton del S.O.S
    Serial.println("Inicio del SOS");
    // Morse para la letra "S"
    for (int i = 0; i < 3 && !interrupt; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }

    // Morse para la letra "O"
    for (int i = 0; i < 3 && !interrupt; i++) {
      digitalWrite(led, HIGH);
      delay(longDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }

    // Morse para la letra "S"
    for (int i = 0; i < 3 && !interrupt; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }
    //Fin de Sos
    Serial.println(interrupt ? "Se interrumpio la secuencia" : "Final del SOS ");
    //Serial.println("Final del SOS");
    delay(2000);

  } else if (buttonState2 == LOW) {
    Serial.println("Boton 2 presionado");  //boton del blink
    Serial.println("Inicio del Blink");
    for (int i = 0; i < 7 && !interrupt; i++) {
      digitalWrite(led, HIGH);
      delay(shortDelay);
      digitalWrite(led, LOW);
      delay(shortDelay);
    }
    //Fin del Blink
    Serial.println(interrupt ? "Se interrumpio la secuencia" : "Final del Blink ");
    //Serial.println("Final del Blink");
    delay(2000);

  } else if (buttonState3 == LOW) {
    Serial.println("Boton 3 presionado"); //boton del fade
    Serial.println("Inicio del Fade");
    for (int j = 0; j <= 7 && !interrupt; j++) {
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
    //fin del Fade
    Serial.println(interrupt ? "Se interrumpio la secuencia" : "Final del Fade ");
    //Serial.println("Final del Fade");
    delay(2000);
  }
}

void myInterruption() {
  interrupt = true;
}