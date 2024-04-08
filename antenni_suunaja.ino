#include <Servo.h> 

//1 pwm = 0.2025 kraad
//5 pwm = 1 kraad
// max pööre 202.5 kraadi ehk 101.25 mõlemale poole

// juhe nr 1 horisontaalne liikumine - PIN 9
// juhe nr 2 vertikaalne - PIN 11

int horpwm;
int vertpwm;

Servo servohoris;
Servo servovert;

void setup() {
  Serial.begin(115200);
  servohoris.attach(9);
  servovert.attach(11);
  //servohoris.writeMicroseconds(1500);  // set servo to mid-point
  //servovert.writeMicroseconds(500);
} 

void turnhoriz(int angle) {
  if (angle > 202) {
    angle = 202;
  }

  if (angle < 0) {
    angle = 0;
  }

  int pwm = map(angle, 0, 202, 1000, 1998);
  Serial.println("Horisontaalne nurk: " + String(angle) + "Pwm: "+ String(pwm));
  servohoris.writeMicroseconds(pwm);
}

void turnvert(int angle) { //500 min max 2500
  if (angle > 90) {
    angle = 90;
  }

  if (angle < 0) {
    angle = 0;
  }

  int pwm = map(angle, 0, 90, 500, 2500);
  Serial.println("Vert nurk: " + String(angle) + "Pwm: "+ String(pwm));
  servovert.writeMicroseconds(pwm);
}


void endtoend() {
  servohoris.writeMicroseconds(1000);
  servovert.writeMicroseconds(500);
  delay(8000);
  servohoris.writeMicroseconds(1500);
  servovert.writeMicroseconds(1500);
  delay(8000);
  servohoris.writeMicroseconds(2000);
  servovert.writeMicroseconds(2500);
  delay(8000);

}


void loop() {
  endtoend();
  //turnhoriz(0);
  //turnvert(0);
} 
