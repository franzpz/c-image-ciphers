
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
double generateControlParametersLogisticMap(double basicR, double avgOfImageByteSum, int numberOfImageBytes);
double generateControlParametersIkedaMap(double miu, double avgOfImageByteSum, int numberOfImageBytes);


int main(int argc, char* argv[]) {

    // image data
    int imageH = 5;
    int imageW = 5;
    int numberOfImageBytes = imageH*imageW*3;
    unsigned char imageBytes[] = {
		215, 59, 230, 206, 50, 221, 209, 53, 224, 213, 57, 228, 205, 52, 222, 201, 48, 218, 191,
		39, 209, 194, 41, 211, 196, 44, 214, 188, 36, 206, 191, 44, 212, 181, 36, 203, 184, 37,
		205, 187, 42, 209, 179, 34, 201, 185, 44, 210, 176, 37, 202, 181, 40, 206, 185, 46, 211,
		180, 39, 205, 178, 43, 207, 168, 36, 199, 176, 41, 205, 179, 47, 210, 176, 41, 205
    };

    // controll parameter
    double r = 3.812345678; // 3.6 <= r <= 4.0
    double xPermutation = 0.345678914; // 0 < x < 1

    double miuDiffusion = 0.60122344; // 0.6 < miu <= 1.0
    double yDiffusion = 0.600030404055; // 0 < y < 1
    double xDiffusion = 0.9523456; // 0 < x < 1



    int permutationSequenceLogisticMap[numberOfImageBytes];
    unsigned char mDiffusionSequenceOne[numberOfImageBytes];
    unsigned char mDiffusionSequenceTwo[numberOfImageBytes];

    long sumOfAllImageBytes = 0;
    double avg = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += imageBytes[i];
    }

    PTF("Sum of bytes = %ld\n", sumOfAllImageBytes);

    avg = ((double)sumOfAllImageBytes) / (double)(numberOfImageBytes * 63 * 10);
    PTF("Average = %.15f\n", avg);
    /*
    // 1. generate control parameters for logistic map based on image
    r = generateControlParametersLogisticMap(r, avg, numberOfImageBytes);
    PTF("\n-------------\nr = %.15f\n", r);

    // 2. create permutation = fill permutation array
    createPermutationSequence(permutationSequenceLogisticMap, r, x, numberOfImageBytes);
    */
    // 3. generate control parameters for ikeda map based on image
    miuDiffusion = generateControlParametersIkedaMap(miuDiffusion, avg, numberOfImageBytes);

    // 4. create ikeda map diffusion sequence
    createDiffusionSequenceIkedaMap(miuDiffusion, xDiffusion, mDiffusionSequenceOne, mDiffusionSequenceTwo, numberOfImageBytes);


}

void createDiffusionSequenceIkedaMap(double miu, double x, double y, unsigned char mOneSequence[], unsigned char mTwoSequence[], int sequenceLength){
    int entriesToSkip = 1000;
    double multiply = pow(10.0, 16);
    double absX;
    double absY;
    double xn = x;
    double yn = y;
    double tn;
    double cosT;
    double sinT;

    // initialize empty sequences
    for(int i = 0; i < sequenceLength; i++) {
        mOneSequence[i] = -1;
        mTwoSequence[i] = -1;
    }

    PTF("--------- Creating Diffusion Sequence ---------\n")

    // calculate chaotic map sequences
    for(int i = 0; i < entriesToSkip + sequenceLength; i++) {
        tn = 0.4 - (6.0 / (1.0 + xn*xn + yn*yn));

        cosT = cos(tn);
        sinT = sin(tn);

        xn = 1.0 + miu * ((xn * cosT) - (yn * sinT));
        yn = miu * ((xn * sinT) - (yn * cosT));

        if(i >= entriesToSkip) {
            absX = fabs(xn);
            absY = fabs(yn);
            mOneSequence[i-entriesToSkip] = ((long long)((absX - ((double)floor(absX))) * multiply)) % 255;
            mTwoSequence[i-entriesToSkip] = ((long long)((absY - ((double)floor(absY))) * multiply)) % 255;

            PTF("%d - xn: %.20f yn: %.20f m1: %d\n", i, xn, yn, mOneSequence[i-entriesToSkip]);
            PTF("%d - xn: %.20f yn: %.20f m1: %d\n", i, xn, yn, mTwoSequence[i-entriesToSkip]);
        }
    }
}

double generateControlParametersIkedaMap(double miu, double avgOfImageByteSum, int numberOfImageBytes) {
    double r = 0.0;

    if(numberOfImageBytes <= 1000000)
        r = (miu+0.0)+(1.0-avgOfImageByteSum)/2;
    else if(numberOfImageBytes > 1000000 && numberOfImageBytes <= 4000000)
        r = (miu+0.1)+(1.0-avgOfImageByteSum)/2;
    else if(numberOfImageBytes > 4000000)
        r = (miu+0.2)+(1.0-avgOfImageByteSum)/2;

	return r;
}

double generateControlParametersLogisticMap(double basicR, double avgOfImageByteSum, int numberOfImageBytes) {
    double r = 0.0;

    if(numberOfImageBytes <= 1000000)
        r = (basicR+0.0)+(0.4-avgOfImageByteSum);
    else if(numberOfImageBytes > 1000000 && numberOfImageBytes <= 4000000)
        r = (basicR+0.1)+(0.4-avgOfImageByteSum);
    else if(numberOfImageBytes > 4000000)
        r = (basicR+0.2)+(0.4-avgOfImageByteSum);

	return r;
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
