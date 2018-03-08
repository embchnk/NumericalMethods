#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

void fill(std::vector<std::vector<double> >& vec, int n) {
	for (int i = 0; i <= n; i += 2)
		vec[i][0] = vec[i][n] = 0;;
	for (int i = 1; i < n; ++i) {
		vec[0][i] = 0.1;
		vec[n][i] = -0.1;
	}
}
/*******************************************************/
double returnDensity(int i, int j, double step) {
	double x = (double)i * step;
	double y = (double)j * step;
	if (pow(x - 0.4, 2) + pow(y - 0.64, 2) <= pow(0.051, 2)) return 80;
	else if (pow(x - 0.88, 2) + pow(y - 0.64, 2) <= pow(0.051, 2)) return -80;
	else return 0;
}
/*******************************************************/
void exc1b(double w, double k, int n, double step) {
	std::vector<std::vector<double> > v(n + 1, std::vector<double>(n + 1));
	double S = 0.;
	double prevS;
	double TOL = 10e-12;
	int iCounter = 0;
	std::ofstream file, file1, file2;

	file.open(std::string("dat/pot2_2") + std::to_string(w) + ".dat");
	file1.open(std::string("dat/exc2_2") + std::to_string(w) + ".dat");
	file2.open(std::string("dat/den2_2") + std::to_string(w) + ".dat");

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j)
			v[i][j] = 0.;
	}

	fill(v, n);

	while (fabs((S - prevS) / prevS) >= TOL) {
		prevS = S;
		S = pow(k * step, 2) * (0.5 * (pow((v[0 + k][0] - v[0][0]) / (k * step), 2) + 
				pow((v[0][0 + k] - v[0][0]) / (k * step), 2)) - returnDensity(0, 0, step) * v[0][0]);
		for (int i = k; i <= n - k; i += k) {
			for (int j = k; j <= n - k; j += k) {
				v[i][j] = (1 - w) * v[i][j] + 
									0.25 * w * (v[i + k][j] + v[i - k][j] + v[i][j + k] + v[i][j - k] +
									pow(k * step, 2) * returnDensity(i, j, step));

				S += pow(k * step, 2) * (0.5 * (pow((v[i + k][j] - v[i][j]) / (k * step), 2) + 
						pow((v[i][j + k] - v[i][j]) / (k * step), 2)) - returnDensity(i, j, step) * v[i][j]);
			}
		}
		file1 << iCounter++ << " " << S << std::endl;
	} 
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			file << (double)i * step << " " << (double)j * step << " " << v[i][j] << std::endl;
			file2 << (double)i * step << " " << (double)j * step << " " << returnDensity(i, j, step) << std::endl;
		}
	}
	file.close();
	file1.close();
	file2.close();
}
/*******************************************************/
int main() {
	std::vector<double> vW;
	for (double d = 1.1; d < 2.0; d += 0.1)
		vW.push_back(d);
	for (double w : vW)
		exc1b(w, 1, 128, 0.01);

	return 0;
}