#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEV 1
#define TEST 1

#define BUFFER_SIZE 256
#define KEY_SIZE 32 // as unsigned char array = 256 bit

#ifdef DEV
    #define PTF(A,...) printf(A,##__VA_ARGS__);
#else
    #define PTF(A,...) do {} while(0);
#endif

#ifdef TEST
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
void encrypt(AlgorithmParameter *params, unsigned char *imageBytes, unsigned char *key);
