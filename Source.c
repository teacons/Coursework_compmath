
#include <stdio.h>
#include <math.h>
#include "zeroin.h"
#include "cmath.h"
#include "quanc8.h"
#include "rkf45.h"

double alpha;

double start_fun(double x)
{
    return 1 / (sqrt(2 * (alpha + x * x * x / 3 - x)));
}

double fun(double y)
{
    int flag, nofun;
    double a = 0, b = 1;
    double relerr = 1.0e-12, abserr = 1.0e-12, errest, posnr, result;
    alpha = y;
    quanc8(start_fun, a, b, abserr, relerr, &result, &errest, &nofun, &posnr, &flag);
    return result - 1;
}
int fun_rkf(int n, double t, double z[], double dz[])
{
    dz[0] = z[1];
    dz[1] = pow(z[0], 2) -1; 
   
}
void main(void)
{
    double a = 0, b = 1;
    int tol = 1.0e-12, flag;
    double alp = zeroin(a, b, fun, tol, &flag);
    int n = 2, fl = 1;
    double z[2] = {0, sqrt(2*alp)}, dz[2];
    double t = 0.0, tout = 1.0;
    int fail, nfe;
    double h;
    int maxnfe = 6000;
    double relerr = 0.0001, abserr = 0.0001;
    rkfinit(n, &fail);

    if (fail == 0)
    {
        rkf45(fun_rkf, n, z, dz, &t, tout, &relerr, abserr, &h, &nfe, maxnfe, &fl);
        printf("Solve: %10.6f \n", z[0]);
    }
    rkfend();
}