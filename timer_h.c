#include "inter.h"

void *timer_h(void *hari_par){
  struct hari_par* par;
  par = (struct hari_par*)hari_par;
  float maizt;
  float maizt2; 
  
  while(1){
    sem_wait(&sem_timer);
    maizt=tic%5;
    maizt2=tic%12;
    if(maizt==0.0){
      sem_post(&sem_sched);
      //sem_post(&sem_proc_gen);
    }
    if(maizt2==0.0)
      sem_post(&sem_bal);
  }



}

