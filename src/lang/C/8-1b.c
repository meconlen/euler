#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

#include "bignumber.h"

// main //
int main(int argc, char *argv[])
{
	uint64_t	i=0, n=0, maxProd = 0, curProd = 1, cur, len; 
	char		copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			default:
				goto usage;	
		}
	}
	len = strlen(string);
	for(i=0; i<len; i++) string[i] -= '0';
	for(cur = 4; cur <len; cur++) {
		curProd = string[cur - 4] * string[cur - 3] * string[cur - 2] * string[cur -1] * string[cur];
		if(curProd > maxProd) maxProd = curProd;
	}
	printf("maxProd = %llu\n", maxProd);
	exit(0);
error0:
	exit(-1);
usage:
	fprintf(stderr, "Usage: %s\n", argv[0]);
	exit(-1);
}
// end main //
