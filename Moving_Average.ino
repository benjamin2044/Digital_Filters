//Moving Average

int readings[15];      // the readings from the analog input
int index = 0;         // the index of the current reading
int total = 0;        // the running total
int average = 0;      // the average

void setup() {
  Serial.begin(9600);
  // initialize all the elements of the array "readings[15]"
  for (int i = 0; i < 15; i++) { 
    readings[i] = 0; }
}

void loop() {
  total = total - readings[index]; // subtract the last reading:
  readings[index] = analogRead(0); // read from the sensor:
  total = total + readings[index];  // add the reading to the total:
  index++; // advance to the next position in the array:
  
  // if we're at the end of the array...
  if (index >= 15) { index = 0;  }

  average = total / 15;  // calculate the average:
  
  Serial.print(readings[index]); Serial.print("\t");
  Serial.println(average);
  delay(50); 
}
