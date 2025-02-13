
#include"DigitalFilters.h"

ExponentialFilter expFilter;
BiquadFilter biquadFilter;
KalmanFilter kalmanFilter;

float initialEstimate_ef = 10, smoothingFactor = 0.5; //ExponentialFilter initial values
float initialEstimate_bf = 20; //BiquadFilter initial values
float process_variance = 0.01, measurement_variance=1.2, initialEstimate_kf = 0, initial_error_estimate = 0;

int sensorPin = A0; 

void setup() {
  ExponentialFilter_Init(&expFilter, initialEstimate_ef, smoothingFactor);
  BiquadIIRfilter_Init(&biquadFilter, initialEstimate_bf);
  KalmanFilter_Init(&kalmanFilter, process_variance, measurement_variance, initialEstimate_kf, initial_error_estimate);

  Serial.begin(9600);
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  Serial.println(ExponentialFilter_Update(&expFilter, sensorValue));
  Serial.println(BiquadIIRfilter_Update(&biquadFilter, sensorValue));
  Serial.println(KalmanFilter_Update(&kalmanFilter, sensorValue));
  delay(1000);
}
