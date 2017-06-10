#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//#define DEV 1
#define TEST 1

#ifndef __STDC_IEC_559__
    #define __STDC_IEC_559__ 1
#endif

#define BUFFER_SIZE 32
#define KEY_SIZE 32 // as unsigned char array = 256 bit

#if(DEV == 1)
    #define PTF(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF(A,...) do {} while(0);
#endif

#if(TEST == 1)
    #define PTF_IMPT(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF_IMPT(A,...) do {} while(0);
#endif

static int ENC_MODE = 1;
static int DEC_MODE = 2;

typedef struct AlgorithmParameters {
    double X;
    unsigned char C;
} AlgorithmParameter;

AlgorithmParameter generateInitialContitions(unsigned char *key);
void encrypt(AlgorithmParameter *params, unsigned char *imageBytes, int numberOfImageBytes, unsigned char *key);
void decrypt(AlgorithmParameter *params, unsigned char *imageBytes, int numberOfImageBytes, unsigned char *key);
