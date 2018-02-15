/* Traffic light system where one direction is normally open, and the other only when triggered by a push button.
 * By Nick Puylaert.
 */

const int button = 8; //init button
const int stateLed = 13; //init state led (to show if button has been pressed)
int state;

// init traffic light 1
const int red1 = 2;
const int yellow1 = 3; 
const int green1 = 4;

// traffic light 2
const int red2 = 5; // init red1
const int yellow2 = 6; // init yellow1
const int green2 = 7; // init green 1

void setup() {
  // put your setup code here, to run once:
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
pinMode(button, INPUT); // button is input
pinMode(stateLed, OUTPUT);
pinMode(red1, OUTPUT);
pinMode(yellow1, OUTPUT);
pinMode(green1, OUTPUT);
pinMode(red2, OUTPUT);
pinMode(yellow2, OUTPUT);
pinMode(green2, OUTPUT);

// init state
state = LOW;


// init traffic light 1 -> GREEN
digitalWrite(red1, LOW);
digitalWrite(yellow1, LOW);
digitalWrite(green1, HIGH);

// init traffic light 2 -> RED
digitalWrite(red2, HIGH);
digitalWrite(yellow2, LOW);
digitalWrite(green2, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
state = digitalRead(button); 
  
  // when button is NOT pressed keep stateLed of
while (state == LOW) {
  digitalWrite(stateLed, LOW);
  Serial.println(state);
  delay(1);
  state = digitalRead(button);  
}

// when button is pressed, switch state to HIGH and start script for switching traffic lights
  state = HIGH;
  digitalWrite(stateLed, HIGH);
  Serial.println(state);
  delay(1000);

  digitalWrite(green1, LOW);
  digitalWrite(yellow1, HIGH);
  delay(1000);
  digitalWrite(yellow1, LOW);

  digitalWrite(red1, HIGH);
  delay(2000);

  digitalWrite(red2, LOW);
  digitalWrite(green2, HIGH);
  delay(2000);

  digitalWrite(green2, LOW);
  digitalWrite(yellow2, HIGH);
  delay(1000);
  digitalWrite(yellow2, LOW);
  digitalWrite(red2, HIGH);
  delay(2000);

  digitalWrite(red1, LOW);;
  digitalWrite(green1, HIGH);
  delay(2000);
  
// reset state to LOW and led off

state = LOW;
digitalWrite(stateLed, LOW);
  Serial.println(state);
  delay(1);    
}
