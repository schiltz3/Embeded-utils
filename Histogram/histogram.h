/**
 * @file histogram.h
 * @author John Schiltz
 * @date 14 October 2021
 * @brief File containing the data structures, and public function prototypes for histogram.h
 */
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdint.h>

typedef enum
{
    NO_ERROR,
    MEM_ERROR,
    ZERO_VALUE
} histogram_error;

typedef struct
{
    uint32_t *pHistogramCount;
    uint8_t *pHistogramPercentage;
    uint32_t *pBucketLimits;
    uint8_t num_of_buckets;
    histogram_error error;
} histogram_s;

histogram_s *CreateHistogram(uint32_t *pBuckets, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength);
histogram_error UpdateHistogram(histogram_s *histogram_struct, uint32_t element);
histogram_error FreeHistogram(histogram_s *pHistogramStruct);
void PrintHistogram(histogram_s *pHistogramStruct);

#endif