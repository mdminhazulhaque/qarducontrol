/*
  QArduControl - Burn once and control your Arduino board via USB/Serial
  by Muhammad Minhazul Haque <contact@minhazulhaque.com>, Thursday 27 Feb 2014
  http://minhazulhaque.com
  
  rev 1.0
 */

void setup() {                
  Serial.begin(9600);
}

void loop() {
  // Parse serial input
  // d 12 255 will write 255 to pin 12
  // a 3 128 will write 128 to pwm pin 3
  if(Serial.available())
  {
    char c = Serial.read();
    if(c=='r')
    {
      // software reset
      asm volatile ("jmp 0");
    }
    else if(c=='d')
    {
      int pin = Serial.parseInt();
      // Qt checkbox returns 2 for enabled state
      if(Serial.parseInt()==2)
        digitalWrite(pin, HIGH);
      else
        digitalWrite(pin, LOW);
      //      DEBUG
      //      Serial.print("digital ");
      //      Serial.print(pin);
      //      Serial.print(" ");
      //      Serial.println(value);
    }
    else if(c=='a')
    {
      int pin = Serial.parseInt();
      int value = Serial.parseInt();
      analogWrite(pin, value);
      //      DEBUG
      //      Serial.print("analog ");
      //      Serial.print(pin);
      //      Serial.print(" ");
      //      Serial.println(value);
    }
  }
  // print uptime
  Serial.print(millis());
  Serial.print(" ");
  // print analog pins' values
  for(int i=0;i<5;i++)
  {
    Serial.print(analogRead(i));
    Serial.print(" ");
  }
  Serial.println(analogRead(5));
  delay(500);
}







