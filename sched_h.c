#include "inter.h"

void *sched_h(void *hari_par){
  struct hari_par* par;
  par = (struct hari_par*)hari_par;
  int proba=0;
  int coren=0;
   
  while(1){
    sem_wait(&sem_sched);
    proba++;
    //printf("JASOTA%d!\n",proba);
    //printf("Arraya:");
    
    printf("         [1:%d | 2:%d | 3:%d | 4:%d | 5:%d | 6:%d | 7:%d | 8:%d]\n\n",p_array[0].p_prio,p_array[1].p_prio,p_array[2].p_prio,p_array[3].p_prio,p_array[4].p_prio,p_array[5].p_prio, p_array[6].p_prio, p_array[7].p_prio);
    int k;
    int y;
    for (y=0;y<corenum;y++){
      
      printf("                             -----------Core%d-----------\n",y);

      for(k=0;k<140;k++){
        if(prozesu_ll[y][k]!=NULL){
          printf("                             Lista %d:",k);
          print_list(prozesu_ll[y][k]);
        } 
      }
      printf("                            -----------------------------\n\n");
    }
    printf("\n");
    
    int i; 

/*
    for(i=orrihas;i<orrihas+200;i+=4)
      printf("0x%08X 0x%08X\n",i,*((int*)&PMem[i]));

    for(i=proghas;i<proghas+200;i+=4)
      printf("0x%08X 0x%08X\n",i,*((int*)&PMem[i]));
*/  
    
    if (array_k>0){
      int i=0;
      int j;
      while(i<corenum){
        if (array_k>0){
          insert_head(p_array[0],coren);
          for (j=0;j<array_k;j++)
            p_array[j]=p_array[j+1];
          array_k--;
          coren++;
          i++;
          if (coren==corenum)
            coren=0;
        }
        else
          i++;
      }  
    }

  }


}

