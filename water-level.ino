/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D6, INPUT);// Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  int val;
  val = digitalRead(D6);
  if (val == 0) {
    digitalWrite(D0, HIGH);
  }
  else {
    digitalWrite(D0, LOW);
  }
  Serial.println(val);
  delay(2000);
}
