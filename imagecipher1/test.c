
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
        104, 104, 15, 231, 253, 3, 37, 202, 184, 96, 3, 8, 70, 129, 129, 67, 32, 102, 138, 203, 
        227, 255, 250, 240, 85, 92, 88, 64, 220, 42, 113, 226, 149, 98, 163, 160, 253, 0, 101, 
        31, 44, 225, 47, 90, 250, 58, 241, 129, 176, 72, 87, 13, 189, 250, 242, 102, 255, 195, 
        83, 27, 223, 205, 144, 246, 184, 111, 200, 200, 72, 164, 223, 89, 126, 3, 237,
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

    unsigned char encryptedImageBytes[] = {
        104, 104, 15, 231, 253, 3, 37, 202, 184, 96, 3, 8, 70, 129, 129, 67, 32, 102, 138, 203, 
        227, 255, 250, 240, 85, 92, 88, 64, 220, 42, 113, 226, 149, 98, 163, 160, 253, 0, 101, 
        31, 44, 225, 47, 90, 250, 58, 241, 129, 176, 72, 87, 13, 189, 250, 242, 102, 255, 195, 
        83, 27, 223, 205, 144, 246, 184, 111, 200, 200, 72, 164, 223, 89, 126, 3, 237,
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

    return 0;
}


