#include "histogram.h"
#include <stdio.h>

#define HISTOGRAM_LENGTH 32

int main()
{
    uint32_t histogramCount[HISTOGRAM_LENGTH] = {0};
    uint8_t histogramPercent[HISTOGRAM_LENGTH] = {0};
    uint32_t histogramLimits[HISTOGRAM_LENGTH];
    histogramLimits[0] = 1; /* 0-1s */
    histogramLimits[1] = 2; /* 1-2s */
    histogramLimits[2] = 3; /* ... */
    histogramLimits[3] = 4;
    histogramLimits[4] = 5;
    histogramLimits[5] = 6;
    histogramLimits[6] = 7;
    histogramLimits[7] = 8;
    histogramLimits[8] = 9;
    histogramLimits[9] = 10;

    /* Limits for upto a minute */
    histogramLimits[10] = 12; /* 10-12s */
    histogramLimits[11] = 15; /* 12-15s */
    histogramLimits[12] = 20; /* 15-20s */
    histogramLimits[13] = 30; /* > 20-30s */
    histogramLimits[14] = 45; /* 30-45s */
    histogramLimits[15] = 60; /* 45s-1min */

    /*Limits upto 8+hr */
    histogramLimits[16] = 90;   /* 1min - 1:30 min */
    histogramLimits[17] = 120;  /* 1:30 -2 min */
    histogramLimits[18] = 180;  /* 2-3 min */
    histogramLimits[19] = 300;  /* 3-5 min */
    histogramLimits[20] = 420;  /* 5-7 min */
    histogramLimits[21] = 600;  /* 7-10 Minutes */
    histogramLimits[22] = 900;  /* 10 - 15 Minutes */
    histogramLimits[23] = 1800; /* 15-30 Minutes */
    histogramLimits[24] = 2700; /* 30-45 min */
    histogramLimits[25] = 3600; /* 45min -1 Hour */

    histogramLimits[26] = 7200;  /* 1-2 Hours */
    histogramLimits[27] = 10800; /* 2-3 Hours */
    histogramLimits[28] = 14400; /* 3-4 Hrs */
    histogramLimits[29] = 21600; /* 4-6 Hour */
    histogramLimits[30] = 28800; /* 6-8 Hours */
    histogramLimits[31] = 28800; /* > 8 hrs */

    histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);
    if (pMagHistogram == NULL)
    {
        printf("Createhistogram\n");
    }

    PrintHistogram(pMagHistogram);

    UpdateHistogram(pMagHistogram, 400);
    UpdateHistogram(pMagHistogram, 0);
    UpdateHistogram(pMagHistogram, 20);
    UpdateHistogram(pMagHistogram, 23);
    UpdateHistogram(pMagHistogram, 30000);
    UpdateHistogram(pMagHistogram, 1001);
    UpdateHistogram(pMagHistogram, 843);
    UpdateHistogram(pMagHistogram, 30001);
    UpdateHistogram(pMagHistogram, 83541);

    PrintHistogram(pMagHistogram);

    FreeHistogram(pMagHistogram);
}