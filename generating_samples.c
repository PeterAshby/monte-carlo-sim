#include <stdio.h>
#include <math.h>

#define PI 3.14159265359
#define N 10000
#define B 10
#define X 5

// Minimum standard generator outputting random numbers {0-1}
double rdm_num (){
  static long long seed = 1;
  static int a, c, m;
  a = 16807;
  c = 0;
  m = 2147483647;

  seed = (a * seed + c) % m;
  return (double) seed / m;
}

// Normalised exponential function
float probx (float x){
  float A = sqrt (2);
  return (float) exp (-x);
}

int main (){
  int i;
  float x[N], y[N], xc[N], yc[N];
  int n;
  int bin[B], binc[B];
  int k;
    
    // Clear out bins
    for (i = 0; i < B; i++){
        bin[i] = 0; // Rejection bins
        binc[i] = 0; // Cumulative bins
    }
    
    // REJECTION DISTRIBUTION GENERATION
    for (i = 0; i <= N; i++){
        x[i] = X * rdm_num ();
        y[i] = sqrt(2) * rdm_num ();
      
        // Filter random numbers according to exp. fuinction
        if (y[i] > probx (x[i])){
	        y[i] = 0;
	        x[i] = 0;
	        n++;
        }
        
        // Filter out zeroed elements, also adds count to bins
        if (x[i] > 0){
	        k = x[i] * B / X;
	        bin[k]++;
	    }
    }
    
    // CUMULATIVE DISTRIBUTION GENERATION
    for (i = 0; i <= N; i++){
        yc[i] = rdm_num ();
        xc[i] = -log(1-yc[i]);
	
	// Add counts to bin (no need for filters!)
	k = xc[i] * B/X ;
	binc[k]++;
    }
    
    printf(" Rej. x   Rej. y   Cum. x   Cum. y\n====================================\n");
    for (i = 0; i < N; i++){
        printf("%f,%f,%f,%f\n", x[i], y[i], xc[i], yc[i]);
    }
    
    // Return Distribution throughout bins
    
    printf("\nRejection Distribution (%d values rejected)\n=============================================\n", n);
    for (i = 0; i < B; i++){
        printf ("%d, ", bin[i]);
    }
    printf("\n\nCumulative Distribution\n=======================\n");
    for (i = 0; i < B; i++){
        printf ("%d, ", binc[i]);
    }
    return 0;
}




