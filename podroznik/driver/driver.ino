#include <IRremote.h>
#include "movement.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <avr/pgmspace.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //  SDA=A4 SCL=A5
IRsend irsend; // D3

#define SERVOMIN  150
#define SERVOMAX  600

#define WTV() delay(300)
#define WTH() delay(400)
//WaiT Horizontal, nie What The Hell

//const uint16_t codes[10][67] PROGMEM = {
/*const uint16_t code_w[] PROGMEM =  {4800, 4400, 650, 1650, 650, 1600, 600, 1650, 650, 500, 600, 550, 650, 500, 600, 550, 650, 500, 600, 1650, 650, 1600, 600, 1650, 650, 500, 600, 550, 650, 500, 600, 550, 700, 450, 650, 500, 650, 500, 600, 550, 650, 500, 600, 550, 650, 1600, 600, 1650, 650, 500, 600, 1650, 650, 1600, 650, 1650, 650, 1600, 600, 1650, 650, 500, 600, 550, 650, 1600, 600}; // SAMSUNG E0E006F9
const uint16_t code_s[] PROGMEM =  {4600, 4400, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 600, 500, 550, 600, 600, 500, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 600, 500, 550, 600, 600, 500, 600, 1650, 500, 600, 600, 550, 550, 550, 600, 500, 600, 1650, 600, 1600, 550, 600, 600, 500, 550, 1700, 600, 1600, 550, 1700, 600, 1600, 550, 600, 600, 500, 600, 1650, 500}; // SAMSUNG E0E08679
const uint16_t code_a[] PROGMEM =  {4600, 4450, 550, 1700, 600, 1600, 550, 1700, 600, 550, 500, 600, 600, 550, 550, 550, 600, 550, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 600, 550, 500, 600, 600, 550, 550, 1700, 600, 500, 550, 1700, 600, 500, 550, 600, 600, 1600, 550, 1700, 600, 550, 550, 600, 600, 1600, 550, 600, 600, 1600, 550, 1700, 600, 550, 500, 600, 600, 1650, 550}; // SAMSUNG E0E0A659
const uint16_t code_d[] PROGMEM =  {4600, 4400, 500, 1700, 650, 1600, 550, 1700, 600, 500, 550, 550, 650, 500, 500, 600, 650, 450, 550, 1700, 650, 1600, 500, 1700, 650, 500, 500, 600, 650, 450, 550, 600, 650, 450, 550, 600, 600, 1600, 550, 600, 600, 500, 550, 600, 600, 1600, 550, 1700, 600, 500, 550, 1700, 650, 450, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 650, 1550, 550}; // SAMSUNG E0E046B9

const uint16_t code_x[] PROGMEM =  {4550, 4450, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 600, 500, 550, 600, 550, 550, 550, 1700, 600, 1600, 550, 1700, 600, 500, 550, 600, 550, 550, 500, 600, 600, 550, 500, 600, 600, 500, 550, 600, 600, 1600, 550, 600, 600, 1600, 550, 1700, 600, 500, 550, 1700, 600, 1600, 600, 1650, 600, 500, 550, 1700, 600, 500, 550, 600, 600, 1600, 550}; // SAMSUNG E0E016E9
const uint16_t code_r[] PROGMEM =  {4600, 4400, 600, 1650, 600, 1600, 600, 1650, 650, 450, 600, 550, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 1600, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 500, 650, 500, 600, 500, 650, 450, 600, 1650, 650, 450, 550, 600, 600, 500, 550, 600, 600, 500, 550, 1700, 600, 1600, 600, 550, 650, 1550, 650, 1600, 650, 1600, 550, 1650, 650, 1600, 550}; // SAMSUNG E0E020DF
const uint16_t code_g[] PROGMEM =  {4600, 4400, 600, 1650, 600, 1600, 650, 1600, 600, 500, 650, 500, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 1600, 600, 1650, 600, 500, 600, 550, 600, 500, 650, 500, 650, 500, 650, 1600, 650, 500, 650, 1650, 600, 500, 650, 500, 650, 500, 650, 500, 650, 500, 650, 500, 600, 1650, 650, 500, 650, 1600, 650, 1600, 650, 1600, 650, 1650, 600, 1600, 650}; // SAMSUNG E0E0A05F
const uint16_t code_b[] PROGMEM =  {4550, 4450, 550, 1700, 550, 1700, 500, 1700, 550, 600, 500, 600, 550, 600, 500, 600, 600, 500, 650, 1600, 550, 1700, 550, 1700, 550, 600, 550, 600, 550, 600, 550, 600, 550, 600, 600, 500, 650, 1650, 550, 1700, 550, 600, 550, 600, 550, 600, 550, 600, 600, 500, 650, 1650, 550, 600, 550, 600, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 600, 1650, 600}; // SAMSUNG E0E0609F

const uint16_t code_y[] PROGMEM =  {4550, 4450, 550, 1700, 600, 1600, 550, 1700, 600, 500, 500, 600, 600, 500, 500, 600, 600, 500, 550, 1700, 550, 1650, 500, 1700, 600, 500, 550, 600, 600, 500, 550, 600, 600, 500, 550, 1700, 650, 1600, 550, 1700, 600, 550, 550, 550, 650, 500, 550, 600, 600, 550, 550, 600, 600, 550, 550, 600, 600, 1650, 550, 1700, 650, 1600, 550, 1700, 650, 1600, 600}; // SAMSUNG E0E0E01F
const uint16_t code_n[] PROGMEM =  {4550, 4450, 500, 1700, 600, 1650, 550, 1700, 600, 500, 550, 550, 600, 550, 500, 600, 600, 500, 550, 1700, 600, 1650, 500, 1700, 600, 550, 500, 600, 600, 500, 550, 600, 600, 500, 550, 1700, 600, 1650, 500, 600, 600, 1650, 500, 600, 600, 500, 550, 600, 600, 500, 550, 600, 600, 500, 550, 1700, 600, 500, 500, 1700, 600, 1650, 550, 1700, 600, 1600, 550}; // SAMSUNG E0E0D02F*/
uint16_t kody[] = {
  0x20DF02FD,
  0x20DF827D,
  0x20DFE01F,
  0x20DF609F,

  0x20DF22DD,
  0x20DF8877,
  0x20DF48B7,
  0x20DFC837,

  0x20DF40BF,
  0x20DFC03F
};
//#define OW 3772778233
//#define OS 3772810873
//#define OA 3772819033
//#define OD 3772794553

