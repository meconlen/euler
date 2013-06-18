#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findMaxChain //
int findChain(uint64_t n)
{
	uint64_t	collatz;

	collatz = n;
	printf("%llu -> \n", collatz);
	while((collatz = collatz % 2 == 0 ? collatz >> 1 : (3*collatz)+1) != 1) printf("%llu -> \n", collatz);
	printf("%llu\n", collatz);
	return(0);
}
// end findMaxChain //

int main(int argc, char *argv[])
{
	uint64_t	n=0;
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
	findChain(n);
		
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
