#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findMaxChain //
int findMaxChain(uint64_t n, uint64_t *maxCount, uint64_t *maxI)
{
	uint64_t	curCount = 0, i, collatz;

	for(i=2; i<n; i++) {
		curCount = 1;
		collatz = i;
		do curCount++; while((collatz = collatz % 2 == 0 ? collatz >> 1 : (3*collatz) + 1 ) != 1);
		if(curCount > *maxCount) { *maxCount = curCount; *maxI = i; }
	}
	return(0);
}
// end findMaxChain //

int main(int argc, char *argv[])
{
	uint64_t	n=0,  maxCount = 0, maxI = 0;
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
	if(n == 0) goto usage;
	findMaxChain(n, &maxCount, &maxI);
	printf("maxCount = %llu, maxI = %llu\n", maxCount, maxI);
		
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
