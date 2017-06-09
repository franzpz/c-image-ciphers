#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagecipher2.h"

static double LOGISTIC_R = 3.9;

AlgorithmParameter generateInitialContitions(unsigned char key[KEY_SIZE]) {
    AlgorithmParameter param;

    double r = 0;
    param.C = 0;

    for(int i = 0; i < KEY_SIZE; i++) {
        r += ((double)key[i])/1000.0;
        param.C = (param.C + key[i]) % 256;
    }

    param.X = r - floor(r);

    return param;
}

void encrypt(AlgorithmParameter *params, unsigned char imageBytes[BUFFER_SIZE], unsigned char key[KEY_SIZE]) {

    double x = params->X;
    unsigned char lastC = params->C;

    long double xn;
    long double logisticSum;
    int numberOfLogisticMapRepititions;

    for(int l = 0; l < BUFFER_SIZE; l++) {
        x = ((double)(x+(double)lastC+(double)key[l]))/1000.0;
        numberOfLogisticMapRepititions = key[l+1] + lastC;

        xn = x;
        logisticSum = 0.0;
        for(int i = 0; i < numberOfLogisticMapRepititions; i++) {
            xn = LOGISTIC_R * xn * (1 - xn);
            logisticSum += xn;
        }

        imageBytes[l] = (imageBytes[l] + (((int)logisticSum)%256)) % 256;
        lastC = imageBytes[l];
    }
}
