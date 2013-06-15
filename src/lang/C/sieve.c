#include <config.h>
#include "dlmalloc/dlmalloc.h"
#include <math.h>
#include <stdlib.h>

#include "sieve.h"

#ifdef HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#if HAVE_CUNIT_CUNIT_H

int init_sieve(void) 
{
	return(0);
}

int clean_sieve(void)
{
	return(0);
}

void unit_sieveE(void)
{
	int	rc;
	uint64_t	*list, len, i;
	uint64_t	primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	
	CU_ASSERT((rc = sieveE(2, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT(len == 1);
	if(list == NULL) goto error1;
	CU_ASSERT(list[0] == primes[0]);
	if(list[0] != primes[0]) printf("list[0] = %llu, should be %llu\n", list[0], primes[0]);
	free(list);

	CU_ASSERT((rc = sieveE(4, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT(len == 2);
	for(i=0; i<2; i++) CU_ASSERT(list[i] == primes[i]);
	free(list);

	CU_ASSERT((rc = sieveE(8, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT(len == 4);
	for(i=0; i<4; i++) CU_ASSERT(list[i] == primes[i]);
	free(list);

	CU_ASSERT((rc = sieveE(16, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT(len == 6);
	for(i=0; i<6; i++) CU_ASSERT(list[i] == primes[i]);
	free(list);

	return;
error1:
	CU_FAIL("list = NULL");
	free(list);
error0:
	CU_FAIL("Tests Short Curited on Failure");
	return;
}

// Tests found using Mathematica FindRoot on f(x)

void unit_findBound(void)
{
	uint64_t r;

	CU_ASSERT((r = findBound(10001)) == 106571);
	CU_ASSERT((r = findBound(1001)) == 8109);	
	CU_ASSERT((r = findBound(2001)) == 17764);
	return;
}
#endif

// findBound //
uint64_t findBound(uint64_t n)
{
	long double	x, y, lx;

	if(n<599) n = 599;
	x = n*logl(n);
	while(1) {
		lx = logl(x);
		y = x + ( lx * (-x -x * lx + n * lx * lx)) / ( -2 + lx * lx);
		if(fabsl(y-x)< 1e-1) return((uint64_t)round(y));
		x = y;
	}
}
// end findBound //

// sieve //
int sieveE(uint64_t x, uint64_t **list, uint64_t *len)
{
	uint64_t	i, j, count=0;
	uint64_t	*s;
	
	if(x < 2) goto error0;
	if((s = calloc(x+1, sizeof(uint64_t))) == NULL) goto error0;
	s[0] = 1; s[1] = 1;
	for(i=2; i<=x; i++) {
		for(j=2; j*i<=x; j++) {
			s[i*j] = 1;
		}
	}
	*len = 0;
	for(i=2; i<=x; i++) if(s[i] == 0) (*len)++;
	if((*list = malloc(sizeof(uint64_t)* *len)) == NULL) goto error1;
	for(i=2; i<=x; i++) if(s[i] == 0) (*list)[count++] = i;

	free(s);
	return(0);
error1:
	free(s);
error0:
	return(-1);
}	
// end sieve //
