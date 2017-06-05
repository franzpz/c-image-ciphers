
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagecipher1.h"


void test5x5ImageEncryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test5x5ImageEncryption ----");
    int imageH = 5;
    int imageW = 5;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = ENC_MODE;

    int encryptionRounds = 10;

    unsigned char origImageBytes[] = {
        215, 59, 230, 206, 50, 221, 209, 53, 224, 213, 57, 228, 205, 52, 222, 201, 48, 218, 191,
        39, 209, 194, 41, 211, 196, 44, 214, 188, 36, 206, 191, 44, 212, 181, 36, 203, 184, 37,
        205, 187, 42, 209, 179, 34, 201, 185, 44, 210, 176, 37, 202, 181, 40, 206, 185, 46, 211,
        180, 39, 205, 178, 43, 207, 168, 36, 199, 176, 41, 205, 179, 47, 210, 176, 41, 205
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }

    unsigned char expectedEncryptedImageBytes[] = {
        186, 86, 172, 105, 93, 202, 241, 58, 39, 180, 147, 224, 18, 125, 179, 201, 211, 192, 161, 
        234, 16, 68, 104, 218, 43, 103, 80, 27, 177, 188, 77, 105, 97, 89, 111, 152, 93, 229, 202, 
        40, 93, 130, 249, 70, 217, 183, 23, 186, 176, 241, 163, 108, 100, 111, 83, 11, 127, 204, 
        250, 30, 167, 87, 237, 2, 88, 176, 164, 18, 41, 125, 184, 202, 40, 125, 243
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

    int encryptionRounds = 10;

    unsigned char expectedEncryptedImageBytes[] = {
        215, 59, 230, 206, 50, 221, 209, 53, 224, 213, 57, 228, 205, 52, 222, 201, 48, 218, 191,
        39, 209, 194, 41, 211, 196, 44, 214, 188, 36, 206, 191, 44, 212, 181, 36, 203, 184, 37,
        205, 187, 42, 209, 179, 34, 201, 185, 44, 210, 176, 37, 202, 181, 40, 206, 185, 46, 211,
        180, 39, 205, 178, 43, 207, 168, 36, 199, 176, 41, 205, 179, 47, 210, 176, 41, 205
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += expectedEncryptedImageBytes[i];
    }

    unsigned char origImageBytes[] = {
        186, 86, 172, 105, 93, 202, 241, 58, 39, 180, 147, 224, 18, 125, 179, 201, 211, 192, 161, 
        234, 16, 68, 104, 218, 43, 103, 80, 27, 177, 188, 77, 105, 97, 89, 111, 152, 93, 229, 202, 
        40, 93, 130, 249, 70, 217, 183, 23, 186, 176, 241, 163, 108, 100, 111, 83, 11, 127, 204, 
        250, 30, 167, 87, 237, 2, 88, 176, 164, 18, 41, 125, 184, 202, 40, 125, 243
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

void test2x3ImageDecryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test2x3ImageDecryption ----");
    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = DEC_MODE;

    int encryptionRounds = 2;

    unsigned char expectedEncryptedImageBytes[] = {
        201, 40, 208, 200, 39, 207, 214, 53, 221,
        213, 52, 220, 216, 50, 220, 216, 50, 220
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += expectedEncryptedImageBytes[i];
    }

    unsigned char origImageBytes[] = {
        241, 197, 171,  77, 121, 26, 101, 155, 186,
        226, 110,   0, 231, 214, 7, 216, 156, 25
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

void test2x3ImageEncryption(PermutationSetup permSetups[4], DiffusionSetup diffuSetups[2]) {

    printf("\n---- test2x3ImageEncryption ----");
    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = ENC_MODE;

    int encryptionRounds = 2;

    unsigned char origImageBytes[] = {
        201, 40, 208, 200, 39, 207, 214, 53, 221,
        213, 52, 220, 216, 50, 220, 216, 50, 220
    };

    long sumOfAllImageBytes = 0;
    for(int i = 0; i < numberOfImageBytes; i++) {
        sumOfAllImageBytes += origImageBytes[i];
    }

    unsigned char expectedEncryptedImageBytes[] = {
        241, 197, 171,  77, 121, 26, 101, 155, 186,
        226, 110,   0, 231, 214, 7, 216, 156, 25
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

    diffuSetups[0].miu = 0.8597000122;
    diffuSetups[0].x = 0.7733460001;
    diffuSetups[0].y = 0.6543224322;

    diffuSetups[1].miu = 0.84234123412;
    diffuSetups[1].x = 0.78225545794;
    diffuSetups[1].y = 0.66346604384;

    test5x5ImageEncryption(permSetups, diffuSetups);
    test5x5ImageDecryption(permSetups, diffuSetups);
    test2x3ImageEncryption(permSetups, diffuSetups);
    test2x3ImageDecryption(permSetups, diffuSetups);

    return 0;
}


