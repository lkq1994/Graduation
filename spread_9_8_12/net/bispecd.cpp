#include "bispecd.h"

bispecd::bispecd()
{

}


double bispecd::Bispectrum(double *x, int Num, int Nfft, int wind, int nsamp, int overlap)
{
    int ly, nrecs;
    int nadvance;
    int overlaptemp;

//	float *Bspec = NULL;//保存双谱估计结果
//	Bspec = (float*)malloc(Nfft*Nfft*sizeof(float));

    double *xseg = NULL;
    xseg = (double *)malloc(nsamp*sizeof(double));

    struct compx *s = NULL;
    s = (struct compx *)malloc(Nfft*sizeof(struct compx));
    struct compx *s_out = NULL;
    s_out = (struct compx *)malloc(Nfft*sizeof(struct compx));

    double SumBspec = 0;//双谱估计求和

    overlaptemp = overlap;

    ly = Num; nrecs = 1;		//在x为一维数组的情况下
    ly = 2*nsamp - overlap;

    overlap = (int)(nsamp * overlap / 100.0);
    nadvance = nsamp - overlap;
    nrecs = (int)((double)(ly*nrecs - overlap) / nadvance);//这一段没有特别看懂


    nadvance = nsamp - overlaptemp - 1;
    double mean = 0;


    for (int krec = 0; krec < nrecs+1; krec++)
    {
        double sumDATA = 0;
        for (int i = 0; i < nsamp; i++)
        {
            sumDATA = x[i + nadvance] + sumDATA;
        }
        mean = sumDATA / nsamp;

        for (int i = 0; i < nsamp; i++)
        {
            xseg[i] = x[i+nadvance];
            s[i].real = xseg[i]-mean;
            s[i].imag = 0;

        }

        nadvance++;
        myfft::fft(s, Nfft, s_out);

        for (int i = 0; i < Nfft; i++)
        {
            s[i].real = s[i].real / nsamp;
            s[i].imag = s[i].imag / nsamp;
        }

        for (int i = 0; i < Nfft; i++)
        {
            for (int j = i; j < Nfft; j++)
            {
                if (j != i)
                {
                    SumBspec = SumBspec + ConjMultiAbs(s[i], s[j]) * 2;
                }
                else
                {
                    SumBspec = SumBspec + ConjMultiAbs(s[i], s[j]);
                }
            }
        }
    }


    free(xseg);
    free(s);
    //free();

    //printf("%f  ", SumBspec);
    return SumBspec;
}



double bispecd::ConjMultiAbs(struct compx a, struct compx b)
{
    struct compx c;
    c.real = a.real*b.real - a.imag*b.imag;
    c.imag = a.real*b.imag + a.imag*b.real;

    return c.real*c.real + c.imag*c.imag;
}


