
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagecipher2.h"
#include "time.h"


void test2x8ImageEncryption() {

    printf("\n---- test2x8ImageEncryption ----");

    unsigned char key[] = {
        49, 50, 51, 52, 53, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 0
    };

    unsigned char origImageBytes[] = {
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255,
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255,
    };

    unsigned char expectedEncryptedImageBytes[] = {
        145, 105, 220, 160, 194, 136, 240, 174, 201, 135, 235, 167, 192, 134, 237, 172,
        202, 138, 233, 165, 193, 134, 237, 173, 200, 139, 241, 170, 194, 133, 208, 120

    };

    int numberOfImageBytes = 32;

    PTF("key: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", key[i]);
    }
    PTF("\n--------\n")

    PTF("origImageBytes: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", origImageBytes[i]);
    }
    PTF("\n--------\n")

    PTF("expectedEncryptedImageBytes: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", expectedEncryptedImageBytes[i]);
    }
    PTF("\n--------\n")

    AlgorithmParameter params = generateInitialContitions(key);

    PTF("\nParams: c = %d, x = %0.15f\n", params.C, params.X);

    encrypt(&params, origImageBytes, numberOfImageBytes, key);

    PTF("actual: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", origImageBytes[i]);
    }
    PTF("\n--------\n")

    PTF("Done encrypting");

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


int main(int argc, char* argv[]) {

    test2x8ImageEncryption(); 

    return 0;
}


