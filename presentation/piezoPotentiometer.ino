/*
 In this experiment:
 The Potentiometer - POT1 from the GPIO Board is connected to analog input pin of the Arduino Board.
 The analog value, converted by the inbuilt ADC to a 10 bit value lies between 0-1023.
 It is mapped to a result in the range 0-255.
 This result is used to set the pulsewidth modulation (PWM) of an Analog output pin.
 A Buzzer is connected to the PWM outpin pin and we will observe that as the POT is turned,
 the sound (tone) produced by the Buzzer also changes correspondingly.
 The 10 bit ADC value and 8 bit PWM value is also printed on the serial monitor.
 
 The circuit:
 * POT1 connected to analog pin 1.

 * Buzzer (from GPIO Board) connected to digital pin 10
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A1;  // Analog input pin that the POT is attached to
const int analogOutPin = 10; // Analog output pin that the Buzzer is attached to

int sensorValue = 0;        // value read from the POT
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
