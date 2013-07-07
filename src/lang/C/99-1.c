#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findMaxExponent //
uint64_t findMaxExponent(void)
{
	FILE		*f;
	uint64_t	i = 1, b, e, maxI = 0;
	long double	val, maxVal = 0;
	char		c;
	
	if((f = fopen("p99.txt", "r")) == NULL) goto error0;
	while(fscanf(f, "%llu%c%llu", &b, &c, &e) != EOF) {
		val = e*logl(b);
		if(val > maxVal) { maxVal = val; maxI = i; }
		i++;
	}
	fclose(f);
	return(maxI);
error0:
	return(0);
}
// end findMaxExponent //

int main(int argc, char *argv[])
{
	uint64_t	x;
	
	x = findMaxExponent();
	printf("%llu\n", x);	
	exit(0);
// error0:
	exit(-1);
}
