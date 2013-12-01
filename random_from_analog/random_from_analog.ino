/*
  RamdomFromAnalog
  With nothing connected to the analog input on pin 0, I have no idea what values it's reading.
  Let's call it random.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  if (sensorValue % 12 == 0) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("flash");
  } else {
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
  delay(30);        // delay in between reads for stability
}
