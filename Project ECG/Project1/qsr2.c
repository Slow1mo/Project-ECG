#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

// Own variables
int PEAKS[100] = { 0 };											// Et antal ud fra hvor mange R peaks man kan misse, uden hjertestop (min puls) - givet i opgaven (ganget med 20)
int timeCount = 1;												// Antallet af samples
int SCAN[3] = { 0 };											// Til sammenligning af værdier for peaks
int countDiv = 0;
double Temp = 0;

void peakDetection(QRS_params *params, int x)
{

	SCAN[0] = x;
	timeCount += 1;

	// Find and save peaks then shift SCAN for next value
	if (SCAN[1] >= SCAN[0] && SCAN[1] >= SCAN[2]) {
		PEAKS[0] = SCAN[1];
	}
	for (int i = 1; i >= 0; i--) {
		SCAN[i + 1] = SCAN[i];
	}
	printf(" %7d, %7d, %7.2f, > %7.2f, %7d, %7.2f, < %7.2f, < %7.2f %7.2f, %7.2f\n", SCAN[1], PEAKS[0], params->THRESHOLD1, params->THRESHOLD2, timeCount, params->RR_LOW, params->RR[1], params->RR_HIGH, params->SPKF, params->NPKF);

	// Compare peak to thres1
	if (PEAKS[0] <= params->THRESHOLD1) {
		params->NPKF = 0.125 * PEAKS[0] + 0.875 * params->NPKF;
		params->THRESHOLD1 = params->NPKF + 0.25 *
			
			
			(params->SPKF - params->NPKF);
		params->THRESHOLD2 = 0.5 * params->THRESHOLD1;

		for (int i = 99; i >= 0; i--) {
			PEAKS[i + 1] = PEAKS[i];
		}
		PEAKS[0] = 0;
	}

	else if (PEAKS[0] > params->THRESHOLD1 && PEAKS[0] != 0) {
		// Calculate RR

		params->RR[0] = (timeCount - 1);
		timeCount = 1;

		// Shifting arrays for new values
		for (int i = 6; i >= 0; i--) {
			params->RR[i + 1] = params->RR[i];
		}
		params->RR[0] = 0;
		for (int i = 99; i >= 0; i--) {
			PEAKS[i + 1] = PEAKS[i];
		}
		PEAKS[0] = 0;

		// Compare RR_HIGH > RR[0] > RR_LOW
		if (params->RR[1] > params->RR_LOW && params->RR[1] < params->RR_HIGH) {
			params->Rpeak = PEAKS[1];
			printf("gnkjsdlkgjsdklgj fukgjhxfkjgnjgflghbfvgnd.rg hddzfghzdkjgdkg ghdrkg hdfkjgh d");
			printf("PEAK %i; THRES; %f", PEAKS[0], params->THRESHOLD1);
			printf("\n RPEAK; %f, PEAKS[1]; %i\n", params->Rpeak, PEAKS[1]);
			if (countDiv < 9) {
				countDiv += 1;
			}

			if (params->Rpeak < 2000) {
				printf("\n WARNING1! WARNIG1! WARNING1! WARNING1! WARNING1! Rpeak is: %.2f\n", params->Rpeak);
			}
			params->SPKF = 0.125*PEAKS[1] + 0.875 * params->SPKF;
			params->RecentRR_OK[0] = params->RR[1];
			params->RecentRR[0] = params->RR[1];
			// Average 1 Effektivisering ved hjælp af last method fra filters
			for (int i = 0; i < 8; i++) {
				Temp += params->RecentRR[i];
			}
			params->RR_Average1 = Temp / countDiv;
			Temp = 0;
			// Average 2
			for (int i = 0; i < 8; i++) {
				Temp += params->RecentRR_OK[i];
			}
			params->RR_Average2 = Temp / countDiv;
			Temp = 0;

			params->RR_HIGH = 1.16*params->RR_Average2;
			params->RR_LOW = 0.92*params->RR_Average2;
			params->RR_MISS = 1.66*params->RR_Average2;

			params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF - params->NPKF);
			params->THRESHOLD2 = 0.5*params->THRESHOLD1;

			// Shift
			for (int i = 6; i >= 0; i--) {
				params->RecentRR_OK[i + 1] = params->RecentRR_OK[i];
			}
			params->RecentRR_OK[0] = 0;

			for (int i = 6; i >= 0; i--) {
				params->RecentRR[i + 1] = params->RecentRR[i];
			}
			params->RecentRR[0] = 0;
		}
	}

	if (params->RR[1] > params->RR_MISS) {
		for (int i = 0; i < sizeof(PEAKS); i++) {
			if (PEAKS[i] > params->THRESHOLD2) {
				if (countDiv < 9) {
					countDiv += 1;
				}
				params->Rpeak = PEAKS[i];
				if (params->Rpeak < 2000) {
					printf("\n WARNING2! WARNING2! WARNING2! WARNING2! WARNING2! Rpeak is: %.2f\n", params->Rpeak);
				}
				params->SPKF = 0.25*PEAKS[i] + 0.75*params->SPKF;
				// Store RR in Recent_RR
				params->RecentRR[0] = params->RR[1];
				for (int i = 6; i >= 0; i--) {
					params->RecentRR[i + 1] = params->RecentRR[i];
				}
				params->RecentRR[0] = 0;

				for (int i = 0; i < 8; i++) {
					Temp += params->RecentRR[i];
				}
				params->RR_Average1 = Temp / countDiv;
				Temp = 0;

				params->RR_HIGH = 1.16*params->RR_Average1;
				params->RR_LOW = 0.92*params->RR_Average1;
				params->RR_MISS = 1.66*params->RR_Average1;

				params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF - params->NPKF);
				params->THRESHOLD2 = 0.5*params->THRESHOLD1;

				break;
			}
		}
	}
	
	return 0;
}




