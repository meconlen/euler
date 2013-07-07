#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

uint64_t findMaxExponent(void)
{
	FILE		*f;
	uint64_t	i, b, e, maxI = 0;
	long double	val, maxVal = 0;
	char		c;
	
	f = fopen("p99.txt", "r");
	for(i=0; i<1000; i++) {
		fscanf(f, "%llu%c%llu", &b, &c, &e);
		val = e*logl(b);
		if(val > maxVal) { maxVal = val; maxI = i; }
	}
	fclose(f);
	return(maxI + 1);

}

int main(int argc, char *argv[])
{
	uint64_t	x;
	
	x = findMaxExponent();
	printf("%llu\n", x);	
	exit(0);
// error0:
	exit(-1);
}
