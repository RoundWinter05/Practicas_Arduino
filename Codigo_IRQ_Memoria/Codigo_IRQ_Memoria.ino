//Pin declaration
int pausePin = 2;

int button1 = 5;
int button2 = 6;
int button3 = 7;
int led = 10;

//Delays
int shortDelay = 200;
int longDelay = 900;

//Secuence variables
volatile int currentMode = 0;  // 0 - none / 1 - SOS / 2 - blink / 3 - fade
volatile int currentStep = 0;

volatile int savedMode;
volatile int savedStep;

//Puase flags
volatile bool pauseEvent = false;
bool isPaused = false;

void setup() {
  pinMode(pausePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pausePin), setPause, FALLING);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //read button inputs 
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  int buttonState3 = digitalRead(button3);

  //check pauseEvent (pause/interruptionFlag)
  if (pauseEvent) {
    delay(5);
    pauseEvent = false;

    //check if the button was pressed before
    if (!isPaused) {
      //Save current step into the saved state if not
      isPaused = true;
      savedMode = currentMode;
      savedStep = currentStep;

      Serial.println("Secuencia pausada");
      Serial.print("Modo guardado:");
      Serial.println(savedMode);
      Serial.print("Paso guardado:");
      Serial.println(savedStep);
      Serial.println();
    } else {
      //Set the current where it was before the save
      Serial.println("Resuminedo Secuencia");
      isPaused = false;
      currentMode = savedMode;
      currentStep = savedStep;
      resumeSecuence();
    }
  }

  //Continue as normal when there's no pause
  if (!pauseEvent) {
    if (buttonState1 == LOW) {
      currentMode = 1;
      currentStep = 0;
      SOS();


    } else if (buttonState2 == LOW) {
      currentMode = 2;
      currentStep = 0;
      blink();


    } else if (buttonState3 == LOW) {
      currentMode = 3;
      currentStep = 0;
      fade();

    }
  }
}

//
//LED Methods... slightly modified
//

void SOS() {
  Serial.println("Inicio del SOS");
  //Morse for letter "S"
  for (int i = currentStep; i < 3 && !pauseEvent && currentMode == 1; i++) {
    overrideSecuence(); //<- Checks if any button has been pressed

    digitalWrite(led, HIGH);
    delay(shortDelay);
    digitalWrite(led, LOW);
    delay(shortDelay);

    currentStep++;
    Serial.print("Paso acutal: ");
    Serial.println(currentStep);

    overrideSecuence(); // checks twice to ensure capturing the button press
  }

  // Morse for letter "O"
  for (int i = currentStep; i < 6 && !pauseEvent && currentMode == 1; i++) {
    overrideSecuence();

    digitalWrite(led, HIGH);
    delay(longDelay);
    digitalWrite(led, LOW);
    delay(shortDelay);

    currentStep++;
    Serial.print("Paso acutal: ");
    Serial.println(currentStep);

    overrideSecuence();
  }

  // Morse for letter "S"
  for (int i = currentStep; i < 9 && !pauseEvent && currentMode == 1; i++) {
    
    overrideSecuence(); 

    digitalWrite(led, HIGH);
    delay(shortDelay);
    digitalWrite(led, LOW);
    delay(shortDelay);

    currentStep++;
    Serial.print("Paso acutal: ");
    Serial.println(currentStep);

    overrideSecuence(); 
  }
  //Indicates whether it has finished its cycle or if it has been paused
  Serial.println(currentStep < 9 ? "Se pauso el SOS" : "Final del SOS ");
  Serial.println();
}

void blink() {
  Serial.println("Inicio del blink");
  for (int i = currentStep; i < 7 && !pauseEvent && currentMode == 2; i++) {
    overrideSecuence();

    digitalWrite(led, HIGH);
    delay(shortDelay);
    digitalWrite(led, LOW);
    delay(shortDelay);


    currentStep++;
    Serial.print("Paso acutal: ");
    Serial.println(currentStep);

    overrideSecuence();
  }
  //Fin del blink
  Serial.println(currentStep < 7 ? "Se pauso el blink" : "Final del blink ");
  Serial.println();
}

void fade() {
  Serial.println("Inicio del fade");
  delay(200); //wait .2 seconds to avoid ghost pressing 
  // 512 (duration of one cycle) * 7 (the amount of cycles needed) = 3584
  // 3584 for 7 cycle - 2048 for testing (it takes a while to make it run 7 times)
  for (int i = currentStep; i < 2048 && !pauseEvent && currentMode == 3; i++) {

    int cyclePosition = i % 512;
    int brightness;

    // Fade in (0–255), then fade out (256–511) (?]??)
    if (cyclePosition < 256) {
      brightness = cyclePosition;
    } else {
      brightness = 511 - cyclePosition;
    }

    analogWrite(led, brightness);
    delay(10);

    currentStep = i;

    currentStep++;
    Serial.print("Paso acutal: ");
    Serial.println(currentStep);
    
    overrideSecuence();
  }

  Serial.println(currentStep < 2048 ? "Se pauso la secuencia" : "Final del fade ");
  Serial.println();
}


//
// Auxiliary methods ... 
//(basically the rest of the methods not related to turning the switch on/off)
//


void setPause() {
  pauseEvent = true;
}

//Resume secuence and clear saved values for the next save
void resumeSecuence() {
  if (savedMode == 1) SOS();
  if (savedMode == 2) blink();
  if (savedMode == 3) fade();

  savedMode = 0;
  savedStep = 0;
}

//Override any other secuence going on and starting the new pressed secuence
void overrideSecuence() {
  if (digitalRead(button1) == LOW && currentStep != 0) {
    currentMode = 1;
    currentStep = 0;

    Serial.println("Nueva secuencia; Valores actualizados");
    Serial.print("Modo:");
    Serial.println(currentMode);
    Serial.print("Paso:");
    Serial.println(currentStep);
    Serial.println();
    SOS();

  } else if (digitalRead(button2) == LOW && currentStep != 0) {
    currentMode = 2;
    currentStep = 0;

    Serial.println("Nueva secuencia; Valores actualizados");
    Serial.print("Modo:");
    Serial.println(currentMode);
    Serial.print("Paso:");
    Serial.println(currentStep);
    Serial.println();
    blink();

  } else if (digitalRead(button3) == LOW && currentStep != 0) {
    currentMode = 3;
    currentStep = 0;

    Serial.println("Nueva secuencia; Valores actualizados");
    Serial.print("Modo:");
    Serial.println(currentMode);
    Serial.print("Paso:");
    Serial.println(currentStep);
    Serial.println();
    fade();
  }
}

