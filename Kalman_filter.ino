#include <SoftwareSerial.h>

// Kalman Filter application (Barun Basnet)
// Initialization of Kalman Variables
float R = 40.0, Q = 1e-1;  //Q = process noise covariance, R = measurement noise covariance
double Xpe0 = 0.0;  // Xpe0 = prior estimation of signal X at time t=0 (current state)
double Xe1 = 0.0;  //Xe1 = estimation of X at time t=1 (previous state)
double Ppe0 = 0.0;  //Ppe0 = prior estimation of "error covariance" at t=0,  
double P1 = 1, P0 = 0; //P1 = error covariance at t=1, P0 = error covariance at t=0
double  K = 0.0, Xe0 = 0.0, Z = 0.0; //K = Kalman gain, Xe0 = estimation of signal at t=0, Z = measured signal at t=0

void setup() {
  Serial.begin(9600);
}

void loop() {
 
  Z = analogRead(A0);
  Serial.print(Z, 4);Serial.print("\t");

 Xpe0 = Xe1; //Assumption or prediction 1
 Ppe0 = P1 + Q; //Assumption or prediction 2
 K = Ppe0/(Ppe0 + R); // Measurement update or correction of "Kalman gain"
 Xe0 = Xpe0 + K * (Z - Xpe0); // Measurement update or correction of "estimated signal"
 P0 = (1 - K) * Ppe0; // Measurement update or correction of "error covariance"
 Serial.println(Xe0, 4);
 Xe1 = Xe0; //Update: current t=0 becomes t=1 in the next step
 P1 = P0; //Update: current t=0 becomes t=1 in the next step
 delay(50);
}
