#include <SoftwareSerial.h>

// Kalman Filter application (Barun Basnet)
// Initialization of Kalman Variables
float R = 40, Q = 1e-1;
double Xpe0 = 0.0, Xe1 = 0.0;
double Ppe0 = 0.0, Pp1 = 40, P0 = 0, K = 0.0;      
double Xe0 = 0.0, Z = 0.0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
 
  Z = analogRead(A0);
  Serial.print(Z, 4);Serial.print("\t");

 Xpe0 = Xe1; 
 Ppe0 = Pp1 + Q;
 K = Ppe0/(Ppe0 + R);
 Xe0 = Xpe0 + K * (Z - Xpe0);
 P0 = (1 - K) * Ppe0;
 Serial.println(Xe0, 4);
 Xe1 = Xe0;
 Pp1 = P0;
 delay(50);
}
