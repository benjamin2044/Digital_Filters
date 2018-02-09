//Exponential Filter

//S_t = a * X_t + (1 - a) * S_t1
//where, S_t = output, a = smoothing factor, X_t = measured data, S_t1 = previous output
//Values of α closer to zero have a greater smoothing effect and 
//are less responsive to recent changes and vice-versa

#include<SoftwareSerial.h>

double S_t = 0, X_t = 0, S_t1 = 0;
const double a = 0.1; 

void setup() {
  Serial.begin(19200);
}

void loop() {
  int sen_val = analogRead(0);
  X_t = sen_val * 5.0/1023.0;
  S_t = a * X_t + (1 - a) * S_t1; 
  Serial.print(X_t * 10, 4); Serial.print("\t");
  Serial.println(S_t * 10, 4);
  delay(50);
  S_t1 = S_t; //update
}
