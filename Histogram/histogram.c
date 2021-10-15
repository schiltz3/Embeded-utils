#include "histogram.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

/* function prototypes */
histogram_s *CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength);
histogram_error UpdateHistogram(histogram_s *pHistogramStruct, uint32_t element);
histogram_error FreeHistogram(histogram_s *pHistogramStruct);
void PrintHistogram(histogram_s *pHistogramStruct);

/**
 * @brief Initialize the histogram handed it.
*/
histogram_s *CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength)
{
    histogram_s *pHistogramStruct = (histogram_s *)malloc(sizeof(histogram_s));
    pHistogramStruct->pBucketLimits = pBucketLimits;
    pHistogramStruct->pHistogramCount = pHistogramCount;
    pHistogramStruct->pHistogramPercentage = pHistogramPercentage;
    pHistogramStruct->num_of_buckets = histogramLength;
    pHistogramStruct->error = NO_ERROR;
    return pHistogramStruct;
}

histogram_error UpdateHistogram(histogram_s *pHistogramStruct, uint32_t element)
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
        pHistogramStruct->pHistogramPercentage[i] = (pHistogramStruct->pHistogramCount[i] * 100) / binSum;
    }

    return NO_ERROR;
}

histogram_error FreeHistogram(histogram_s *pHistogramStruct)
{
    free(pHistogramStruct);
}

void PrintHistogram(histogram_s *pHistogramStruct)
{
    printf("|Bucket\tCount\tPercent\t|\n");
    printf("|-----------------------|\n");
    for (uint8_t i = 0; i < pHistogramStruct->num_of_buckets; i++)
    {
        printf("|%u\t%u\t%u%\t|\n", i, pHistogramStruct->pHistogramCount[i], pHistogramStruct->pHistogramPercentage[i]);
    }
    printf("-------------------------\n");
}