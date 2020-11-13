#include "inter.h"


void *process_exec0(void* core){
  int coren=*(int*)core;
  //sem_post(&prozBil);
  while(1){
    int past=0;
    //int QT=100;
    //printf("Hasiera\n");
    sem_wait(&prozBil[coren]);
    prozesu* p=findLowPrioLastAndRemove(coren);
    //sleep(1);
    //printf("Prozesu lortua\n");
    if (p!=NULL){
      
      //printf("Prozesua ez da NULL\n");
      //printf("%d\n",p->p_prio);
      int priosave=p->p_prio;
      //int exist=removeByPID(&prozesu_ll[coren][p->p_prio], p->pid);
      //printf("Prozesu ezabatua\n");
      //printf("%d\n",p->p_time);
      //printf("Exist:%d\n",exist);
      //if (exist==1){
        //p->exec=1;
        while(p->p_time>0 && past<=QT){
          p->p_time--;
          past++;
          //printf("%d\n",p->p_time);
          sleep(1);
        }
        if(p->p_time!=0){
          insert_head(*p,coren);
          printf("           !!!!! %d prio-ko prozesuak denbora maximoa gainditu du %d corean !!!!!\n\n",    priosave, coren);
        }
        else
          printf("               !!!!! %d prio-ko prozesua amaitu da %d corean !!!!!\n\n",priosave, coren);
      //}
    }
    //else
      //printf("NULL DA\n");
  }
}


void *process_balance(void *a){
  while(1){
    //prioritatez prioritate lortu core bakoitzean zenbat prozesu
    sem_wait(&sem_bal);
    int i;
    int j;
    int core[corenum];
    for(i=0;i<140;i++){
      for(j=0;j<corenum;j++){
        core[j]=countProzesu(&prozesu_ll[j][i]);
        //if(prozesu_ll[j][i]!=NULL)
          //printf("Core %d, prio %d: %d prozesu\n",j,i,core[j]);
      }
      int handiena=0;
      for(j=0;j<corenum;j++)
        if(core[j]>core[handiena])
          handiena=j;
      int txikiena=0;
      for(j=0;j<corenum;j++)
        if(core[j]<core[txikiena])
          txikiena=j;
    
      if ((core[handiena]-core[txikiena])>1){
        //balance
        prozesu p=prozesu_ll[handiena][i]->val;
        //printf("Mugitutako prozesua %d coretik %d corera: %d\n",handiena,txikiena,p.p_prio);
        sem_wait(&prozBil[handiena]);
        removeByPID(&prozesu_ll[handiena][i], p.pid, handiena);
        insert_head(p, txikiena);
      }
      


    } 
    //aukeratu core guztietatik balio handien eta txikiena eta konparatu:
    //diferentzia 1 edo gutxiago orduan balanced
    
    //orain prozesu guztiak hartu eta coreen artean banatu edo pixkanaka gehien
    //duenetik gutxien duenera pasa?
  }


}




/*
void *process_exec1(void* a){






}


void *process_exec2(void* a){





}


void *process_exec3(void* a){





}*/
