
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imagecipher1.h"



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
    // image data
 /*
    // orig 5x4
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

    // orig 2x3
    unsigned char imageBytes[] = {
        201, 40, 208, 214, 53, 221, 216, 50, 220,
        200, 39, 207, 213, 52, 220, 216, 50, 220
    };
/*
    // enc 2x3 2 rounds
    unsigned char imageBytes[] = {
        241, 197, 171,  77, 121, 26, 101, 155, 186,
        226, 110,   0, 231, 214, 7, 216, 156, 25
    };*/

    int imageH = 2;
    int imageW = 3;
    int numberOfImageBytes = imageH*imageW*3;
    int mode = ENC_MODE;

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

    /*
    diffuSetups[0].miu = 0.8597000122;
    diffuSetups[0].x = 0.7733460001;
    diffuSetups[0].y = 0.6543224322;

    diffuSetups[1].miu = 0.84234123412;
    diffuSetups[1].x = 0.78225545794;
    diffuSetups[1].y = 0.66346604384;
    */

    long sumOfAllImageBytes = 2840; // set if decryption mode is on!
    if(mode == ENC_MODE) {
        sumOfAllImageBytes = 0;
        for(int i = 0; i < numberOfImageBytes; i++) {
            sumOfAllImageBytes += imageBytes[i];
        }
    }



    runAlgorithm(mode, imageBytes, numberOfImageBytes, sumOfAllImageBytes, permSetups, diffuSetups, encryptionRounds);



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
