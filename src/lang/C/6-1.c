#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// SSD //
unsigned long long int SSD(unsigned long long  n)
{
	return((3*n*n*n*n+2*n*n*n-3*n*n-2*n)/(12));
}
// end SSD //

int main(int argc, char *argv[])
{
	unsigned long long	n=0;
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
	printf("%llu\n", SSD(n));
	exit(0);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
