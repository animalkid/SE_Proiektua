#include "inter.h"

int *subpro;

void *process_exec0(void* core){
  int coren=*(int*)core;
  CPU CPU;
  CPU.core=coren;
  CPU.hari=subpro[coren];
  subpro[coren]++;
  while(1){
    int past=0;
    sem_wait(&prozBil[coren]);
    prozesu* p=findLowPrioLastAndRemove(coren);
    if (p!=NULL){
      CPU.PC=p->mm.PC;
      CPU.PTBR=p->mm.pgb; 
      int priosave=p->p_prio;
      
      memcpy(&CPU.reg,&p->reg,sizeof(p->reg));
      
      int exit=0;
      nodeOrri *blokorria=CPU.PTBR;
      int orria=CPU.PTBR->val;
      int instdesp=CPU.PC;
      //if(instdesp!=0)
       //printf("\n           !!!!! Beste core subprozesu batek berreskuratu du prozesua!\n"); 


      while(exit!=1 && QT>past){
      
      

      while(instdesp>=(ORRIBLOK*FRAMETAM)){
        blokorria=blokorria->next;
        orria=blokorria->val;
        //printf("Pasatako orrira:%08X ; orri balioa:%08X\n",orria, *((int*)&PMem[orria]));
        instdesp-=ORRIBLOK*FRAMETAM;
      }
      int instruk=*(int*)&PMem[(*(int*)&PMem[orria])+instdesp];
      instdesp+=HELBIDE; 
      CPU.PC+=HELBIDE;
       
      
      
      //printf("\nInstruk: %08X\n",instruk);

      switch((instruk >> 28) & 0x0F){
        case 0: 
                //printf("LD eragiketa\n");
                CPU=erag(0,instruk,CPU);
                sleep(2);
                past+=2; 
                break;
        case 1: 
                //printf("ST eragiketa\n");
                CPU=erag(1,instruk,CPU);   
                sleep(2);
                past+=2;
                break;
        case 2: 
                //printf("Add eragiketa\n");
                CPU=erag(2,instruk,CPU);
                sleep(1);
                past++;
                break;
        case 15: 
                //printf("EXIT:%08X\n",instruk);
                exit=1; 
                
                
                break;


      }


      }

        if(exit==1){
          printf("               !!!!! %d prio-ko prozesua amaitu da %d corean !!!!!\n\n",priosave, coren);
          sem_wait(&sem_ezab);
          memEzab(p);
          sem_post(&sem_ezab);
        }
        else{
          printf("\n           !!!!! %d prio-ko prozesuak denbora maximoa gainditu du %d corean !!!!!\n",    priosave, coren);
          p->mm.PC=CPU.PC;
          memcpy(&p->reg,&CPU.reg,sizeof(p->reg));
          insert_head(*p,coren);
        }


        /*while(p->p_time>0 && past<=QT){
          p->p_time--;
          past++;
          sleep(2);
        }
        if(p->p_time!=0){
          insert_head(*p,coren);
          printf("           !!!!! %d prio-ko prozesuak denbora maximoa gainditu du %d corean !!!!!\n\n",    priosave, coren);
        }
        else
          printf("               !!!!! %d prio-ko prozesua amaitu da %d corean !!!!!\n\n",priosave, coren);
      */ 
    }
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




CPU erag(int op, int  instruk, CPU cpu){
  int despor, blokor, addr, pframe, desp, addrval, page;
  int r, r1, r2, r3;
  nodeOrri *norri;
  switch(op){
    case 0:
      r=(instruk >> 24) & 0x0F;
      addr= instruk & 0x00FFFFFF;
      pframe=addr/FRAMETAM;//kontuan izan frame-ak eta desplazamenduak 0-n hasten direla
      desp=addr%FRAMETAM;
      blokor=pframe/FRAMEHELB;
      despor=pframe%FRAMEHELB;

     


      norri=cpu.PTBR;

      for(int i=0;i<blokor;i++)
        norri=norri->next;
  



      page=*((int*)&PMem[norri->val+despor*HELBIDE]);
      
      addrval=*((int*)&PMem[page+desp]);
      
      cpu.reg[r]=addrval;
      //printf("pos: %08X ;addrval:%d\n", page+desp, addrval);
  
      return cpu;   
      
      break;



    case 1:
      r=(instruk >> 24) & 0x0F;
      addr= instruk & 0x00FFFFFF;
      pframe=addr/FRAMETAM;//kontuan izan frame-ak eta desplazamenduak 0-n hasten direla
      desp=addr%FRAMETAM;
      blokor=pframe/FRAMEHELB;
      despor=pframe%FRAMEHELB;



      norri=cpu.PTBR;

      for(int i=0;i<blokor;i++)
        norri=norri->next;

      page=*((int*)&PMem[norri->val+despor*HELBIDE]);
      
      *((int*)&PMem[page+desp])=cpu.reg[r];

      addrval=*((int*)&PMem[page+desp]);

      //printf("pos: %08X ;addrval:%d\n", page+desp, addrval);

      return cpu;

      break;

    case 2:
      r1=(instruk >> 24) & 0x0F;
      r2=(instruk >> 20) & 0x0F;
      r3=(instruk >> 16) & 0x0F;
      cpu.reg[r1]=cpu.reg[r2]+cpu.reg[r3];
    
      //printf("Batuketa:%d\n",cpu.reg[r1]);


      return cpu;

      break;

  }





}




void memEzab(prozesu *p){
  
  int frameak=p->framekop;
  nodeOrri *orriak=p->mm.pgb;
  int h=p->mm.pgb->val;

  while(orriak!=NULL){
    for(int i=0;i<ORRIBLOK;i++){
      int balioa=*((int*)&PMem[orriak->val+i*HELBIDE]);
      
      if(balioa==0){
        break;
      }
      
      nodeFree *previous=NULL;
      nodeFree *current=freeframes;
      while(current!=NULL){
        if(current->buk < balioa){
              previous=current;
              current=current->next;
        }

        else if(current->buk == balioa){
          current->buk+=FRAMETAM;

          if(current->next!=NULL){
            if(current->buk==current->next->has){
              current->buk=current->next->buk;
              current->next=current->next->next;
              if(previous!=NULL){
                previous->next=current;
              }
              else{
                freeframes=current;
              }
            }
          }
          break;
        } 
        
        else if(current->has == balioa+FRAMETAM){
          current->has-=FRAMETAM;
          if(previous!=NULL){
            if(current->has==previous->buk){
              nodeFree *preprevious=freeframes;
              while(preprevious->next->has!=previous->has)
                preprevious=preprevious->next;
              previous->buk=current->buk;
              previous->next=current->next;
              preprevious->next=previous;
            }
           }
          break;
        }

        else if(current->has > balioa+FRAMETAM){
          if (previous==NULL){
            previous=(nodeFree*) malloc(sizeof(nodeFree));
            previous->has=balioa;
            previous->buk=balioa+FRAMETAM;
            previous->next=current;
            freeframes=previous;
          }
          else{
          previous->next=(nodeFree*) malloc(sizeof(nodeFree));
          previous->next->has=balioa;
          previous->next->buk=balioa+FRAMETAM;
          previous->next->next=current;
          }
          break;

        }
        else{
          printf("BUG\n");
          break;
        }

        
      }
      if (current==NULL){
        previous->next=(nodeFree*) malloc(sizeof(nodeFree));
        previous->next->has=balioa;
        previous->next->buk=balioa+FRAMETAM;
        previous->next->next=NULL;
      }
    }
    orriak=orriak->next;
  }






  printf("Prozesu ezabatuta:\n\n");
  nodeFree *proba=freeframes;
  while(proba!=NULL){
    printf("Has:%08X ;buk:%08X\n",proba->has,proba->buk);
    proba=proba->next;
  }


orriak=p->mm.pgb;
while(orriak!=NULL){

  for(int i=0;i<ORRIBLOK;i++)
    *((int*)&PMem[orriak->val+i*HELBIDE])=0;

  orriak=orriak->next;
}


}














  
