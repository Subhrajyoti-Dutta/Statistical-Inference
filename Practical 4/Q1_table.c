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

double MSE_expo(int numOfSample, int sampleSize, double theta) {
	double sum, mean, theta_cap, t, MSE;
	for (int n = 0; n < numOfSample; n++) {
		sum = 0;
		for (int i = 0; i < sampleSize; i++) {
			t = genExpo(theta);
			sum += t;
		}
		mean = sum / sampleSize;
		theta_cap = 1 / mean;
		MSE += pow(theta - theta_cap, 2);
	}
	MSE /= numOfSample;
	return MSE;
}

int main() {
	srand(time(NULL));
	int i, j, numOfSamples = 1000;
	int sampleSize[] = { 10,25, 50,75,100 };
	double theta[] = { 0.3, 0.5, 1.0, 1.5, 2.0 , 5.0 };
	int sampleSizeLen = 5, thetaLen = 6;

	printf("    ");
	for (j = 0; j < thetaLen;j++) {
		printf("%5.4lf ", theta[j]);
	}
	printf("\n");
	for (i = 0; i < sampleSizeLen; i++) {
		printf("%3d ", sampleSize[i]);
		for (j = 0; j < thetaLen; j++) {
			printf("%5.4lf ", MSE_expo(numOfSamples, sampleSize[i], theta[j]));
		}
		printf("\n");
	}
	return 0;
}

/*
Output:
			0.3000 0.5000 1.0000 1.5000 2.0000 5.0000
		 10 0.0139 0.0428 0.1672 0.3855 0.7143 3.8537
		 25 0.0041 0.0114 0.0480 0.1233 0.2129 1.1885
		 50 0.0022 0.0059 0.0214 0.0490 0.0910 0.5936
		 75 0.0013 0.0034 0.0159 0.0343 0.0587 0.3485
		100 0.0010 0.0027 0.0108 0.0233 0.0397 0.2540
*/