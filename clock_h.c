#include "inter.h"

int tic=0;


void *clock_h(void *hari_par){
  struct hari_par* par;
  par = (struct hari_par*)hari_par;
  while(1){
    sleep(1);
    tic++;
    sem_post(&sem_timer);

  }

}


