

#ifndef MYQTHREAD_H
#define MYQTHREAD_H


#include <QThread>
#include <QFile>


#include "widget.h"
#include "myfft.h"
#include "bispecd.h"
#include "mycorr.h"
#include "despread.h"

#define DATALENGTH 128
#define BUFFERLENGTH  200


typedef struct{
    bool flag;
    int position;
} positionStruct;





class mythread_one : public QThread
{
    Q_OBJECT
public:
    explicit mythread_one(QObject *parent = nullptr);
protected:
    void run();//多线程执行的内容将通过重新该虚函数实现

private:
    int LFMLength = int(0.1*100000);
    double *LFMData = new double[LFMLength]{0};
    double *LFMCorrOut = new double[2*LFMLength-1]{0};
    double *corrifft = new double[32768];
    double *fft_corr1 = new double[32768];
    double *fft_corr2 = new double[32768];
    complex *datatoifft = new complex[32768];
    int *range = new int[2*LFMLength-1]{0};
    const double Threshold = 2000;//相关门限
    int count = 0;
    const int length = 305550;
    double *signaltodespread = new double[length]{0};
    //double *carrier = new double[511*50*49]{0};
    double *signaldatac = new double[511*50*49]{0};


public:
    positionStruct findLFMPosition(double*, double,int);
    static bool LFMCreat(double fs, double fl, double fh,
                         double time, double *LFMOut);
    double abs(double x);
    //static void mycorr(double *u, int m, double *v, int n, double *w);
    static int position;
    static bool CorrFlag;
    static double FrameData[5*1000000];
    static positionStruct flag;
    static bool despreadProcessingFlag;


signals:
    void SendMessageContent(QString);


};



#endif

 // QTHREAD_H
