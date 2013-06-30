#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

uint64_t	triangle[] = { 
3,
7, 4,
2, 4, 6,
8, 5, 9, 3
};

#define ROWS 4

int main(int argc, char *argv[])
{
	uint64_t	n=0, max, j, k, l, r, *distance;
	char		copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if((distance = calloc((ROWS*(ROWS+1))/2, sizeof(uint64_t))) == NULL) goto error0;	
	distance[0] = 0;
	for(j=1; j<ROWS; j++) {
		distance[(j*(j+1))/2] = distance[(j*(j-1))/2] + triangle[(j*(j-1))/2];
		distance[(j*(j+1))/2 + j] = distance[(j*(j-1))/2 + (j-1)] + triangle[(j*(j-1))/2 + (j-1)];
		for(k=1; k<j; k++) {
			l = distance[(j*(j-1))/2 + k-1] + triangle[(j*(j-1))/2 + k - 1];
			r = distance[(j*(j-1))/2 + k] + triangle[(j*(j-1))/2 + k];
			distance[(j*(j+1))/2 + k] = l > r ? l : r;
		}
	}	
	max = 0;
	for(j=0; j<ROWS; j++) {
		if(triangle[(ROWS*(ROWS-1))/2 + j] + distance[(ROWS*(ROWS-1))/2 + j] > max) max = triangle[(ROWS*(ROWS-1))/2 + j] + distance[(ROWS*(ROWS-1))/2 + j];
	}
	printf("max = %llu\n", max);
	exit(0);
error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
