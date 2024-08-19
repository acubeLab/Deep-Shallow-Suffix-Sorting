/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
   simplesa.c
   simple program showin the usage of the deep shallow suffix sort algorithm  
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
#include <stdlib.h>
#include <stdio.h>
#include "common.h"




/* --------- prototypes ----------------- */ 
void ds_ssort(UChar *x, int *p, int n);
void set_global_variables(void);
int compute_overshoot(void);


int main(int argc, char *argv[])
{
  int c, *p, n, overshoot;
  UChar *x;
  char *fnam, *sa_filename;
  FILE *f, *g;

  if(argc!=3) {
    printf("\nUsage:\n\t%s infile safile\n\n",argv[0]);
    printf("Compute the Suffix Array of an input file of size at most ~ 2**31-1\n");
    printf("and write it to safile as a sequence of 32 bit ints\n\n"); 
    exit(1);
  }
  fnam = argv[1]; 
  sa_filename =argv[2];

  // set default values for the algorithm parameters 
  // and compute the corresponding overshoot (default is 575) 
  set_global_variables();
  overshoot = compute_overshoot();

  // ---- open output file 
  g = fopen(sa_filename,"wb");
  if(g==NULL) {
    perror(sa_filename); return 2;
  }

  /* ---------- open input file and read text ----------- */
  if (! (f=fopen(fnam, "rb"))) {
    perror(fnam); return 1;
  }
  if (fseek(f, 0L, SEEK_END)) {
    perror(fnam); return 1;
  }
  long nlong = ftell(f);
  if (nlong==0) {
    fprintf(stderr, "%s: file empty\n", fnam);
    return 0;
  }
  else if(nlong + overshoot >= (1L<<31)) {
    fprintf(stderr, "%s: file too large, max size: %ld\n", fnam, (1L<<31)-overshoot-1);
    return 2;
  }
  n = (Int32) nlong;


  // ------ allocate memory for text and sa -------
  p=malloc((n)*sizeof *p);               // sa
  x=malloc((n+overshoot)*sizeof *x);     // text with extra overshhot chars
  if (! p || ! x) {
    fprintf(stderr, "malloc failed\n"); return 1;
  }

  // ------------ read input text ---------------
  rewind(f); 
  c=fread(x, (size_t) 1, (size_t) n, f);
  if(c!=n) {
    perror("Error reading the input file"); return 1;
  }
  fclose(f);

  // ---- compute SA 
  ds_ssort(x, p, n);

  // ---- write SA as sequence of 32-bit ints
  c = fwrite(p,sizeof(*p),n,g);
  if(c!=n) {
    perror("Error writing the sa file"); return 2;
  }
  fclose(g);

  // deallocate and exit
  free(x); free(p);
  return 0;
}
