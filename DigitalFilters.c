/*
 * DigitalFilters.c
 *
 *  Created on: Feb 4, 2025
 *      Author: BARUN
 */

#include"DigitalFilters.h"
#include"math.h"

/*-----Exponential Filter-----*/
void ExponentialFilter_Init(ExponentialFilter *ef, float initial_estimate, float inputSmoothingFactor){
	 ef->Previous_Output = initial_estimate;
	 ef->smoothingFactor = inputSmoothingFactor;
 }

 float ExponentialFilter_Update(ExponentialFilter *ef, float measurement){
	ef->filterOutput = ef->smoothingFactor * measurement + (1 - ef->smoothingFactor)*ef->Previous_Output;
	ef->Previous_Output = ef->filterOutput;
	return ef->filterOutput;
 }

 /*-----Biquad Filter-----*/
static float aCoff[3] = {0.014401418980573148, 0.028802837961146296, 0.014401418980573148};
static float bCoff[2] =  {-1.6329907391512004, 0.690596415073493};

 void BiquadIIRfilter_Init(BiquadFilter *bf, float initial_estimate){
	 bf->Input_z1 = initial_estimate;
	 bf->Input_z2 = initial_estimate;
	 bf->Output_z1 = initial_estimate;
	 bf->Output_z2 = initial_estimate;
 }

 float BiquadIIRfilter_Update(BiquadFilter *bf, float measurement){
	 bf->filter_output = (aCoff[0]*measurement + aCoff[1]*bf->Input_z1 + aCoff[2]*bf->Input_z2)
			                - (bCoff[0]*bf->Output_z1 + bCoff[1]*bf->Output_z2);
	 bf->Input_z2 = bf->Input_z1;
	 bf->Input_z1 = measurement;
	 bf->Output_z2 = bf->Output_z1;
	 bf->Output_z1 = bf->filter_output;
	 return bf->filter_output;
 }


 /*-----Kalman Filter-----*/
// process_variance=0.01, measurement_variance=1.2
 void KalmanFilter_Init(KalmanFilter* kf, float process_variance, float measurement_variance, float initial_estimate, float initial_error_estimate) {
     kf->process_variance = process_variance;
     kf->measurement_variance = measurement_variance;
     kf->estimate = initial_estimate;
     kf->error_estimate = initial_error_estimate;
 }

 float KalmanFilter_Update(KalmanFilter* kf, float measurement) {
     float kalman_gain = kf->error_estimate / (kf->error_estimate + kf->measurement_variance);
     kf->estimate = kf->estimate + kalman_gain * (measurement - kf->estimate);
     kf->error_estimate = (1 - kalman_gain) * kf->error_estimate + fabs(kf->estimate - measurement) * kf->process_variance;
     return kf->estimate;
 }

