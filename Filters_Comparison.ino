#include<SoftwareSerial.h>

//Exponential Filter
double S_t = 0, X_t = 0, S_t1 = 0;
const double alp = 0.1; 

//Moving Average
double readings[15], total = 0, average = 0;       
int index = 0; 

// Kalman Filter 
double R = 6e-3, Q = 1e-4;
double Xpe0 = 0.0, Xe1 = 0.0, Xe0 = 0.0;
double P1 = 1.0, Ppe0 = 0.0, P0 = 0;
double  K = 0.0, Z = 0.0; 

void setup() {
  Serial.begin(19200);
}

void loop() {
  int sen_val = analogRead(0);
  //Exponential Filter
  X_t = sen_val * 5.0/1023.0;
  Serial.print(X_t * 10, 4); Serial.print("\t");
  S_t = alp * X_t + (1 - alp) * S_t1; 
  Serial.print(S_t * 10, 4);  Serial.print("\t");
  S_t1 = S_t;

  //Moving Average
  total = total - readings[index];
  readings[index] = sen_val * 5.0/1023.0;
  total = total + readings[index]; index++;
  if (index >= 15) { index = 0;  }
  average = total / 15.0; 
  Serial.print(average * 10, 4);  Serial.print("\t");   

  // Kalman Filter
 Z = sen_val * 5.0/1023.0;
 Xpe0 = Xe1;  Ppe0 = P1 + Q; 
 K = Ppe0/(Ppe0 + R);    Xe0 = Xpe0 + K * (Z - Xpe0);    P0 = (1 - K) * Ppe0; 
 Serial.println(Xe0 * 10, 4);
 Xe1 = Xe0;  P1 = P0; 

 delay(50);
}
