
/* TimeTimer: set timer with pot meter, start timer with button, reset timer with other button.
 * By Nick Puylaert.
 */

#include <Stepper.h>

int stepsPerRevolution = 200;
int stepsToDo = 0;  // change this to fit the number of steps per revolution
// for your motor

int sensorPin = A0;    // select the input pin for the potentiometer 
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the potentiometer
int buttonPin = 2;    // select the input pin for the button
int buttonState = 0;  // variable to store button state
int sensorTime = 0; // variable to store sensorTime
int startTime = 0; // variable for startTime steppermovement
int elapsedTime = 0; // variable for elapsedTime steppermovement
int buzzer = 4; 

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  // declare the buttonPin as an INPUT:
  pinMode(buttonPin, INPUT);
    // declare the buzzer as an OUTPUT:
  pinMode(buzzer, OUTPUT);
  // set the speed at 60 rpm:
  myStepper.setSpeed(120);
  
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue/17.05);
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
  // turn led on:
  digitalWrite(ledPin, HIGH);
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // convert sensorValue to sensorTime:
  sensorTime = sensorValue/17.05;
  sensorTime = round(sensorTime);
  // convert sensorValue to stepsToDo
  stepsToDo = sensorValue/17.05*34.13333;
  // print value from sensor:
  Serial.println(sensorValue/17.05);
  // put stepper in correct timer position
  Serial.println("Setting up timer");
  myStepper.step(stepsToDo);
  delay(500);
  // start countdown timer in seconds
  Serial.println("Start");
  for (int sensorTimePieces=sensorTime; sensorTimePieces > 0; sensorTimePieces--) {
  Serial.println(sensorTimePieces);
  // register startTime
  startTime = millis();
  // start stepper for each second
  myStepper.step(-stepsToDo/sensorTime);
  //register elapsedTime and change delay to have exactly 1 second
  elapsedTime = millis() - startTime;
  delay(1000-elapsedTime);
  }
  // Stop and reset timer and led
  Serial.println("Stop & reset");
  //reset sensorState and led off:
  buttonState = LOW;
  digitalWrite(ledPin, LOW);
  buzzerDo();
  } else {
  digitalWrite(ledPin, LOW);
    }
  
}

void buzzerDo() {
  digitalWrite(buzzer, HIGH); 
  delay(500);
  digitalWrite(buzzer, LOW);
}

