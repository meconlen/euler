#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

#include "ds/queue.h"

// findMaxChain //
#define MEMO_SIZE	2147483648
int findMaxChain(uint64_t n, uint64_t *maxCount, uint64_t *maxI)
{
	uint64_t	curCount = 0, i, j, collatz, *z, *memo, length, base;
	size_t		zlen = 2048, zCursor = 0;
	queue		*q;

	uint64_t	maxVal = 0;

	if((memo = (uint64_t *)mmap(NULL, (MEMO_SIZE)*sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED) goto error0;
	if((q = queueCreate(NULL)) == NULL) goto error1;
	if((z = malloc(sizeof(uint64_t)*zlen)) == NULL) goto error2;
	memo[0] = 0; memo[1] = 1;
	*maxCount = 1; *maxI = 1;
	for(i=2; i<=n; i++) {
		collatz = i;
		curCount = 1;
		while(collatz > MEMO_SIZE || memo[collatz] == 0) {
			z[zCursor++] = collatz;
			if(zCursor == zlen) {
				if((z = realloc(z, sizeof(uint64_t)*zlen*2)) == NULL) goto error2;
				zlen *=2;
			}
			collatz = collatz % 2 == 0 ? collatz >> 1 : (3*collatz) + 1; 
			if(collatz > maxVal) maxVal = collatz;
		}
		base = memo[collatz];
		length = zCursor;
		if((base + length) > *maxCount) { *maxCount = base + length; *maxI = i; }
		for(j=0; j<length; j++) {
			if(z[j] < MEMO_SIZE) memo[z[j]] = base + length - j;
		}
		zCursor = 0;
	}
	free(z);
	queueDestroy(q);
	munmap(memo, (n+1)*sizeof(uint64_t));
	return(0);
	free(z);	
error2:
	queueDestroy(q);
	goto error1b;
error1:
	perror("mmap");
error1b:
	munmap(memo, (n+1)*sizeof(uint64_t));
error0:
	return(-1);
}
// end findMaxChain //

int main(int argc, char *argv[])
{
	uint64_t	n=0,  maxCount = 0, maxI = 0;
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
	rc = findMaxChain(n, &maxCount, &maxI);
	if(rc == 0) printf("maxCount = %llu, maxI = %llu\n", maxCount, maxI); else printf("failed\n");
		
	exit(0);
// error0:
	exit(-1);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
