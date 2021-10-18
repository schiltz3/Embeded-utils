#include <stdint.h>
#include "unity.h"
#include "histogram.h"

/**
 * @brief Test for the histogram
 * 
 */
void test_CreateHistogram(void);

void setUp(void)
{
    //Required by Ceedling
}

/**
 * @brief A simple test of the CreateHistogram function
 * 
 */
void test_CreateHistogram(void)
{
#define HISTOGRAM_LENGTH 32
    uint32_t magHistoLimits[HISTOGRAM_LENGTH] = {0};
    uint32_t histogramCount[HISTOGRAM_LENGTH] = {0};
    uint8_t histogramPercentage[HISTOGRAM_LENGTH] = {0};
    magHistoLimits[0] = 1; /* 0-1s */
    magHistoLimits[1] = 2; /* 1-2s */
    magHistoLimits[2] = 3; /* ... */
    magHistoLimits[3] = 4;
    magHistoLimits[4] = 5;
    magHistoLimits[5] = 6;
    magHistoLimits[6] = 7;
    magHistoLimits[7] = 8;
    magHistoLimits[8] = 9;
    magHistoLimits[9] = 10;

    /* Limits for upto a minute */
    magHistoLimits[10] = 12; /* 10-12s */
    magHistoLimits[11] = 15; /* 12-15s */
    magHistoLimits[12] = 20; /* 15-20s */
    magHistoLimits[13] = 30; /* > 20-30s */
    magHistoLimits[14] = 45; /* 30-45s */
    magHistoLimits[15] = 60; /* 45s-1min */

    /*Limits upto 8+hr */
    magHistoLimits[16] = 90;   /* 1min - 1:30 min */
    magHistoLimits[17] = 120;  /* 1:30 -2 min */
    magHistoLimits[18] = 180;  /* 2-3 min */
    magHistoLimits[19] = 300;  /* 3-5 min */
    magHistoLimits[20] = 420;  /* 5-7 min */
    magHistoLimits[21] = 600;  /* 7-10 Minutes */
    magHistoLimits[22] = 900;  /* 10 - 15 Minutes */
    magHistoLimits[23] = 1800; /* 15-30 Minutes */
    magHistoLimits[24] = 2700; /* 30-45 min */
    magHistoLimits[25] = 3600; /* 45min -1 Hour */

    magHistoLimits[26] = 7200;  /* 1-2 Hours */
    magHistoLimits[27] = 10800; /* 2-3 Hours */
    magHistoLimits[28] = 14400; /* 3-4 Hrs */
    magHistoLimits[29] = 21600; /* 4-6 Hour */
    magHistoLimits[30] = 28800; /* 6-8 Hours */
    magHistoLimits[31] = 28800; /* > 8 hrs */

    histogram_s *pMagHistogram = CreateHistogram(magHistoLimits, histogramPercentage, histogramCount, HISTOGRAM_LENGTH);
    TEST_ASSERT_NOT_NULL(pMagHistogram);
}