//#define OR 3772784863
//#define OG 3772817503
//#define OB 3772801183
//#define OX 0x00000000

//#define PY 0xE0E0E01F-
//#define PN 0xE0E0D02F
uint16_t buffer[67];
uint16_t codeid;
void obiekt(int kod) {
  /*switch(kod) {
    case 0:
      codeid = code_w;
      break;
    case 1:
      codeid = code_s;
      break;
    case 2:
      codeid = code_a;
      break;
    case 3:
      codeid = code_d;
      break;

    case 4:
      codeid = code_x;
      break;
    case 5:
      codeid = code_r;
      break;
    case 6:
      codeid = code_g;
      break;
    case 7:
      codeid = code_b;
      break;

    case 8:
      codeid = code_y;
      break;
    case 9:
      codeid = code_n;
      break;
  }
  //strcpy_P(buffer, (unsigned int*)pgm_read_word(&(data_table[kod])));
  for (int i = 0; i < 67; i++) {
    buffer[i] = pgm_read_word_near(codeid + i); // może zadziała
  }*/
  for (int i = 0; i < 5; i++) {
    irsend.sendNEC(kody[kod], 32);

    //irsend.sendRaw(buffer, sizeof(buffer) / sizeof(buffer[0]), 38);
    delay(40);
  }
  delay(100);
  flushBuffer();
}


#include "schematbudowy.h"

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
void flushBuffer() {
  char __flushtmp;
  while (Serial.available()) { //is there anything to read?
    __flushtmp = Serial.read();  //if yes, read it
  } // and never touch it again
}
/* ts
  ￼<21:16:41> "szymszl": jestem
  ￼<21:28:25> "goku": 1:
  ￼<21:28:42> "goku": trojkat lewy: góra
  ￼<21:29:07> "goku": >
  ￼<21:29:09> "goku": prawy
  ￼<21:29:11> "goku": do tylu
  ￼<21:29:30> "goku": >
  ￼<21:29:35> "goku": lewy na ziemie
  ￼<21:29:43> "goku": >
  ￼<21:29:48> "goku": prawy srodek
  ￼<21:29:51> "goku": >lewy do tylu
*/
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
void p() {
  p1(srv);
  writeServos();
  WTV();
  p2(srv);
  writeServos();
  WTH();
  p3(srv);
  writeServos();
  WTV();
  p4(srv);
  writeServos();
  WTV();
  p5(srv);
  writeServos();
  WTH();
  p6(srv);
  writeServos();
  WTV();
}
void r() {
  r1(srv);
  writeServos();
  WTV();
  r2(srv);
  writeServos();
  WTH();
  r3(srv);
  writeServos();
  WTV();
  r4(srv);
  writeServos();
  WTV();
  r5(srv);
  writeServos();
  WTH();
  r6(srv);
  writeServos();
  WTV();
}
void l() {
  l1(srv);
  writeServos();
  WTV();
  l2(srv);
  writeServos();
  WTH();
  l3(srv);
  writeServos();
  WTV();
  l4(srv);
  writeServos();
  WTV();
  l5(srv);
  writeServos();
  WTH();
  l6(srv);
  writeServos();
  WTV();
}
void b() {
  b1(srv);
  writeServos();
  WTV();
  b2(srv);
  writeServos();
  WTH();
  b3(srv);
  writeServos();
  WTV();
  b4(srv);
  writeServos();
  WTV();
  b5(srv);
  writeServos();
  WTH();
  b6(srv);
  writeServos();
  WTV();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  srvinit();
  zero(srv);
  writeServos();
  pinMode(3, OUTPUT);
}
char command = '\0';
void loop() {
  command = Serial.read();
  switch (command) {
    case 0x2A:
      p();
      break;
    case 0x2B:
      b();
      break;
    case 0x2C:
      l();
      break;
    case 0x2D:
      r();
      break;


    case 0x3A:
      obiekt(0);
      break;
    case 0x3B:
      obiekt(1);
      break;
    case 0x3C:
      obiekt(2);
      break;
    case 0x3D:
      obiekt(3);
      break;


    case 0x4A:
      obiekt(5);
      break;
    case 0x4B:
      obiekt(6);
      break;
    case 0x4C:
      obiekt(7);
      break;
    case 0x4D:
      obiekt(4);
      break;


    case 0x70:
      zero(srv);
      writeServos();
      break;
    case 0x71:
      stop(srv);
      writeServos();
      break;
    case 0x72:
      obiekt(8);
      break;
    case 0x73:
      obiekt(9);
      break;
  }
  command = '\0';
}
