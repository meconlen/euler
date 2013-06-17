#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// sumPrimes //
uint64_t sumPrimes(uint64_t n)
{
	uint64_t	*list = NULL, len, rc, i, sum = 0;

	rc = sieveE(n, &list, &len);
	if(list == NULL) goto error0;
	for(i=0; i<len; i++) sum+= list[i];
	free(list);
	return(sum);
error0:
	return(0);
}
// end sumPrimes //

int main(int argc, char *argv[])
{
	uint64_t	n=0, sum = 0;
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
	sum = sumPrimes(n);
	printf("sum = %llu\n", sum);
	exit(0);
error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
