#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

FILE *pFile = NULL;


int time_loop(double* n_i, const double r, const double K, const double A, const int tmax,
              const int dt, const double tol, const int iter_max){

  double kn_i, kn_ii;
  int count;
  double aux = (r * dt);

  for(count = 0; count < tmax/dt; count++){
    kn_i = n_i[count];

    /*
      call iteration_loop function
    */
    if(!iteration_loop(n_i[count], &kn_i, aux, K, A, dt, tol, iter_max))
      printf("\n WARNING: The method did not converge with %d iterations. \n", iter_max);

    /*
      Updates the approximation of the time step with the value obtained in the iterative process
    */
    n_i[count+1] = kn_i;
  }

  pFile = fopen("output_1_newton.dat", "w");
  if(!pFile){
    printf("\n FILE ERROR: Could not open the file. \n");
    return 0;
  }
  printf(pFile, "N \n");

  for(count = 0; count < tmax/dt; count++){
    fprintf(pFile, "%d \t %.12lf\n", (count * dt), n_i[count]);
  }
  fclose(pFile);
  return 1;
}

int iteration_loop(double n_i, double* kn_i, const double aux, const double K, const double A,
                   const int dt, const double tol, const int iter_max){

  double kn_ii;
  double b = *kn_i; // Auxiliar
  int count = 0;

  do{
    /*
      Equation for the iterative process using Picard
    */
    kn_ii = n_i / ( 1 - (aux*b)*(1/A + 1/K) + aux + (aux/(K*A))*(b*b) );

    /*
      Equation for the iterative process using Newton
    */
    //kn_ii = (n_i - (aux*(b*b)*(1/A + 1/K)) + (((2*aux)*(b*b*b))/(K*A))) / (1 - aux*( - 1 + (2*b*(1/A + 1/K))) - 3*((b*b)/(K*A)));

    if(abs((kn_ii - b) < tol)){
      *kn_i = kn_ii;
      return 1;
    }
    *kn_i = kn_ii;
    b = *kn_i;
    count++;
  } while(count <= 20);

  return 0;
}

int main(int argc, char *argv[]){
  /*
    Problem values
  */
  double n_0 = 300, r = 0.01;
  double K = 5000;
  double A = 200;

  /*
    Input values
  */
  int dt = atoi(argv[1]);
  int tmax = atoi(argv[2]);
  double tol = atof(argv[3]);
  int iter_max = atoi(argv[4]);

  /*
    Auxiliars vars
  */
  double n_i[tmax/dt];
  n_i[0] = n_0;

  time_loop(n_i, r, K, A, tmax, dt, tol, iter_max);

  return 1;
}
