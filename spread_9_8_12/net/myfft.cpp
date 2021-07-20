
#include "myfft.h"


double *SIN_TAB;
myfft::myfft()
{

}



void myfft::create_sin_tab(double *sin_t,int PointNum, double *sintab_out)
{
  int i;
  sintab_out = (double *)malloc(sizeof (double)*(PointNum/4+1));
  sintab_out=sin_t;
//  FFT_N=PointNum;
  for(i=0;i<= PointNum /4;i++)
    sintab_out[i]=sin(2*PI*i/ PointNum);
}


double myfft::sin_tab(double_t pi, int nfft, double *sintab_in)
{

  int n=0;
  double a=0;
   n=(int)(pi*nfft /2/PI);

  if(n>=0&&n<= nfft /4)
    a=sintab_in[n];
  else if(n>nfft /4&&n<nfft /2)
    {
     n-= nfft /4;
     a=sintab_in[nfft /4-n];
    }
  else if(n>= nfft /2&&n<3* nfft /4)
    {
     n-= nfft /2;
     a=-sintab_in[n];
   }
  else if(n>=3* nfft /4&&n<3* nfft)
    {
     n= nfft -n;
     a=-sintab_in[n];
   }

  return a;
}


double myfft::cos_tab(double pi, int nfft, double *sintab_in)
{

    double a,pi2;
    pi2=pi+PI/2;
    if(pi2>2*PI)
      pi2-=2*PI;
    a=sin_tab(pi2,nfft,sintab_in);
    return a;
}

struct compx myfft::EE(struct compx a,struct compx b)
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

void myfft::ChangeSeat(complex *DataInput, int N_fft)
{
    int nextValue, nextM, i, k, j = 0;
    complex temp;

    nextValue = N_fft / 2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
    nextM = N_fft - 1;
    for (i = 0; i<nextM; i++)
    {
        if (i<j)                    //如果i<j,即进行变址
        {
            temp = DataInput[j];
            DataInput[j] = DataInput[i];
            DataInput[i] = temp;
        }
        k = nextValue;                //求j的下一个倒位序
        while (k <= j)                //如果k<=j,表示j的最高位为1
        {
            j = j - k;                    //把最高位变成0
            k = k / 2;                    //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
        }
        j = j + k;                        //把0改为1
    }
}


complex myfft::multiply_complex(complex a, complex b)
{
    complex temp;

    temp.real = a.real * b.real - a.imag*b.imag;
    temp.imag = b.imag*a.real + a.imag*b.real;

    return temp;
}


void myfft::fft(struct compx *xin, int nfft, struct compx *xout)
{

  double *sintab = (double *)malloc(sizeof (double)*(nfft/4+1));
  double *sintab_out;
  //sintab = malloc(sizeof (double))*(nfft/4+1);
  create_sin_tab(sintab,nfft,sintab_out);
  int f,m,i,k,l,j=0;
  int nv2,nm1;
  struct compx u,w,t;

   nv2= nfft /2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
   nm1= nfft -1;
   for(i=0;i<nm1;i++)
   {
    if(i<j)                    //如果i<j,即进行变址
     {
      t=xin[j];
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //求j的下一个倒位序
    while(k<=j)               //如果k<=j,表示j的最高位为1
     {
      j=j-k;                 //把最高位变成0
      k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
     }
   j=j+k;                   //把0改为1
  }


   int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f= nfft;
   for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
           ;
  for(m=1;m<=l;m++)                         // 控制蝶形结级数
   {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
    le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
    lei=le/2;                               //同一蝶形结中参加运算的两点的距离
    u.real=1.0;                             //u为蝶形结运算系数，初始值为1
    u.imag=0.0;
    //w.real=cos(PI/lei);                  //不适用查表法计算sin值和cos值
    // w.imag=-sin(PI/lei);
    w.real=cos_tab(PI/lei,nfft,sintab);                //w为系数商，即当前系数与前一个系数的商
    w.imag=-1*sin_tab(PI/lei,nfft,sintab);
    for(j=0;j<=lei-1;j++)                  //控制计算不同种蝶形结，即计算系数不同的蝶形结
     {
      for(i=j;i<=nfft-1;i=i+le)           //控制同一蝶形结运算，即计算系数相同蝶形结
       {
        ip=i+lei;                          //i，ip分别表示参加蝶形运算的两个节点
        t=EE(xin[ip],u);                   //蝶形运算，详见公式
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                          //改变系数，进行下一个蝶形运算
     }
   }
   for (int i=0;i<nfft;i++) {
       xout[i] = xin[i];
   }

}



void myfft::create_sin_table(double *sin_table,int nfft)
{
    for(int i=0; i<=nfft/4; i++)
    {
        sin_table[i] = sin(PI*i/(nfft/2));//SIN_TABLE[i] = sin(PI2*i/N);
        //qDebug()<<sin_table[i];
    }
}


double myfft::sin_find(double x,double *sin_table,int nfft)
{
    int i = (int)(nfft*x);
    i = i>>1;
    if(i>nfft/4)//注意：i已经转化为0~N之间的整数了！
    {//不会超过N/2
        i = nfft/2 - i;//i = i - 2*(i-Npart4);
    }
    return sin_table[i];
}

double myfft::cos_find(double x,double *sin_table,int nfft)
{
    int i = (int)(nfft*x);
    i = i>>1;
    if(i<nfft/4)//注意：i已经转化为0~N之间的整数了！
    {//不会超过N/2
        //i = Npart4 - i;
        return sin_table[nfft/4 - i];
    }
    else//i>Npart4 && i<N/2
    {
        //i = i - Npart4;
        return -sin_table[i - nfft/4];
    }
}


void myfft::ifft(complex *fft_data, int nfft_prescribe)
{
    int n_nfft = pow(2,nfft_prescribe);
    //int L = 0, J = 0, K = 0;
    int B = 0;
    int step = 0,KB = 0;
    double P = 0, T = 0;
    complex W, Temp_XX;
    double angle;
    double *SIN_TABLE = new double[n_nfft/4+1];
    //ElemType TempResult[N];
    create_sin_table(SIN_TABLE,n_nfft);

    ChangeSeat(fft_data, n_nfft);
    for(int L=1; L<=nfft_prescribe; L++)
     {
         step = 1<<L;//2^L
         B = step>>1;//B=2^(L-1)
         for(int J=0; J<B; J++)
         {
             //P = (1<<(M-L))*J;//P=2^(M-L) *J
             angle = (double)J/B;            //这里还可以优化

             W.imag =   sin_find(angle,SIN_TABLE,n_nfft);        //用C++该函数课声明为inline
             W.real =   cos_find(angle,SIN_TABLE,n_nfft);        //用C++该函数课声明为inline
             //W.real =  cos(angle*PI);
             //W.imag = -sin(angle*PI);
             for(int K=J; K<n_nfft; K=K+step)
             {
                 KB = K + B;
                 //Temp_XX = XX_complex(data[KB],W);
                 //用下面两行直接计算复数乘法，省去函数调用开销
                 Temp_XX.real = fft_data[KB].real * W.real-fft_data[KB].imag*W.imag;
                 Temp_XX.imag = W.imag*fft_data[KB].real + fft_data[KB].imag*W.real;

                 fft_data[KB].real = fft_data[K].real - Temp_XX.real;
                 fft_data[KB].imag = fft_data[K].imag - Temp_XX.imag;

                 fft_data[K].real = fft_data[K].real + Temp_XX.real;
                 fft_data[K].imag = fft_data[K].imag + Temp_XX.imag;
             }
         }
     }
}





