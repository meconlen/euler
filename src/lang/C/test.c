#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#include "factor.h"

int main() 
{
#if HAVE_CUNIT_CUNIT_H
	CU_pSuite pSuite = NULL;

	if(CU_initialize_registry() != CUE_SUCCESS) goto error0;

	if((pSuite = CU_add_suite("factor", init_factor, clean_factor)) == NULL) goto error1;
	
	if((CU_add_test(pSuite, "factorN()", unit_factorN)) == NULL) goto error1;

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

error1:
	CU_cleanup_registry();
error0:
	return(CU_get_error());
#endif
}

