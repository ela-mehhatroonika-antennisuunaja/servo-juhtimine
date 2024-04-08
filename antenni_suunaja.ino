#include <Servo.h> 

//1 pwm = 0.2025 kraad
//5 pwm = 1 kraad
// max pööre 202.5 kraadi ehk 101.25 mõlemale poole
Servo myservo;
int angle;
void setup() 
{ 
  Serial.begin(115200);
  myservo.attach(9);
  myservo.writeMicroseconds(1500);  // set servo to mid-point
} 

void turnhoriz(int angle) {
  int pwm = map(angle, 0, 202, 1000, 1998);
  Serial.println(pwm);
}

void loop() {
  /*
  delay(15000);
  myservo.writeMicroseconds(1000);
  delay(15000);
  myservo.writeMicroseconds(1500);
  delay(15000);
  myservo.writeMicroseconds(2000);
  */
  turnhoriz(202);
} 
