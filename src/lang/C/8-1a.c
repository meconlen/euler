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
	uint64_t	n=0, maxProd = 0, curProd = 1, cur, len; 
	char		copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			default:
				goto usage;	
		}
	}
	len = strlen(string);
	for(cur = 4; cur <len; cur++) {
		curProd = (string[cur - 4] - '0') * (string[cur - 3] - '0') * (string[cur - 2] - '0') * (string[cur -1] - '0') * (string[cur] - '0');
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
