#ifndef inter_h

#define inter_h

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>



#define HELBIDE 4 //helbide baten tamaina
#define FRAMETAM 16 //frame baten tamaina
#define ORRIBLOK 4 //orri bloke batean sartzen diren orri koputua
#define FRAMEHELB 4 //frame batean sartzen diren helbide kopurua  




sem_t sem_timer;

sem_t sem_sched;

sem_t sem_proc_gen;

sem_t sem_bal;

//sem_t *prozBil;

sem_t sem_ezab;

sem_t prozBil[128];

extern int tic;

extern int QT;

extern int array_k;

struct hari_par{

  int hari_id;

};


extern int orrihas;
extern int proghas; //


//FRAME TIPOA SORTU

//extern char frame[8][4];


typedef struct nodeOrri {
  int val;
  struct nodeOrri * next;
} nodeOrri;


typedef struct nodeFree {
  int has;
  int buk;
  struct nodeFree * next;
} nodeFree;

extern nodeFree *freeframes;

typedef struct memMan{
  
  int PC; 
  unsigned int data;
  unsigned int code;
  nodeOrri *pgb;

}memMan;

//malloc-ekin hasieratu
extern unsigned char *PMem;

//int **VMem;



typedef struct CPU{
  
  int core;
  int hari;
  nodeOrri *PTBR;
  int PC;
  int IR;
  int reg[15];

}CPU;






extern int *subpro;

typedef struct prozesu{

  //int bukhelb;  
  int framekop;
  int pid;
  int p_prio;
  //int p_time;
  int reg[15];
  memMan mm;


}prozesu;


extern prozesu p_array[8];

typedef struct node {
  prozesu val;
  struct node * next;
} node;

extern node *head;







void insert_head(prozesu val, int core);

void print_list(node * head);

void push_end(node * head, prozesu val);

void push_first(node ** head, prozesu val);

int remove_first(node ** head, int core);

void remove_last(node * head);

int remove_by_index(node ** head, int n);

int removeByPID(node ** head, int PID, int core);

prozesu* findLowPrioLastAndRemove(int core);

int countProzesu(node ** head);



extern int corenum;

//node ***prozesu_ll;

node *prozesu_ll[128][140];


static pthread_mutex_t prmutex = PTHREAD_MUTEX_INITIALIZER;

void *clock_h(void *hari_par);

void *timer_h(void *hari_par);

void *process_gen_h(void *hari_par);

void *process_load_h(void *hari_par);

void *sched_h(void *hari_par);

void process_disp_h(prozesu p);



void *process_exec0(void *core);

void *process_balance(void *a);

CPU erag(int op, int instruk, CPU cpu);

void memEzab(prozesu *p);

#endif
