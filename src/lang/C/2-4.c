#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
	unsigned long long	n=0, j,k,Fk, Fk2;
	char				copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if(n==0) goto usage;
	j=0; k=0;
	k = (unsigned long long)(log(n*RF+0.5)/LPHI);
	Fk = fib(k);
	if(Fk > n) k--;
	k -= k%3;
	Fk2=fib(k+2);	
	j = (Fk2 - 1)/2;
	printf("%llu\n", j);
	exit(0);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
