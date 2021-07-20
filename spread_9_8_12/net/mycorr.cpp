#include "mycorr.h"

mycorr::mycorr()
{

}


void mycorr::CorrDirect(double *xcorr, double *ycorr, int xlength, int ylength, double *corrout)
{
    int ii = 0;
    int k = 0;
    int i = 0;//求和次数
    int wLength = xlength + ylength - 1;//相关输出序列的长度
    for (k = 0; k<wLength; k++) {
        corrout[k] = 0;
        for (i = (0>k + 1 - xlength ? 0 : k + 1 - xlength); i <= (k<ylength - 1 ? k : ylength - 1); i++) {
            corrout[k] += (xcorr[k-i]*ycorr[ylength-1-i]);
            ii++;
        }
    }
}


void mycorr::CorrFFT(double *xcorr, double *ycorr, int length, double *corrout)
{
    QTime t;
    t.start();
    int length2 = 2*length-1;
    int index;
    int *range = new int[length2]{0};
    for (index=0;length2>=pow(2,index);++index) {}
    int index_2 = pow(2,index);
    int index_2_2 = pow(2,index-1);
    complex *xdata = new complex[index_2];
    complex *ydata = new complex[index_2];
    complex *datatoifft = new complex[index_2];
    double *corrifft = new double[index_2]{0};
    for (int i=0;i<length;++i) {
        xdata[i].real = xcorr[i];
        ydata[i].real = ycorr[i];
    }

    myfft::fft(xdata,index_2,xdata);
    myfft::fft(ydata,index_2,ydata);

    for (int i=0;i<index_2;++i) {
        ydata[i].imag = -ydata[i].imag;
        datatoifft[i] = myfft::multiply_complex(xdata[i],ydata[i]);
    }
    myfft::ifft(datatoifft,index);


    for (int i=index_2_2;i<index_2;++i) {
        corrifft[i-index_2_2] = datatoifft[i].real/index_2;
    }
    for (int i=0;i<index_2_2;++i) {
        corrifft[i+index_2_2] = datatoifft[i].real/index_2;
    }

    int range1 = index_2_2+1-(length2-1)/2-1;
    for (int i=0;i<=length2;i++) {
        range[i] = range1+i;
    }

    for (int i=0;i<length2;i++) {
        corrout[i] = corrifft[range[i]];
        //qDebug()<<corrout[i];
    }

}

