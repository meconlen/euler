#include <config.h>
#include "dlmalloc/dlmalloc.h"
#include <math.h>
#include <stdlib.h>

#include "algebra.h"

#ifdef HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#if HAVE_CUNIT_CUNIT_H

int init_algebra(void) 
{
	return(0);
}

int clean_algebra(void)
{
	return(0);
}

void unit_gcd(void)
{
	uint64_t	a, b, g;

	a = 10;
	b = 4;
	CU_ASSERT((g = gcd(a, b)) == 2);
	a = 30;
	b = 15;
	CU_ASSERT((g = gcd(a,b)) == 15);
	a = 15;
	b = 30;
	CU_ASSERT((g = gcd(a,b)) == 15);
	
	return;

// error0:
	CU_FAIL("no tests");
	return;
}
#endif

uint64_t gcd(uint64_t a, uint64_t b)
{
	uint64_t	t;
	while(b != 0) {
		t = b;
		b = a % t;
		a = t;
	}
	return(a);
}
