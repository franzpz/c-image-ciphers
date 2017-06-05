
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEV 1
#define TEST 1

#ifdef DEV
    #define PTF(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF(A,...) do {} while(0);
#endif

#ifdef TEST
    #define PTF_IMPT(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF_IMPT(A,...) do {} while(0);
#endif

static int ENC_MODE = 1;
static int DEC_MODE = 2;

typedef struct PermutationSetups {
    double r; // 3.6 <= r <= 4.0
    double x; // 0 < x < 1
} PermutationSetup;

typedef struct DiffusionSetups {
    double miu; // 0.6 < miu <= 1.0
    double y; // 0 < y < 1
    double x; // 0 < x < 1
} DiffusionSetup;

void runAlgorithm(int mode, unsigned char imageBytes[], int numberOfImageBytes);

void printSequence(double a[], int n);
void copyArray(double source[], double dest[], int n);
void bubbleSort(double a[], int n);
int calcGroupNumber(double t);
int find(double array[], double data, int length);

void createPermutationSequence(int permutationSequence[], double r, double x, int sequenceLength);
double generateControlParametersLogisticMap(double basicR, double avgOfImageByteSum, int numberOfImageBytes);
void createDiffusionSequenceIkedaMap(double miu, double x, double y, unsigned char mOneSequence[], unsigned char mTwoSequence[], int sequenceLength);
double generateControlParametersIkedaMap(double miu, double avgOfImageByteSum, int numberOfImageBytes);

int main(int argc, char* argv[]) {

    /*argv[1] = "../../5x5image.jpgbytes.txt\0";
    argv[2] = "75";
    argc = 3;

    int maxFilePathLength = 100;

    if(argc < 3)
        return -1;

    char filePath[maxFilePathLength];
    //char *filePath = "../../5x5image.jpgbytes.txt";

    if (strlen(argv[1]) >= maxFilePathLength)
        fprintf(stderr, "%s is too long!\n", argv[1]);
    else
        strcpy(filePath, argv[1]);

    PTF_IMPT("\nusing file: %s\n", filePath);

    int numberOfImageBytes;
    sscanf (argv[2],"%d",&numberOfImageBytes);

    PTF_IMPT("\nnumber of bytes: %d\n", numberOfImageBytes);

    FILE *myFile;
    myFile = fopen(filePath, "r");

    //read file into array
    unsigned char imageBytes[numberOfImageBytes];
    int i;

    for (i = 0; i < numberOfImageBytes; i++)
    {
        fscanf(myFile, "%d", &imageBytes[i]);
    }

    free(myFile);

    #ifdef DEV
    PTF("\n------- Number is: [");
    for (int i = 0; i < numberOfImageBytes; i++)
    {
        PTF("%d, ", imageBytes[i]);
    }
    PTF("] -------- \n");
    #endif // DEV
*/
    /**/
    // image data
    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = DEC_MODE;
 /* orig 5x4
    unsigned char imageBytes[] = {
		215, 59, 230, 206, 50, 221, 209, 53, 224, 213, 57, 228, 205, 52, 222, 201, 48, 218, 191,
		39, 209, 194, 41, 211, 196, 44, 214, 188, 36, 206, 191, 44, 212, 181, 36, 203, 184, 37,
		205, 187, 42, 209, 179, 34, 201, 185, 44, 210, 176, 37, 202, 181, 40, 206, 185, 46, 211,
		180, 39, 205, 178, 43, 207, 168, 36, 199, 176, 41, 205, 179, 47, 210, 176, 41, 205
    };

    enc 5x5 10 rounds
    unsigned char imageBytes[] = {
        47, 205, 43, 201, 194, 36, 53, 181, 230, 205, 205, 199, 228, 224, 211, 207, 39, 209, 36,
        212, 41, 34, 44, 209, 201, 176, 205, 221, 209, 48, 215, 37, 179, 44, 187, 41, 179, 210,
        191, 40, 211, 181, 176, 59, 52, 184, 42, 206, 176, 180, 37, 188, 202, 210, 178, 44, 206,
        36, 57, 203, 41, 214, 191, 39, 168, 46, 185, 222, 206, 205, 185, 196, 50, 213, 218
    };

    */
/*
    // orig 2x3
    unsigned char imageBytes[] = {
        201, 40, 208, 200, 39, 207, 214, 53, 221,
        213, 52, 220, 216, 50, 220, 216, 50, 220
    };*/

    // enc 2x3 2 rounds
    unsigned char imageBytes[] = {
        241, 197, 171,  77, 121, 26, 101, 155, 186,
        226, 110,   0, 231, 214, 7, 216, 156, 25
    };






    // controll parameter
    /*
    double r = 3.812345678; // 3.6 <= r <= 4.0
    double xPermutation = 0.345678914; // 0 < x < 1

    double miuDiffusion = 0.60122344; // 0.6 < miu <= 1.0
    double yDiffusion = 0.600030404055; // 0 < y < 1
    double xDiffusion = 0.9523456; // 0 < x < 1
*/

    runAlgorithm(mode, imageBytes, numberOfImageBytes);
/*
    char encryptedSuffix[] = ".encrypted";
    strcat(filePath, encryptedSuffix);
    PTF_IMPT("new filename = %s\n", filePath);

    FILE *encryptedImageBytes = fopen(filePath, "w");
    for (i = 0; i < numberOfImageBytes; i++)
    {
        fprintf(encryptedImageBytes, "%u ", imageBytes[i]);
    }
    fclose(encryptedImageBytes);*/

    return 0;
}

void runAlgorithm(int mode, unsigned char imageBytes[], int numberOfImageBytes) {

    #ifdef TEST
    PTF_IMPT("\n----------- original Image [");
    for(int j = 0; j < numberOfImageBytes; j++) {
        PTF_IMPT("%u, ", imageBytes[j]);
    }
    PTF_IMPT("] -------------------\n");
    #endif

    PermutationSetup permSetups[4];

    permSetups[0].r = 3.6000000001;
    permSetups[0].x = 0.8000000001;

    permSetups[1].r = 3.6000000002;
    permSetups[1].x = 0.8000000002;

    permSetups[2].r = 3.6000000003;
    permSetups[2].x = 0.8000000003;

    permSetups[3].r = 3.6000000004;
    permSetups[3].x = 0.8000000004;

    DiffusionSetup diffuSetups[2];

    diffuSetups[0].miu = 0.8597000122;
    diffuSetups[0].x = 0.7733460001;
    diffuSetups[0].y = 0.6543224322;

    diffuSetups[1].miu = 0.84234123412;
    diffuSetups[1].x = 0.78225545794;
    diffuSetups[1].y = 0.66346604384;

    int encryptionRounds = 2;

    int permutationSequenceLogisticMap[4][numberOfImageBytes];
    unsigned char diffustionSequenceIkedaMap[4][numberOfImageBytes];

    long sumOfAllImageBytes = 2840;
    double avg = 0;
    /*for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += imageBytes[i];
    }*/

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

    #ifdef TEST
    PTF_IMPT("\n----------- encrypted Image [");
    for(int j = 0; j < numberOfImageBytes; j++) {
        PTF_IMPT("%u, ", imageBytes[j]);
    }
    PTF_IMPT("] -------------------\n");
    #endif
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
