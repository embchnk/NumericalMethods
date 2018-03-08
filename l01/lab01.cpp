#include <stdlib.h>
#include <iostream>
#include <cmath>

// Zadanie 1

double foo(double t, double u) {
	return u * cos(t);
}

void exc1(double h) {
	double t = 0.;
	double u;
	double tempU = 1.;
	double currResult;

	FILE* f = fopen("result1.dat", "a");

	for (t = 0; t < M_PI; t += h) {
		currResult = exp(sin(t + h));
		u = tempU + (h * foo(t, tempU));
		tempU = u;
	}

	fprintf(f, "%25.10e %25.10e\n", h, currResult - tempU);

	fclose(f);


}

// Zadanie 2

void exc2(double h) {
	double t = 0.;
	double u;
	double tempU = 1.;
	double currResult;

	FILE* f = fopen("result2.dat", "a");

	for (t = 0; t < M_PI; t += h) {
		currResult = exp(sin(t + h));
		u = tempU / (1 - (h * cos(t + h)));
		tempU = u;
	}

	fprintf(f, "%25.10e %25.10e\n", h, currResult - tempU);

	fclose(f);
}

// Zadanie 4

void exc4(double h) {
	double u1;
	double u12;
	double u2;
	double u2p = 1.;
	double u;
	double tempU = 1.;

	FILE* fp = fopen("result4.dat", "w");

	for (double t = 0; t <= 4 * M_PI; t += 2 * h) {
		for (int i = 0; i < 2; ++i) {
			u = tempU + (h * foo(t + (h * i), tempU));
			tempU = u;
		}
		u1 = u2p + (2 * h * foo(t, u2p));
		u12 = u2p + (h * foo(t, u2p));
		u2 = u12 + (h * foo(t + h, u12));
		u2p = 2 * u2 - u1;
		fprintf(fp, "%25.10e %25.10e %25.10e\n", t + 2 * h, u2p - exp(sin(t + 2 * h)), u - exp(sin(t + 2 * h)));
	}

	fclose(fp);

}

// Zadanie 5

void exc5(double h, double tol, double S) {
	double u1;
	double u12;
	double u2;
	double tempU = 1.;
	double t = 0;
	double E;

	FILE* fp = fopen("result5.dat", "w");

	while (true) {
		u1 = tempU + (2 * h * foo(t, tempU));
		u12 = tempU + (h * foo(t, tempU));
		u2 = u12 + (h * foo(t + h, u12));
		E = u2 - u1;
		if (fabs(E) < tol) {
			tempU = u2;
			t += 2 * h;
			fprintf(fp, "%25.10e %25.10e %25.10e %25.10e\n", t, tempU, h, exp(sin(t)));
		}
		h *= sqrt(S * tol / fabs(E));
		if (t >= 4 * M_PI) break;
	} 

	fclose(fp);
}

// Zadanie 6

// double f1(double x) {

// }

// void exc6(double h) {
// 	double x = 0.;
// 	double y = 1.;
// 	double a = 1.;
// 	double k11, k21, k12, k22, k13, k23, k14, k24;

// 	for (double t = 0; t < 4 * M_PI; t += h) {

// 	}
// }

int main() {
	for (int i = 0; i < 10; ++i) {
		exc1(M_PI / (10 * (10 - i)));
		exc2(M_PI / (10 * (10 - i)));
	}
	exc4(M_PI / 400);
	exc5(5 * M_PI, 10e-5, 0.75);
	return 0;
}