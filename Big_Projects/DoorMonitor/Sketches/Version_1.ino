
#include <SoftwareSerial.h>
#define SWITCH 13U
SoftwareSerial mySerial(10,11); // Rx, Tx
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH, INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Door Alarm Sketch");
}

void loop() {
  // Read Button State (HIGH == 1 & LOW == 0)
  int state = digitalRead(SWITCH);
  
  // Tell HC05 to alert the alarm on tablet if switch is triggered.
  if (state == LOW && flag == false) {
    mySerial.println("Open");
    Serial.println("Sent command \"Open\" to HC05");
    flag = !flag;
  }
  if (state == HIGH && flag == true) {
    mySerial.println("Close");
    Serial.println("Sent command \"Close\" to HC05");
    flag = !flag;
  }
  delay(2500); //2.5 second delay for swinging door
}


void test_loop_1() {
  // put your main code here, to run repeatedly:
  // Read Button State (HIGH == 1 & LOW == 0)
  int state = digitalRead(SWITCH);
  Serial.println("Entry Loop");
  Serial.println(state);
  Serial.println(flag);
  // Tell HC05 to alert the alarm on tablet if switch is triggered.
  if (state == LOW && flag == false) {
    Serial.println("Switch has been triggered");
    flag = !flag;
  }
  if (state == HIGH && flag == true) {
    Serial.println("Switch has been reset");
    flag = !flag;
  }
  delay(2500); //2.5 second delay for swinging door
}
