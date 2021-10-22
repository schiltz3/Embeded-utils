#include "histogram.h"
#include "unity.h"
#include <stdint.h>
#include <string.h>

/**
 * @brief Test for the histogram
 *
 */
void test_CreateHistogram(void);
void test_UpdateHistogram_0(void);
void test_UpdateHistogram_1(void);
void test_UpdateHistogram_2(void);
void test_UpdateHistogram_3(void);
void test_UpdateHistogram_4(void);
void test_UpdateHistogram_5(void);
void test_UpdateHistogram_6(void);
void test_ResetHistogram(void);
void test_FreeHistogram(void);

#define HISTOGRAM_LENGTH 32
uint32_t histogramLimits[HISTOGRAM_LENGTH] = {0};
uint32_t histogramCount[HISTOGRAM_LENGTH] = {0};
uint8_t histogramPercent[HISTOGRAM_LENGTH] = {0};

void setUp(void)
{
  memset(histogramCount, 0, HISTOGRAM_LENGTH * sizeof(uint32_t));
  memset(histogramPercent, 0, HISTOGRAM_LENGTH * sizeof(uint8_t));
  memset(histogramLimits, 0, HISTOGRAM_LENGTH * sizeof(uint8_t));
  // Required by Ceedling
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

  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);
  TEST_ASSERT_NOT_NULL(pMagHistogram);

  TEST_ASSERT_EQUAL_PTR_MESSAGE(histogramLimits,
                                pMagHistogram->pBucketLimits,
                                "pBucketLimits pointer does not point to correct array");
  TEST_ASSERT_EQUAL_PTR_MESSAGE(histogramPercent,
                                pMagHistogram->pHistogramPercent,
                                "pHistogramPercent pointer does not point to correct array");
  TEST_ASSERT_EQUAL_PTR_MESSAGE(histogramCount, pMagHistogram->pHistogramCount, "pHistogramCount are not equal");
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(HISTOGRAM_LENGTH,
                                  pMagHistogram->numberOfBuckets,
                                  "number of buckets not equal to input");
}
/**
 * @brief Test that zeros get discarded
 *
 */
void test_UpdateHistogram_0(void)
{
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);
  histogram_error h_error = UpdateHistogram(pMagHistogram, 0);

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ZERO_ERROR, h_error, "Should return ZERO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "All buckets should be 0");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "All buckets should be 0");
}
/**
 * @brief Test that an element gets added, and the percentage is calculated correctly on 1 entry
 *
 */
void test_UpdateHistogram_1(void)
{
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);
  histogram_error h_error = UpdateHistogram(pMagHistogram, 800);

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [22] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY(test_HistogramCount, histogramCount, HISTOGRAM_LENGTH);

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [22] = 100};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(test_HistogramPercent, histogramPercent, HISTOGRAM_LENGTH);
}
/**
 * @brief Test that element that equals bucket limit gets put in that bucket
 *
 */
void test_UpdateHistogram_2(void)
{
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  histogram_error h_error = UpdateHistogram(pMagHistogram, 30);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [13] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Bucket 13 should be 1");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [13] = 100};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Bucket 13 should be 100");
}

/**
 * @brief Test that elemnts get added, and percentage is calculated correctly on 2 entries
 *
 */
void test_UpdateHistogram_3(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  h_error = UpdateHistogram(pMagHistogram, 87);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  h_error = UpdateHistogram(pMagHistogram, 2000);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [16] = 1, [24] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Buckets 16 and 24 should be 1");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [16] = 50, [24] = 50};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Bucket 16 and 24 should be 50");
}

/**
 * @brief Test that elements get added, and percentage is calculated correctly on 3 entries
 *
 */
void test_UpdateHistogram_4(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  h_error = UpdateHistogram(pMagHistogram, 87);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  h_error = UpdateHistogram(pMagHistogram, 2000);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  h_error = UpdateHistogram(pMagHistogram, 6);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [5] = 1, [16] = 1, [24] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Buckets 16 and 24 should be 1");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [5] = 33, [16] = 33, [24] = 33};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Bucket 16 and 24 should be 50");
}
/**
 * @brief Test that elements get added, and percentage is calculated correctly on 3 entries with two being
 * in the same bucket
 *
 */
void test_UpdateHistogram_5(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  h_error = UpdateHistogram(pMagHistogram, 87);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  h_error = UpdateHistogram(pMagHistogram, 2000);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  h_error = UpdateHistogram(pMagHistogram, 2000);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [16] = 1, [24] = 2};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Buckets 16 and 24 should be 1");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [16] = 33, [24] = 66};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Bucket 16 and 24 should be 50");
}
/**
 * @brief Test that elements larger than the largest bucket get put in the correct bucket and the percentage is
 * calculated correctly
 *
 */
void test_UpdateHistogram_6(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  h_error = UpdateHistogram(pMagHistogram, 30000);
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(NO_ERROR, h_error, "Should return NO_ERROR");

  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [HISTOGRAM_LENGTH - 1] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Bucket 31 should be 1");

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [HISTOGRAM_LENGTH - 1] = 100};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Bucket 31 should be 100");
}

/**
 * @brief Test that the histogramPercent and histogramCount are set to zero
 *
 */
void test_ResetHistogram(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);

  /* populate histogram and arrays */
  UpdateHistogram(pMagHistogram, 30000);
  UpdateHistogram(pMagHistogram, 10);
  UpdateHistogram(pMagHistogram, 67);
  UpdateHistogram(pMagHistogram, 894);
  uint32_t test_HistogramCount[HISTOGRAM_LENGTH] = {0, [9] = 1, [16] = 1, [22] = 1, [31] = 1};
  TEST_ASSERT_EQUAL_UINT32_ARRAY(test_HistogramCount, histogramCount, HISTOGRAM_LENGTH);

  uint8_t test_HistogramPercent[HISTOGRAM_LENGTH] = {0, [9] = 25, [16] = 25, [22] = 25, [31] = 25};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(test_HistogramPercent, histogramPercent, HISTOGRAM_LENGTH);

  uint32_t test_HistogramLimits[HISTOGRAM_LENGTH];
  for (int i = 0; i < HISTOGRAM_LENGTH; i++)
  {
    test_HistogramLimits[i] = histogramLimits[i];
  }

  /* Reset histogram and test arrays */
  ResetHistogram(pMagHistogram);

  memset(test_HistogramCount, 0, HISTOGRAM_LENGTH * sizeof(uint32_t));
  memset(test_HistogramPercent, 0, HISTOGRAM_LENGTH * sizeof(uint8_t));

  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramCount,
                                         histogramCount,
                                         HISTOGRAM_LENGTH,
                                         "Array should be empty");
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(test_HistogramPercent,
                                        histogramPercent,
                                        HISTOGRAM_LENGTH,
                                        "Array should be empty");
  TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(test_HistogramLimits,
                                         histogramLimits,
                                         HISTOGRAM_LENGTH,
                                         "Arrays should be the same");
}
/**
 * @brief Test that pointer is freed and set to null in FreeHistogram
 *
 */
void test_FreeHistogram(void)
{
  histogram_error h_error;
  histogram_s *pMagHistogram = CreateHistogram(histogramLimits, histogramPercent, histogramCount, HISTOGRAM_LENGTH);
  TEST_ASSERT_NOT_NULL(pMagHistogram);

  FreeHistogram(&pMagHistogram);

  TEST_ASSERT_NULL(pMagHistogram);
}