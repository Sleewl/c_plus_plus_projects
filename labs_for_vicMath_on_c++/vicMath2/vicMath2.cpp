


/**using namespace std;

const int size = 8;

double p = 1;
double Amatrix[size][size] = { { 13.0 + p, 2.0, 8.0, -7.0, 7.0, 5.0, -7.0, -7.0, },
				{  7.0,   2.0, -4.0,  2.0,  3.0,  3.0, -1.0, -2.0, },
				{ -7.0,   2.0,  1.0,  3.0,  6.0, -6.0, -3.0, -4.0, },
				{ -2.0,  -8.0, -6.0, -1.0,  6.0,  2.0,  1.0, -4.0, },
				{  0.0,   4.0, -7.0,  1.0, 22.0,  0.0, -6.0, -6.0, },
				{  0.0,  -3.0, -6.0,  6.0,  4.0, 13.0,  0.0,  6.0, },
				{ -8.0,  -6.0, -4.0,  7.0, -5.0, -5.0, -2.0,  1.0, },
				{  5.0,   5.0, -2.0, -2.0, -3.0,  0.0, -7.0, 14.0  } };

double norma(double** A) {
  double norm = 0;
  double tmp = 0;
  for (int i = 0; i < size; i++) {
	tmp = 0;
	for (int j = 0; j < size; j++)
	  tmp = tmp + abs(A[i][j]);
	if (tmp > norm)
	  norm = tmp;
  }
  return norm;
}


double** obrat(double** A) {
  double** result = new double* [size];
  for (int i = 0; i < size; i++)
	result[i] = new double[size];

  double cond;
  int ipvt[size];
  int flag;
  int k = 0;
  double newA[size * size];

  for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++, k++)
	  newA[k] = A[i][j];

  decomp(size, size, newA, &cond, ipvt, &flag);
  if (flag != 0) {
    printf("\nОшибка разложения: flag = %d\n", flag);
  }

  double B[size];
  printf("\nA^-1:");
  for (int i = 0; i < size; i++) {
	for (int k = 0; k < size; k++)
	  B[k] = 0;
	B[i] = 1;
    solve(size, size, newA, B, ipvt);
	printf("\n");
	for (int j = 0; j < size; j++) {
	  result[j][i] = B[j];
	  printf("%.0f  ", result[j][i]);
	}
  }
  return result;
}
double** multiplier(double** B) {
  double** result = new double* [size];

  for (int i = 0; i < size; i++)
	result[i] = new double[size];
  for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	  result[i][j] = 0;
  for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
	  for (int k = 0; k < size; k++)
		result[i][j] += Amatrix[i][k] * B[k][j];
	}
  }
  return result;
}
double** getR(double** R) {
  double** result = new double* [size];
  for (int i = 0; i < size; i++)
	result[i] = new double[size];
  for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	  result[i][j] = Amatrix[i][j];
  result = obrat(result);
  R = multiplier(result);
  for (int i = 0; i < size; i++)
	R[i][i]--;
  printf("\nMatrix R:\n");
  for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++)
	  printf("%.6f  ", R[i][j]);
	printf("\n");
  }
  return R;
}
int main() {

  double** R = new double* [size];
  for (int i = 0; i < size; i++) {
	R[i] = new double[size];
  }
  printf("Matrix A:\n");
  for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
	  printf("%.1f  ", Amatrix[i][j]);
	}
	printf("\n");
  }

  R = getR(R);
  double norm = norma(R);
  printf("Norma %0.14f, p = %f", norm, p);
  return 0;
}*/



#include "math.h"
#include <cmath>
#include "conio.h"
#include "stdio.h"
#include "cmathsrc/cmath.h"
#include "cmathsrc/RCS/decomp.c"


using namespace std;

const int size = 8;

double p = 0.000001;

