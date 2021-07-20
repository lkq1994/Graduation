#ifndef MYFFT_H
#define MYFFT_H


#include <math.h>
#include <QDebug>
#include <QTime>
//#include "widget.h"
const double PI = 3.1415926535897932384626433832795028841971;
struct compx {double real,imag;};

typedef struct compx complex;

class myfft
{
public:
    myfft();

    static void create_sin_tab(double *sin_t,int PointNum,double *);
    static struct compx EE(struct compx a,struct compx b);
    static double sin_tab(double pi, int nfft, double *sintab);
    static double cos_tab(double pi, int nfft, double *);
    static void fft(struct compx *xin, int nfft , struct compx *xout);
    static void ChangeSeat(complex *DataInput, int N_fft);
    static void ifft(complex *fft_data, int nfft);
    static complex multiply_complex(complex a, complex b);
    static void create_sin_table(double*,int);
    static double sin_find(double,double*,int);
    static double cos_find(double,double*,int);

private:



};

#endif // MYFFT_H
