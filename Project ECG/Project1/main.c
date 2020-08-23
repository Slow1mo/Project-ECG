#define _CRT_SECURE_NO_DEPRECATE
#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{	
	int readData = 0;
	int lowPassData = 0;
	int highPassData = 0;
	int derivativeData = 0;
	int squaringData = 0;
	int mwiData = 0;

	//clock_t start, end;											// Clock timer for performance test
	//double cpu_time_used;

	int k = 0;

    //QRS_params qsr_params;										// Instance of the made avaiable through: #include "qsr.h"
	QRS_params qsr_params = {
		// Estimated Values
		.THRESHOLD1 = 3500.0,										// Start initaliseringsværdi af threshold1 ud fra mwi plottet i excel (Kval gæt)
		.NPKF = 50.0,												// Estimated value for low noise
		.SPKF = 5147.0,												// Estimated value for SPKF through first 10 R-peak average

		// Herfra beregnes værdierne i algoritmen og de initialiseres til 0
		.THRESHOLD2 = 0.0,											//
		.RR = { 0 },												//
		.RR_LOW = 0,												//
		.RR_MISS = 0,												//
		.RR_HIGH = 6000,											// High inital value for first boolean accept
		.Rpeak = 2000,												// Value for first boolean accept
		.RecentRR = { 0 },											//
		.RecentRR_OK = { 0 },										//
		.RR_Average1 = 0,											//
		.RR_Average2 = 0
	};

	FILE *file;														// Pointer to a file object
	file = openfile("ECG.txt");

	//FILE *fp;														// Pointer to test file output
	//fp = fopen("Test.txt", "w");

	//start = clock();

	while (readData != INT_MAX) {
		//if (k == 20) {											// For printing data in error detection
			//getchar();
			//k = 0;
		//}
		readData = getNextData(file);								// Read Data from Sensor
		lowPassData = lowPassFilter(readData);						// LowPass filter Data
		highPassData = highPassFilter(lowPassData);					// HighPass filter Data
		derivativeData = derivativeFilter(highPassData);			// Derivative Data
		squaringData = squaringFilter(derivativeData);				// Squaring Data
		mwiData = movingWindowIntegrationFilter(squaringData);		// Moving Window Integration filter Data

		peakDetection(&qsr_params,mwiData);							// Perform Peak Detection

		//fprintf(fp,"%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", mwiData, qsr_params.THRESHOLD1, qsr_params.THRESHOLD2, qsr_params.RR_LOW, qsr_params.RR[1], qsr_params.RR_HIGH, qsr_params.RR_MISS, qsr_params.SPKF, qsr_params.NPKF);
		
		k++;
	}

	//end = clock();
	//cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // cpu time
	//printf("time used: %f\n", cpu_time_used);

	//fclose(fp);

	return 0;
}
