/*
Question: Write C code for simulating a random sample of size n
	from exponential distribution using inverse cdf method.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double genUnif(double a, double b){
	return (b-a)*rand()/(RAND_MAX+1.0);
}

double genExpo(double lambda){
	return -1/lambda*log(1-genUnif(0,1));
}

int main(){
	srand(time(NULL));
	int sampleSize = 100000;
	double lambda = 0.2, t, sum = 0, ss=0, mean, var, skew, kurt;
	double m1, m2, m3, m4, m1p, m2p, m3p, m4p;
	for (int i = 0; i < sampleSize; i++){
		t = genExpo(lambda);
		m1p += t;
		m2p += t*t;
		m3p += t*t*t;
		m4p += t*t*t*t;
	}
	m1p /= sampleSize; m2p /= sampleSize; m3p /= sampleSize; m4p /= sampleSize;
	m1 = 0;
	m2 = m2p - pow(m1p,2);
	m3 = m3p - 3*m1p*m2p + 2*pow(m1p,3);
	m4 = m4p - 4*m3p*m1p + 6*m2p*pow(m1p,2) - 3*pow(m1p,4);
	mean = m1p;
	var = m2;
	skew = m3 / pow(m2,1.5);
	kurt = m4 / pow(m2,2);
	printf("mean = %lf\n", mean);
	printf("var  = %lf\n", var);
	printf("skew = %lf\n", skew);
	printf("kurt = %lf\n", kurt);
	return 0;
}

/*
Output:
		mean = 5.011575
		var  = 25.493378
		skew = 2.047891
		kurt = 9.324445
*/