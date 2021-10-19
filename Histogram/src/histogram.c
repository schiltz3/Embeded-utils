/**
 * @file histogram.c
 * @author John Schiltz
 * @date 14 October 2021
 * @brief General histogram solution
 */

#include "histogram.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

/* function prototypes */
histogram_s *CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength);
histogram_error UpdateHistogram(histogram_s *pHistogramStruct, uint32_t element);
histogram_error ResetHistogram(histogram_s *phistogramStruct);
histogram_error FreeHistogram(histogram_s *pHistogramStruct);
void PrintHistogram(histogram_s *pHistogramStruct);

/**
 * @brief Initialize a histogram struct that wraps the arrays handed it
 * @param pBucketLimits The array of size histogramLength containing upper buckets limit. The lower limit is the limit before it
 * @param pHistogramPercentage The array of size histogramlength to store the histogram percentages in
 * @param pHistogramCount The array of size histogramLength to store the histogram bucket counters in
 * @param histogramLength The length of the 3 arrays
 * @return The newly created histogram struct
 */
histogram_s *CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercentage, uint32_t *pHistogramCount, uint8_t histogramLength)
{
    histogram_s *pHistogramStruct = (histogram_s *)malloc(sizeof(histogram_s));
    pHistogramStruct->pBucketLimits = pBucketLimits;
    pHistogramStruct->pHistogramCount = pHistogramCount;
    pHistogramStruct->pHistogramPercentage = pHistogramPercentage;
    pHistogramStruct->numberOfBuckets = histogramLength;
    return pHistogramStruct;
}

/**
 * @brief Update the histogram structs with the new element
 * @param pHistogramStruct A histogram struct
 * @param element The element to be added to the histogram
 * @return A histogram error enum (0 is no error)
 */
histogram_error UpdateHistogram(histogram_s *pHistogramStruct, uint32_t element)
{
    /* Return if element will not be put in histogram */
    if (element <= 0)
    {
        return ZERO_ERROR;
    }

    /* Add the element in the last bucket if it is too large for the histogram */
    else if (element >= pHistogramStruct->pBucketLimits[pHistogramStruct->numberOfBuckets - 1])
    {
        pHistogramStruct->pHistogramCount[pHistogramStruct->numberOfBuckets - 1]++;
    }
    else
    {
        /* Find and increment bucket that element goes in */
        for (uint8_t i = 0; i < pHistogramStruct->numberOfBuckets - 1; i++)
        {
            if (element <= pHistogramStruct->pBucketLimits[i])
            {
                pHistogramStruct->pHistogramCount[i]++;
                break;
            }
        }
    }

    /* Calculate the sum of all the buckets */
    uint32_t binSum = 0;
    for (uint8_t i = 0; i < pHistogramStruct->numberOfBuckets; i++)
    {
        binSum += pHistogramStruct->pHistogramCount[i];
    }

    /* Calculate the percentage of each bucket */
    for (uint8_t i = 0; i < pHistogramStruct->numberOfBuckets; i++)
    {
        pHistogramStruct->pHistogramPercentage[i] = (pHistogramStruct->pHistogramCount[i] * 100) / binSum;
    }

    return NO_ERROR;
}
/**
 * @brief Set the elements in phistogramCount and phistogramPercentage to 0
 * 
 * @param phistogramStruct
 * @return histogram_error 
 */
histogram_error ResetHistogram(histogram_s *phistogramStruct)
{
    memset(phistogramStruct->pHistogramCount, 0, sizeof(phistogramStruct->pHistogramCount[0]));
    memset(phistogramStruct->pHistogramPercentage, 0, sizeof(phistogramStruct->pHistogramPercentage[0]));
}
/**
 * @brief Frees the memory allocated to the histogram struct, but leaves the arrays pointed to intact
 * @param pHistogramStruct A histogram Struct
 * @return A histogram error enum (0 is no error)
 */
histogram_error FreeHistogram(histogram_s *pHistogramStruct)
{
    free(pHistogramStruct);
    return NO_ERROR;
}

/**
 * @brief Pretty prints the pHistogramCount and pHistogramPercentage arrays
 * @param pHistogramStruct A histogram Struct
 */
void PrintHistogram(histogram_s *pHistogramStruct)
{
    printf("|Bucket\tCount\tPercent\t|\n");
    printf("|--------------------------|\n");
    for (uint8_t i = 0; i < pHistogramStruct->numberOfBuckets; i++)
    {
        printf("|%u \t%u\t%u %\t|\n", i, pHistogramStruct->pHistogramCount[i], pHistogramStruct->pHistogramPercentage[i]);
    }
    printf("----------------------------\n");
}