#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

// sumOfAmicable //
int64_t sumOfAmicable(uint64_t n)
{
	uint64_t	i, j, *list, len, *factorList, maxPrime;
	uint64_t	*d, x = 0;

	if((d = malloc(sizeof(uint64_t)*(n+1))) == NULL) goto error0;
	for(i=1; i<=n; i++) {
		factorN(i, &list, &len);	
		if(list == NULL) goto error1;
		maxPrime = 1;
		for(j=0; j<len; j++) if(list[j] > maxPrime) maxPrime = list[j];
		if((factorList = calloc(maxPrime + 1, sizeof(uint64_t))) == NULL) goto error2;
		for(j=0; j<len; j++) factorList[list[j]]++;
		d[i] = 1;
		for(j=0; j<=maxPrime; j++) {
			if(factorList[j] != 0) {
				d[i] *= (pow(j, factorList[j]+1) - 1) / (j - 1);
			}
		}
		d[i] -=i;
		free(list);
	}
	for(i=1; i<=n; i++) {
		if(i == d[d[i]] && i != d[i]) x+=i;
	}
	free(factorList);
	free(d);
	return(x);
// error3:
	free(factorList);
error2:
	free(list);
error1:
	free(d);
error0:
	return(-1);
}
// end sumOfAmicable //

int main(int argc, char *argv[])
{
	uint64_t	n=0;
	int64_t		x;
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
	x = sumOfAmicable(n);
	printf("%llu\n", x);	
	exit(0);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
