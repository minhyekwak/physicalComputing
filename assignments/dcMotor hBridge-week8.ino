const int control1 = 2;
const int control2 = 3;
const int enable = 9;

const int directionSwitch = 4;
const int onOff = 5;
const int changeSpeed = A0;

int onOffState = 0;
int previousOnOffState = 0;

int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorRun = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  
  pinMode(directionSwitch, INPUT);
  pinMode(onOff, INPUT);
  pinMode(control1, OUTPUT);
  pinMode(control2, OUTPUT);
  pinMode(enable, OUTPUT);

  digitalWrite(enable, LOW);

}

void loop() {

  onOffState = digitalRead(onOff);
  delay(1);

  directionSwitchState = digitalRead(directionSwitch);

  motorSpeed = analogRead(changeSpeed)/4;

  if(onOffState != previousOnOffState) {
      if(onOffState == HIGH) {
          motorRun = !motorRun;
        }
    }

   if(directionSwitchState != previousDirectionSwitchState) {
      if(directionSwitchState == HIGH) {
          motorDirection = !motorDirection;
        }
    }

   if (motorDirection == 1) {
      digitalWrite(control1, HIGH);
      digitalWrite(control2, LOW);
    } else 
    {
      digitalWrite(control1, LOW);
      digitalWrite(control2, HIGH);
    }

   if (motorRun == 1) {
      analogWrite(enable, motorSpeed);
    } else 
    {
      analogWrite(enable, 0);
    }

   previousOnOffState = onOffState;
   previousDirectionSwitchState = directionSwitchState;

}
