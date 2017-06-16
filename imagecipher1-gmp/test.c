
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagecipher1.h"
#include "time.h"


void test5x5ImageEncryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test5x5ImageEncryption ----");
    int imageH = 5;
    int imageW = 5;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = ENC_MODE;

    int encryptionRounds = 2;

    unsigned char origImageBytes[] = {
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }

    unsigned char expectedEncryptedImageBytes[] = {
        9, 29, 41, 153, 71, 68, 153, 25, 162, 182, 26, 67, 154, 91, 99, 92, 44, 239, 174, 125, 56, 
        98, 193, 32, 62, 97, 62, 34, 80, 193, 83, 6, 243, 116, 70, 84, 10, 172, 144, 168, 176, 134, 
        110, 204, 252, 41, 142, 66, 156, 210, 85, 8, 193, 122, 57, 128, 124, 152, 158, 247, 15, 16, 
        177, 242, 206, 232, 176, 174, 41, 223, 102, 186, 125, 112, 29
    };


    runAlgorithm(mode, origImageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);

    char *result = "success";

    for(int i = 0; i < numberOfImageBytes; i++) {
        if(origImageBytes[i] != expectedEncryptedImageBytes[i]) {
            result = "failure";
            PTF("error at byte %d, expected: %u, actual %u", i, expectedEncryptedImageBytes[i], origImageBytes[i]);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

void test5x5ImageDecryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test5x5ImageDecryption ----");
    int imageH = 5;
    int imageW = 5;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = DEC_MODE;

    int encryptionRounds = 2;

    unsigned char origImageBytes[] = {
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,
        67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243,67,76,243
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }

    unsigned char encryptedImageBytes[] = {
        9, 29, 41, 153, 71, 68, 153, 25, 162, 182, 26, 67, 154, 91, 99, 92, 44, 239, 174, 125, 56, 
        98, 193, 32, 62, 97, 62, 34, 80, 193, 83, 6, 243, 116, 70, 84, 10, 172, 144, 168, 176, 134, 
        110, 204, 252, 41, 142, 66, 156, 210, 85, 8, 193, 122, 57, 128, 124, 152, 158, 247, 15, 16, 
        177, 242, 206, 232, 176, 174, 41, 223, 102, 186, 125, 112, 29
    };

    runAlgorithm(mode, encryptedImageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);

    char *result = "success";

    for(int i = 0; i < numberOfImageBytes; i++) {
        if(encryptedImageBytes[i] != origImageBytes[i]) {
            result = "failure";
            PTF("error at byte %d, expected: %u, actual %u", i, origImageBytes[i], encryptedImageBytes[i]);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

void test2x3ImageDecryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test2x3ImageDecryption ----");
    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = DEC_MODE;

    int encryptionRounds = 2;

    unsigned char expectedOrigImageBytes[] = {
        201, 40, 208, 214, 53, 221, 216, 50, 220,
        200, 39, 207, 213, 52, 220, 216, 50, 220 
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += expectedOrigImageBytes[i];
    }

    unsigned char encryptedImageBytes[] = {
        60, 90, 93, 241, 230, 60, 122, 214, 108, 53, 
        253, 63, 33, 143, 147, 216, 192, 16
    };

    runAlgorithm(mode, encryptedImageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);

    char *result = "success";

    for(int i = 0; i < numberOfImageBytes; i++) {
        if(encryptedImageBytes[i] != expectedOrigImageBytes[i]) {
            result = "failure";
            printf("error at byte %d, expected: %u, actual %u", i, expectedOrigImageBytes[i], encryptedImageBytes[i]);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

void test2x3ImageEncryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test2x3ImageEncryption ----");
    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = ENC_MODE;

    int encryptionRounds = 2;

    unsigned char origImageBytes[] = {
        201, 40, 208, 214, 53, 221, 216, 50, 220,
        200, 39, 207, 213, 52, 220, 216, 50, 220 
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }

    unsigned char expectedEncryptedImageBytes[] = {
        60, 90, 93, 241, 230, 60, 122, 214, 108, 53, 
        253, 63, 33, 143, 147, 216, 192, 16
    };

    runAlgorithm(mode, origImageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);

    char *result = "success";

    for(int i = 0; i < numberOfImageBytes; i++) {
        if(origImageBytes[i] != expectedEncryptedImageBytes[i]) {
            result = "failure";
            printf("error at byte %d, expected: %u, actual %u", i, expectedEncryptedImageBytes[i], origImageBytes[i]);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

void testExecutionTime(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]){
    printf("\n---- testExecutionTime ----");

    int height = 100;
    int width = 100;
    int numberOfImageBytes = height*width*3;
    printf("\nnumber of image bytes %d\n", numberOfImageBytes );

    unsigned char origImageBytes[numberOfImageBytes];

    printf("creating image sequence");
    for(int i = 0; i < (height*width); i++) {
        origImageBytes[i*3] = 67;
        origImageBytes[i*3+1] = 76;
        origImageBytes[i*3+2] = 243;
    }

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }
    printf("starting encryption");

    clock_t begin = clock();
    runAlgorithm(ENC_MODE, origImageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, 1);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nResult: took %0.15f seconds\n", time_spent);
}


int main(int argc, char* argv[]) {
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

    diffuSetups[0].miu = 0.600000000000001;
    diffuSetups[0].x = 0.350000000000001;
    diffuSetups[0].y = 0.350000000000002;

    diffuSetups[1].miu = 0.600000000000002;
    diffuSetups[1].x = 0.360000000000001;
    diffuSetups[1].y = 0.360000000000002;

    test5x5ImageEncryption(permSetups, diffuSetups);
    test5x5ImageDecryption(permSetups, diffuSetups);
    test2x3ImageEncryption(permSetups, diffuSetups);
    test2x3ImageDecryption(permSetups, diffuSetups);

    //testExecutionTime(permSetups, diffuSetups); 

    return 0;
}


