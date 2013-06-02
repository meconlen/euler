#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned long long	n = 600851475143, sn;
	unsigned long long	i,j,k;

	sn = sqrt(n);
	while(n & 1 == 0) n = n >> 1;	
	for(i=3; i< sn; i+=2) {
		while(n%i == 0) { n = n/i; sn = sqrt(n); }
	}
	printf("%llu\n", n);
	return(0);
}
