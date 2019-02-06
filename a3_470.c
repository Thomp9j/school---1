/* Name: Jeffrey Thompson
 Due Date: Febuary 4th, 2019
 Section Number: 22362460
 Assignment Number: 3
 Total Points: 10

 Problem:

 Solution:

 Constraints:

 Data-structure used:

 Limitations:

 Errors handled: None.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct lnode {
  int pid;
  struct lnode *next;
} lnode;

int main(int argv , char argc[]){
  void getnode(lnode **ptr);
  void freenode(lnode **ptr);
  int forkproc(lnode **ptr);
  void usage(char *progname);
  lnode *list;
  getnode(&list);
  forkproc(&list);
  printf("Done: %s\n" );

}
void usage(char *progname){
   fprintf(stderr, "./%s <rep-count>\n", progname); exit(1);
 }

int forkproc(lnode **ptr){
  void getnode(lnode **ptr);
  int retpid;
  lnode *newnode, *tempptr;
  tempptr = *ptr;
while(*ptr){
  fork();
  tempptr->next = newnode;
  getnode(&newnode);
  return 1;
    if(fork() < 1){
      usage("Fork has failed: \n ");
      return 0;
    }
  }
}

/*
Problem: Given the reference to lnode , allocate memory for that node.
Solution: Use malloc to allocate the memory for *ptr. The size will be dependent on lnode.
*/

void getnode(lnode **ptr){
  if (!(*ptr = malloc(sizeof(lnode)))){
    usage("Malloc failed. \n");
  }else{
    *ptr = malloc(sizeof(lnode));
  }


}
/*
Problem: Given the reference to lnode, free that space in memory.
Solution: If the pointer is vaild, call free on it and set the ptr to NULL;
*/
void freenode(lnode **ptr){
  if(*ptr){
    free(*ptr);
    *ptr = NULL;
  }
}
