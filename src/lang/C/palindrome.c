#include <config.h>
#include "dlmalloc/dlmalloc.h"
#include <math.h>
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
	palindromeN 		n;
	uint64_t			intN;
	struct mallinfo		smi, emi;

	smi = mallinfo();
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
	CU_ASSERT((intN = palindromeInteger(n)) == 12344321);
	if(intN != 12344321) printf("intN = %llu\n", intN);
	
	emi = mallinfo();

	CU_ASSERT(smi.uordblks == emi.uordblks);
	if(smi.uordblks != emi.uordblks) printf("memory lost = %u\n", (int)(emi.uordblks - smi.uordblks));
	return;
// error0:
	CU_FAIL("no test");
	return;
}

void unit_palindromeSuccessor(void)
{
	palindromeN	n;
	int			i;
	
	n.a = 0; n.b = 0;
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 1 && n.b == 0);
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 2 && n.b == 0);

	n.a = 9; n.b = 0;
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 1 && n.b == 1);

	n.a = 9; n.b = 1;
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 10 && n.b == 0);
	if(n.a != 10 || n.b != 0) printf("a = %llu, b = %lld\n", n.a, n.b);

	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 11 && n.b == 0);
	if(n.a != 11 || n.b != 0) printf("a = %llu, b = %lld\n", n.a, n.b);

	n.a = 99; n.b = 0;
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 10 && n.b == 1);
	if(n.a != 10 || n.b != 1) printf("a = %llu, b = %lld\n", n.a, n.b);

	n.a = 99; n.b = 1;
	palindromeSuccessor(&n);
	CU_ASSERT(n.a == 100 && n.b == 0);

	for(i=0; i<21; i++) {
		printf("%d: % .20e, % .20e, % .20e\n", i, pow(10, i), log10(pow(10, i)), log10(pow(10, i)+1));
	}
	
	return;
// error0:
	CU_FAIL("no test");
	return;
}

void unit_palindromePredecessor(void)
{
	palindromeN	n;

	n.a = 0; n.b = 0;
	palindromePredecessor(&n);
	CU_ASSERT(n.b == -1);

	n.a = 100; n.b = 1;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 999 && n.b == 0);	

	n.a = 100; n.b = 0;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 99 && n.b == 1);

	n.a = 10; n.b = 1;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 99 && n.b == 0);

	n.a = 10; n.b = 0;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 9 && n.b == 1);

	palindromePredecessor(&n);
	CU_ASSERT(n.a == 8 && n.b == 1);

	n.a = 1; n.b = 1;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 9 && n.b == 0);
	if(n.a != 9 || n.b != 0) printf("n.a = %llu, n.b = %lld\n", n.a, n.b);
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 8 && n.b == 0);

	n.a = 2; n.b = 0;
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 1 && n.b == 0);
	palindromePredecessor(&n);
	CU_ASSERT(n.a == 0 && n.b == 0);
	if(n.a != 0 || n.b != 0) printf("n.a = %llu, n.b = %lld\n", n.a, n.b);


	return;
// error0:
	CU_FAIL("no test");
	return;
}

#endif

// palindromeInteger //
uint64_t palindromeInteger(palindromeN n) {
	uint64_t	d, shift, len, i;
	char		*str;

	len = floor(log10(n.a)) + 1;
	shift = n.b == 1 ? len : len - 1;
	d = n.a * pow(10, shift);
	if((str = malloc(sizeof(char)*(len + 1))) == NULL) goto error0;
	sprintf(str, "%llu\n", n.a);
	for(i=0; i< shift; i++) {
		d += ((int)str[i] -	'0')*pow(10, i);
	}
	free(str);
	return(d);
error0:
	return(0);
}
// end palindromeInteger //

// palindromeSuccessor //
int palindromeSuccessor(palindromeN *n)
{
	double		k;

	k = log10(n->a + 1);
	if(k - floor(k) < 1e-15 && (int)k >= 1) {	// k in N
		if(n->b == PALINDROME_ODD) {
			n->a = (n->a + 1)/10;
			n->b = PALINDROME_EVEN;	
		} else {
			n->a++;
			n->b = PALINDROME_ODD;
		}
	} else { // k not in N
		n->a++;
	}
	return(0);
error0:
	return(-1);
}
// end palindromeSuccessor //

// palindromePredecessor //
int palindromePredecessor(palindromeN *n) 
{
	double	k;

	if(n->a == 0 && n->b == PALINDROME_ODD) {
		n->b = PALINDROME_UNDEF;
		return(0);
	}
	if(n->a == 1 && n->b == PALINDROME_ODD) {
		n->a--;
		return(0);
	}
	k = log10(n->a);
	if(k - floor(k) < 1e-15) {
		if(n->b == PALINDROME_ODD) {
			n->a--;
			n->b = PALINDROME_EVEN;
		} else {
			n->a = (n->a - 1)*10 + 9;
			n->b = PALINDROME_ODD;
		}
	} else {
		n->a--;
	}
	
	return(-1);
}
// end palindromePredecessor //
