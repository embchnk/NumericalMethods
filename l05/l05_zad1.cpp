#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

// Zadanie 1
class Zadanie1 {
public:
	Zadanie1();
	void exc();
	void fill();
	double integralCheck();
	double packCenter();
	double returnRo(double y, double x);
private:
	int nx, ny, t;
	double d, yMin, yMax, Q, mi, dt, actIntegral, TOL, actCenter;
	std::vector<std::vector<double> > u;
	std::vector<std::vector<double> > v;
	std::vector<std::vector<double> > ro;
	std::vector<std::vector<double> > ro2;
	std::vector<std::vector<double> > roPrev;
	std::vector<std::vector<bool> > mask;
};
/***************************************************************************/
Zadanie1::Zadanie1()
	: nx		(300)
	, ny		(90)
	, d 		(0.01)
	, yMin	(0.0)
	, yMax	(0.9)
	, Q			(-1)
	, mi 		(1)
	, t 		(100)
	, TOL		(10e-6)
	, actIntegral (0.)
	, actCenter 	(0.)
{
	u =	*(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	v = *(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	ro =	*(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	ro2 = *(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	roPrev = *(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	mask = *(new std::vector<std::vector<bool> >(ny + 1, std::vector<bool>(nx + 1)));
	fill();
}
/***************************************************************************/
double Zadanie1::integralCheck() {
	double nextIntegral = 0.;
	double diff;
	for (int j = 0; j <= ny; ++j) {
			for (int i = 0; i <= nx; ++i)
				nextIntegral += ro[j][i]; 
	}
	nextIntegral *= d * d;
	diff = fabs(nextIntegral - actIntegral);
	actIntegral = nextIntegral;
	return actIntegral;
}
/***************************************************************************/
double Zadanie1::packCenter() {
	double nextCenter = 0.;
	double diff;
	for (int j = 0; j <= ny; ++j) {
			for (int i = 1; i <= nx; ++i)
				nextCenter += ro[j][i] * i; 
	}
	nextCenter *= d * d * d / actIntegral;
	diff = fabs(nextCenter - actCenter);
	actCenter = nextCenter;
	return actCenter;
}
/***************************************************************************/
double Zadanie1::returnRo(double y, double x) {
	return exp(-25 * ((x - 0.4) * (x - 0.4) +
																(y - 0.45) * (y - 0.45)));
}
/***************************************************************************/
void Zadanie1::fill() {
	for (int j = 0; j <= ny; ++j) {
		for (int i = 0; i <= nx; ++i) {
			roPrev[j][i] = returnRo(j * d, i * d);
			u[j][i] = (Q / (2 * mi)) * (j * d) * (j * d - yMax);
			v[j][i] = 0.;
			ro[j][i] = 0.;
		}
	}

}
/***************************************************************************/
void Zadanie1::exc() {
	dt = d / (4 * u[44][0]);
	int i, j;
	std::ofstream file, file2;
	file.open("dat/z1_integrals.dat");
	std::string s = "dat/z1_it";
	int counter = 0;
	// Pierwsze chwile czasowe
	for (j = 0; j <= ny; ++j) {
			for (i = 0; i <= nx; ++i)
				ro[j][i] = returnRo(j * d - (v[j][i] * dt), i * d - (u[j][i] * dt));
	}
	// Zadanie
	for (double n = 0; n < 100; n += dt) {
		if (!(counter % 300) && counter <= 1500) {
			file2.close();
			file2.open(s + std::to_string(counter) + ".dat");
			for (j = 0; j <= ny; ++j) {
				for (i = 0; i <= nx; ++i)
					file2 << i << " " << j << " " << ro[j][i] << std::endl;
				file2 << std::endl;
			}
		}
		for (j = 1; j < ny; ++j) {
			ro2[j][0] = roPrev[j][0] - dt * (u[j][0] * (ro[j][1] - ro[j][nx]) + 
														(v[j][0] * (ro[j + 1][0] - ro[j - 1][0]))) / d;
			ro2[j][nx] = roPrev[j][nx] - dt * (u[j][nx] * (ro[j][0] - ro[j][nx - 1]) + 
														 (v[j][nx] * (ro[j + 1][nx] - ro[j - 1][nx]))) / d;
		}
		for (j = 1; j < ny; ++j) {
			for (i = 1; i < nx; ++i)
				ro2[j][i] = roPrev[j][i] - dt * (u[j][i] * (ro[j][i + 1] - ro[j][i - 1]) +
									 (v[j][i] * (ro[j + 1][i] - ro[j - 1][i]))) / d; 
		}
		roPrev = ro;
		ro = ro2;
		file << n << " " << integralCheck() << " " << packCenter() << std::endl;
		++counter;
	}




	file.close();
	file2.close();
}
/***************************************************************************/
int main(void) {
	Zadanie1 test = Zadanie1();
	test.exc();
	return 0;
}
