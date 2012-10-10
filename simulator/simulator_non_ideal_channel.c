#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b)       (a < b) ? (b) : (a)
#define MIN(a,b)       (a < b) ? (a) : (b)

#define B 8
#define EPSILON 0.1 //packet error probability
#define NUMBER_OF_ROUNDS 10000

main (int argc, char *argv[])
{
  int n,nn,N;
  int transmission_bin[B];
  int collision_or_error[B];
  long int round_counter;
  long int successful_transmission_counter;

  N=atoi(argv[1]);
  srand(getpid());
  successful_transmission_counter=0;
  
  // assign the first transmission for each of the stations
  // to a randomly selected bin
  for (n=0;n<N;n++)
    {
    transmission_bin[n]=rand()%B;
    }
  for (round_counter=1;round_counter<NUMBER_OF_ROUNDS;round_counter++)
    {
    // check for collisions
    for (n=0;n<N;n++)
      {
      collision_or_error[n] = 0; 
      for (nn=0;nn<N;nn++)
        {
        if ((n!=nn)&&(transmission_bin[n]==transmission_bin[nn]))
          {
          collision_or_error[n]=1;
          }
        }
      }
    // check for channel errors
    for (n=0;n<N;n++)
      {
      if (!collision_or_error[n])
        {
        if (rand()*1.0/RAND_MAX<EPSILON)
          {
          collision_or_error[n]=1;
          }
        }
      }
    // schedule next transmission
    // and count successful transmissions
    for (n=0;n<N;n++)
      {
      if (collision_or_error[n])
        {
        transmission_bin[n]=rand()%B;
        }
        else
        {
        successful_transmission_counter++;
        }
      }
    printf("%ld\n", successful_transmission_counter);
    }
  printf("%f\n", successful_transmission_counter*1.0/round_counter);
}
