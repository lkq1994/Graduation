#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>



#include <QtNetwork>
#include <iostream>
#include <fstream>
#include <string>

#include "myqthread.h"
#include "myfft.h"




#include <qapplication.h>
#include <qlayout.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <math.h>


#define cow224 16777216.0

namespace Ui {
class widget;
}



class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    //按钮
    void on_ReceiveButton_clicked();
    void on_SendButton_clicked();
    void on_SetupButton_clicked();
    void on_ClearButton_clicked();
    void on_ConnectButton_clicked();
    void on_StartButton_clicked();
    void on_StopButton_clicked();


    //信号
    void DataRead();
    void DisConnect();
    void DisplayASCII(QString);

private:
    Ui::widget *ui;
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    QString receivetxt = "";
    QString message = "";

    QwtPlotCurve * curve = new QwtPlotCurve("Acc_X");

    int DataCount = 0;
    double *Signalx = new double[200]{0};



public:
    static double DatatoLFM0[10000];
    static double DatatoLFM1[10000];
    static bool DataFlag;
    static double SignalData[200];

};





#endif // WIDGET_H
