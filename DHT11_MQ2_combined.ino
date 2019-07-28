#include <SimpleDHT.h>
int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// threshold value
int sensorThres = 400;
int pinDHT11 = 7;
SimpleDHT11 dht11(pinDHT11);

    void setup() {
      pinMode(redLed, OUTPUT);
      pinMode(greenLed, OUTPUT);
      pinMode(buzzer, OUTPUT);
      pinMode(smokeA0, INPUT);
      Serial.begin(9600);
      Serial.println("Starting");
    }


void loop1(){
   int analogSensor = analogRead(smokeA0);

  Serial.print("Concentration: ppm ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);
}


void loop2(){
  delay (250);
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
}


void loop() {
  loop1();
  loop2();
}  
