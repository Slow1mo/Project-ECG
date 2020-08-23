#ifndef QSR_H
#define QSR_H

// Header file for QRS functionality 
// it is recommended to use the structure "QRS_parameters"
// to organize all variables and parameters

typedef struct QRS_params
{ // Structure for QRS parameters
   double SPKF;
   double NPKF; 
   double THRESHOLD1;
   double THRESHOLD2;
   double RR[8];
   double RR_LOW;
   double RR_MISS;
   double RR_HIGH;
   double Rpeak;
   double RecentRR[8];
   double RecentRR_OK[8];
   double RR_Average1;
   double RR_Average2;
   // Add parameters that are missing
   // or of use to you
   
} QRS_params;

// Feel free to change and add methods
void peakDetection(QRS_params *params,int x);

#endif // QSR_H

