#include <Servo.h>
Servo l;
Servo r;

#define lstop 80
#define rstop 100
#define step 20
#define bstep 40
#define MOVELEN 50

#define SRV_L 2
#define SRV_R 3
#define RECV_PIN 6

#define R 9
#define G 10
#define B 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("serial connected");
  l.attach(SRV_L);
  r.attach(SRV_R);
  l.write(lstop);
  r.write(rstop);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  Serial.println("setup ended");
}
//finetune this v
#define czasobrotu 4000
#define loopwait 30000
void loop() {
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);

  // put your main code here, to run repeatedly:
  l.write(lstop - step);
  r.write(rstop + step); //przod
  delay(3000);

  l.write(lstop); //stop
  r.write(rstop);
  delay(500);

  l.write(lstop + bstep); //lewo
  r.write(rstop + step);
  delay(czasobrotu);

  l.write(lstop); //stop
  r.write(rstop);
  delay(500);



  l.write(lstop - step);
  r.write(rstop + step); //przod
  delay(3000);

  l.write(lstop); //stop
  r.write(rstop);
  delay(500);

  l.write(lstop + bstep); //lewo
  r.write(rstop + step);
  delay(czasobrotu);

  l.write(lstop); //stop
  r.write(rstop);
  delay(500);



  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  delay(1000);

  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
  delay(1000);

  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
  delay(1000);

  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);


  delay(loopwait);
}
