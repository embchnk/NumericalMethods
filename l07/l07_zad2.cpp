#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

class Zadanie1 {
public:
	Zadanie1();
	void exc1();
	void exc2();
	void exc2c();
	double returnU(double x, double t) const;
	double returnV(double x, double t) const;
	double returnA(double x, double t) const;
	double returnAExcC(double x, double t) const;
	std::ofstream file;
private:
	std::vector<double> u, v, a;
	double dt, x, t, dx, ro, x0;
};
/*************************************************************************/
Zadanie1::Zadanie1()
	:	dt		(1./200)
	, x			(0)
	, t			(0)
	, dx 		(1./100)
	, ro		(3.0)
	, x0		(0.75)
{
	u = *(new std::vector<double>(101));
	v = *(new std::vector<double>(101));
	a = *(new std::vector<double>(101));
	file.open("dat/zad2.dat");
}
/*************************************************************************/
double Zadanie1::returnU(double x, double t) const {
	return cos(M_PI * t) * sin(M_PI * x) - 
				 0.5 * cos(2 * M_PI * t) * sin(2 * M_PI * x);
}
/*************************************************************************/
double Zadanie1::returnV(double x, double t) const {
	return -M_PI * sin(M_PI * t) * sin(M_PI * x) + 
					M_PI * sin(2 * M_PI * t) * sin(2 * M_PI * x);
}
/*************************************************************************/
double Zadanie1::returnA(double x, double t) const {
	return -M_PI * M_PI * cos(M_PI * t) * sin(M_PI * x) +
					2 * M_PI * M_PI * cos(2 * M_PI * t) * sin(2 * M_PI * x);
}
/*************************************************************************/
double Zadanie1::returnAExcC(double i, double t) const {
	return (1. / (dx * dx)) * (u[i+1] + u[i-1] - 2 * u[i]) * (1. / (((i * dx) < x0) ? 1 : ro));
}
/*************************************************************************/
void Zadanie1::exc1() {
	for (int i = 0; i < 100; ++i) {
		u[i] = exp(-100 * (x + i * dx - 0.5) * (x + i * dx - 0.5));
		v[i] = 0;
		a[i] = returnA(x + i * dx, 0);
	}
	for (double t = 0; t <= 4.1; t += dt) {
		u[0] = u[100] = 0;
		for (int i = 0; i <= 100; ++i) {
			v[i] = v[i] + (dt/2) * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for (int i = 1; i < 100; ++i)
			a[i] = (u[i+1] + u[i-1] - 2 * u[i]) / (dx * dx);
		for (int i = 0; i <= 100; ++i)
			v[i] = v[i] + (dt/2) * a[i];

		for (int i = 0; i < 101; ++i)
			file << t << " " << x + i * dx << " " << u[i] << std::endl;
		file << std::endl;
	}
	file.close();
}
/*************************************************************************/
void Zadanie1::exc2() {
	for (int i = 0; i < 100; ++i) {
		u[i] = exp(-100 * (x + i * dx - 0.5) * (x + i * dx - 0.5));
		v[i] = 0;
		a[i] = returnA(x + i * dx, 0);
	}
	file.open("dat/zad2b.dat");
	for (double t = 0; t <= 4.1; t += dt) {
		for (int i = 0; i <= 100; ++i) {
			v[i] = v[i] + (dt/2) * a[i];
			u[i] = u[i] + dt * v[i];
		}
		u[0] = u[1];
		u[100] = u[99];
		for (int i = 1; i < 100; ++i)
			a[i] = (u[i+1] + u[i-1] - 2 * u[i]) / (dx * dx);
		for (int i = 0; i <= 100; ++i)
			v[i] = v[i] + (dt/2) * a[i];

		file << " " << t << " " << fabs(u[0]) << " " << fabs(u[100]) << std::endl;
	}
	file.close();
}
/*************************************************************************/
void Zadanie1::exc2c() {
	for (int i = 0; i < 100; ++i) {
		u[i] = exp(-100 * (x + i * dx - 0.5) * (x + i * dx - 0.5));
		v[i] = 0;
		a[i] = 0;
	}
	file.open("dat/zad2c.dat");
	for (double t = 0; t <= 4.1; t += dt) {
		u[0] = u[100] = 0;
		for (int i = 0; i <= 100; ++i) {
			v[i] = v[i] + (dt/2) * a[i];
			u[i] = u[i] + dt * v[i];
		}
		for (int i = 1; i < 100; ++i)
			a[i] = returnAExcC(i, t);
		for (int i = 0; i <= 100; ++i)
			v[i] = v[i] + (dt/2) * a[i];

		for (int i = 0; i < 101; ++i)
			file << t << " " << x + i * dx << " " << u[i] << std::endl;
		file << std::endl;
	}
	file.close();
}
/*************************************************************************/
int main() {
	Zadanie1 test;
	test.exc1();
	test.exc2();
	test.exc2c();
}