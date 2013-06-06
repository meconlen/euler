#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "factor.h"

int main(int argc, char *argv[])
{
	unsigned long long	n = 600851475143, i, d=0; 
	unsigned long long	len, *list;	

/*
	sn = sqrt(n);
	while((n & 1) == 0) n = n >> 1;	
	for(i=3; i< sn; i+=2) {
		while(n%i == 0) { n = n/i; sn = sqrt(n); }
	}
*/
	factorN(n, &list, &len);
	for(i=0; i<len; i++) {
		if(d<list[i]) d = list[i];
	}
	printf("%llu\n", d);
	return(0);
}
