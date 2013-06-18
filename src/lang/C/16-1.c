#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <gmp.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findSum //
int findSum(uint64_t n)
{
	char		*line = NULL, *cursor;
	mpz_t		exp;
	uint64_t	x = 0, digits;

	mpz_init(exp);
	mpz_ui_pow_ui(exp, 2, n);
	digits = mpz_sizeinbase(exp, 10);
	line = calloc(digits+2, sizeof(char));
	mpz_get_str(line, 10, exp);
	cursor = line;
	while(*cursor != 0) x += (*(cursor++) - '0');
	free(line);
	return(x);	
}
// end findSum //

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

	x = findSum(n);
	printf("sum = %llu\n", x);
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
