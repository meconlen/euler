#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findTriangle //
uint64_t findTriangle(uint64_t n)
{
	uint64_t	i, j, sum, *list, len, *factorList, maxPrime, divisors = 1;
	for(i=1; ; i++) {
		sum = (i*(i+1))/2;
		factorN(sum, &list, &len);
		maxPrime = 0;	
		for(j=0; j<len; j++) if (list[j] > maxPrime) maxPrime = list[j];
		factorList = calloc(maxPrime + 1, sizeof(uint64_t));
		for(j=0; j<len; j++) factorList[list[j]]++;
		divisors=1;
		for(j=0; j<len; j++) {
			divisors = divisors * (factorList[list[j]]	+ 1);
			factorList[list[j]] = 0;
		}
		free(list);
		free(factorList);
		if(divisors > n) break;
	}
	return(sum);
}
// end findTriangle //

int main(int argc, char *argv[])
{
	uint64_t	n=0, sum;
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
	sum = findTriangle(n);
	printf("sum = %llu\n", sum);
	
	exit(0);
error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
