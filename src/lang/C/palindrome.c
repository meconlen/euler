#include <config.h>
#include <stdlib.h>

#include "palindrome.h"

#ifdef HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#if HAVE_CUNIT_CUNIT_H

int init_palindrome(void)
{
	return(0);
}

int clean_palindrome(void)
{
	return(0);
}

void unit_palindromeInteger(void)
{
	palindromeN 	n;
	uint64_t	intN;

	n.a = 10;
	n.b = 0;	// odd
	CU_ASSERT((intN = palindromeInteger(n)) == 101);
	
	n.a = 12;
	n.b = 1;
	CU_ASSERT((intN = palindromeInteger(n)) == 1221);

	n.a = 123;
	n.b = 0;
	CU_ASSERT((intN = palindromeInteger(n)) == 12321);

	n.a = 1234;
	n.b = 1;
	CU_ASSERT((intN = palindromeInteger(n)) == 1234321);
	return;
// error0:
	CU_FAIL("no test");
	return;
}

void unit_palindromeSuccessor(void)
{
	CU_FAIL("no test");
	return;
}

void unit_palindromePredecessor(void)
{
	CU_FAIL("no test");
	return;
}

#endif

uint64_t palindromeInteger(palindromeN n) {
	return(0);
}

int palindromeSuccessor(palindromeN *n)
{
	return(-1);
}
int palindromePredecessor(palindromeN *n) 
{
	return(-1);
}

