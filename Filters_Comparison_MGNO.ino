#include<SoftwareSerial.h>
#include<MegunoLink.h>

TimePlot MyPlot; 

//Exponential Filter
double S_t = 0, X_t = 0, S_t1 = 0;
const double alp = 0.05; 

//Moving Average
double readings[15], total = 0, average = 0;       
int index = 0; 

// Kalman Filter 
double R = 40.0, Q = 1e-1;
double Xpe0 = 0.0, Xe1 = 0.0, Xe0 = 0.0;
double P1 = 1, Ppe0 = 0, P0 = 0;
double  K = 0.0, Z = 0.0; 

void setup() {
  Serial.begin(9600); 
  MyPlot.SetTitle("Comparison of 3 Filters");
}

void loop() {
  //Exponential Filter
  X_t = analogRead(0);
  MyPlot.SendData("RawData", X_t);
  Serial.print(X_t); Serial.print("\t");
  S_t = alp * X_t + (1 - alp) * S_t1; 
  MyPlot.SendData("Exponential", S_t);
  Serial.print(S_t, 4);  Serial.print("\t");
  S_t1 = S_t;

  //Moving Average
  total = total - readings[index];
  readings[index] = analogRead(0);
  total = total + readings[index]; index++;
  if (index >= 15) { index = 0;  }
  average = total / 15; 
  MyPlot.SendData("Moving_Avg", average);
  Serial.print(average, 4);  Serial.print("\t");   

  // Kalman Filter
 Z = analogRead(0);
 Xpe0 = Xe1;  Ppe0 = P1 + Q; 
 K = Ppe0/(Ppe0 + R);    Xe0 = Xpe0 + K * (Z - Xpe0);    P0 = (1 - K) * Ppe0; 
 MyPlot.SendData("Kalman", Xe0);
 Serial.println(Xe0, 4);
 Xe1 = Xe0;  P1 = P0; 
 delay(50);
}
