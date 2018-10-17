#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[]){
  int argone, argtwo, argthree, outcary, sum;
  void usage(char *progname);
  void printresult(char *label, int a);
  void halfaddr(int a, int b, int *sum, int *outcary);
  void fulladdr(int a, int b, int incary, int *sum, int *outcary);
  void rcadd4(int a, int b, int incary, int *sum, int *outcary);
  void lacadd4(int a, int b, int incary, int *sum, int *outcary);
  void evenparity3gen(int a, int *paritybit);
  void oddparity4chk(int a, int *checkbit);
  char progname[2] = "a4";
  argone = strtol(argv[1], NULL, 16);
  argtwo = strtol(argv[2], NULL, 16);
  argthree = strtol(argv[3], NULL, 16);
  if (argc != 4)
    usage(progname);
  halfaddr(argone, argtwo, &sum, &outcary);
  printresult("Sum", sum);
  printresult("Outcary", outcary);
  printf("\n");
  fulladdr(argone, argtwo, argthree, &sum, &outcary);
  printresult("Sum", sum);
  printresult("Outcary", outcary);
  printf("\n");
  rcadd4(argone, argtwo, argthree, &sum, &outcary);
  printresult("Sum", sum);
  printresult("Outcary", outcary);
  printf("\n");
  lacadd4(argone, argtwo, argthree, &sum, &outcary);
  printresult("Sum", sum);
  printresult("Outcary", outcary);
  exit(0);
}

/*
-Problem solved by this module
  If incorrect command line arguments are found, an error will be
  thrown.
-How the problem is solved by this module
  Prints usage to stderr and terminates.
-Limitations
  None
*/
void usage(char *progname){
  printf("Error: Three args must be in base 16!");
  fprintf(stderr, "./%s <rep-count>\n", progname);
  exit(1);
}

void halfaddr(int a, int b, int *sum, int *outcary){
  *outcary = (a & 1) & (b & 1);
  *sum = (a & 1) ^ (b & 1);
}

void fulladdr(int a, int b, int incary, int *sum, int *outcary){
  *sum = ((a & 1) ^ (b & 1)) ^ (incary & 1);
  *outcary = ((a & 1) & (b & 1)) | (((a & 1) ^ (b & 1)) & (incary & 1));
}

void rcadd4(int a, int b, int incary, int *sum, int *outcary){
  int out = 0, ci;
  int tempa = a >> 3;
  int tempb = b >> 3;
  out = ((tempa & 1) ^ (tempb & 1)) ^ (incary & 1);
  ci = ((tempa & 1) & (tempb & 1)) | (((tempa & 1) ^ (tempb & 1)) & (incary & 1));
  tempa = a >> 2;
  tempb = b >> 2;
  out = out << 1;
  out = out ^ (((tempa & 1) ^ (tempb & 1)) ^ (ci & 1));
  ci = ((tempa & 1) & (tempb & 1)) | (((tempa & 1) ^ (tempb & 1)) & (ci & 1));
  tempa = a >> 1;
  tempb = b >> 1;
  out = out << 1;
  out = out ^ (((tempa & 1) ^ (tempb & 1)) ^ (ci & 1));
  ci = ((tempa & 1) & (tempb & 1)) | (((tempa & 1) ^ (tempb & 1)) & (ci & 1));
  tempa = a >> 0;
  tempb = b >> 0;
  out = out << 1;
  out = out ^ (((tempa & 1) ^ (tempb & 1)) ^ (ci & 1));
  ci = ((tempa & 1) & (tempb & 1)) | (((tempa & 1) ^ (tempb & 1)) & (ci & 1));
  *sum = out;
  *outcary = ci;
}

void lacadd4(int a, int b, int incary, int *sum, int *outcary){
  int cione, citwo, cithree, tempa, tempb, tempout;
  cione = (((a & 1) | (b & 1)) & (incary & 1)) | ((a & 1) & (b & 1));
  citwo = (((a & 2) | (b & 2)) & (cione & 2)) | ((a & 2) & (b & 2));
  cithree = (((a & 4) | (b & 4)) & (citwo & 4)) | ((a & 4) & (b & 4));
  tempa = a >> 3;
  tempb = b >> 3;
  tempout = (((tempa & 1) ^ (tempb & 1)) ^ (incary & 1));
  tempout = tempout << 1;
  tempa = a >> 2;
  tempb = b >> 2;
  tempout = tempout ^ (((tempa & 1) ^ (tempb & 1)) ^ (cione & 1));
  tempout = tempout << 1;
  tempa = a >> 1;
  tempb = b >> 1;
  tempout = tempout ^ (((tempa & 1) ^ (tempb & 1)) ^ (citwo & 1));
  tempout = tempout << 1;
  tempa = a;
  tempb = b;
  tempout = tempout ^ (((tempa & 1) ^ (tempb & 1)) ^ (cithree & 1));
  *sum = tempout;
  *outcary = cithree;
}

void evenparity3gen(int a, int *paritybit){
  int tempfst = a >> 2;
  int tempnd = a >> 1;
  int temprd = a >> 0;
  *paritybit = (tempfst & 1) ^ (tempnd & 1) ^(temprd & 1);
}

void oddparity4chk(int a, int *checkbit){
  int tempfst = a >> 3;
  int tempnd = a >> 2;
  int temprd = a >> 1;
  int tempth = a >> 0;
  *checkbit = (~((tempfst & 1) ^ (tempnd & 1) ^(temprd & 1) ^ (tempth & 1)) & 1);
}
/*
void modulus4bit(int a, int *rslt){

}
*/
void mux2by1(int a, int b, int *yout){
  *yout = (~(b&1) & (a&1)) + ((b&1) & (b&1));
}
/*
void mux4by1(int a, int b, int *yout){

}
*/
void printresult(char *label, int a){
    int i, j;
    printf("%14s: ", label);
    for(i = 31, j = 0; i >= 0; i--, j++) {
        if ((j & 0x7)  == 0) putchar(' ');
        (a & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
