  /* Name: Jeffrey Thompson
   Due Date: Febuary 1st, 2019
   Section Number: 22362460
   Assignment Number: 3
   Total Points: 10

   Problem: Generate unique integers using a random number generator. How do you generate random numbers? Even and odd integers will be placed into sepereate
   lists using bit-wiseoperators. How can the program determine if an integer is even or odd using bit-wiseoperator?. If an integer is generated that is already
   in a list, that integer will be removed. If an integer is not in a list add it to the appropriate list. How can the program remove and add to the lists at
   runtime? Also how can the program determine if a node is to be inserted in to a list , or removed from one? How can the program show that the lists are correct
   and are being added to and deleted from?


   Solution: To generate random integers the program will use the rand() system call, rand() returns an integer from 0 - MAX_RANGE.The function accomplishing
   this task will be nextnum. This will random number generator will be seeded in main(). To determine if an integer is even or odd with bit-wise operators
   only the least significant bit will be checked. If the bit is a 1 the number will be odd. If the bit is 0 the number will be even as all the other bits
   are multiples of 2. When added together they cannont be odd. Since memory must be allocated dynamically for the constant changing of the lists, the free()
   system function needs to be called in order to remove integers nodes in a list. This task will carried out by the freenode(). Alternativly creating a node
   should be done with malloc(), this will be accomplished by the function getnode(). In order to determine if the numbers generated should be added to a list
   a function insertinlist() should be written. To determine if a node should be removed from a list a function delfromlist() should be written. In order to verify
   the lists are working as intended the function printlist() should be written. This function will print the lists to the terminal.

   Constraints: Modulo arithmetic is not allowed to determine if a odd/even number (use bit-wiseoperators). No head/dummy nodes are allowed
   for this singly linked list. No specification violations are allowed (ie., no change of function name, return type, count of parameters,
   data type of parameters etc.). Function declarations are not allowed in the global scope(declare it in the module called).Memory is NOT
   preallocated for the lists.

   Data-structure used: Two singly linked lists. One list containing unique random even integers (levens). The other containing unique odd integers
   (lodds).

   Limitations: If a number is generated that is already in one of the lists, the program will remove the integer from that list.

   Errors handled: None.

*/

#include <stdlib.h>
#include <stdio.h>

#define RANGE 5
typedef struct lnode lnode;
struct lnode {

int value;
struct lnode *next;

};



/* Seeds random number generator too! */
int main(int argc, char *argv[]){
  void usage(char *progname);
  int nextnum();
  void getnode(lnode **ptr);
  void freenode(lnode **ptr);
  void search(lnode *list, lnode **crnt, lnode **pred, int x);
  int insertinlist(lnode **list, int x);
  void printlist(lnode *list);
  void freelist(lnode **list);

  int  argone , i, valuegen;

  char progname[2] = "a3";

  lnode *levens;
  getnode(&levens);


  for(i = 0; i < 10; i++){
    valuegen = nextnum();
      printf("done: %s%d\n", valuegen);
    if(valuegen  % 2 == 0){
      insertinlist(&levens, valuegen);
    }
    }

    printlist(&levens);


    freelist(&levens);



}


/* Prints usage to stderr and terminates */
void usage(char *progname){
   fprintf(stderr, "./%s <rep-count>\n", progname); exit(1);
 }

/* Generates the next number */
int nextnum(){
   return (rand() % RANGE);
  }

/* Gets a node for list using malloc(). The caller should check
for call failure */
void getnode(lnode **ptr){
    *ptr = malloc(sizeof(lnode));
  }

/* Returns node storage to system using free(). */
void freenode(lnode **ptr){
  if(*ptr) free(*ptr);
  *ptr = NULL;
  }

/* Searches list for node containing x, if found crnt is
defined and pred points to crnt’s predecessor node.
Crnt is undefined otherwise and pred has no meaning. */
void search(lnode *list, lnode **crnt, lnode **pred, int x){
  *crnt = list;
  *pred = NULL;

    while(*crnt) {
        if((*crnt)->value == x) return;
        *pred = *crnt;
        *crnt = (*crnt)->next;
  }
}
  /*
  Problem: Given the address to the address of list and an integer x, use the address to call the search function to find if the integer is contained in the list.
  If the integer is in the list delete it. If it is not add the integer to the front of the list. Return 1 if the integer is added 0 if it is deleted.

  Solution: Create 3 temp pointers to be used in the search function. Create an int found which will be used in a do while loop. Found will be acting as an end
  condition for our do while. The search function sets current to undefined if it is not found and defined if it has a value. at the end of the search tempcurrent
  will be updated and we will check it in an if statement. if it is greater than 0 the value was found and we have to remove that node in the list. Else the value
  is undefined and we must add the value to the list and update the list.

  Inserts x at the front of list if found in list, deletes it
  from the list otherwise. Returns 1 on success, 0 otherwise,
  calls search()
  */
int insertinlist(lnode **list, int x){

  void search(lnode *list, lnode **crnt, lnode **pred, int x);

  int found ;
  found = 0;

  lnode *templist, **tempcurr , **temppred;
  templist = *list;

  do {
    search( templist ,  tempcurr , temppred,  x);
    if  ( tempcurr > 0){
      freenode(tempcurr);
      found = 1;
      return 1;
    }else{

      lnode *newnode = malloc(sizeof(lnode));
      newnode->value = x;
      newnode->next = templist;
      found = 1;
      return 0;
    }
  } while(found < 1 );
  return 1;
}

/* Deletes the node from list that is successor of the node
pointed by after. Returns 1 on success, 0 otherwise.)
*/

/* Prints the contents of given list (on one line on stdout) */
void printlist(lnode *list){
while(list != NULL){
  fprintf(stdout, "%s%d\n",list->value );
  list = list->next;
}
}

/* Returns the node storage to system for nodes in the list, one
node at a time. Calls freenode(). Returns empty list to caller. */
void freelist(lnode **list){

  lnode *ptr, *tp;
  ptr = *list;

  while(ptr) {
  tp = ptr;
  ptr = ptr->next;

  freenode(&tp);
  }
  *list = NULL;
  }
