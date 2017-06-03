
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void printSequence(double a[], int n);
void copyArray(double source[], double dest[], int n);
void bubbleSort(double a[], int n);

int find(double array[], double data, int length) {
   int lowerBound = 0;
   int upperBound = length -1;
   int midPoint = -1;
   int comparisons = 0;      
   int index = -1;
	
   while(lowerBound <= upperBound) {
      printf("Comparison %d\n" , (comparisons +1) );
      printf("lowerBound : %d, array[%d] = %.15f\n",lowerBound,lowerBound,
         array[lowerBound]);
      printf("upperBound : %d, array[%d] = %.15f\n",upperBound,upperBound,
         array[upperBound]);
      comparisons++;
		
      // compute the mid point
      // midPoint = (lowerBound + upperBound) / 2;
      midPoint = lowerBound + (upperBound - lowerBound) / 2;	
		
      // data found
      if(array[midPoint] == data) {
         index = midPoint;
         break;
      } else {
         // if data is larger 
         if(array[midPoint] < data) {
            // data is in upper half
            lowerBound = midPoint + 1;
         }
         // data is smaller 
         else {
            // data is in lower half 
            upperBound = midPoint -1;
         }
      }               
   }
   printf("Total comparisons made: %d" , comparisons);
   return index;
}

int main(int argc, char* argv[]) {

    double test1 = 0.174841450890799; // expected 1st 6 and 9
    double test2 = 0.946153363651837; // expected 1st 4 und 1

    printf("orig1 - %.15f\n", test2);
    printf("orig2 - %.15f\n", test1);
    
    printf("result1 - %d\n", calcGroupNumber(test2));
    printf("result2 - %d\n", calcGroupNumber(test1));


    double sortedArray[5] = { 1.234, 2.3456, 2.897, 3.45, 4.123 };

    int index = find(sortedArray, 3.45, 5);

    printf("expected: %d, actual: %d", 3, index);

	return 0;
}

int calcGroupNumber(double t) {
    double tTimes = t*1000000;

    //int result1 = ((((int)floor(tTimes * 10)) / 10) - ((int)tTimes))*10;
    int result1 = (((int)floor(tTimes)) % 10);
    //printf("tmp ttimes %.15f\n", tTimes);
    printf("tmp result 1 %d for %.15f\n", result1, t);
    int result2 = (((int)floor(tTimes * 1000)) % 10);
    printf("tmp result 2 %d for %.15f", result2, t);

    if(result1 >= result2)
        return result1-result2;
    if(result2 >= result1)
        return result2-result1;
    
    return 0;
}

void printDoubleAsBits(double decker) {
    unsigned char * desmond = (unsigned char *) & decker;
    int i;

    for (i = 0; i < sizeof (double); i++) {
         printf ("%02X ", desmond[i]);
    }
    printf ("\n");
}

void printSequence(double a[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d - %.15f\n", i, a[i]);
    }
}

void copyArray(double source[], double dest[], int n){
    for(int i = 0; i < n; i ++)
        dest[i] = source[i];
}

void bubbleSort(double a[], int n){
	for(int i=0; i<n; i++){
		int swaps=0;
		for(int j=0; j<n-i-1; j++){
			if(a[j]>a[j+1]){
				double t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				swaps++;
			}
		}
		if(swaps==0)
			break;
	}
}