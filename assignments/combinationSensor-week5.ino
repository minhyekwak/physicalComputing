const int trigPin = 11; 
const int echoPin = 12;

const int photoResistor = A0;

const int led1 = 7;
const int led2 = 6;
const int led3 = 5;

int lightValue;

void setup() {
  Serial.begin (9600);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);

  pinMode (photoResistor, INPUT);

}

void loop() {
    long duration, distance;
    digitalWrite (trigPin, HIGH);
    delayMicroseconds (1000);
    digitalWrite (trigPin, LOW);
    duration = pulseIn (echoPin, HIGH);
    distance = (duration/2)/29.1;
    lightValue = analogRead(photoResistor);
    Serial.print(distance);
    Serial.print("CM");
    Serial.print("\t");
    Serial.println(lightValue);
    delay(10);

    if (lightValue < 200) {
      digitalWrite (led1, LOW);
      digitalWrite (led2, LOW);
      digitalWrite (led3, LOW);
      }
    
    else {
      if (distance <= 7) {
        digitalWrite (led1, HIGH);
        }
      else {
        digitalWrite (led1, LOW);
        }

      if (7 < distance && distance <= 14) {
        digitalWrite (led2, HIGH);
        }
      else {
        digitalWrite (led2, LOW);
        }

      if (distance > 14) {
        digitalWrite (led3, HIGH);
        }
      else {
        digitalWrite (led3, LOW);
        }

    }
}
