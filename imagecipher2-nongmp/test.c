
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagecipher2.h"
#include "time.h"

void test2x4ImageEncryption() {

    printf("\n---- test2x4ImageEncryption ----");

    unsigned char key[] = {
        49, 50, 51, 52, 53, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 0
    };

    unsigned char origImageBytes[] = {
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255,
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255
    };

    unsigned char expectedEncryptedImageBytes[] = {
        154, 124, 242, 193, 229, 177, 23, 46, 128, 107, 229, 186, 225, 172, 19, 48, 
        134, 109, 229, 184, 221, 169, 15, 44, 131, 111, 236, 187, 222, 167, 235, 188
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

void test2x4ImageDecryption() {

    printf("\n---- test2x4ImageDecryption ----");

    unsigned char key[] = {
        49, 50, 51, 52, 53, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 0
    };

    unsigned char encrypted[] = {
        154, 124, 242, 193, 229, 177, 23, 46, 128, 107, 229, 186, 225, 172, 19, 48, 
        134, 109, 229, 184, 221, 169, 15, 44, 131, 111, 236, 187, 222, 167, 235, 188
    };

    unsigned char expectedDecrypted[] = {
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255,
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255 
    };

    int numberOfImageBytes = 32;

    PTF("key: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", key[i]);
    }
    PTF("\n--------\n")

    PTF("encrypted: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", encrypted[i]);
    }
    PTF("\n--------\n")

    PTF("expectedDecrypted: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", expectedDecrypted[i]);
    }
    PTF("\n--------\n")

    AlgorithmParameter params = generateInitialContitions(key);

    PTF("\nParams: c = %d, x = %0.15f\n", params.C, params.X);

    decrypt(&params, encrypted, numberOfImageBytes, key);

    PTF("actual: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", encrypted[i]);
    }
    PTF("\n--------\n")

    PTF("Done decrypting");

    char *result = "success";

    for(int i = 0; i < numberOfImageBytes; i++) {
        if(encrypted[i] != expectedDecrypted[i]) {
            result = "failure";
            PTF("error at byte %d, expected: %u, actual %u", i, expectedDecrypted[i], encrypted[i]);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

void test3x3ImageEncryption() {

    printf("\n---- test3x3ImageEncryption ----");

    unsigned char key[] = {
        49, 50, 51, 52, 53, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 0
    };

    unsigned char origImageBytes[] = {
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255
    };

    unsigned char expectedEncryptedImageBytes[] = {
        154, 124, 242, 193, 229, 177, 23, 46, 128, 107, 229, 
        186, 225, 172, 19, 48, 134, 109, 229, 184, 221, 169, 
        15, 44, 131, 111, 236, 187, 222, 167, 235, 188, 222, 
        169, 14, 42
    };

    int numberOfImageBytes = 3*3*4;

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

    char *result = "success";

    AlgorithmParameter params = generateInitialContitions(key);

    int block = 0;
    int blockPos;
    int bytesProcessed = 0;

    while(block < 2) {

        PTF("\n-------- running block %d\n", block);
        blockPos = 0;
        unsigned char buffer[BUFFER_SIZE];
        while(blockPos < BUFFER_SIZE && bytesProcessed < numberOfImageBytes) {
            buffer[blockPos] = origImageBytes[bytesProcessed];
            blockPos++;
            bytesProcessed++;
        }

        PTF("\n%d. Params: c = %d, x = %0.15f, bytes = %d\n", block, params.C, params.X, blockPos);
        encrypt(&params, buffer, blockPos, key);

        PTF("actual: \n")
        for(int i = 0; i < blockPos; i++) {
            PTF("%u ", buffer[i]);
        }
        PTF("\n--------\n");

        PTF("Done encrypting block %d\n", block);

        for(int i = 0; i < blockPos; i++) {
            if(buffer[i] != expectedEncryptedImageBytes[block*BUFFER_SIZE+i]) {
                result = "failure";
                PTF("error at byte %d, expected: %u, actual %u", i, expectedEncryptedImageBytes[block*BUFFER_SIZE+i], buffer[i]);
                break;
            }
        }

        block++;
    }

    printf(" Result: %s ----\n", result);
}

void test3x3ImageDecryption() {

    printf("\n---- test3x3ImageDecryption ----");

    unsigned char key[] = {
        49, 50, 51, 52, 53, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 0
    };

    unsigned char expectedDecrypted[] = {
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255, 
        66, 244, 125, 255, 66, 244, 125, 255, 66, 244, 125, 255
    };

    unsigned char encryptedBytes[] = {
        154, 124, 242, 193, 229, 177, 23, 46, 128, 107, 229, 
        186, 225, 172, 19, 48, 134, 109, 229, 184, 221, 169, 
        15, 44, 131, 111, 236, 187, 222, 167, 235, 188, 222, 
        169, 14, 42
    };

    int numberOfImageBytes = 3*3*4;

    PTF("key: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", key[i]);
    }
    PTF("\n--------\n")

    PTF("encryptedBytes: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", encryptedBytes[i]);
    }
    PTF("\n--------\n")

    PTF("expectedDecrypted: \n")
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u ", expectedDecrypted[i]);
    }
    PTF("\n--------\n")

    char *result = "success";

    AlgorithmParameter params = generateInitialContitions(key);

    int block = 0;
    int blockPos;
    int bytesProcessed = 0;

    while(block < 2) {

        PTF("\n-------- running block %d\n", block);
        blockPos = 0;
        unsigned char buffer[BUFFER_SIZE];
        while(blockPos < BUFFER_SIZE && bytesProcessed < numberOfImageBytes) {
            buffer[blockPos] = encryptedBytes[bytesProcessed];
            blockPos++;
            bytesProcessed++;
        }

        PTF("\n%d. Params: c = %d, x = %0.15f, bytes = %d\n", block, params.C, params.X, blockPos);
        decrypt(&params, buffer, blockPos, key);

        PTF("actual: \n")
        for(int i = 0; i < blockPos; i++) {
            PTF("%u ", buffer[i]);
        }
        PTF("\n--------\n");

        PTF("Done decrypting block %d\n", block);

        for(int i = 0; i < blockPos; i++) {
            if(buffer[i] != expectedDecrypted[block*BUFFER_SIZE+i]) {
                result = "failure";
                PTF("error at byte %d, expected: %u, actual %u", i, expectedDecrypted[block*BUFFER_SIZE+i], buffer[i]);
                break;
            }
        }

        block++;
    }

    printf(" Result: %s ----\n", result);
}

void testConvertM1AndM2() {
    printf("\n---- testConvertM1AndM2 ----");

    int imageBytes[] = {
        0, 5, 10, 134, 254, 255
    };

    double expectedX[] = {
        0.0, 0.01960784313, 0.03921568627, 0.52549019607, 0.99607843137, 1.0
    };

    char *result = "success";

    for(int i = 0; i < 6; i++) {
        double actual = convertM1(imageBytes[i]);

        int m = actual * 100000000000;
        int k = expectedX[i] * 100000000000;

        if(m != k) {
            result = "failure";
            PTF("error at %d, expected: %d, actual: %d\n", i, k, m);
            break;
        }
    }

    printf(" Result: %s ----\n", result);
}

int main(int argc, char* argv[]) {

    test2x4ImageEncryption(); 
    test2x4ImageDecryption(); 

    test3x3ImageEncryption(); 
    test3x3ImageDecryption();

    //testConvertM1AndM2();

    return 0;
}


