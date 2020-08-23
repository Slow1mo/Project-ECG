#include "filter.h"

// Initialisation of holding arrays
int lx[12] = { 0 };											// Array to hold old x-values
int ly[3] = { 0 };											// Array to hold old y-values

int lowPassFilter(int x)									// x-in
{
	
	int y;													// 
	int d = 32;												// Denominator value for equation

	y = (2 * ly[1] - ly[2] + ((x - 2 * lx[5] + lx[11]) / d));
	// Replace ly[0] with y
	ly[0] = y;

	// Shift array ly, 1 to the right
	for (int i = 2; i >= 0 ; i--) {
		ly[i + 1] = ly[i];
	}
	
	// Shift array lx, 1 to the right and replace lx[0] with x
	for (int i = 11; i >= 0; i--) {
		lx[i + 1] = lx[i];
	}
	lx[0] = x;

	return y;
}

int hx[32] = { 0 };
int hy[2] = { 0 };

void highPassFilter(int x)
{

	int y;
	int d = 32;

	y = hy[1] - (x / d) + hx[15] - hx[16] + (hx[31] / d);
	hy[0] = y;

	for (int i = 1; i >= 0; i--) {
		hy[i + 1] = hy[i];
	}

	for (int i = 31; i >= 0; i--) {
		hx[i + 1] = hx[i];
	}
	hx[0] = x;

	return y;
}

int dx[4] = { 0 };

void derivativeFilter(int x)
{

	int y;

	y = ((2 * x) + dx[0] - dx[2] - (2 * dx[3]))/8;

	for (int i = 4; i >= 0; i--) {
		dx[i + 1] = dx[i];
	}
	dx[0] = x;

	return y;

}

void squaringFilter(int x)
{

	int y;

	y = x*x;
	return y;
}

mwiX[30] = { 0 };

void movingWindowIntegrationFilter(int x)
{
	int y;
	int N = 30;
	int X = 0;

	mwiX[0] = x;
	for (int i = 0; i < N; i++) {
		X += mwiX[i];
	}
	// Code optimitation needed here for better efficiency
	for (int i = 30; i >= 0; i--) {
		mwiX[i + 1] = mwiX[i];
	}

	y = X / N;
	return y;
}
