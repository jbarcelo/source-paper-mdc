#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b)       (a < b) ? (b) : (a)
#define MIN(a,b)       (a < b) ? (a) : (b)

#define B 8

main (int argc, char *argv[])
{
  int n,nn,N;
  int transmission_bin[B];
  int collision_sta[B];
  int collision_flag;
  long int round_counter;

  N=atoi(argv[1]);
  srand(getpid());
  
  // assign the first transmission for each of the stations
  // to a randomly selected bin
  for (n=0;n<N;n++)
  {
    transmission_bin[n]=rand()%B;
  }
  for (round_counter=1;1;round_counter++)
  {
    // print transmission positions
    //for (n=0;n<N;n++)
    //{
    //  printf("%d ",transmission_bin[n]);
    //}
    //printf("\n");
    // check for collisions
    collision_flag=0;
    for (n=0;n<N;n++)
    {
      collision_sta[n] = 0; 
      for (nn=0;nn<N;nn++)
        {
        if ((n!=nn)&&(transmission_bin[n]==transmission_bin[nn]))
          {
          collision_sta[n]=1;
          collision_flag=1;
          }
        }
    }
    // print collisions
    //for (n=0;n<N;n++)
    //{
    //  printf("%d ",collision_sta[n]);
    //}
    //printf("\n\n");
    if (!collision_flag)
      {
      break;
      }
    // assign next tx bin
    for (n=0;n<N;n++)
    {
      if (collision_sta[n])
        {
        transmission_bin[n]=rand()%B;
        }
    }
  }
  printf("%ld\n", round_counter);
}
