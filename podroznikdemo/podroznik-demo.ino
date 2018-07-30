#include "movement.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //  SDA=A4 SCL=A5
#define SERVOMIN  150
#define SERVOMAX  600

#define W8T 700
#define loopwait 30000

void srvinit() {
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}
int angle(int ang) {
  return map(ang, -90, 90, SERVOMIN, SERVOMAX);
}
int angle2(int ang) {
  return map(ang, 90, -90, SERVOMIN, SERVOMAX);
}
int srv [12] = { };

void writeServos() {

  pwm.setPWM(0, 0, angle(srv[0]));
  pwm.setPWM(1, 0, angle(srv[1]));
  pwm.setPWM(2, 0, angle(srv[2]));
  pwm.setPWM(3, 0, angle2(srv[3]));
  pwm.setPWM(4, 0, angle(srv[4]));
  pwm.setPWM(5, 0, angle2(srv[5]));
  pwm.setPWM(6, 0, angle2(srv[6]));
  pwm.setPWM(7, 0, angle(srv[7]));
  pwm.setPWM(8, 0, angle2(srv[8]));
  pwm.setPWM(9, 0, angle(srv[9]));
  pwm.setPWM(10, 0, angle2(srv[10]));
  pwm.setPWM(11, 0, angle2(srv[11]));
  //Serial.write("Servos written\r\n");
  flushBuffer();
}
void stop(int s[12]) {
  s[0] = 0;
  s[1] = 20;
  s[2] = 0;
  s[3] = 20;
  s[4] = 0;
  s[5] = 20;
  s[6] = 0;
  s[7] = 20;
  s[8] = 0;
  s[9] = 20;
  s[10] = 0;
  s[11] = 20;
}
void inba(int s[12]) {
  s[0] = 0;
  s[1] = 20;
  s[2] = 0;
  s[3] = 40;
  s[4] = 0;
  s[5] = 20;
  s[6] = 0;
  s[7] = 20;
  s[8] = 0;
  s[9] = 40;
  s[10] = 0;
  s[11] = 20;
}
void setup() {
  // put your setup code here, to run once:
  srvinit();
  zero(srv);
  writeServos();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 5; i++) {
    stop(srv);
    delay(W8T);
    inba(srv); //dQw4w9WgXcQ
    delay(W8T);
  }
  delay(loopwait);
}
