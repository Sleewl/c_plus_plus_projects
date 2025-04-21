#include <stdio.h>
#include <math.h>
#include "cmathsrc/cmath.h"
#include "cmathsrc/RCS/quanc8.c"
#include "cmathsrc/spline.c"
#include <conio.h>

double f(double x) {
  return sin(x) / x;
}

double lagrange(double x, double* x_values, double* y_values, int size) {
  double lagrange_pol = 0.0;
  for (int i = 0; i < size; i++) {
    double basics_pol = 1.0;
    for (int j = 0; j < size; j++) {
      if (j == i) continue;
      basics_pol *= (x - x_values[j]) / (x_values[i] - x_values[j]);
    }
    lagrange_pol += basics_pol * y_values[i];
  }
  return lagrange_pol;
}

int main() {
  int n = 11;
  double a = 2.0, b = 3.0;
  double epsabs = 0.0, epsrel = 1.0e-10;
  double errest, posn, flag, result;
  int nofun;

  double funValues[11];

  printf("\nИнтервалы и значения интеграла:\n");
  for (int i = 0; i < n; i++) {
    printf("[%.1f, %.1f]   ", a, b);
    quanc8(f, a, b, epsabs, epsrel, &result, &errest, &nofun, &posn, &flag);
    funValues[i] = result;
    printf("%f\n", funValues[i]);
    b += 0.1; 
  }

  double X[11] = { 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0 };

  double B[11], C[11], D[11];
  int iflag;

  spline(n, 0, 0, 0.0, 0.0, X, funValues, B, C, D, &iflag);

  printf("\n\nПроверка в исходных узлах:\n");
  printf("Xk           Quanc8                Spline                Lagrange              Diff(Q-S)       Diff(Q-L)\n\n");
  double xk = 2.0;
  int last = 0;
  for (int i = 0; i < n; i++) {
    quanc8(f, a, xk + 0.95, epsabs, epsrel, &result, &errest, &nofun, &posn, &flag);
    double tmpQuanc = result;
    double tmpSeval = seval(n, xk, X, funValues, B, C, D, &last);
    double tmpLagrange = lagrange(xk, X, funValues, n);
    
    double diffSpline = fabs(tmpQuanc - tmpSeval);
    double diffLagrange = fabs(tmpQuanc - tmpLagrange);
    
    printf("%.2f    %.16f    %.16f    %.16f    %.8f    %.8f\n", xk, tmpQuanc, tmpSeval, tmpLagrange, diffSpline, diffLagrange);
    xk += 0.1;
  }

  printf("\nПроверка в промежуточных точках (шаг 0.05):\n");
  printf("Xk           Quanc8                Spline                Lagrange              Diff(Q-S)       Diff(Q-L)\n\n");

  double x_inter = 2.05;
  while (x_inter < 3.0) {
    quanc8(f, a, x_inter + 0.95, epsabs, epsrel, &result, &errest, &nofun, &posn, &flag);
    double tmpQuanc = result;
    double tmpSeval = seval(n, x_inter, X, funValues, B, C, D, &last);
    double tmpLagrange = lagrange(x_inter, X, funValues, n);
    
    double diffSpline = fabs(tmpQuanc - tmpSeval);
    double diffLagrange = fabs(tmpQuanc - tmpLagrange);
    
    printf("%.2f    %.16f    %.16f    %.16f    %.8f    %.8f\n", x_inter, tmpQuanc, tmpSeval, tmpLagrange, diffSpline, diffLagrange);
    x_inter += 0.05;
  }

  _getch();
  return 0;
}









