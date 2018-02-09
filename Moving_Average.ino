#include <SoftwareSerial.h>

//Moving Average
double readings[15];      // the readings from the analog input
int index = 0;         // the index of the current reading
double total = 0;        // the running total
double average = 0;      // the average

void setup() {
  Serial.begin(19200);
  // initialize all the elements of the array "readings[15]"
  for (int i = 0; i < 15; i++) { 
    readings[i] = 0; }
}

void loop() {
  total = total - readings[index];  // subtract the last reading:
  int sen_val = analogRead(0); //Read from the sensor
  readings[index] =  sen_val * 5.0/1023.0;
  total = total + readings[index]; // add the reading to the total:
  index++; // advance to the next position in the array:

  if (index >= 15) { index = 0;  }  // if we're at the end of the array...

  average = total / 15.0;  // calculate the average:
  
  Serial.print(readings[index] * 10, 4); Serial.print("\t");
  Serial.println(average * 10, 4);
  delay(50);    
}
