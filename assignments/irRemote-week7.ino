#include <IRremote.h>

int recvLED = 13;
int recvPin = 11;

IRrecv irReciver(recvPin);
decode_results results;

// Defining the pins for the 7 segment display
byte s7segment[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

// Initializing the digits array
byte digits[][13] = {
   { 1, 1, 1, 1, 1, 1, 0, 0}, // digit 0
   { 0, 0, 1, 1, 0, 0, 0, 0}, // digit 1
   { 1, 1, 0, 1, 1, 0, 1, 0}, // digit 2
   { 0, 1, 1, 1, 1, 0, 1, 0}, // digit 3
   { 0, 0, 1, 1, 0, 1, 1, 0}, // digit 4
   { 0, 1, 1, 0, 1, 1, 1, 0}, // digit 5
   { 1, 1, 1, 0, 1, 1, 1, 0}, // digit 6
   { 0, 0, 1, 1, 1, 0, 0, 0}, // digit 7
   { 1, 1, 1, 1, 1, 1, 1, 0}, // digit 8
   { 0, 1, 1, 1, 1, 1, 1, 0}, // digit 9
   { 1, 0, 0, 1, 1, 1, 1, 0}, // Power button
   { 1, 0, 1, 1, 1, 1, 0, 0}, // Volume up
   { 1, 1, 1, 1, 0, 1, 0, 0}  // Volume down
};

const unsigned long decodeHASH[] = {
//  0xC101E57B, // Digit 0
  0xFF6897, // Digit 0
//  0x9716BE3F, // digit 1
  0xFF30CF, // digit 1
//  0x3D9AE3F7, // digit 2
  0xFF18E7, // digit 2 
//  0x6182021B, // digit 3
  0xFF7A85, // digit 3
//  0x8C22657B, // digit 4
  0xFF10EF, // digit 4
//  0x488F3CBB, // digit 5
  0xFF38C7, // digit 5
//  0x449E79F,  // digit 6
  0xFF5AA5,  // digit 6
//  0x32C6FDF7, // digit 7
  0xFF42BD, // digit 7
//  0x1BC0157B, // digit 8
  0xFF4AB5, // digit 8
//  0x3EC3FC1B, // digit 9
  0xFF52AD, // digit 9
//  0xE318261B, // Power button
  0xFFA25D, // Power button
//  0xE5CFBD7F, // Volume up
  0xFF629D, // Volume up
//  0xA3C8EDDB  // volume down
  0xFFA857  // volume down
};
  
unsigned long lastTime = 0;
  
void setup()
{
  pinMode(recvLED, OUTPUT); //Configue the recvLED pin as an OUTPUT pin
  digitalWrite(recvLED, LOW); //Leave the LED off as we start

  Serial.begin(9600); // Initialize the serial port with a baud rate of 9600 bps

  irReciver.enableIRIn(); // Start the receiver
  
  for (int i=0; i<8; i++) 
  {
    pinMode(s7segment[i], OUTPUT); //Configure all pins in the 7 segments display as OUTPUT  
  }  
}

void loop()
{
  unsigned long recv_value;
  
  if (irReciver.decode(&results)) {
    recv_value = results.value; 
    
    if (  recv_value != 0xFFFFFFFF ) //Ignore the 0x00 values recived as a result of pressing and holding a button on the remote for long
    {
      // Blink the LED each time a button is pressed
      digitalWrite(recvLED, HIGH);
      delay(10);
      digitalWrite(recvLED, LOW);  
      
      // Output the decoded hash value to th serial monitor. This is for debugging purposes only.
      Serial.println(recv_value, HEX);
      
      //Iterate through the decoded hash array values to find a match
      for (int i=0; i<13; i++)
      {
        if ( recv_value == decodeHASH[i] ) // If the received value matches one of the values in the hash array
        { 
          lastTime = millis(); // Start power saving delay timer
          for (int j=0; j<=8; j++)
            //Set the relevant segments HIGH or LOW as defined in the digits[][] double array
            digitalWrite(s7segment[j], digits[i][j]);
            
          break; // Exit from the inner loop as we have now toggled all required segments to display the appropriate value
        }
      }
    }
    irReciver.resume(); // Read the next value
  }
  
  // To save power switch off all segments if 5 seconds has elapsed since 
  if ( millis() - lastTime >= 5000 )
  {
    for (int k=0; k<=8; k++)
      digitalWrite(s7segment[k], LOW);
      
    lastTime = 0; // Reset the power saving delay timer to zero '0'   
  }
}
