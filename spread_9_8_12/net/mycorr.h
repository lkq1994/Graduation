#ifndef MYCORR_H
#define MYCORR_H

#include <math.h>
#include <QTime>

#include "myfft.h"


class mycorr
{
public:
    mycorr();

public:
    static void CorrDirect(double*, double*, int, int, double*);
    static void CorrFFT(double*, double*, int, double*);

};

#endif // MYCORR_H
