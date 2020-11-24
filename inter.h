#ifndef inter_h

#define inter_h

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>


sem_t sem_timer;

sem_t sem_sched;

sem_t sem_proc_gen;

sem_t sem_bal;

//sem_t *prozBil;


sem_t prozBil[128];

extern int tic;

extern int QT;

extern int array_k;

struct hari_par{

  int hari_id;

};


/*
typedef struct prozesu{
  
  int pid;
  memMan mm;

}prozesu;

typedef struct memMan{
  
  int data;
  int code;
  int pgb;
}memMan;

//malloc-ekin hasieratu
int **PMem;

//int **VMem;


//int PTBR[128][2];

typedef struct CPU{
  
  int core;
  int hari;
  int PTBR;
  int PC;
  int IR;

}CPU;




*/



typedef struct prozesu{
  
  int pid;
  int p_prio;
  int p_time;

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

void *sched_h(void *hari_par);

void process_disp_h(prozesu p);



void *process_exec0(void *core);

void *process_balance(void *a);


#endif
