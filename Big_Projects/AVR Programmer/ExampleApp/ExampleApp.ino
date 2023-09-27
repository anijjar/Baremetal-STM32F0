void setup() {
  // put your setup code here, to run once:
  DDRB |= 10; 
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= 0x10; // Turn LED ON
}
