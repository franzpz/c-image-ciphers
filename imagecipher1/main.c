
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "imagecipher1.h"

#define MAX_FILE_PATH_LENGTH 512

int main(int argc, char* argv[]) {

    // -- reading input parameters
    if(argc < 5) {
        printf("no file path provided and/or mode 1 = encryption, 2 = decryption, usage <path> <mode> <width> <height> <channels> <optional sum of orig image bytes>");
        exit(1);
    }

    char filePath[MAX_FILE_PATH_LENGTH];

    if (strlen(argv[1]) >= MAX_FILE_PATH_LENGTH) {
        fprintf(stderr, "%s is too long!\n", argv[1]);
        exit(1);
    }
    else
        strcpy(filePath, argv[1]);

    int mode = atoi(argv[2]);
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    int channels = atoi(argv[5]);
    long sumOfAllImageBytes = 0;

    if(mode == DEC_MODE) {
        if(argc < 6) {
            fprintf(stderr, "decryption requires sum of all bytes of orig image\n");
            exit(1);
        }
        sumOfAllImageBytes = atol(argv[6]);
    }

    /*int rounds = 5;
    if(argc == 4)
        rounds = atoi(argv[3]);*/

    PTF_IMPT("\nusing file: %s\n", filePath);

    char convFilePath[MAX_FILE_PATH_LENGTH+15];
    strcpy(convFilePath, filePath);

    if(mode == DEC_MODE) {
        strcat(convFilePath, ".decrypted.txt");
        PTF_IMPT("running decryption\n");
    }
    else if(mode == ENC_MODE){
        strcat(convFilePath, ".encrypted.txt");
        PTF_IMPT("running encryption\n");
    }

    FILE *origFile = fopen(filePath, "r");
    if (origFile == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        exit(1);
    }

    int numberOfImageBytes = width * height * channels;
    PTF_IMPT("number of bytes expected: %d\n", numberOfImageBytes);

    unsigned char* imageBytes = (unsigned char*)malloc(sizeof(unsigned char)*numberOfImageBytes);
    int curByte;

    PTF_IMPT("reading file ... \n");

    fscanf(origFile, "%d", &curByte);

    int k = 0;
    while(!feof(origFile)) {
        imageBytes[k] = (unsigned char)curByte;
        fscanf(origFile, "%d", &curByte);
        k++;
    }

    #ifdef DEV
    PTF("read bytes [\n")
    for(int i = 0; i < k; i++ )
        PTF("%u, ", imageBytes[i]);
    PTF("] \n");
    #endif

    numberOfImageBytes = k;

    fclose(origFile);

    PTF_IMPT("done reading file, got %d bytes; expected %d bytes! \n", k, numberOfImageBytes);

    /**/
/*
    long sumOfAllImageBytes = 0;

    // for the encryption we need the size of the image
    // and for the decryption we need the sum of the image bytes of the plain image,
    // therefore I inserted this testdata below

    // usage:
    // uncomment the block you want to test, we currently have orig 2x3 uncommented, which encrypts the given bytes
    // the bytes are RGB values of the pixel of an image

    // orig 5x5
    int mode = ENC_MODE;
    int imageH = 5;
    int imageW = 5;
    unsigned char imageBytes[] = {
		67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76,
		243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67,
		76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243, 67, 76, 243,
		67, 76, 243, 67, 76, 243,
    };

    // enc 5x5 2 rounds
    sumOfAllImageBytes = 9650;
    int mode = DEC_MODE;
    int imageH = 5;
    int imageW = 5;
    unsigned char imageBytes[] = {
        9, 29, 41, 153, 71, 68, 153, 25, 162, 182, 26, 67, 154, 91, 99, 92, 44, 239, 174, 125, 56, 98, 193,
        32, 62, 97, 62, 34, 80, 193, 83, 6, 243, 116, 70, 84, 10, 172, 144, 168, 176, 134, 110, 204, 252, 41,
        142, 66, 156, 210, 85, 8, 193, 122, 57, 128, 124, 152, 158, 247, 15, 16, 177, 242, 206, 232, 176, 174,
        41, 223, 102, 186, 125, 112, 29
    };


    // orig 2x3
    int mode = ENC_MODE;
    int imageH = 2;
    int imageW = 3;
    unsigned char imageBytes[] = {
        201, 40, 208, 214, 53, 221, 216, 50, 220,
        200, 39, 207, 213, 52, 220, 216, 50, 220
    };*/
 /*
    // enc 2x3 2 rounds
    sumOfAllImageBytes = 2840; // set if decryption mode is on!
    int mode = DEC_MODE;
    int imageH = 2;
    int imageW = 3;
    unsigned char imageBytes[] = {
        60, 90, 93, 241, 230, 60, 122, 214, 108,
        53, 253, 63, 33, 143, 147, 216, 192, 16
    };

    int numberOfImageBytes = imageH*imageW*3;*/
    int encryptionRounds = 2;

    // values would have to be based on an key phrase or similar
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

    if(mode == ENC_MODE) {
        sumOfAllImageBytes = 0;
        for(int i = 0; i < numberOfImageBytes; i++) {
            sumOfAllImageBytes += imageBytes[i];
        }
    }

    // measure overall time
    clock_t begin = clock();

    runAlgorithm(mode, imageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    PTF_IMPT("\ntook total %0.15f seconds\n", time_spent);

    FILE *convFile = fopen(convFilePath, "w");
    if (convFile == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", convFilePath);
        exit(1);
    }

    PTF("\n---- Writing : [\n");
    for(int i = 0; i < numberOfImageBytes; i++) {
        PTF("%u, ", imageBytes[i]);
        fprintf(convFile, "%d ", (int)imageBytes[i]);
    }
    PTF("] ----\n")

    return 0;
}
