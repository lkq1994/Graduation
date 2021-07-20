#ifndef DESPREAD_H
#define DESPREAD_H

#include "math.h"
#include "myfft.h"
#include "mycorr.h"
#include <QTime>

class despread
{
public:
    despread();

public:
    static void DeSpreadCode(double , double , double , double *,
                             int , double *, int , char *);
    static double pn[511];

};

#endif // DESPREAD_H
