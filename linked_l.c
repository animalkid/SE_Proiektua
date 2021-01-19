//HEMENDIK HARTUTA
//https://www.learn-c.org/en/Linked_lists


#include "inter.h"

node * head = NULL;

//node ***prozesu_ll;


nodeFree *freeframes;



node *prozesu_ll[128][140];


int QT;
int corenum;

void insert_head(prozesu val,int core) {
   //create a link
   node *save= (node*) malloc(sizeof(node));
	
   
   save->val = val;
	 save->next=prozesu_ll[core][val.p_prio];
   prozesu_ll[core][val.p_prio]=save;
}


void print_list(node * head) {
    node * current = head;
    //printf("Lista:");
    while (current != NULL) {
        printf("%d ", current->val.p_prio);
        current = current->next;
    }
    
    printf("| %d prozesu\n",countProzesu(&head));
}

void push_end(node * head, prozesu val) {
    node * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node *) malloc(sizeof(node));
    current->next->val = val;
    current->next->next = NULL;
}

void push_first(node ** head, prozesu val) {
    node * new_node;
    new_node = (node *) malloc(sizeof(node));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int remove_first(node ** head, int core) {
    //prozesu retval;
    node * next_node = NULL;

    if (*head == NULL) {
        sem_post(&prozBil[core]);
        return -1;
    }

    next_node = (*head)->next;
    //retval = (*head)->val;
    //free(*head);
    *head = next_node;
    sem_post(&prozBil[core]);
    return 1;
}


void remove_last(node * head) {
     //prozesu retval;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        //retval = head->val;
        free(head);
        //return 1;
    }

    /* get to the second to last node in the list */
    node * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    //retval = current->next->val;
    free(current->next);
    current->next = NULL;
    //return 1;

}

/*int remove_by_index(node ** head, int n) {
    int i = 0;
    //prozesu retval;
    node * current = *head;
    node * temp_node = NULL;

    if (n == 0) {

        return remove_first(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    //retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return 1;

}*/

int removeByPID(node ** head, int PID, int core){
  node *current=*head;
  node *before;
  if (current->val.pid==PID)
    return remove_first(head, core);
  while (current->val.pid!=PID){
    if(current->next==NULL){
      sem_post(&prozBil[core]);
      return -1;
    }
    before=current;
    current=current->next;
  }
  before->next=current->next;
  sem_post(&prozBil[core]);
  return 1;
  


}
prozesu* findLowPrioLastAndRemove(int core){
  node *current;
  int i=0;
  int found=0;
  while(i<140 && found==0){
    if (prozesu_ll[core][i]!=NULL){
      //printf("AURKITUA\n");
      found=1;
    }
    else
      i++;
  }
  if (found==0){
    sem_post(&prozBil[core]);
    return NULL;
  }
  
  current=prozesu_ll[core][i];
  //printf("Currentean sartua\n");
  while(current->next!=NULL){
    current=current->next;
  }
  //printf("Whileko bukaera\n current:%p\n ",current);

  //printf("%p\n",&current->val);
  
  prozesu* p=&current->val;

  if(removeByPID(&prozesu_ll[core][i],current->val.pid,core)==1) 
  //printf("%p\n",p);
  //printf("Ezabatuta\n");
    return p;
  //return &current->val;
  else
    return NULL;
}


int countProzesu(node ** head){
  node *current=*head;
  int i=0;
  while(current!=NULL){
    i++;
    current=current->next;
  }
  return i;



}