double Amatrix[size][size] = {
    { 13.0 + p,  2.0,  8.0, -7.0,  7.0,  5.0, -7.0, -7.0 },
    {  7.0,      2.0, -4.0,  2.0,  3.0,  3.0, -1.0, -2.0 },
    { -7.0,      2.0,  1.0,  3.0,  6.0, -6.0, -3.0, -4.0 },
    { -2.0,     -8.0, -6.0, -1.0,  6.0,  2.0,  1.0, -4.0 },
    {  0.0,      4.0, -7.0,  1.0, 22.0,  0.0, -6.0, -6.0 },
    {  0.0,     -3.0, -6.0,  6.0,  4.0, 13.0,  0.0,  6.0 },
    { -8.0,     -6.0, -4.0,  7.0, -5.0, -5.0, -2.0,  1.0 },
    {  5.0,      5.0, -2.0, -2.0, -3.0,  0.0, -7.0, 14.0 }
};

double normInf(double** A) {
  double norm = 0.0;
  for (int i = 0; i < size; i++) {
    double rowSum = 0.0;
    for (int j = 0; j < size; j++) {
      rowSum += fabs(A[i][j]);
    }
    if (rowSum > norm) {
      norm = rowSum;
    }
  }
  return norm;
}

double normOne(double** A) {
  double norm = 0.0;
  for (int j = 0; j < size; j++) {
    double colSum = 0.0;
    for (int i = 0; i < size; i++) {
      colSum += fabs(A[i][j]);
    }
    if (colSum > norm) {
      norm = colSum;
    }
  }
  return norm;
}

double** obrat(double** A, double& condOut) {
  double** result = new double* [size];
  for (int i = 0; i < size; i++) {
    result[i] = new double[size];
  }

  double cond;
  int ipvt[size];
  int flag;
  double newA[size * size];

  int k = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++, k++) {
      newA[k] = A[i][j];
    }
  }

  decomp(size, size, newA, &cond, ipvt, &flag);
  if (flag != 0) {
    printf("\nОшибка разложения: flag = %d\n", flag);
  }

  condOut = cond;

  double B[size];
  printf("\nA^-1:\n");
  for (int i = 0; i < size; i++) {
    for (int k = 0; k < size; k++)
      B[k] = 0.0;
    B[i] = 1.0;

    solve(size, size, newA, B, ipvt);

    for (int j = 0; j < size; j++) {
      result[j][i] = B[j];
      printf("%10.2f  ", result[j][i]);
    }
    printf("\n");
  }

  return result;
}

double** multiplier(double** B) {
  double** result = new double* [size];
  for (int i = 0; i < size; i++) {
    result[i] = new double[size];
    for (int j = 0; j < size; j++) {
      result[i][j] = 0.0;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        result[i][j] += Amatrix[i][k] * B[k][j];
      }
    }
  }
  return result;
}

double** getR(double** R, double& cond) {
  double** tempA = new double* [size];
  for (int i = 0; i < size; i++) {
    tempA[i] = new double[size];
    for (int j = 0; j < size; j++) {
      tempA[i][j] = Amatrix[i][j];
    }
  }

  double** Ainv = obrat(tempA, cond);

  R = multiplier(Ainv);

  for (int i = 0; i < size; i++) {
    R[i][i] -= 1.0;
  }

  printf("\nMatrix R = A*A^-1 - I:\n");
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%10.6f  ", R[i][j]);
    }
    printf("\n");
  }

  return R;
}

int main() {
  double** R = new double* [size];
  for (int i = 0; i < size; i++) {
    R[i] = new double[size];
  }

  printf("Matrix A:\n");
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%6.1f  ", Amatrix[i][j]);
    }
    printf("\n");
  }

  double condA = 0.0;

  R = getR(R, condA);

  double normInfR = normInf(R);
  double normOneR = normOne(R);

  printf("\ncond(A) = %.14f\n", condA);
  printf("||R||inf  = %.14f\n", normInfR);
  printf("||R||1 = %.14f\n", normOneR);
  printf("cond(A)*||R||inf = %.14f\n", condA * normInfR);
  printf("cond(A)*||R||1 = %.14f\n", condA * normOneR);

  return 0;
}




















