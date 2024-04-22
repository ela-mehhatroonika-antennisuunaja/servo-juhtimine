#include <Servo.h> 
#include <ArduinoJson.h>

//1 pwm = 0.2025 kraad
//5 pwm = 1 kraad
// max pööre 202.5 kraadi ehk 101.25 mõlemale poole

// juhe nr 1 horisontaalne liikumine - PIN 9
// juhe nr 2 vertikaalne - PIN 11

int horpwm;
int vertpwm;

Servo servohoris;
Servo servovert;

struct guidanceinfo{
  float hor_dir;
  float vert_dir;
  float initialbear;
};

void setup() {
  Serial.begin(9600);
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
guidanceinfo getdata(){
  guidanceinfo data;
  if (Serial.available() >= sizeof(float)*3){
    float hor_dir, vert_dir, initialbear;
    Serial.readBytes((char *)&hor_dir, sizeof(float));
    Serial.readBytes((char *)&vert_dir, sizeof(float));
    Serial.readBytes((char *)&initialbear, sizeof(float));
    data.hor_dir = hor_dir;
    data.vert_dir = vert_dir;
    data.initialbear = initialbear;
  }
  return data;
}

void senddataback(guidanceinfo data){
  Serial.println(data.hor_dir);
}
void loop() {
  guidanceinfo data;
  //endtoend();
  data = getdata();
  senddataback(data);

  //turnhoriz(0);
  //turnvert(0);
} 
