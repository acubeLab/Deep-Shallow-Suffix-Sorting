SHELL=/bin/sh

CC=gcc

#these are for testing
#CFLAGS =-std=c99 -g -Wextra -Wall -Winline -O2

#these are for maximum speed
CFLAGS=-std=c99 -g -O3 -fomit-frame-pointer -Wextra -Wall -Winline -DDEBUG=0 -DNDEBUG=1  


.PHONY: all
all: sa32 ds unbwt bwt testlcp


# simple construction of the sa using deep-shallow suffix sort
sa32: sa32.o ds_ssort.a 
	$(CC) $(CFLAGS) -o sa32  sa32.o ds_ssort.a

# deep-shallow suffix sort algorithm with full options 
# suffix array is stored using ceil(log n) bits x entry
ds: suftest2.o ds_ssort.a 
	$(CC) $(CFLAGS) -o ds suftest2.o ds_ssort.a

# bwt using ds_ssort
bwt: bwt.c ds_ssort.a
	 $(CC) $(CFLAGS) -o bwt bwt.c ds_ssort.a 

# inverse bwt computed by bwt 
unbwt: unbwt.c
	 $(CC) $(CFLAGS) -o unbwt unbwt.c 

# compare linear time lcp construction algorithms 
# described in SWAT 04 "Two Space Saving tricks..."
testlcp: testlcp.c bwtlcp.a ds_ssort.a 
	 $(CC) $(CFLAGS) -o testlcp testlcp.c bwtlcp.a ds_ssort.a 

# archive containing the ds sort algorithm
ds_ssort.a: globals.o ds.o shallow.o deep2.o helped.o blind2.o
	ar rc ds_ssort.a globals.o ds.o shallow.o deep2.o helped.o blind2.o

# archive containing the bwt and lcp auxiliary routines 
bwtlcp.a: bwt_aux.o lcp_aux.o
	ar rc bwtlcp.a bwt_aux.o lcp_aux.o

# pattern rule for all objects files
%.o: %.c *.h
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f *.o *.a
