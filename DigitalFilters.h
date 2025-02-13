/*
 * DigitalFilters.h
 *
 *  Created on: Feb 4, 2025
 *      Author: BARUN
 */

#ifndef DIGITALFILTERS_H_
#define DIGITALFILTERS_H_

/*-----Exponential Filter-----*/
typedef struct{
	float filterOutput;
	float Previous_Output;
	float smoothingFactor;
} ExponentialFilter;
void ExponentialFilter_Init(ExponentialFilter *ef, float initial_estimate, float inputSmoothingFactor);
float ExponentialFilter_Update(ExponentialFilter *ef, float measurement);

/*-----Biquad Filter-----*/
typedef struct {
	float Input_z1, Input_z2; //previous inputs
	float Output_z1, Output_z2; //previous outputs
	float filter_output;
}BiquadFilter;

void BiquadIIRfilter_Init(BiquadFilter *bf, float initial_estimate);
float BiquadIIRfilter_Update(BiquadFilter *bf, float measurement);

/*-----Kalman Filter-----*/
typedef struct {
    float process_variance;
    float measurement_variance;
    float estimate;
    float error_estimate;
} KalmanFilter;

void KalmanFilter_Init(KalmanFilter* kf, float process_variance, float measurement_variance, float initial_estimate, float initial_error_estimate);
float KalmanFilter_Update(KalmanFilter* kf, float measurement);

#endif /* DIGITALFILTERS_H_ */
