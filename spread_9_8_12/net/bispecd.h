#ifndef BISPECD_H
#define BISPECD_H
#include "math.h"
#include "myfft.h"
#include <QDebug>

class bispecd
{
public:
    bispecd();

    static double ConjMultiAbs(struct compx a, struct compx b);
    static double Bispectrum(double *x, int Num, int Nfft, int wind, int nsamp, int overlap);

};

#endif // BISPECD_H
