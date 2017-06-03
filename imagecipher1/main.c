
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "debug.h"

#ifdef DEV
    #define PTF(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF(A,...) do {} while(0);
#endif

void printSequence(double a[], int n);
void copyArray(double source[], double dest[], int n);
void bubbleSort(double a[], int n);
int calcGroupNumber(double t);
int find(double array[], double data, int length);

void createPermutationSequence(int permutationSequence[], double r, double x, int sequenceLength);


int main(int argc, char* argv[]) {
    // create permutation sequence
    double r = 3.812345678;
    double x = 0.345678914;

    int sequenceLength = 30;
    int permutationSequence[sequenceLength];

    createPermutationSequence(permutationSequence, r, x, sequenceLength);

    // generate control parameter




	return 0;
}

void createPermutationSequence(int permutationSequence[], double r, double x, int sequenceLength) {
    double sequenceC[sequenceLength];
    double sequenceS[sequenceLength];
    double xn = x;

    // create original chaotic sequence (skip 1st 1000 entries)
    int transientResultsToSkip = 1000;
    for(int i = 0; i < transientResultsToSkip + sequenceLength; i++) {
        xn = r * xn * (1 - xn);
        if(i >= transientResultsToSkip)
            sequenceC[i-transientResultsToSkip] = xn;
    }

    PTF("original sequence C\n");
    printSequence(sequenceC, 10);

    // create sorted sequence S based on sequence C
    copyArray(sequenceC, sequenceS, sequenceLength);

    bubbleSort(sequenceS, sequenceLength);

    PTF("sorted sequence S\n");
    printSequence(sequenceS, 10);

    // better allocation (use malloc)
    double groupedArrays[10][sequenceLength];
    int lastGroupedArrayPosition[10];

    // initialize arrays
    for(int i = 0; i < 10; i++) {
        lastGroupedArrayPosition[i] = 0;

        for(int j = 0; j < sequenceLength; j++) {
            groupedArrays[i][j] = -1;
        }
    }

    for(int i = 0; i < 10; i++) lastGroupedArrayPosition[i] = 0;

    // create grouped arrays based on sequence C
    for(int i = 0; i < sequenceLength; i++) {

        int result = calcGroupNumber(sequenceS[i]);
        if(result < 0 || result > 9)
            return;

        //printf("result = %d writing to grouped Array number %d lastGroupArrayPosition = %d, value = %.15f\n\n", result, result,lastGroupedArrayPosition[result], sequenceS[i]);
        groupedArrays[result][lastGroupedArrayPosition[result]++] = sequenceS[i];
    }

    // create permuation sequence
    for(int i = 0; i < sequenceLength; i++) {
        permutationSequence[i] = -1;
    }

    int permutationIndex = 0;
    for(int i = 0; i < 10; i++) {
        if(permutationIndex >= sequenceLength)
            break;

        int j = 0;
        while(groupedArrays[i][j] > 0) {
            permutationSequence[permutationIndex++] = find(sequenceS, groupedArrays[i][j], sequenceLength);
            j++;
        }
    }

    PTF("\nPermutation Sequence: \n");
    for(int i = 0; i < sequenceLength; i++) {
        PTF("%d - %d\n", i, permutationSequence[i]);
    }
    PTF("-------------------\n");
}

int calcGroupNumber(double t) {
    double tTimes = t*1000000;

    int result1 = (((int)floor(tTimes)) % 10);
    int result2 = (((int)floor(tTimes * 1000)) % 10);

    if(result1 >= result2)
        return result1-result2;
    if(result2 >= result1)
        return result2-result1;

    return 0;
}

void printSequence(double a[], int n) {
    #ifdef DEV
    for(int i = 0; i < n; i++) {
        PTF("%d - %.15f\n", i, a[i]);
    }
    PTF("-------------------\n");
    #endif
}

void copyArray(double source[], double dest[], int n){
    for(int i = 0; i < n; i ++)
        dest[i] = source[i];
}

void bubbleSort(double a[], int n){
	for(int i=0; i<n; i++){
		int swaps=0;
		for(int j=0; j<n-i-1; j++){
			if(a[j]>a[j+1]){
				double t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				swaps++;
			}
		}
		if(swaps==0)
			break;
	}
}

int find(double array[], double data, int length) {
   int lowerBound = 0;
   int upperBound = length -1;
   int midPoint = -1;
   int comparisons = 0;
   int index = -1;

   while(lowerBound <= upperBound) {
      PTF("Comparison %d\n" , (comparisons +1) );
      PTF("lowerBound : %d, array[%d] = %.15f\n",lowerBound,lowerBound,
         array[lowerBound]);
      PTF("upperBound : %d, array[%d] = %.15f\n",upperBound,upperBound,
         array[upperBound]);
      comparisons++;

      // compute the mid point
      // midPoint = (lowerBound + upperBound) / 2;
      midPoint = lowerBound + (upperBound - lowerBound) / 2;

      // data found
      if(array[midPoint] == data) {
         index = midPoint;
         break;
      } else {
         // if data is larger
         if(array[midPoint] < data) {
            // data is in upper half
            lowerBound = midPoint + 1;
         }
         // data is smaller
         else {
            // data is in lower half
            upperBound = midPoint -1;
         }
      }
   }
   PTF("Total comparisons made: %d" , comparisons);
   return index;
}
