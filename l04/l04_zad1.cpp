#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

// Zadanie 1
class Zadanie1 {
public:
	Zadanie1(int QVal, int i1, int i2, std::string fileName, std::string fileName2);
	void createMask();
	void exc();
	double returnPVal(int j, int i);
	double returnZVal(int j, int i);
	void fill();

private:
	int nx, ny, j1, j2, i1, i2, Q;
	double d, TOL, ro, mi;
	std::vector<std::vector<double> > p;
	std::vector<std::vector<double> > z;
	std::vector<std::vector<bool> > mask;
	std::string fName, fName2;
};
/***************************************************************************/
Zadanie1::Zadanie1(int QVal, int i1, int i2, std::string fileName, std::string fileName2)
	: Q 		(QVal)
	, nx		(400)
	, ny		(200)
	, j1 		(0)
	, j2		(50)
	, d 		(0.01)
	, TOL		(1e-10)
	, ro		(1.0)
	, mi 		(1.0)
	, i1 		(i1)
	, i2		(i2)
	, fName (fileName)
	, fName2(fileName2)
{
	p =	*(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	z = *(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	mask = *(new std::vector<std::vector<bool> >(ny + 1, std::vector<bool>(nx + 1)));
	createMask();
	fill();
}
/***************************************************************************/
void Zadanie1::createMask() {
	for (int j = 0; j < mask.size(); ++j) {
		for (int i = 0; i < mask[0].size(); ++i)
			mask[j][i] = false;
	}

	for (int j = j1 + 1; j < j2; ++j) {
		for (int i = 0; i < nx; ++i)
			mask[j][i] = true;

	}
	for (int j = j2; j < ny; ++j) {
		for (int i = i1 + 1; i < i2; ++i)
			mask[j][i] = true;
	}
}
/***************************************************************************/
void Zadanie1::fill() {
	for (int j = 0; j < p.size(); ++j) {
		for (int i = 0; i < z[0].size(); ++i) {
			p[j][i] = 0;
			z[j][i] = 0;
		}
	}
	// Strumień
	// Wejście / wyjście
	for (int j = j1; j <= j2; ++j)
		p[j][0] = p[j][nx] = ((Q * d * d * d) / 2) * (
							 (j * j * j / 3) - (25 * j * j));

	// A
	for (int i = 1; i <= i1; ++i)
		p[j2][i] = p[j2][0];

	// B
	for (int j = j2; j <= ny; ++j)
		p[j][i1] = p[j2][0];

	// C
	for (int i = i1; i <= i2; ++i)
		p[ny][i] = p[j2][0];

	// D
	for (int j = j2; j <= ny; ++j)
		p[j][i2] = p[j2][0];

	// E
	for (int i = i2; i <= nx - 1; ++i)
		p[j2][i] = p[j2][0];

	// F
	for (int i = 1; i <= nx - 1; ++i)
		p[0][i] = p[j1][0];
	

	// Wirowość
	// Wejście wyjście
	for (int j = j1; j <= j2; ++j)
		z[j][0] = z[j][nx] = (Q * d) * (j - 25);

	// A
	for (int i = 1; i <= i1 - 1; ++i)
		z[j2][i] = (p[j2 - 1][i] - p[j2][i]) * (2 / (d * d));

	// B
	for (int j = j2 + 1; j <= ny - 1; ++j)
		z[j][i1] = (p[j][i1 + 1] - p[j][i1]) * (2 / (d * d));

	// C
	for (int i = i1 + 1; i <= i2 - 1; ++i)
		z[ny][i] = (p[ny - 1][i] - p[ny][i]) * (2 / (d * d));

	// D
	for (int j = j2 + 1; j <= ny - 1; ++j)
		z[j][i2] = (p[j][i2 - 1] - p[j][i2]) * (2 / (d * d));

	// E
	for (int i = i2 + 1; i <= nx - 1; ++i)
		z[j2][i] = (p[j2 - 1][i] - p[j2][i]) * (2 / (d * d));

	// F
	for (int i = 1; i <= nx - 1; ++i)
		z[j1][i] = (p[j1 + 1][i] - p[j1][i]) * (2 / (d * d));

	// A-B D-E
	z[j2][i1] = (z[j2][i1 - 1] + z[j2 + 1][i1]) / 2;
	z[j2][i2] = (z[j2][i2 + 1] + z[j2 + 1][i2]) / 2;
}
/***************************************************************************/
void Zadanie1::exc() {
	double a = 0.;
	double aPrev = 1.;
	int iCounter = 0;
	std::ofstream file;
	std::string fileName = "dat/";
	fileName += fName + ".dat";
	file.open(fileName);

	while (fabs(a - aPrev) / aPrev > TOL) {
		aPrev = a;
		a = 0;

		// A
		for (int i = 1; i <= i1 - 1; ++i)
			z[j2][i] = (p[j2 - 1][i] - p[j2][i]) * (2 / (d * d));

		// B
		for (int j = j2 + 1; j <= ny - 1; ++j)
			z[j][i1] = (p[j][i1 + 1] - p[j][i1]) * (2 / (d * d));

		// C
		for (int i = i1 + 1; i <= i2 - 1; ++i)
			z[ny][i] = (p[ny - 1][i] - p[ny][i]) * (2 / (d * d));

		// D
		for (int j = j2 + 1; j <= ny - 1; ++j)
			z[j][i2] = (p[j][i2 - 1] - p[j][i2]) * (2 / (d * d));

		// E
		for (int i = i2 + 1; i <= nx - 1; ++i)
			z[j2][i] = (p[j2 - 1][i] - p[j2][i]) * (2 / (d * d));

		// F
		for (int i = 1; i <= nx - 1; ++i)
			z[j1][i] = (p[j1 + 1][i] - p[j1][i]) * (2 / (d * d));

		// A-B D-E
		z[j2][i1] = (z[j2][i1 - 1] + z[j2 + 1][i1]) / 2;
		z[j2][i2] = (z[j2][i2 + 1] + z[j2 + 1][i2]) / 2;

		for (int i = 1; i < nx; ++i) {
			for (int j = 1; j < ny; ++j) {
				if (mask[j][i]) {
					p[j][i] = returnPVal(j, i); 
					z[j][i] = returnZVal(j, i);
					a += ((p[j + 1][i] - p[j - 1][i]) / (2 * d)) * 
						 ((p[j + 1][i] - p[j - 1][i]) / (2 * d)) +
						 ((p[j][i + 1] - p[j][i - 1]) / (2 * d)) *
						 ((p[j][i + 1] - p[j][i - 1]) / (2 * d)) -
						 (d * d * z[j][i] * p[j][i]);
				}
			}
		}
		a *= (d * d / 2);
	}
		
	for (int j = 1; j < j2; ++j) {
		file << j << " " << p[j][0] << " " << p[j][200] << " " << z[j][0] <<
				" " << z[j][200] << " " << (p[j + 1][200] - p[j - 1][200]) / (2 * d) << " " << 
				std::endl;
	}

	file.close();
	fileName = "dat/";
	fileName += fName2 + ".dat";
	file.open(fileName);

	if (Q != -1000) {
		for (int j = 0; j < p.size(); ++j) {
			for (int i = 0; i < p[0].size(); ++i)
				file << i << " " << j << " " << p[j][i] << std::endl;
			file << std::endl;
		}
	}
	else {
		for (int j = 0; j < p.size(); ++j) {
			for (int i = 0; i < p[0].size(); ++i)
				file << i << " " << j << " " << p[j][i] << " " << z[j][i] << std::endl;
			file << std::endl;
		}
	}

	file.close();
}
/***************************************************************************/
double Zadanie1::returnZVal(int j, int i) {
	return 0.25 * (z[j][i + 1] + z[j][i - 1] + z[j + 1][i] + z[j - 1][i]) -
				 ((d * d * ro) / (4 * mi)) * (
				 ((p[j + 1][i] - p[j - 1][i]) / (2 * d)) * 
				 ((z[j][i + 1] - z[j][i - 1]) / (2 * d)) -
				 ((p[j][i + 1] - p[j][i - 1]) / (2 * d)) * 
				 ((z[j + 1][i] - z[j - 1][i]) / (2 * d))
				 );
}
/***************************************************************************/
double Zadanie1::returnPVal(int j, int i) {
	return 0.25 * (p[j][i + 1] + p[j][i - 1] + p[j + 1][i] + p[j - 1][i] - (d * d * z[j][i]));
}
/***************************************************************************/
int main(void) {
	Zadanie1 test = Zadanie1(-500, 125, 126, "z1_prof", "z1_map");
	test.exc();
	std::string fileName;
	std::vector<int> vQ = {10, 100, 500, 1000};

	for (int Q : vQ) {
		fileName = "z2_Qm" + std::to_string(Q) + "_map";
		test = Zadanie1(-Q, 125, 275, "unnecesary", fileName);
		test.exc();
	}
	return 0;
}
