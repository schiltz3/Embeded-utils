/**
 * @file histogram.h
 * @author John Schiltz
 * @date 14 October 2021
 * @brief File containing the data structures, and public function prototypes for histogram.h
 */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "stdlib.h"
#include "string.h"
#include <stdint.h>
#include <stdio.h>

/**
 * @enum histogram_error
 * @brief Enum containing the different errors created by the histogram file
 */
typedef enum
{
  NO_ERROR,
  MEM_ERROR,
  ZERO_ERROR
} histogram_error;

/**
 * @struct histogram_s histogram.h
 * @brief Histogram containing pointers to HistogramCount, histogramPercent, BucketLimits, as well as the number of
 * buckets and an error enum
 */
typedef struct
{
  uint32_t *pHistogramCount;  //!< contains a pointer to the count array for the histogram
  uint8_t *pHistogramPercent; //!< Contains a pointer to the percentage array for the histogram
  uint32_t *pBucketLimits;    //!< Contains a pointer to the bucket limit array for the histogram
  uint8_t numberOfBuckets;    //!< Contains the length of the 3 arrays
} histogram_s;

/**
 * @brief struct of the types CreateHistogram can return
 *
 */
typedef struct
{
  histogram_s *pHistogramStructReturn;
  histogram_error histogramErrorReturn;
  /* data */
} histogramReturn_s;

histogramReturn_s
CreateHistogram(uint32_t *pBuckets, uint8_t *pHistogramPercent, uint32_t *pHistogramCount, uint8_t histogramLength);
histogram_error UpdateHistogram(histogram_s *histogram_struct, uint32_t element);
histogram_error ResetHistogram(histogram_s *phistogramStruct);
histogram_error FreeHistogram(histogram_s **pHistogramStruct);
void PrintHistogram(histogram_s *pHistogramStruct);

#endif