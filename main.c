#include "inter.h"

unsigned char *PMem;

int proghas;

int orrihas;


void sortu_hariak(int hari_kop, int core_kop){
  int i, err;
  pthread_t *hariak_id;
  struct hari_par *h_p;
 
  hariak_id = malloc(hari_kop * sizeof(pthread_t));
  h_p = malloc(hari_kop * sizeof(struct hari_par));
  pthread_t *core_id= malloc(core_kop* 2 * sizeof(pthread_t));
  int *core_p=malloc(core_kop * sizeof(int));
  for(i = 0; i < hari_kop; i++)
      h_p[i].hari_id = i;
  pthread_create(&hariak_id[0], NULL, clock_h, (void*)&h_p[0]);;
  pthread_create(&hariak_id[1], NULL, timer_h, (void*)&h_p[1]);;
  pthread_create(&hariak_id[2], NULL, process_load_h, (void*)&h_p[2]);;
  pthread_create(&hariak_id[3], NULL, sched_h, (void*)&h_p[3]);; 
  pthread_create(&hariak_id[4], NULL, process_balance, NULL);;
  int y=0;
  for(i=0;i<core_kop;i++){
    core_p[i]=i;
    pthread_create(&core_id[y], NULL, process_exec0, (void*)&core_p[i]);;
    pthread_create(&core_id[y+1], NULL, process_exec0, (void*)&core_p[i]);;
    y=y+2;
  }
    //core_p[0]=0;
    //pthread_create(&core_id[0], NULL, process_exec0, (void*)&core_p[0]);;
    //pthread_create(&core_id[1], NULL, process_exec0, (void*)&core_p[0]);;

  for(i = 0;i < hari_kop;i++) // Ume guztiak amaitu arte
      pthread_join(hariak_id[i], NULL);
  for(i=0;i<(core_kop*2);i++)
    pthread_join(core_id[i], NULL);
  free(hariak_id);
  free(h_p);

  free(core_id);
  free(core_p);

}


int main(int argc, char *argv[]){
  
  sem_init(&sem_sched, 1, 0);
  sem_init(&sem_timer, 1, 0);
  sem_init(&sem_proc_gen, 1, 0); 
  sem_init(&sem_bal, 1, 0);  

  sem_init(&sem_ezab, 1, 0);
  sem_post(&sem_ezab);


  corenum=atoi(argv[1]);
  QT=atoi(argv[2]);
  int i;
  //sem_t *prozBil=malloc(corenum*sizeof(sem_t));
  for(i=0;i<corenum;i++){
    sem_init(&prozBil[i], 1, 0);
    sem_post(&prozBil[i]);
  }
  
  /*prozesu_ll= malloc(corenum * sizeof(node**));
  
  printf("%p\n",prozesu_ll);
  int i;
  int j;
  for(i=0;0<corenum;i++)
    prozesu_ll[i]=malloc(140 * sizeof(node*));
    for(j=0;0<140;j++)
      prozesu_ll[i][j]=malloc(sizeof(node));
  */

//hasieratu coreen hari kontroladorea
  subpro=malloc(corenum*sizeof(int));
  for(i=0;i<corenum;i++)
    subpro[i]=0;
  orrihas=0x0;
  proghas=1024*4;
//hasieratu memoria fisikoa  
  PMem=malloc(4*1024*1024);

  freeframes=(nodeFree*) malloc(sizeof(nodeFree));
  freeframes->has=proghas; 
  freeframes->buk=1024*1024*4-1;
  
  sortu_hariak(5,corenum);
  /*
  //programa amaitu ondoren nodoen matrizea askatu
  for(i=0;0<corenum;i++){
    for(j=0;0<140;j++)
      free(prozesu_ll[i][j]);
    free(prozesu_ll[i]);
  }
  free(prozesu_ll);
  */






}




