#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "algebra.h"

int main(int argc, char *argv[])
{
	uint64_t	n=0, l=0, i; 
	char		copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if(n<3) goto usage;
	l = lcm(2, 3);
	for(i=4; i<=n; i++) {
		l = lcm(l, i);
	}
	printf("lcm = %llu\n", l);
	exit(0);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
