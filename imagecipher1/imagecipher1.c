#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagecipher1.h"

void printSequence(double a[], int n);
void copyArray(double source[], double dest[], int n);
void bubbleSort(double a[], int n);
int calcGroupNumber(double t);
int find(double array[], double data, int length);

void decrypt(int numberOfBytes, int permutationSeqs[4][numberOfBytes], unsigned char diffustionSeqs[4][numberOfBytes], unsigned char imageBytes[numberOfBytes],int rounds);
void encrypt(int numberOfBytes, int permutationSeqs[4][numberOfBytes], unsigned char diffustionSeqs[4][numberOfBytes], unsigned char imageBytes[numberOfBytes],int rounds);

void createPermutationSequence(int permutationSequence[], double r, double x, int sequenceLength);
double generateControlParametersLogisticMap(double basicR, double avgOfImageByteSum, int numberOfImageBytes);
void createDiffusionSequenceIkedaMap(double miu, double x, double y, unsigned char mOneSequence[], unsigned char mTwoSequence[], int sequenceLength);
double generateControlParametersIkedaMap(double miu, double avgOfImageByteSum, int numberOfImageBytes);

void runAlgorithm(int mode, unsigned char imageBytes[], int numberOfImageBytes, long sumOfAllImageBytes, PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2], int encryptionRounds) {

    int permutationSequenceLogisticMap[4][numberOfImageBytes];
    unsigned char diffustionSequenceIkedaMap[4][numberOfImageBytes];

    double avg = 0;
    PTF("Sum of bytes = %ld\n", sumOfAllImageBytes);

    avg = ((double)sumOfAllImageBytes) / (double)(numberOfImageBytes * 63 * 10);
    PTF("Average = %.15f\n", avg);

    // 1. generate control parameters for logistic map based on image
    PTF("\n-------------Permutation Parameters\n");
    for(int i = 0; i < 4; i++) {
        permSetups[i].r = generateControlParametersLogisticMap(permSetups[i].r, avg, numberOfImageBytes);
        PTF("r%d = %.15f\n", i, permSetups[i].r);
    }
    PTF("-------------\n");

    // 2. create permutation = fill permutation array
    PTF("\n-------------Permutation Sequences \n");
    for(int i = 0; i < 4; i++) {
        createPermutationSequence(permutationSequenceLogisticMap[i], permSetups[i].r, permSetups[i].x, numberOfImageBytes);

        #ifdef DEV
        PTF("\nPermutation Sequence %d: \n [", i);
        for(int j = 0; j < 18; j++) {
            PTF("%d ", permutationSequenceLogisticMap[i][j]);
        }
        PTF(" ]-------------------\n");
        #endif
    }


    // 3. generate control parameters for ikeda map based on image
    PTF("\n-------------Diffustion Parameters\n");
    for(int i = 0; i < 2; i++) {
        diffuSetups[i].miu = generateControlParametersLogisticMap(diffuSetups[i].miu, avg, numberOfImageBytes);
        PTF("miu%d = %.15f\n", i, diffuSetups[i].miu);
    }
    PTF("-------------\n");


    // 4. create ikeda map diffusion sequence
    PTF("\n-------------Diffustion Sequences \n");
    for(int i = 0; i < 2; i++) {
        createDiffusionSequenceIkedaMap(diffuSetups[i].miu, diffuSetups[i].x, diffuSetups[i].y, diffustionSequenceIkedaMap[i*2], diffustionSequenceIkedaMap[(i*2)+1], numberOfImageBytes);

        #ifdef DEV
        PTF("\nDiffusion Sequence %d: \n [ ", i*2);
        for(int j = 0; j < 18; j++) {
            PTF("%d ", diffustionSequenceIkedaMap[i*2][j]);
        }
        PTF(" ]-------------------\n");

        PTF("\nDiffusion Sequence %d: \n [ ", (i*2)+1);
        for(int j = 0; j < 18; j++) {
            PTF("%d ", diffustionSequenceIkedaMap[(i*2)+1][j]);
        }
        PTF(" ]-------------------\n");
        #endif
    }

    if(mode == ENC_MODE) {
        // 5. Encryption rounds
        encrypt(numberOfImageBytes, permutationSequenceLogisticMap, diffustionSequenceIkedaMap, imageBytes, encryptionRounds);
    }
    else if(mode == DEC_MODE) {
        // 4. decryption rounds
        decrypt(numberOfImageBytes, permutationSequenceLogisticMap, diffustionSequenceIkedaMap, imageBytes, encryptionRounds);
    }
}

void decrypt(int numberOfBytes, int permutationSeqs[4][numberOfBytes], unsigned char diffustionSeqs[4][numberOfBytes], unsigned char imageBytes[numberOfBytes],int rounds) {

    unsigned char tmpImageBytes[numberOfBytes];

    for(int i = 0; i < rounds; i++) {

        for(int k = 3; k >= 0; k--) {

            PTF("\n----------- round %d after diffusion %d [", i, k);
            for(int j = 0; j < numberOfBytes; j++) {
                tmpImageBytes[j] = imageBytes[j]^diffustionSeqs[k][j];
                PTF("%u, ", tmpImageBytes[j]);
            }
            PTF("] \n");

            PTF("\n----------- after permutation %d [", k);
            // 1. shuffle
            for(int j = 0; j < numberOfBytes; j++) {
                imageBytes[permutationSeqs[k][j]] = tmpImageBytes[j];
                PTF("%u, ", imageBytes[j]);
            }
            PTF("] -------------------\n");
        }
    }
}

void encrypt(int numberOfBytes, int permutationSeqs[4][numberOfBytes], unsigned char diffustionSeqs[4][numberOfBytes], unsigned char imageBytes[numberOfBytes],int rounds) {

    unsigned char tmpImageBytes[numberOfBytes];

    for(int i = 0; i < rounds; i++) {

        for(int k = 0; k < 4; k++) {
            // 1. shuffle
            PTF("\n----------- round %d after permutation %d [", i, k);
            for(int j = 0; j < numberOfBytes; j++) {
                tmpImageBytes[j] = imageBytes[permutationSeqs[k][j]];
                PTF("%u, ", tmpImageBytes[j]);
            }
            PTF("] \n");

            PTF("\n----------- after diffusion %d [", k);
            // 2. xor 1
            for(int j = 0; j < numberOfBytes; j++) {
                imageBytes[j] = tmpImageBytes[j]^diffustionSeqs[k][j];
                PTF("%u, ", imageBytes[j]);
            }
            PTF("] -------------------\n");
        }
    }
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

            //PTF("%d - xn: %.20f yn: %.20f m1: %d\n", i, xn, yn, mOneSequence[i-entriesToSkip]);
            //PTF("%d - xn: %.20f yn: %.20f m1: %d\n", i, xn, yn, mTwoSequence[i-entriesToSkip]);
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
      //PTF("Comparison %d\n" , (comparisons +1) );
      //PTF("lowerBound : %d, array[%d] = %.15f\n",lowerBound,lowerBound,
      //   array[lowerBound]);
      //PTF("upperBound : %d, array[%d] = %.15f\n",upperBound,upperBound,
      //   array[upperBound]);
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
   //PTF("Total comparisons made: %d" , comparisons);
   return index;
}
