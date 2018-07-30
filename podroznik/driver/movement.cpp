#include "movement.h"
/* Mateusz:
 * 
 * jeszcze raz
 * faza 1: strona nr 1 podnosi się w górę
 * faza 2: strona 2 cofa się, około 20 stopni
 * w tym samym czasie
 * równo
 * strona 1 schodzi
 * żeby w momencie
 * 'maksymalnym' strony 2
 * strona 1 stała juz na dole
 * potem
 * faza 3:
 * strona 2 do góry
 * faza 2 do pozycji wyjściowej
 * strona*
 * w sensie
 * zero w poziomie
 * ale w pionie powietrze
 * robot opiera się na stronie 1 aktualnie 
 * 
 */

#define DWN -10
#define UPP 30
#define BCK 20
#define FRONT -20
// DOWN UP i BACK były zajęte :)))))



#ifndef _MVMNT_
#define _MVMNT_
void p1(int s[12]) {
  s[1] = UPP;
  s[3] = -20;
  s[5] = UPP;
  s[7] = DWN;
  s[9] = UPP;
  s[11] = DWN;
}
void p2(int s[12]) {
  s[0] = FRONT;
  s[2] = BCK;
  s[4] = FRONT;
  s[6] = BCK;
  s[8] = FRONT;
  s[10] = BCK;
}
void p3(int s[12]) {
  alldown(s);
}
void p4(int s[12]) {
  s[1] = DWN;
  s[3] = UPP;
  s[5] = DWN;
  s[7] = UPP;
  s[9] = DWN;
  s[11] = UPP;
}
void p5(int s[12]) {
  s[0] = BCK;
  s[2] = FRONT;
  s[4] = BCK;
  s[6] = FRONT;
  s[8] = BCK;
  s[10] = FRONT;
}
void p6(int s[12]) {
  alldown(s);
}

void r1(int s[12]) {
  s[7] = UPP;
  s[11] = UPP;
  s[3] = UPP;
}
void r2(int s[12]) {
  s[0] = BCK;
  s[2] = FRONT;
  s[4] = BCK;
  s[6] = BCK;
  s[8] = FRONT;
  s[10] = BCK;
}
void r3(int s[12]) {
  alldown(s);
}
void r4(int s[12]) {
  s[5] = UPP;
  s[1] = UPP;
  s[9] = UPP;
}
void r5(int s[12]) {
  s[0] = FRONT;
  s[2] = BCK;
  s[4] = FRONT;
  s[6] = FRONT;
  s[8] = BCK;
  s[10] = FRONT;
}
void r6(int s[12]) {
  alldown(s);
}

void l1(int s[12]) {
  s[7] = UPP;
  s[11] = UPP;
  s[3] = UPP;
}
void l2(int s[12]) {
  s[0] = FRONT;
  s[2] = BCK;
  s[4] = FRONT;
  s[6] = FRONT;
  s[8] = BCK;
  s[10] = FRONT;
}
void l3(int s[12]) {
  alldown(s);
}
void l4(int s[12]) {
  s[5] = UPP;
  s[1] = UPP;
  s[9] = UPP;
}
void l5(int s[12]) {
  s[0] = BCK;
  s[2] = FRONT;
  s[4] = BCK;
  s[6] = BCK;
  s[8] = FRONT;
  s[10] = BCK;
}
void l6(int s[12]) {
  alldown(s);
}


void b1(int s[12]) {
  s[1] = UPP;
  s[3] = DWN;
  s[5] = UPP;
  s[7] = DWN;
  s[9] = UPP;
  s[11] = DWN;
}
void b2(int s[12]) {
  s[0] = BCK;
  s[2] = FRONT;
  s[4] = BCK;
  s[6] = FRONT;
  s[8] = BCK;
  s[10] = FRONT;
}
void b3(int s[12]) {
  alldown(s);
}
void b4(int s[12]) {
  s[1] = DWN;
  s[3] = UPP;
  s[5] = DWN;
  s[7] = UPP;
  s[9] = DWN;
  s[11] = UPP;
}
void b5(int s[12]) {
  s[0] = FRONT;
  s[2] = BCK;
  s[4] = FRONT;
  s[6] = BCK;
  s[8] = FRONT;
  s[10] = BCK;
}
void b6(int s[12]) {
  alldown(s);
}

void alldown(int s[12]) {
  s[1] = DWN;
  s[3] = DWN;
  s[5] = DWN;
  s[7] = DWN;
  s[9] = DWN;
  s[11] = DWN;
}
void stop(int s[12]) {
  for (int i=0; i<11; i+=2) {
    s[i] = 0;
    s[i+1] = 40;
  }
}
void zero(int s[12]) {
  s[0] = 0;
  s[1] = 0;
  s[2] = 0;
  s[3] = 0;
  s[4] = 0;
  s[5] = 0;
  s[6] = 0;
  s[7] = 0;
  s[8] = 0;
  s[9] = 0;
  s[10] = 0;
  s[11] = 0;
}
#endif
