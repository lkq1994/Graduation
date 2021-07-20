#include "despread.h"

//double despread::pn[63] = { 1,-1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,1,-1,
//                           -1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1 };



double despread::pn[511] = { 1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,
                             -1,1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,
                             -1,1,1,-1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,
                             -1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,1,
                             1,1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,-1,1,1,
                             1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,
                             -1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,
                             -1,-1,1,-1,1,1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,1,1,
                             1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,1,-1,1,
                             -1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,
                             -1,1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,
                             1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,
                             1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,
                             1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,1,
                             -1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,
                             1,1,1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,-1,
                             -1,-1,1,-1,-1,-1,-1};





despread::despread()
{

}



/*

walsh		m序列
walshlength	m序列长度
SignalTotalLength	信号数据总长
SpreadCodeTotalLength	扩频后的数据总长
CodeTotalLength	数据总长

*/
void despread::DeSpreadCode(double fs, double flow, double fhigh, double *walsh,
                            int PNLength, double *SignalData, int CodeTotalLength, char *decode)
{
    QTime t;
    t.start();

    //以下为了适配项目固定的参数
    //fs = 100000;
    //CodeTotalLength = 96;



    double M = fs / (fhigh - flow)*2;
    int walshlength = (int)pow(2, PNLength) - 1;
    int SignalTotalLength = M*(CodeTotalLength+1)*walshlength;
    int SpreadCodeTotalLength = walshlength*(CodeTotalLength + 1);

    double enery1 = 0;
    double enery2 = 0;

    double f0 = (fhigh + flow) / 2;
    //float *a = (float *)malloc((2 * walshlength - 1)*sizeof(float));
    //float *b = (float *)malloc((2 * walshlength - 1)*sizeof(float));
    //float *c = (float *)malloc((2 * walshlength - 1)*sizeof(float));
    //float *d = (float *)malloc((2 * walshlength - 1)*sizeof(float));
    //float *e = (float *)malloc((2 * walshlength - 1)*sizeof(float));
    //float *PN = (float *)malloc((2 * walshlength)*sizeof(float));


    double *a = new double[4 * walshlength - 1];
    double *b = new double[4 * walshlength - 1];
    double *c = new double[4 * walshlength - 1];
    double *d = new double[4 * walshlength - 1];
    double *e = new double[2 * walshlength - 1];
    double *PN1 = new double[2 * walshlength];
    double *PN2 = new double[2 * walshlength];

    //float *codereal = (float *)malloc(SpreadCodeTotalLength*sizeof(float));
    //float *codeimag = (float *)malloc(SpreadCodeTotalLength*sizeof(float));

    double *codereal = new double[SpreadCodeTotalLength];
    double *codeimag = new double[SpreadCodeTotalLength];

    //int *decode = (int *)malloc(CodeTotalLength*sizeof(int));

    //struct compx *sindata = (struct compx *)malloc(SignalTotalLength*sizeof(struct compx));
    //struct compx *CodeCalculation = (struct compx *)malloc(SignalTotalLength*sizeof(struct compx));

    struct compx *sindata = new struct compx[SignalTotalLength];
    struct compx *CodeCalculation = new struct compx[SignalTotalLength];

    //float *sindata = (float *)malloc(SIGNALDATALENGTH*sizeof(float));
    //float *CodeCalculation = (float *)malloc(SIGNALDATALENGTH*sizeof(float));



    memset(a, 0, (2 * walshlength - 1)*sizeof(double));
    memset(b, 0, (2 * walshlength - 1)*sizeof(double));
    memset(c, 0, (2 * walshlength - 1)*sizeof(double));
    memset(d, 0, (2 * walshlength - 1)*sizeof(double));
    memset(e, 0, (2 * walshlength - 1)*sizeof(double));
    memset(codereal, 0, SpreadCodeTotalLength*sizeof(double));
    memset(codeimag, 0, SpreadCodeTotalLength*sizeof(double));
    memset(sindata, 0, SignalTotalLength*sizeof(struct compx));
    memset(CodeCalculation, 0, SignalTotalLength*sizeof(struct compx));


    for (int i = 0; i < walshlength; i++)
    {
        PN1[i] = walsh[i];
        PN2[i] = walsh[i];
    }

    for (int i = walshlength; i < 2*walshlength; i++)
    {
        PN1[i] = walsh[i- walshlength];
        PN2[i] = -1*walsh[i- walshlength];
    }

    for (int i = 0; i < SignalTotalLength; i++)
    {
        sindata[i].real = sin(2 * PI*f0*i / fs);                                    //改正一
        sindata[i].imag = cos(2 * PI*f0*i / fs);
        //printf("%f  ",sindata[i].real);
    }

    for (int i = 0; i < SignalTotalLength; i++)
    {
        CodeCalculation[i].real = sindata[i].real * SignalData[i];
        CodeCalculation[i].imag = sindata[i].imag * SignalData[i];
        //printf("%f  ", CodeCalculation[i].real);
    }

    for (int i = 0; i < SpreadCodeTotalLength; i++)
    {
        double SumReal = 0,SumImag = 0;
        int j = 0;
        j = M*i;
        for (int k = 0; k < M; k++)
        {
            SumReal = CodeCalculation[j+k].real + SumReal;
            SumImag = CodeCalculation[j+k].imag + SumImag;
            //printf("%f  ", SumReal);
        }
        codereal[i] = SumReal / M;
        codeimag[i] = SumImag / M;
        //codereal[i] = CodeCalculation[j + 2].real;
        //codeimag[i] = CodeCalculation[j + 2].imag;

        //printf("%f  ", codereal[i]);
    }

    for (int i = 0; i < SpreadCodeTotalLength- 2*walshlength+1; i = i + walshlength)
    {
        enery1 = 0 , enery2 = 0;

        mycorr::CorrDirect( &codereal[i], PN1, 2 * walshlength, 2 * walshlength, a );
        mycorr::CorrDirect( &codeimag[i], PN1, 2 * walshlength, 2 * walshlength, b );
        mycorr::CorrDirect( &codereal[i], PN2, 2 * walshlength, 2 * walshlength, c );
        mycorr::CorrDirect( &codeimag[i], PN2, 2 * walshlength, 2 * walshlength, d );


        for (int j = walshlength+5; j < 3 * walshlength-5; j++)
        {
            enery1 = a[j] * a[j] + b[j] * b[j] + enery1;
            enery2 = c[j] * c[j] + d[j] * d[j] + enery2;
        }

        if (enery1 - enery2 > 0) {decode[i / walshlength] = 1;
            //qDebug()<<"1";
        }
        else {decode[i / walshlength] = 0;
            //qDebug()<<"0";
        }
        //printf("%d ", decode[i / walshlength]);
        //printf("%f  ", enery2);
        //printf("%d ", i/31);


    }

    free(sindata);
    free(CodeCalculation);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(PN1);
    free(PN2);
    //free(decode);

    qDebug()<<"despread:"<<t.elapsed()<<"ms";
}




