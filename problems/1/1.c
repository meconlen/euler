#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	unsigned long long	q=0, r=0, n=0;
	unsigned long long	mq, mr, mqr, sum;
	char			copt;	

	while((copt = getopt(argc, argv, "n:q:r:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg)-1;
				break;
			case	'q':
				q = atoll(optarg);
				break;
			case	'r':
				r = atoll(optarg);
				break;	
			default:
				goto usage;
		}
	}
	if(n == 0 || q == 0 || r == 0) goto usage;

	mq = n/q;
	mr = n/r;
	mqr = n/(q*r);
	sum = q*(mq*(mq+1))/2 + r*(mr*(mr+1))/2 - (q*r)*(mqr*(mqr+1))/2;
	printf("%lld\n", sum);
	exit(0);
usage:
	fprintf(stderr, "%s -n N -q Q -r R\n", argv[0]);
	exit(-1);
}
