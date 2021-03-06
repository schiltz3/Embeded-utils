/**
 * @file histogram.c
 * @author John Schiltz
 * @date 14 October 2021
 * @brief General histogram solution
 */

#include "histogram.h"

/* function prototypes */
histogramReturn_s CreateHistogram(uint32_t *pBucketLimits,
                                  uint8_t *pHistogramPercent,
                                  uint32_t *pHistogramCount,
                                  uint8_t histogramLength);
histogram_error UpdateHistogram(histogram_s *pHistogramStruct, uint32_t element);
histogram_error ResetHistogram(histogram_s *pHistogramStruct);
histogram_error FreeHistogram(histogram_s **pHistogramStruct);
void PrintHistogram(histogram_s *pHistogramStruct);

/**
 * @brief Initialize a histogram struct that wraps the arrays handed it
 * @param pBucketLimits The array of size histogramLength containing upper buckets limit. The lower limit is the limit
 * before it
 * @param pHistogramPercent The array of size histogramlength to store the histogram percentages in
 * @param pHistogramCount The array of size histogramLength to store the histogram bucket counters in
 * @param histogramLength The length of the 3 arrays
 * @return The newly created histogram struct
 */
histogramReturn_s
CreateHistogram(uint32_t *pBucketLimits, uint8_t *pHistogramPercent, uint32_t *pHistogramCount, uint8_t histogramLength)
{
  histogram_s *pHistogramStruct = (histogram_s *)malloc(sizeof(histogram_s));
  pHistogramStruct->pBucketLimits = pBucketLimits;
  pHistogramStruct->pHistogramCount = pHistogramCount;
  pHistogramStruct->pHistogramPercent = pHistogramPercent;
  pHistogramStruct->numberOfBuckets = histogramLength;
  histogramReturn_s returnValue = {.histogramErrorReturn = (pHistogramStruct == NULL) ? MEM_ERROR : NO_ERROR,
                                   .pHistogramStructReturn = pHistogramStruct};
  return returnValue;
}

/**
 * @brief Update the histogram structs with the new element
 * @param pHistogramStruct a pointer to a histogram struct
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
    pHistogramStruct->pHistogramPercent[i] = (pHistogramStruct->pHistogramCount[i] * 100) / binSum;
  }

  return NO_ERROR;
}
/**
 * @brief Set the elements in phistogramCount and phistogramPercent to 0
 *
 * @param pHistogramStruct a pointer to a histogram struct
 * @return histogram_error
 */
histogram_error ResetHistogram(histogram_s *pHistogramStruct)
{
  memset(pHistogramStruct->pHistogramCount,
         0,
         pHistogramStruct->numberOfBuckets * sizeof(pHistogramStruct->pHistogramCount[0]));
  memset(pHistogramStruct->pHistogramPercent,
         0,
         pHistogramStruct->numberOfBuckets * sizeof(pHistogramStruct->pHistogramPercent[0]));
  return NO_ERROR;
}
/**
 * @brief Frees the memory allocated to the histogram struct, but leaves the arrays pointed to intact
 * @param pHistogramStruct a double pointer to a histogram Struct
 * @return A histogram error enum (0 is no error)
 */
histogram_error FreeHistogram(histogram_s **pHistogramStruct)
{
  free(*pHistogramStruct);
  *pHistogramStruct = NULL;

  return NO_ERROR;
}

/**
 * @brief Pretty prints the pHistogramCount and pHistogramPercent arrays
 * @param pHistogramStruct A histogram Struct
 */
void PrintHistogram(histogram_s *pHistogramStruct)
{
  printf("|Bucket\tCount\tPercent\t|\n");
  printf("|--------------------------|\n");
  for (uint8_t i = 0; i < pHistogramStruct->numberOfBuckets; i++)
  {
    printf("|%u \t%u\t%u %\t|\n", i, pHistogramStruct->pHistogramCount[i], pHistogramStruct->pHistogramPercent[i]);
  }
  printf("----------------------------\n");
}