#include <stdlib.h>
#include <stdio.h>

unsigned long long int fib(unsigned long long  n)
{
	if(n==0) return(0);
	if(n==1) return(1);
	return(fib(n-1) + fib(n-2));
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
