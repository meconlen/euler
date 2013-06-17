#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findTriple //
int findTriple(uint64_t n, uint64_t *a, uint64_t *b, uint64_t *c)
{
	for(*a=1; *a<n; (*a)++) {
		for(*b=0; *b<*a; (*b)++) {
			*c=n - (*a) - (*b);
			if((*a) * (*a) + (*b) * (*b) == (*c) * (*c)) return(0);
		}
	}
	return(-1);
}
// end findTriple //

int main(int argc, char *argv[])
{
	uint64_t	n, a, b, c;
	int		rc;
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
	rc = findTriple(n, &a, &b, &c);	
	if(rc == 0) printf("a = %llu, b = %llu, c = %llu, abc = %llu\n", a, b, c, a*b*c);
/*
	for(a=1; a<n; a++) {
		for(b=0; b<a; b++) {
			c=n-a-b;
			if(a*a+b*b==c*c) {
				printf("%llu^2 + %llu^2 = %llu^2\n", a*a, b*b, c*c);
				printf("a = %llu, b = %llu, c = %llu, a + b + c = %llu\n", a, b, c, a+b+c);
				printf("abc = %llu\n", a*b*c);
				exit(0);
			}
			
		}
	}
*/
	exit(0);
error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
