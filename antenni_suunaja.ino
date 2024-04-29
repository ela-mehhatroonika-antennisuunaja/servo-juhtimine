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

String data;

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

void turnhoriz(guidanceinfo data) {
  float corr;
  float angle = data.hor_dir;
  float init = data.initialbear;

  corr = 101 + init - angle;

  if (corr > 202) {
    corr = 202;
  }

  if (corr < 0) {
    corr = 0;
  }

  int pwm = map(corr, 0, 202, 1000, 1998);
  //Serial.println("Horisontaalne nurk: " + String(angle) + "Pwm: "+ String(pwm));
  servohoris.writeMicroseconds(pwm);
}

void turnvert(guidanceinfo data) { //500 min max 2500
  int angle = data.vert_dir;
  if (angle > 90) {
    angle = 90;
  }

  if (angle < 0) {
    angle = 0;
  }

  int pwm = map(angle, 0, 90, 500, 2500);
  //Serial.println("Vert nurk: " + String(angle) + "Pwm: "+ String(pwm));
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

void senddataback(guidanceinfo data){
  Serial.println(data.hor_dir);
  //Serial.println("tere");
}

guidanceinfo recmessage (){
  guidanceinfo data;
  if (Serial.available()) {
    // Read the incoming data until newline character '\n'
    String json_str = Serial.readStringUntil('\n');
    
    // Parse the JSON data
    DynamicJsonDocument json_doc(1024);
    DeserializationError error = deserializeJson(json_doc, json_str);
    
    // Check if parsing was successful
    if (!error) {
      data.hor_dir = json_doc["hor_dir"];
      data.vert_dir = json_doc["vert_dir"];
      data.initialbear = json_doc["initialbear"];
      //senddataback(data);
      return(data);

    } else {
      // Print an error message if parsing failed
      Serial.print("Parsing failed: ");
      Serial.println(error.c_str());
    }
  }
}

void loop() {
  guidanceinfo data;
  data = recmessage();
  turnhoriz(data);
  turnvert(data);
} 
