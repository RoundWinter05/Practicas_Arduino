int ejemplo[6];
int randomNumber;

int Led1 = 5;
int Led2 = 6;
int Led3 = 7;
int Led4 = 8;
int Led5 = 9;
int Led6 = 10;

int interruptionPin = 2;

int pressedButton = -1;

volatile bool resetFlag = false;

int tries = 3;

void setup() {
  Serial.begin(9600);
  pinMode(interruptionPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptionPin), resetButton, FALLING);
  /*
  pinMode(button0, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
*/
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led5, OUTPUT);
  pinMode(Led6, OUTPUT);

  reset();
}

void loop() {
  if (resetFlag == true) {
    reset();
  }

  if (tries > 0) {
    checkAttempt();
  } else {
    Serial.println("Se acabaron los intentos, Intente de nuevo");
    Serial.println();
    reset();
  }
}

int readButton() {

  int buttonState0 = digitalRead(A5);
  int buttonState1 = digitalRead(A4);
  int buttonState2 = digitalRead(A3);
  int buttonState3 = digitalRead(A2);
  int buttonState4 = digitalRead(A1);
  int buttonState5 = digitalRead(A0);

  if (buttonState0 == LOW) {
    pressedButton = 0;
    delay(500);
  } else if (buttonState1 == LOW) {
    pressedButton = 1;
    delay(500);
  } else if (buttonState2 == LOW) {
    pressedButton = 2;
    delay(500);
  } else if (buttonState3 == LOW) {
    pressedButton = 3;
    delay(500);
  } else if (buttonState4 == LOW) {
    pressedButton = 4;
    delay(500);
  } else if (buttonState5 == LOW) {
    pressedButton = 5;
    delay(500);
  }

  return pressedButton;
}

void checkAttempt() {
  switch (readButton()) {
    case 0:
      Serial.println("El boton 0 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led1, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intentos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
    case 1:
      Serial.println("El boton 1 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led2, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intentos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
    case 2:
      Serial.println("El boton 2 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led3, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intentos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
    case 3:
      Serial.println("El boton 3 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led4, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intenos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
    case 4:
      Serial.println("El boton 4 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led5, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intentos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
    case 5:
      Serial.println("El boton 5 fue presionado");
      if (ejemplo[pressedButton] != 0) {
        Serial.println("Felicidades");
        successSecuence();
        reset();
      } else {
        digitalWrite(Led6, HIGH);
        Serial.println("No está aquí  :(");
        tries -= 1;
        Serial.print("Intentos: ");
        Serial.println(tries);
        Serial.println();
      }
      break;
  }
  pressedButton = -1;
}

void resetSecuence() {
  digitalWrite(Led1, HIGH);
  delay(100);
  digitalWrite(Led1, LOW);

  digitalWrite(Led2, HIGH);
  delay(100);
  digitalWrite(Led2, LOW);

  digitalWrite(Led3, HIGH);
  delay(100);
  digitalWrite(Led3, LOW);

  digitalWrite(Led4, HIGH);
  delay(100);
  digitalWrite(Led4, LOW);

  digitalWrite(Led5, HIGH);
  delay(100);
  digitalWrite(Led5, LOW);

  digitalWrite(Led6, HIGH);
  delay(100);
  digitalWrite(Led6, LOW);
}

void successSecuence() {
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);

  for (int i = 0; i < 3; i++) {
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    digitalWrite(Led5, HIGH);

    delay(500);

    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    digitalWrite(Led5, LOW);

    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    digitalWrite(Led6, HIGH);

    delay(500);

    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);
    digitalWrite(Led6, LOW);
  }
}

void resetButton() {
  resetFlag = true;
}

void reset() {
  for (int i = 0; i < 5; i++) {
    ejemplo[i] = 0;
  }
  randomNumber = random(0, 5);

  ejemplo[randomNumber] = 1;

  Serial.println("Se ha reiniciado el juego");
  Serial.println(randomNumber);
  Serial.println("Array con el numero aleatorio:");
  for (int i = 0; i < 6; i++) {
    Serial.print(ejemplo[i]);
    Serial.print(",  ");
  }
  Serial.println();
  Serial.println();

  tries = 3;
  /*
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);
  digitalWrite(Led4, LOW);
  digitalWrite(Led5, LOW);
  digitalWrite(Led6, LOW);
*/
  resetSecuence();
  delay(1000);
  resetFlag = false;
}
