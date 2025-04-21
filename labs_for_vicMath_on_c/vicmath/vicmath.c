#include "cmathsrc\cmath.h"
#include "cmathsrc\RCS\quanc8.c"
#include "cmathsrc\spline.c"
#include "conio.h"
//#include "Forsythe.h"
#include "stdio.h"
#include "math.h"
#include <float.h>

double f(double x) { return sin(x) / x; }
double lagrange(double x, double* x_values, double* y_values, int size)
{
  double lagrange_pol = 0;
  double basics_pol = 1;
  for (int i = 0; i < size; i++)
  {
	basics_pol = 1;
	for (int j = 0; j < size; j++)
	{
	  if (j == i) continue;
	  basics_pol *= (x - x_values[j]) / (x_values[i] - x_values[j]);
	}
	lagrange_pol += basics_pol * y_values[i];
  }
  return lagrange_pol;
}
void main()
{
  Float  a, b;
  Float  epsabs, epsrel;
  Float  errest;
  int    nofun;
  Float  flag;

  double funValues[10];
  a = 2.0;
  b = 3.0;
  epsrel = 1.0e-10;
  epsabs = 0.0;

  printf("\nInterval      Value     Flag\n");
  for (int i = 0; i < 10; i++) {
	printf("[%.1f, %.1f]   ", a, b);
	funValues[i] = quanc8(f, a, b, epsabs, epsrel, &errest, &nofun, &flag);
	printf("%f   %.1f\n", funValues[i], flag);
	b += 0.1;
  }
  Float B[10], C[10], D[10];
  Float X[10] = { 2.05, 2.15, 2.25, 2.35, 2.45, 2.55, 2.65, 2.75, 2.85, 2.95 };
  Float xk = 2.05;
  Float tmpQuanc, tmpSeval, tmpLagrange;

  spline(10, X, funValues, B, C, D);
  printf("\n\nXk    Quanc8    Spline   Lagrange\n\n");

  for (int i = 0; i < 10; i++) {
	tmpQuanc = quanc8(f, a, xk + 0.95, epsabs, epsrel, &errest, &nofun, &flag);
	tmpSeval = seval(10, xk, X, funValues, B, C, D);
	tmpLagrange = lagrange(xk, X, funValues, 10);

	printf("%.2f    %.16f    %.16f    %.16f\n", xk, tmpQuanc, tmpSeval, tmpLagrange);
	xk += 0.1;
  }
  _getch();
}
