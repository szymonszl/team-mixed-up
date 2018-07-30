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

#include <IRremote.h>

IRrecv irrecv(RECV_PIN);

decode_results results;

#define MOVE_FORWARD 0x20DF02FD
#define MOVE_BACK 0x2df827d
#define MOVE_LEFT 0x20dfe01f
#define MOVE_RIGHT 0x20df609f
#define WHITE 0x20df22dd
#define RED 0x20df8877
#define GREEN 0x20df48b7
#define BLUE 0x20dfc837

unsigned long endtime = millis();
uint8_t timercount = 0;

ISR(TIMER0_COMPA_vect) { //change the 0 to 1 for timer1 and 2 for timer2
  if (timercount == 1) {
    timercount = 0;
    if (millis() > endtime) {
      l.write(lstop);
      r.write(rstop);
    }
  }
  timercount++;
}

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
  irrecv.enableIRIn();
  irrecv.resume();
  Serial.println("setup ended");

  cli();
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR0A = 255;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM21);
  // 1024 prescaler
  TCCR0B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei();
  Serial.println("podłączyłem interrupta :rr:");
}
int nm = 0; //nextmove
void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case MOVE_FORWARD:
        nm = 1; break;
      case MOVE_BACK:
        nm = 2; break;
      case MOVE_LEFT:
        nm = 3; break;
      case MOVE_RIGHT:
        nm = 4; break;
      case RED:
        nm = 5; break;
      case GREEN:
        nm = 6; break;
      case BLUE:
        nm = 7; break;
      case WHITE:
        nm = 8; break;
      default:
        nm = 0; break;
    }
    if (nm != 0) {
      Serial.println(nm, DEC);
      switch (nm) {
        case 1:
          l.write(lstop - step);
          r.write(rstop + step);
          endtime = millis() + MOVELEN;
          break;
        case 2:
          l.write(lstop + bstep);
          r.write(rstop - bstep);
          endtime = millis() + MOVELEN;
          break;
        case 3:
          l.write(lstop + bstep);
          r.write(rstop + step);
          endtime = millis() + MOVELEN;
          break;
        case 4:
          l.write(lstop - step);
          r.write(rstop - bstep);
          endtime = millis() + MOVELEN;
          break;

        case 5:
          digitalWrite(R, LOW);
          digitalWrite(G, HIGH);
          digitalWrite(B, HIGH);
          break;
        case 6:
          digitalWrite(R, HIGH);
          digitalWrite(G, LOW);
          digitalWrite(B, HIGH);
          break;
        case 7:
          digitalWrite(R, HIGH);
          digitalWrite(G, HIGH);
          digitalWrite(B, LOW);
          break;
        case 8:
          digitalWrite(R, LOW);
          digitalWrite(G, LOW);
          digitalWrite(B, LOW);
          break;
      }
      Serial.write("\n");
      Serial.print(l.read(), DEC);
      Serial.write("\t");
      Serial.print(r.read(), DEC);
      nm = 0;
    }

    irrecv.resume();
  }


}
