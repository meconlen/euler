#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

int main() 
{
#if HAVE_CUNIT_CUNIT_H
	CU_pSuite factorSuite = NULL, palindromeSuite = NULL, algebraSuite = NULL, sieveSuite = NULL;

	if(CU_initialize_registry() != CUE_SUCCESS) goto error0;

	if((sieveSuite = CU_add_suite("sieve", init_sieve, clean_sieve)) == NULL) goto error1;
	if((CU_add_test(sieveSuite, "sieveE()", unit_sieveE)) == NULL) goto error1;
	if((CU_add_test(sieveSuite, "findBound()", unit_findBound)) == NULL) goto error1;

	if((algebraSuite = CU_add_suite("algebra", init_algebra, clean_algebra)) == NULL) goto error1;
	if((CU_add_test(algebraSuite, "gcd()", unit_gcd)) == NULL) goto error1;
	if((CU_add_test(algebraSuite, "lcm()", unit_lcm)) == NULL) goto error1;
	
	if((factorSuite = CU_add_suite("factor", init_factor, clean_factor)) == NULL) goto error1;
	if((CU_add_test(factorSuite, "factorN()", unit_factorN)) == NULL) goto error1;
	if((CU_add_test(factorSuite, "twoFactor()", unit_twoFactor)) == NULL) goto error1;

	if((palindromeSuite = CU_add_suite("palindrome", init_palindrome, clean_palindrome)) == NULL) goto error1;
	if((CU_add_test(palindromeSuite, "palindromeInteger", unit_palindromeInteger)) == NULL) goto error1;
	if((CU_add_test(palindromeSuite, "palindromeSuccessor", unit_palindromeSuccessor)) == NULL) goto error1;
	if((CU_add_test(palindromeSuite, "palindromePredecessor", unit_palindromePredecessor)) == NULL) goto error1;
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

error1:
	CU_cleanup_registry();
error0:
	return(CU_get_error());
#endif
}

