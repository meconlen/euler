#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "factor.h"

int main(int argc, char *argv[])
{
	unsigned long long	digits = 3, large, small, i;
	unsigned long long	len, *list;	

	large = 0;	
	for(i=0; i<digits; i++) { 
		large += 9*pow(10, i);
	}
	large = large*large;
	small = pow(10, digits-1);
	small = small*small;
printf("large = %llu, small = %llu\n", large, small);
exit(0);
}
