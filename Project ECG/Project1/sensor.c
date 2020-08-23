#define _CRT_SECURE_NO_DEPRECATE
#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

int getNextData(FILE *file)
{
	int val;
	if (fscanf(file, "%i", &val) != EOF) {
		return val;											// return sensor value
		}
	return INT_MAX;											// return maximum integer value if end of file is reached
}

FILE* openfile(const char* filename)
{
   FILE *file = fopen("ECG.txt", "r");						// Replace NULL with the actual file object

   return file;
}