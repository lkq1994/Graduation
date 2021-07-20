
#include "myqthread.h"
#include "widget.h"

#include <QMessageBox>
#include <QString>
#include <QTime>

extern double menxian;
extern Ui::widget *ui;
int mythread_one::position = 0;
bool mythread_one::CorrFlag = false;
bool mythread_one::despreadProcessingFlag = false;

positionStruct mythread_one::flag = {0,0};

complex test[32768] = {0,0};
double mythread_one::FrameData[5*1000000] = {0};

mythread_one::mythread_one(QObject *parent) : QThread(parent)
{
    LFMCreat(100000, 8000, 12000,
                            0.1, LFMData);
    for (int i=0;i<LFMLength;++i) {
       fft_corr2[i] = LFMData[i];
       //fft_corr1[i].real = LFMData[i];
    }

    for (int i=0;i<6000;++i) {
        fft_corr1[i+4000] = LFMData[i];
    }

    //connect(this, SIGNAL(SendMessageContent(ascii)), widget, SLOT(DisConnect()));

}


//void mythread_one::mycorr(double *u, int m, double *v, int n, double *w)
//{
//    QTime t;
//    t.start();
//    int ii = 0;
//    int k = 0;
//    int i = 0;//求和次数
//    int wLength = m + n - 1;//相关输出序列的长度
//    for (k = 0; k<wLength; k++) {
//        w[k] = 0;
//        for (i = (0>k + 1 - m ? 0 : k + 1 - m); i <= (k<n - 1 ? k : n - 1); i++) {
//            w[k] += (u[k-i]*v[n-1-i]);
//            ii++;
//        }
//    }
//    qDebug()<<ii;

//qDebug()<<t.elapsed()<<"ms";
//}


bool mythread_one::LFMCreat(double fs, double fl, double fh,
                            double time, double *LFMOut)
{
    //QTime x;
    //x.start();
    int LFMLength = fs*time;

    double B = fh-fl;

    for (int t = 0; t<LFMLength; t++) {
        LFMOut[t] = (double)sin(3.141592*t*(2 * fl + t*B / LFMLength) / fs);  //生成线性调频信号
        //std::cout << LFMSignal[t] << std::endl;

    }
//qDebug()<<LFMOut;
    //qDebug()<<x.elapsed()<<"ms";
    return true;
}


double mythread_one::abs(double x)
{
    if((x-0)<10e-4)
        x = -x;
    return x;
}


positionStruct mythread_one::findLFMPosition(double *corrdata, double level, int length)
{
    double maxtemp = 0;
    int position = 0;
    bool corrflag = false;
    positionStruct turn;
    for (int i=0;i<length;++i) {
       //qDebug()<<LFMCorrOut[i];

        if(level<abs(corrdata[i]))
        {
            //maxtemp = LFMCorrOut[i];
            if(maxtemp<=abs(corrdata[i]))
            {
                maxtemp = abs(corrdata[i]);
                position = i+1;
            }
            else {

            }
        }
    }
    if(position>1000&&position<19000)
    {
        corrflag = true;
        qDebug()<<maxtemp;
    }
    turn.flag = corrflag;
    turn.position = position;
    return  turn;
}

void mythread_one::run()
{


    QTime t;
    t.start();


    if(flag.flag == false){
         if(widget::DataFlag)
         {
             widget::DataFlag = false;

             for (int i=0;i<10000;++i) {
                fft_corr1[i] = widget::DatatoLFM0[i];
             }

         }
         else {
             widget::DataFlag = true;
             for (int i=0;i<10000;++i) {
                fft_corr1[i] = widget::DatatoLFM1[i];
             }

         }
         mycorr::CorrFFT(fft_corr1,fft_corr2,10000,LFMCorrOut);
         flag = findLFMPosition(LFMCorrOut,menxian,19999);
         //qDebug()<<flag.flag;
         if(flag.flag == true){
         emit SendMessageContent("sync is ok");
         emit SendMessageContent("position is :");
         emit SendMessageContent(QString::number(flag.position,10));
         emit SendMessageContent("Demodulating...");
         qDebug()<<flag.position;
         }
     }
    else {
            if(widget::DataFlag)
            {
                widget::DataFlag = false;
                for (int i=0;i<10000;i++) {
                    FrameData[count*10000+i] = widget::DatatoLFM0[i];
                }

            }
            else {
                widget::DataFlag = true;
                for (int i=0;i<10000;++i) {
                   FrameData[count*10000+i] = widget::DatatoLFM1[i];
                }
            }

            if(count<2.0*1000000.0/10000.0){
                count++;
            }
            else {
                despreadProcessingFlag = true;
                count = 0;
                qDebug()<<"data is ok";
    //                        if(flag.position>10000)
    //                            flag.position = flag.position;
                for (int i=0;i<50*511*49;i++) {
                    signaldatac[i] = FrameData[flag.position+i];
                }

                char *code = new char[96]{0};

                            //处理程序

                QFile f("E:\\Graduation\\QTprogram\\spread_9_8_12\\test.txt");
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                   qDebug() << "Open failed." << endl;
                }
                QTextStream txtoutput(&f);

                //             for (int i=0;i<50*97*63;i++) {
                //                 txtoutput<<signaldatac[i]<<",";
                //             }
                for (int i=0;i<500000;i++) {
                    txtoutput<<FrameData[i]<<",";
                }
                f.close();

                QFile f1("E:\\Graduation\\QTprogram\\spread_9_8_12\\test1.txt");
                if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                   qDebug() << "Open failed." << endl;
                }
                QTextStream txtoutpu1(&f1);

                for (int i=0;i<50*49*511;i++) {
                   txtoutpu1<<signaldatac[i]<<",";
                }
                //              for (int i=0;i<500000;i++) {
                //                  txtoutput<<FrameData[i]<<",";
                //              }
                f.close();



                despread::DeSpreadCode(100000, 8000, 12000, despread::pn, 9, signaldatac, 48, code);

                //            for (int i=0;i<96;i++) {
                //                qDebug() <<QString::fromLocal8Bit(code);
                //            }
                QString ASCII = "";
                char ascii = 0;
                for (int i=0;i<6;i++) {
                    for (int j=0;j<8;j++) {
                        ascii = (ascii<<1)+code[i*8+j];
                    }
                    qDebug()<<ascii;
                    ASCII += QString(ascii);

                }
                emit SendMessageContent("messagae :");
                emit SendMessageContent(ASCII);
                count = 0;
                despreadProcessingFlag = false;
                flag.flag = false;
                qDebug()<<"processing is ok";
            }



    }




}




