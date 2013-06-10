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

