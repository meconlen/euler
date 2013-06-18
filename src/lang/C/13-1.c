#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <gmp.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

int main(int argc, char *argv[])
{
	char		copt, *line = NULL;	
	size_t		linecap = 0;
	mpz_t		input, sum;
	uint64_t	i;	
	FILE		*f;

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			default:
				goto usage;	
		}
	}
	mpz_init(input);
	mpz_init(sum);	
	mpz_set_ui(sum, 0);
	f = fopen("p13.txt", "r");
	for(i=0; i<100; i++) {
		getline(&line, &linecap, f);
		mpz_set_str(input, line, 10);
		mpz_add(sum, sum, input);
	}	
	printf("sum = ");
	mpz_out_str(stdout, 10, sum);
	printf("\n");
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
