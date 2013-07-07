#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// findMaxExponent //
int64_t findMaxExponent(void)
{
	FILE		*f;
	uint64_t	i, b, e, maxI = 0;
	long double	val, maxVal = 0;
	char		c;
	
	if((f = fopen("p99.txt", "r")) == NULL) goto error0;
	for(i=0; i<1000; i++) {
		fscanf(f, "%llu%c%llu", &b, &c, &e);
		val = e*logl(b);
		if(val > maxVal) { maxVal = val; maxI = i; }
	}
	fclose(f);
	return(maxI + 1);
error0:
	return(-1);
}
// end findMaxExponent //

int main(int argc, char *argv[])
{
	int64_t	x;
	
	x = findMaxExponent();
	printf("%lld\n", x);	
	exit(0);
// error0:
	exit(-1);
}
