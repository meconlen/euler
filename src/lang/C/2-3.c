#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PHI 1.618033988749895
#define OORF 0.4472135954999579
#define RF 2.23606797749979
#define LPHI 0.48121182505960347

unsigned long long int fib(unsigned long long  n)
{
	double	Fn;

	Fn = pow(PHI, n)*OORF + 0.5; 
	return((unsigned long long)Fn);
}

int main(int argc, char *argv[])
{
	unsigned long long	j,k,Fk, Fk2;
	
	j=0; k=0;
	k = (unsigned long long)(log(4000000*RF+0.5)/LPHI);
	Fk = fib(k);
	if(Fk > 4000000) k--;
	Fk2=fib(k+2);	
	j = (Fk2 - 1)/2;
	printf("%llu\n", j);
	return(0);
}
