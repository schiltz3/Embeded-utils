#include "histogram.h"
#include "stdlib.h"
#include "string.h"
/* function prototypes */
histogram_s *CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength);
histogram_error update_histogram(histogram_s *pHistogramStruct, uint32_t element);

/**
 * @brief Initialize the histogram handed it.
*/
histogram_s *CreateHistogramp(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength)
{
    histogram_s pHistogramStruct = {
        .pBucketLimits = pBucketLimits,
        .pHistogramCount = *pHistogramCount,
        .pHistogramPercentage = pHistogramPercentage,
        .num_of_buckets = histogramLength,
        .error = NO_ERROR};
    return &pHistogramStruct;
}

histogram_error update_histogram(histogram_s *pHistogramStruct, uint32_t element)
{
    /* return if element will not be put in histogram*/
    if (element <= 0)
    {
        return ZERO_VALUE;
    }

    /* Find and increment bucket that element goes in */
    for (uint8_t i = 0; i < pHistogramStruct->num_of_buckets - 1; i++)
    {
        if (element < pHistogramStruct->pBucketLimits[i])
        {
            pHistogramStruct->pHistogramCount[i]++;
            break;
        }
    }
    if (element >= pHistogramStruct->pBucketLimits[pHistogramStruct->num_of_buckets - 1])
    {
        pHistogramStruct->pHistogramCount[pHistogramStruct->num_of_buckets - 1]++;
    }

    /* Calculate the sum of all the buckets */
    uint32_t binSum = 0;
    for (uint8_t i = 0; i < pHistogramStruct->num_of_buckets; i++)
    {
        binSum += pHistogramStruct->pHistogramCount[i];
    }

    /* calculate the percentage of each bucket */
    for (uint8_t i = 0; i < pHistogramStruct->num_of_buckets; i++)
    {
        pHistogramStruct->pHistogramPercentage = (pHistogramStruct->pHistogramCount[i] * 100) / binSum;
    }

    return NO_ERROR;
}