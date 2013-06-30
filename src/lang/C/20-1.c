#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <gmp.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// factorialDigitSum //
uint64_t factorialDigitSum(uint64_t n)
{
	char		*line = NULL, *cursor;
	mpz_t		f;
	uint64_t	x = 0, digits;

	mpz_init(f);
	mpz_fac_ui(f, n);
	digits = mpz_sizeinbase(f, 10);
	line = calloc(digits+2,sizeof(char));
	mpz_get_str(line, 10, f);
	cursor = line;
	while(*cursor != 0) x += (*(cursor++) - '0');
	free(line);
	return(x);	
}
// end factorialDigitSum //

int main(int argc, char *argv[])
{
	char		copt;
	uint64_t	n, x;

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

	x = factorialDigitSum(n);
	printf("sum = %llu\n", x);
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
