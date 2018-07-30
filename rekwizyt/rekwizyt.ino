/*
 * Kod rekwizytu
 * kucowal tez szymus
 * (c) 2k18 szymus szlengus
 * 
 * ICogamJjIHRvIHJla3dpenl0IHRvIHRha2llIG1hbGUgIGt0b3JlIG11c2kgc2Nob3dhYyBwZXJ1
a2UKICogdGFrIGt1cndhIHBlcnVrZQogKiBjbyB0byB6YSBkZWJpbCB3eW15c2xhbAogKiBuaWdk
eSB0ZWdvIG5pZSBvZ2FybmlhbGVtCiAqIHBvbXlzbCBvcnlnaW5hbG55IG1hdGllZ28gYnlsIGxl
cHN6eQogKiBqYWtpcyByb2JvdCBjbyBtaWFsLi4KICogdzggY28gb24gbWlhbCByb2JpYz8KICog
d2hhdGV2ZXIKICogdG8gYnlsbyBsZXBzemUKICogYSBuaWUgdGUgc3VycmVhbG5lIGNvcwogKiBt
csOzd2tpCiAqIFRBSyBLVVJXQSBNUsOTV0tJCiAqIERBSkNJRSBNSSBOVU1FUiBETyBESUxFUkEg
VEXFuyBDSENFCiAqIEJPIEpBS0lFxZogUVVBTElUWSBMU0QgV1lDWlVXQU0KICogYWxlIG5hIHNl
cmlvIHR1IGplYmllIGxzZAogKiBuaWUgd2llbSBqYWsgcGFjaG5pZSBsc2QKICogYWxlIGN6dWpl
IHplIHR1IGplc3QgbHNkCiAqIHBvIHphY2hvd2FuaXUgemF6dWxhawogKiAiWkEgTUHFgU8gS1JF
QVRZV05FIEtVUldBIgogKiAiTk8gWkEgTUHFgU8gS1JFQVRZV05FIgogKiAiQ1pFTVUgVE8gTFVE
WklFIExVRFpJRSBOSUUgU08gS1JFQVRZV05JIgogKiAiSkVCTklKIFRVIFpXSUVSWkVOVEEiCiAq
ICJKQUsgVE8gSkFLSUUiCiAqICJPVFdPWiBKQUtPIEVOQ1lLTE9QRURJRSBOQSBMT1NPV0VKIFNU
Uk9OSUUiCiAqICJXWUxPU09XQUxFUyBURVJNSVRBIgogKiAiU1BPS08sIFRFUk1JVCBNQSBLT01Q
TEVLUyBaRSBOSUUgTFVCSSBQUkFDT1dBQyBUWUxLTyBTUElFV0FDIgogKiBubyBrdXJ3YQogKiB0
ZXJtaXQgc3BpZXdhIHhEREQKICogYWxlIGplc3pjemUgZ29yc3plIHPEhSB0ZSBqZWJhbmUgd3l6
d2FuaWEgbmEganXFvAogKiBkbGEgbmllem5hamFjYWp5Y2g6CiAqIHNhIGR3aWUga2F0ZWdvcmll
CiAqIGplZG5hIHRvICJTVEVNIgogKiBjenlsaSB0ZWNobmljem5lCiAqIHcgbWlhcmUgc3Bva28g
c2llCiAqIGFsZSBwaXNhbCBqZSBqZWJhbnkgbWFjZ3l2ZXIKICogZG9zdGFqZXN6IHRyenkgc8WC
b21raSwga2F3YcWCZWsgdGHFm215IDJ4M2NtIGkga2F3YcWCZWsgdGVrdHVyeQogKiB6YWRhbmll
OiB6csOzYiB3aWXFvMSZIDEwIGt1cndhIGtpbG9tZXRyw7N3CiAqIGkgcG9kc3Rhd2EgbWF4IDNj
bQogKiB0bGRyIG1hasSFIGZldHlzeiB3aWXFvAogKiBhbGUgYXJ0IHRvIG5hamdvcnN6ZSBza3Vy
d3lzecWEc3R3bwogKiBDRE4K

 */
#include <IRremote.h>

#define RECV_PIN 11
#define SIL_PIN 6
IRrecv irrecv(RECV_PIN);

decode_results results;
void setup() {
  irrecv.enableIRIn();
  pinMode(SIL_PIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.write(results.value);
    if(results.value==0x20DF40BF) {
      digitalWrite(SIL_PIN, HIGH);
      Serial.write("\r\n\r\nHIGH\r\n\r\n");
    } else if (results.value==0x20DFC03F) {
      digitalWrite(SIL_PIN, LOW);
      Serial.write("\r\n\r\nLOW\r\n\r\n");
    }
    delay(50);
    irrecv.resume(); // Receive the next value
  }
}

