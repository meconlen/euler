#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif

#include "queue.h"

int main() 
{
#if HAVE_CUNIT_CUNIT_H
	CU_pSuite pSuite = NULL;

	if(CU_initialize_registry() != CUE_SUCCESS) goto error0;

	if((pSuite = CU_add_suite("queueElement", init_queueElementUnit, clean_queueElementUnit)) == NULL) goto error1;
	
	if((CU_add_test(pSuite, "queueElementCreate()", unit_queueElementCreate)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueElementDestroy()", unit_queueElementDestroy)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueElementDestroyFree()", unit_queueElementDestroyFree)) == NULL) goto error1;

	if((pSuite = CU_add_suite("queue", init_queueUnit, clean_queueUnit)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueCreate()", unit_queueCreate)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueCopy()", unit_queueCopy)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueEnqueue()", unit_queueEnqueue)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueDequeue()", unit_queueDequeue)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueLength()", unit_queueLength)) == NULL) goto error1;
	if((CU_add_test(pSuite, "queueDestroy()", unit_queueDestroy)) == NULL) goto error1;
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

error1:
	CU_cleanup_registry();
error0:
	return(CU_get_error());
#endif
}

