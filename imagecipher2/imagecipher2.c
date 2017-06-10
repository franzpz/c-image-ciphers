#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagecipher2.h"

static double LOGISTIC_R = 3.9;
static double DIVISOR_M1 = 1000.0;
static double PRECISION = 10000000000.0;

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

void encrypt(AlgorithmParameter *params, unsigned char *imageBytes, int numberOfImageBytes, unsigned char key[KEY_SIZE]) {

    if(numberOfImageBytes > BUFFER_SIZE)
        exit(1);

    double x = params->X;
    unsigned char lastC = params->C;

    double xn;
    double logisticSum;
    int numberOfLogisticMapRepititions;
    int nextKeyPos;

    for(int l = 0; l < numberOfImageBytes; l++) {
        nextKeyPos = (l+1) % KEY_SIZE;

        x = ((double)x + (double)lastC + (double)key[l]) / DIVISOR_M1;
        x = round(x * PRECISION) / PRECISION;

        numberOfLogisticMapRepititions = key[nextKeyPos] + lastC;

        xn = x;
        logisticSum = 0.0;
        for(int i = 0; i < numberOfLogisticMapRepititions; i++) {
            xn = LOGISTIC_R * xn * (1.0 - xn);
            logisticSum += xn;
        }

        imageBytes[l] = (((int)imageBytes[l]) + (((int)logisticSum)%256)) % 256;
        lastC = imageBytes[l];
    }

    params->X = x;
    params->C = lastC;
}

void decrypt(AlgorithmParameter *params, unsigned char *imageBytes, int numberOfImageBytes, unsigned char key[KEY_SIZE]) {

    if(numberOfImageBytes > BUFFER_SIZE)
        exit(1);

    double x = params->X;
    unsigned char lastC = params->C;

    double xn;
    double logisticSum;
    int numberOfLogisticMapRepititions;
    int nextKeyPos;

    for(int l = 0; l < BUFFER_SIZE; l++) {
        nextKeyPos = (l+1) % KEY_SIZE;

        x = ((double)x + (double)lastC + (double)key[l]) / DIVISOR_M1;
        x = round(x * PRECISION) / PRECISION;

        numberOfLogisticMapRepititions = key[nextKeyPos] + lastC;

        xn = x;
        logisticSum = 0.0;
        for(int i = 0; i < numberOfLogisticMapRepititions; i++) {
            xn = LOGISTIC_R * xn * (1.0 - xn);
            logisticSum += xn;
        }

        lastC = imageBytes[l];
        imageBytes[l] = (((int)imageBytes[l]) - (((int)logisticSum)%256)) % 256;
    }

    params->X = x;
    params->C = lastC;
}
