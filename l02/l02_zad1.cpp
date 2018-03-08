#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

// Zadanie 2b.1
void fill(std::vector<std::vector<double> >& vec, int n) {
	for (int i = 0; i <= n; i += 2)
		vec[i][0] = vec[i][n] = 0;;
	for (int i = 1; i < n; ++i) {
		vec[0][i] = 0.1;
		vec[n][i] = -0.1;
	}
}
/*******************************************************/
double returnDensity(double i, double j, double step) {
	double x = (double)i * step;
	double y = (double)j * step;
	if (pow(x - 0.4, 2) + pow(y - 0.64, 2) <= pow(0.051, 2)) return 80;
	else if (pow(x - 0.88, 2) + pow(y - 0.64, 2) <= pow(0.051, 2)) return -80;
	else return 0;
}
/********************************************************************************/
void exc1a(double w, double k, int n, double step) {
	std::vector<std::vector<double> > vDensOld(n + 1, std::vector<double>(n + 1));
	std::vector<std::vector<double> > vDensNew(n + 1, std::vector<double>(n + 1));
	double vDens;
	double S = 0.;
	double prevS;
	double TOL = 10e-12;
	int iCounter = 0;
	std::ofstream file, file1, file2;

	file.open(std::string("dat/pot2_1") + std::to_string(w) + ".dat");
	file1.open(std::string("dat/exc2_1") + std::to_string(w) + ".dat");
	file2.open(std::string("dat/den2_1") + std::to_string(w) + ".dat");

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j)
			vDensOld[i][j] = vDensNew[i][j] = 0.;
	}

	fill(vDensOld, n);
	fill(vDensNew, n);

	while (fabs((S - prevS) / prevS) >= TOL) {
		prevS = S;
		S = pow(k * step, 2) * (0.5 * (pow((vDensNew[0 + k][0] - vDensNew[0][0]) / (k * step), 2) +
			  pow((vDensNew[0][0 + k] - vDensNew[0][0]) / (k * step), 2)) - returnDensity(0, 0, step) * vDensNew[0][0]);
		for (int i = k; i <= n - k; i += k) {
			for (int j = k; j <= n - k; j += k) {
				vDens = (vDensOld[i + k][j] + vDensOld[i - k][j] + vDensOld[i][j + k] +
				vDensOld[i][j - k] + (pow(k * step, 2) * returnDensity(i, j, step))) / 4;

				vDensNew[i][j] = (1 - w) *  vDensOld[i][j] + w * vDens;


				S += pow(k * step, 2) * (0.5 * ((pow((vDensNew[i + k][j] - vDensNew[i][j]) / (k * step), 2)) +
				pow((vDensNew[i][j + k] - vDensNew[i][j]) / (k * step), 2)) - returnDensity(i, j, step) * vDensNew[i][j]);
			}
		}
		std::copy(vDensNew.begin(), vDensNew.end(), vDensOld.begin());
		file1 << iCounter++ << " " << S << std::endl;
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			file << (double)i * step << " " << (double)j * step << " " << vDensNew[i][j] << std::endl;
			file2 << (double)i * step << " " << (double)j * step << " " << returnDensity(i, j, step) << std::endl;
		}
	}

	file.close();
	file1.close();
	file2.close();
}

int main() {
	std::vector<double> vW;
	for (double d = 1.1; d < 2.0; d += 0.1)
		vW.push_back(d);
	for (double w : vW)
	exc1a(w, 1, 128, 0.01);
}