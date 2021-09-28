#include <Servo.h>

Servo spray;
Servo sponge;
Servo fan;

#define trigPin 2
#define echoPin 3
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control


void SensorSetup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int MeasureDistance() {       // a low pull on pin COMP/TRIG  triggering a sensor reading
  long duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //that can also include a timemout
  long distance = (duration / 2) / 29.1;
  return (int)distance;
}

void advance(char a, char b)         //Move forward
{
  analogWrite (E1, a);     //PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite (E2, b);
  digitalWrite(M2, HIGH);
}
void stop(void)                    //Stop
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}


void back_off (char a, char b)         //Move backward
{
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, b);
  digitalWrite(M2, LOW);
}
void setup() {
  Serial.begin(9600);                        
  SensorSetup();
  spray.attach(4);
  sponge.attach(7);
  fan.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:

  int actualDistance = MeasureDistance();
  Serial.print(actualDistance);
  Serial.println(" cm");

  delay(500);


  if (actualDistance > 15) {
    advance(100, 100);
  }

  if (actualDistance <= 15) {
    stop();

    for (int count = 0; count < 1; count++) {
        // move the servo that is supposed to hit the spray bottle 3 times
      for (int countSpray = 0; countSpray < 3; countSpray++) {
        spray.write(200);
        delay(200);
        spray.write(35);
        delay(200);
      }
      delay(1000);
        // move the servo with the sponge 5 times
      for (int countSponge = 0; countSponge < 5; countSponge++) {
        sponge.write(180);
        delay(350);
        sponge.write(20);
        delay(350);
      }
      delay(1000);
        // move the servo with the fan 10 times
      for (int countFan = 0; countFan < 10; countFan++) {
        fan.write(270);
        delay(20);
        fan.write(0);
        delay(20);
      
        delay(1000);
      }
    }
    
  }
}
