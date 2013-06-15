#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "sieve.h"

int main(int argc, char *argv[])
{
	uint64_t	n=0, *list, len, b;
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
	
	b = findBound(n);
	printf("bound = %llu\n", b);
	sieveE(b, &list, &len);
	if(len < n) goto error0;
	printf("%llu\n", list[n-1]);
	free(list);
	exit(0);
error0:
	printf("didn't search deep enough\n");
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
