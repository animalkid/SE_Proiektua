#include "inter.h"

prozesu p_array[8];
int array_k=0;
void *process_gen_h(void *hari_par){
  struct hari_par* par;
  par = (struct hari_par*)hari_par;
  
  int i;
  int sartu;
  while(1){
    sartu=rand() % 100;

    if (sartu==1){

      if (array_k<8){
        prozesu p;
      
      
        p.pid=rand() % INT_MAX;
        p.p_prio=rand() % 140;
        //p.p_prio=15;
        p.p_time=rand() % 15;
        
        p.exec=0;
        
        //printf("time=%d eta prio=%d\n ",p.p_time,p.p_prio);
        //printf("PID:%d",p.pid);
        p_array[array_k]=p;
        array_k++;
        //printf("%d\n",p.pid);
      }
      //sleep(5);
  
    }
  }




}

