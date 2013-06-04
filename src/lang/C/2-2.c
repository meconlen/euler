#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PHI 1.618033988749895
#define OORF 0.4472135954999579

unsigned long long int fib(unsigned long long  n)
{
	double	Fn;

	Fn = pow(PHI, n)*OORF + 0.5; 
	return((unsigned long long)Fn);
}

int main(int argc, char *argv[])
{
	unsigned long long	j,k,Fk;
	
	j=0; k=0;
	while(1) {
		Fk = fib(k++);
		if(Fk > 4000000) break;
		if(Fk%2 == 0) j += Fk;
	}
	printf("%llu\n", j);
	return(0);
}
