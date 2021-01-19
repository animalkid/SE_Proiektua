#include "inter.h"

prozesu p_array[8];
int array_k=0;
void *process_load_h(void *hari_par){
  struct hari_par* par;
  par = (struct hari_par*)hari_par;
  int i;
  int prog_zenb=0;
  int sartu;
  while(1){
    sartu=rand() % 100;

    if (sartu==1){

      if (array_k<8){
        prozesu p;

        prog_zenb= rand() %49;
        //prog_zenb= 0;
        p.pid=rand() % INT_MAX;
        p.p_prio=rand() % 140;
        //p.p_time=rand() % 15;
        
        memMan manager;
       
        manager.pgb=NULL;

        manager.PC=0x0;

        int prog[100];

        char prog_iz[20];
        sprintf(prog_iz,"program/prog%03d.elf",prog_zenb);

        FILE *f=fopen(prog_iz, "r");
        
        //heracles-en gehienez 80 lerro izan ditzazkete, beraz 80koa egin dut.
        char ler[80]; 
          
         
        fscanf(f, "%s %X", ler, &manager.code);
        if (strncmp(ler, ".text",5))
          printf(".text falta da!\n");

        fscanf(f, "%s %X", ler, &manager.data);
        if (strncmp(ler, ".data",5))
          printf(".data falta da!\n");

        int i=2;
        while (fscanf(f, "%8X", &prog[i])!=EOF){
          i++;
        }
        prog[0]=manager.code;
        prog[1]=manager.data;

        int inst=2;
        int framekop=0;
        int frametot=0;
        int orripos=orrihas;
        int orriblokean=0;
        nodeOrri *nodoakt;

        while(prog[inst]!=0){
          if(freeframes!=NULL){
            
            
            sem_wait(&sem_ezab);
            
            int pos;
            framekop++;
            frametot++;

            if(orriblokean==0){
       	      while(*((int*)&PMem[orripos])!=0){
                orripos+=FRAMETAM;
       	  
       	      } 
              memcpy(PMem+(orripos),&freeframes->has,HELBIDE);
              
              nodoakt=manager.pgb;
              if(manager.pgb==NULL){
                manager.pgb=(nodeOrri *) malloc(sizeof(nodeOrri));
                manager.pgb->val=orripos;  
                manager.pgb->next=NULL;
              }else{
                while(nodoakt->next!=NULL)
                  nodoakt=nodoakt->next;
                nodoakt->next=(nodeOrri *) malloc(sizeof(nodeOrri));
                nodoakt->next->val=orripos;
                nodoakt->next->next=NULL;

              }
              
            /*  nodeOrri *proba=manager.pgb;
              while(proba!=NULL){

                printf("%d\n",proba->val);
                proba=proba->next;
              }*/


              orripos+=HELBIDE;
              orriblokean=1;
            }
            else{ 
       	      memcpy(PMem+(orripos),&freeframes->has,HELBIDE); 
              orripos+=HELBIDE;
            }

            if (framekop==FRAMEHELB){
              orriblokean=0;
              framekop=0;
            }
            
            for(pos=0;pos<FRAMEHELB;pos++){
              memcpy(PMem+(freeframes->has+(pos*HELBIDE)),prog+(inst+pos),HELBIDE);
               
              //printf("helb:0x%X  %08X %08X\n",h+pos*4, prog[inst+pos], *((int*)&PMem[h+(pos*4)]));
            }
            inst+=HELBIDE;
            

            freeframes->has+=FRAMETAM;
            if (freeframes->has==freeframes->buk)
              freeframes=freeframes->next;

            if(freeframes->has==1024*1024*4)
              freeframes=NULL;

            
          }
            sem_post(&sem_ezab);
        }      

/*
        nodeFree *proba=freeframes;
        printf("Prozesu sortu eta gero:\n");
        while(proba!=NULL){
          printf("Has:%08X; buk:%08X\n",proba->has, proba->buk);
          proba=proba->next;
        }
*/
        p.framekop=frametot;

        p.mm=manager;

        p_array[array_k]=p;
        array_k++;
      }
//break;
//sleep(2);
    }


  }




}




