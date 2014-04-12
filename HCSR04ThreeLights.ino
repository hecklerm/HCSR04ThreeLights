// Sketch to test the HC-SR04 distance sensor
// Written by Mark A. Heckler
// mark.heckler@gmail.com, @MkHeck
// http://www.thehecklers.org
// All rights reserved, but you're free to use in any way with attribution!

// Define the pins we use on the Arduino to send (Trigger) & receive (Echo)
#define TRIG_PIN 8
#define ECHO_PIN 10
// Define the pins for the visual (LED) display. As the sensed object
// gets closer, we go from COLD to WARM and finally, to HOT!
#define COLD 4
#define WARM 3
#define HOT 2

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Set up trigger pin...
  pinMode(ECHO_PIN, INPUT); // ...and echo pin

  pinMode(COLD, OUTPUT);
  pinMode(WARM, OUTPUT);
  pinMode(HOT, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // Establish variables for duration of the ping and 
  // the distance result in inches & centimeters
  long duration, inches, cm;

  // The ping is triggered by a HIGH pulse of 2 or more microseconds.
  // Send a short LOW pulse beforehand to ensure a clean HIGH pulse.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

  // Now read the signal from the echo pin: a HIGH pulse whose duration is 
  // the time (in microseconds) from the sending of the ping to the reception 
  // of its echo off of an object.
  duration = pulseIn(ECHO_PIN, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  if (cm > 50) {
    lightEmUp(COLD);
  } else if (cm > 25) {
    lightEmUp(WARM);
  } else {
    lightEmUp(HOT);
  }

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet, there are 73.746 microseconds per inch,
  // i.e. sound travels at 1130 feet/second. This gives the distance travelled 
  // by the ping, outbound and return, so we divide by 2 to get the distance 
  // of the sensed object.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 73.746 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object, we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void lightEmUp(int whichLED) {
  // Extinguish all first
  digitalWrite(COLD, LOW);
  digitalWrite(WARM, LOW);
  digitalWrite(HOT, LOW);
  
  // Light up the appropriate LED
  digitalWrite(whichLED, HIGH);
}

