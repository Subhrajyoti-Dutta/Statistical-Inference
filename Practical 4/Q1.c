#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double genUnif(double a, double b) {
	return (b - a) * rand() / (RAND_MAX + 1.0);
}

double genExpo(double lambda) {
	return -1 / lambda * log(1 - genUnif(0, 1));
}

int main() {
	int numOfSample = 1000, sampleSize;
	double theta;
	printf("Input the size of samples: ");
	scanf("%d", &sampleSize);
	printf("Input the value of theta: ");
	scanf("%lf", &theta);


	double sum, mean, theta_cap, MSE = 0;
	for (int n = 0; n < numOfSample; n++) {
		sum = 0;
		for (int i = 0; i < sampleSize; i++) {
			sum += genExpo(theta);
		}
		mean = sum / sampleSize;
		theta_cap = 1 / mean;
		MSE += pow(theta - theta_cap, 2);
	}
	MSE /= numOfSample;

	printf("For theta = %lf and %d samples, the MSE is %lf\n", theta, numOfSample, MSE);
	return 0;
}

/*
Output:
		Input the number of samples: 10
		Input the value of theta: 0.5
		For theta = 0.500000 and 10 samples, the MSE is 0.000338
*/