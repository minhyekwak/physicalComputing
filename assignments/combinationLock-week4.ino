const int button1 = 3;
const int button2 = 4;
const int button3 = 5;
const int button4 = 6;

const int ledYellow = 9;
const int ledBlue = 10;

int button1State = 0; 
int button2State = 0; 
int button3State = 0;
int button4State = 0; 

int ledYellowState = LOW;
int ledBlueState = LOW;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

}

void loop() {
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);

  if (button1State == HIGH && button3State == HIGH && button2State == LOW && button4State == LOW) {
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledBlue, LOW);
    }
  else if (button1State == LOW && button3State == LOW && button2State == HIGH && button4State == HIGH) {
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledBlue, HIGH);
    }
  else {
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledBlue, LOW);
    }

}
