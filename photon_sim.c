#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926
#define N 1000000      // Photon Number
#define z_max 1
#define albedo 1
#define alpha 10         // Absorption coefficient
#define B 10             // Bin number


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

double rdm_theta(){
    double x = rdm_num();
    return (double) x*(PI/2);
}

double rdm_phi(){
    double x = rdm_num();
    return (double) x*(PI);
}
    

int main(){
    double *r, *theta, *phi, *x, *y, *z, *xt, *yt, *zt; // Directions to track
    int i, bin[B]; 
    double p = 0;                  // Photon counter
    double l = (double) 1/alpha;  // Mean free path
    
    // Allocating memory to pointer arrays to accommodate for large N values
    r = (double*) malloc(N * sizeof(double)); 
    theta = (double*) malloc(N * sizeof(double)); 
    phi = (double*) malloc(N * sizeof(double));
    x = (double*) malloc(N * sizeof(double)); 
    y = (double*) malloc(N * sizeof(double)); 
    z = (double*) malloc(N * sizeof(double)); 
    xt = (double*) malloc(N * sizeof(double)); 
    yt = (double*) malloc(N * sizeof(double)); 
    zt = (double*) malloc(N * sizeof(double));
    
    // Clear out solid angle bins
    for (i = 0; i < B; i++){
        bin[i] = 0;
    }
    
    // Pull random nums from exp(-t) dist. using cumulative method
    i = 0;
    while(i < N) {
        p++;
        // Generating a random photon direction
        r[i] = -log(1-rdm_num())*l;
        theta[i] = rdm_theta();
        phi[i] = rdm_phi();
        
        // Calculating xyz values produced by random r θ φ
        x[i] = (double) r[i] * cos(phi[i]) * sin(theta[i]);
        y[i] = (double) r[i] * sin(phi[i]) * sin(theta[i]);
        z[i] = (double) r[i] * cos(theta[i]);
        xt[i] = x[i]; // Total xyz values (relevant line 92)
        yt[i] = y[i];
        zt[i] = z[i];
        
        // Bin photons that immediately travel beyond z_max
        if(z[i] > z_max){
            double j = B * theta[i] / (PI/2) ;
            bin[(int) j]++;
            p++;
        } 
        else {
            
            // Do-while loop that continues ray propogation/scattering until ray's z coordinate is >1
            do {
                
                // Determining whether scattered or absorbed
                double scat_abs_check = rdm_num();
                if (scat_abs_check < albedo){
                    
                    // if scattered, new  rdm direction calculated
                    r[i] = -log(1-rdm_num())*l;
                    theta[i] = rdm_theta();
                    phi[i] = rdm_phi();
                    x[i] = (double) r[i] * cos(phi[i]) * sin(theta[i]);
                    y[i] = (double) r[i] * sin(phi[i]) * sin(theta[i]);
                    z[i] = (double) r[i] * cos(theta[i]);
                    
                    // new values added to total
                    xt[i] = xt[i] + x[i];
                    yt[i] = yt[i] + y[i];
                    zt[i] = zt[i] + z[i];
                    
                    // If new direction takes photon's total z past z_max, photon binned
                    if(zt[i] > z_max){
                        int j = B * theta[i] / (PI/2) ;
                        bin[j]++;
                    }
                }
                
                // If absorbed, photon discarded, photon counter set back 1
                else {
                    p = p-1;
                    break;
                    
                }
            }    
            while(zt[i] < z_max);
        }
    i++;
    }
    
    // Print functions
    printf("\n%.f rays made it beyond z_max\n\n", p);
    for(i = 0; i<B; i++){
        printf("%d exited with a direction between {%d-%d} degrees in the theta direction\n", bin[i], i*9, (i+1)*9);
    }
    printf("\n");
    for(i = 0; i<B; i++){
    	printf("%d,", bin[i]);
    }
}






