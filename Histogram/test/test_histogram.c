#include <stdint.h>
#include "unity.h"
#include "histogram.h"

/**
 * @brief Test for the histogram
 * 
 */
void test_CreateHistogram(void);

#define HISTOGRAM_LENGTH 32
uint32_t histogramLimits[HISTOGRAM_LENGTH] = {0};
uint32_t histogramCount[HISTOGRAM_LENGTH] = {0};
uint8_t histogramPercentage[HISTOGRAM_LENGTH] = {0};
void setUp(void)
{
    //Required by Ceedling
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
}

/**
 * @brief A simple test of the CreateHistogram function
 * 
 */
void test_CreateHistogram(void)
{

    histogram_s *pMagHistogram = CreateHistogram(magHistoLimits, histogramPercentage, histogramCount, HISTOGRAM_LENGTH);
    TEST_ASSERT_NOT_NULL(pMagHistogram);

    TEST_ASSERT_EQUAL_PTR_MESSAGE(pMagHistogram->pBucketLimits, magHistoLimits, "pBucketLimits pointer does not point to correct array");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(pMagHistogram->pHistogramPercentage, histogramPercentage, "pHistogramPercentage pointer does not point to correct array");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(pMagHistogram->pHistogramCount, histogramCount, "pHistogramCount are not equal");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(pMagHistogram->numberOfBuckets, HISTOGRAM_LENGTH, "number of buckets not equal to input");
}
void test_UpdateHistogram_0(void)
{
    histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercentage, histogramCount, HISTOGRAM_LENGTH);
    histogram_error h_error = UpdateHistogram(pMagHistogram, 0);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(h_error, ZERO_ERROR, "Should return ZERO_ERROR");

    uint32_t test_histogram_count[HISTOGRAM_LENGTH] = {0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(histogramCount, test_histogram_count, HISTOGRAM_LENGTH, "All buckets should be 0");

    uint8_t test_histogram_percent[HISTOGRAM_LENGTH] = {0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(histogramPercentage, test_histogram_percent, HISTOGRAM_LENGTH, "All buckets should be 0");
}
void test_UpdateHistogram_1(void)
{
    histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercentage, histogramCount, HISTOGRAM_LENGTH);
    histogram_error h_error = UpdateHistogram(pMagHistogram, 30);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(h_error, NO_ERROR, "Returned error when it should be NO_ERROR");

    uint32_t test_histogram_count[HISTOGRAM_LENGTH] = {0, [13] = 1};
    TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(histogramCount, test_histogram_count, HISTOGRAM_LENGTH, "Bucket 13 should be 1");

    uint8_t test_histogram_percent[HISTOGRAM_LENGTH] = {0, [13] = 100};
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(histogramPercentage, test_histogram_percent, HISTOGRAM_LENGTH, "Bucket 13 should be 100");
void test_UpdateHistogram_2(void)
{
    memset(histogramPercentage, 0, HISTOGRAM_LENGTH);

    histogram_error h_error;
    histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercentage, histogramCount, HISTOGRAM_LENGTH);

    h_error = UpdateHistogram(pMagHistogram, 87);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(h_error, NO_ERROR, "Returned error when it should be NO_ERROR");

    h_error = UpdateHistogram(pMagHistogram, 2000);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(h_error, NO_ERROR, "Returned error when it should be NO_ERROR");

    uint32_t test_histogram_count[HISTOGRAM_LENGTH] = {0, [16] = 1, [24] = 1};
    TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_histogram_count, histogramCount, HISTOGRAM_LENGTH, "Buckets 16 and 24 should be 1,");

    uint8_t test_histogram_percent[HISTOGRAM_LENGTH] = {0, [16] = 50, [24] = 50};
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_histogram_percent, histogramPercentage, HISTOGRAM_LENGTH, "Bucket 16 and 24 should be 50");
}
void test_FreeHistogram(void)
{
    histogram_error FreeHistogram(histogram_s * pHistogramStruct);
}
void test_PrintHistogram(void)
{
    void PrintHistogram(histogram_s * pHistogramStruct);
}