#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

class Zadanie1 {
public:
	Zadanie1();
	void exc();
	double returnU(double x, double t) const;
	double returnV(double x, double t) const;
	double returnA(double x, double t) const;
	std::ofstream file;
private:
	std::vector<double> u, v, a, uPrev;
	double dt, x, t, dx;
};
/*************************************************************************/
Zadanie1::Zadanie1()
	:	dt		(1./200)
	, x			(0)
	, t			(0)
	, dx 		(1./100)
{
	u = *(new std::vector<double>(101));
	v = *(new std::vector<double>(101));
	a = *(new std::vector<double>(101));
	uPrev = *(new std::vector<double>(101));
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
void Zadanie1::exc() {
	std::vector<double> vBeta = { 0.2, 1., 3. };
	for (double beta : vBeta) {
		file.open(std::string("dat/beta") + std::to_string(int(beta * 10)) + ".dat");
		for (int i = 0; i < 100; ++i) {
			u[i] = exp(-100 * ((x + i * dx) - 0.5) * ((x + i * dx) - 0.5));
			v[i] = 0;
			a[i] = returnA(x + i * dx, 0);
		}
		u[0] = u[100] = 0;
		for (double t = 0; t <= 4.1; t += dt) {
			uPrev = u;
			for (int i = 0; i <= 100; ++i) {
				v[i] = v[i] + (dt/2) * a[i];
				u[i] = u[i] + dt * v[i];
			}
			for (int i = 1; i < 100; ++i)
				a[i] = ((u[i+1] + u[i-1] - 2 * u[i]) / (dx * dx)) - ((2. * beta * (u[i] - uPrev[i])) / dt);
			for (int i = 0; i <= 100; ++i)
				v[i] = v[i] + (dt/2) * a[i];
			for (int i = 0; i < 101; ++i)
				file << t << " " << x + i * dx << " " << u[i] << std::endl;
			file << std::endl;
		}	
		file.close();
	}
}
/*************************************************************************/
int main() {
	Zadanie1 test;
	test.exc();
}