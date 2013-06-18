#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <gmp.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findPaths //
int findPaths(uint64_t m, uint64_t n)
{
	mpz_t		a, b, c;

	mpz_init(a);
	mpz_init(b);	
	mpz_init(c);
	mpz_fac_ui(a, m);
	mpz_fac_ui(b, n);
	mpz_fac_ui(c, m+n);
	mpz_divexact(c, c, a);
	mpz_divexact(c, c, b);
	printf("paths = ");	
	mpz_out_str(stdout, 10, c);
	printf("\n");
	return(0);	
}
// end findPaths //

int main(int argc, char *argv[])
{
	char		copt;
	uint64_t	m = 0, n = 0;
	while((copt = getopt(argc, argv, "m:n:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg);
				break;
			case	'm':
				m = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if(m == 0 || n == 0) goto usage;
	findPaths(m, n);
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -m M -n N\n", argv[0]);
	exit(-1);
}
