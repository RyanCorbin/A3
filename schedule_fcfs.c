//By Ryan Corbin and  Michael Deatley

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

void insertEnd(struct node **head, Task *newTask);//adds a task to the end of the list

struct node *H = NULL;
int n = 0;

void add(char *name, int priority, int burst){
    Task *Pnew = malloc(sizeof(Task)); //need to store when not in func call
    Pnew->burst = burst;
    Pnew->name = name;
    Pnew->priority = priority;
    Pnew->tid = n;
    n++;
    insertEnd(&H, Pnew);
}

void schedule() {
    int time = 0;//clock
    int *ta = malloc (n * sizeof *ta);//holds turn around times for tasks
    int *wt = malloc (n * sizeof *wt);//holds waiting times for tasks
    //set waiting times & turn around times to 0
    for(int i = 0; i < n; i++){
        *(ta + i) = 0;
        *(wt + i) = 0;
    }
    
    struct node *temp0 = H;
    while(temp0 != NULL){
        *(wt + (temp0->task->tid)) += time;//set waiting time
        time += temp0->task->burst;//increment clock
        *(ta + (temp0->task->tid)) += time;//set turnaround time
        temp0 = temp0->next;
    }
    //calculate avgs
    float avwt = 0, avta = 0;
    for(int i = 0; i < n; i ++){
        avwt +=  *(wt + i);
    }
    avwt /= n;
    for(int i = 0; i < n; i ++){
        avta +=  *(ta + i);
    }
    avta /= n;
    //print results
    printf("Process\t    Burst Time    \tWaiting Time\tTurnaround Time\n");
    while(H != NULL){
        printf("%s\t\t  %d\t\t    %d\t\t\t%d\n",H->task->name , H->task->burst, *(wt + (H->task->tid)), *(ta + (H->task->tid)));
        delete(&H, H->task);
    }
    printf("\nAverage Waiting Time = %.2f\n",avwt);
    printf("Average Turnaround Time = %.2f\n",avta);
}

void insertEnd(struct node **head, Task *newTask) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;  
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    struct node *Temp = *head;
    while(Temp->next != NULL){
        Temp = Temp->next;
    }
    Temp->next = newNode;
}
