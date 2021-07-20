#include "widget.h"
#include "ui_widget.h"
#include "analydata.h"
//#include "myfft.h"


#include <QString>
#include <QtNetwork/QtNetwork>

#include <QHostAddress>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTime>

#include <iostream>
#include <fstream>
#include <iomanip>

//double *test = new double[10000*2-1]{0};

mythread_one a;
double widget::DatatoLFM0[10000] = {0};
double widget::DatatoLFM1[10000] = {0};
bool widget::DataFlag = true;
double widget::SignalData[200] = {0};

double menxian = 0;

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{

    ui->setupUi(this);
    setWindowTitle("通信接收机");

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(DataRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(DisConnect()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisConnect()));

    connect(&a, SIGNAL(SendMessageContent(QString)), this, SLOT(DisplayASCII(QString)));

    QString localHost = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHost);
    ui->HostNameEdit->setText(localHost);
    QString IPaddress;
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            IPaddress += address.toString();
            IPaddress += QString("\n");
        }
    }
    ui->IPaddressEdit->setText(IPaddress);

    QString defultIP = "192.168.1.168";
    static int defultPort = 8080;
    ui->AddressEdit->setText(defultIP);
    ui->SeverPortEdit->setText(QString::number(defultPort));


    ui->SignalPlot->setAxisScale(2,0,200);//x
    ui->SignalPlot->setAxisScale(0,-5,5);//y
    //ui->PlotlLayout->addWidget(plot);
    //curve->setSamples(x,y,9);
    curve->attach(ui->SignalPlot);
    //ui->SignalPlot->mouseMoveEvent();

    for (int i=0;i<200;++i) {
        Signalx[i] = i;
    }
    ui->throld->setText("2000");
    //DataCount = 0;
}

void widget::DisConnect()
{
    qDebug()<<"发生未知错误";
    ui->constatus->setText("发生未知错误");
    ui->SetupButton->setText("连接");
}

void widget::on_ConnectButton_clicked()
{
    QByteArray sendbuff = "$0,0,0,0*";
    tcpSocket->write(sendbuff);
    //a.start();
    qDebug()<<"send data : "<<sendbuff;
}


void widget::on_StartButton_clicked()
{
    QString StartCommand = "$0,5,0,";
    QByteArray SendStartCommand = "";
    StartCommand += QString::number((ui->SampBox->currentIndex()));
    StartCommand += ",";
    StartCommand += QString::number((ui->GainBox->currentIndex()));
    StartCommand += ",1,1*";
    SendStartCommand = StartCommand.toLatin1();
    qDebug()<<SendStartCommand;
    tcpSocket->write(SendStartCommand);
    qDebug()<<"send data : "<<SendStartCommand;
    menxian = ui->throld->text().toDouble();
    //qDebug()<<menxian;
}



void widget::on_SendButton_clicked()
{
    QByteArray sendbuff = ui->SendEdit->text().toLatin1();
    tcpSocket->write(sendbuff);
    a.start();
    qDebug()<<"send data : "<<sendbuff;

}


void widget::on_ReceiveButton_clicked()
{
    qDebug()<< AnalyData::GetVoltage(AnalyData::HexStr2Int("7F FF FF"));

}

void widget::DataRead()
{
    //qDebug()<<"2";
    QTime t;
    t.start();

    QString qsPointData[200] = {""};

    QByteArray data = tcpSocket->read(664);
    if (data.length() <= 0) {
        return;
    }


    QString qsMesTmp = data.mid(3,8);
    if((0 == qsMesTmp.compare("$0,5,0,0")) || (0 == qsMesTmp.compare("$0,0,0,0")) || (0 == qsMesTmp.compare("$0,6,0,0")))
    {
        QString qstemp = "";
        qstemp = qsMesTmp+"\n";
        receivetxt = qstemp+receivetxt;
        qDebug()<<"receive data : "<<qsMesTmp;
        ui->ReceiveEdit->setText(receivetxt);
    }

    else
    {
        QString qsTemp = AnalyData::byteArrayToHexStr(data);
        QString qsDataTemp = qsTemp.mid(192,qsTemp.length()-192);//去除包头
        if(data.length() == 664)
        {
            QString qsTempMid = qsTemp.mid(0,11);
            if( 0 == qsTempMid.compare("AA AA 55 55"))
            {

                for (int i=0;i<qsDataTemp.length();i=i+9) {
                    qsPointData[i/9] = qsDataTemp.mid(i,8);
                    //qDebug()<<qsPointData[i/9];
                }

                for (int i = 0; i < 200; ++i) {
                    //qDebug()<<AnalyData::GetVoltage(AnalyData::HexStr2Int(qsPointData[i]));
                    SignalData[i] =
                            AnalyData::GetVoltage(AnalyData::HexStr2Int(qsPointData[i]));    
                }
//
                curve->setSamples(Signalx,SignalData,200);
                curve->attach(ui->SignalPlot);
                ui->SignalPlot->replot();



                if(DataFlag)
                {
                    for (int i=0;i<200;i++) {
                        DatatoLFM0[DataCount*200+i] = SignalData[i];
                    }
                }
                else {
                    for (int i=0;i<200;i++) {
                        DatatoLFM1[DataCount*200+i] = SignalData[i];
                    }
                }


                if(DataCount >= 49)
                {
                    DataCount = 0;
                    if(mythread_one::despreadProcessingFlag == false)
                    {
                        a.start();
                    }

                }
                else {
                    DataCount++;
                }









                //emit SendMessageContent(qsTemp);

            }
        }

    }

//qDebug()<<t.elapsed()<<"ms";

}


void widget::on_StopButton_clicked()
{
    QByteArray StopCommand = "$0,6,0,0*";
    tcpSocket->write(StopCommand);
    qDebug()<<"send data : "<<StopCommand;
}



void widget::on_SetupButton_clicked()
{
    if(ui->SetupButton->text() == "连接")
    {
        QString severIP = ui->AddressEdit->text();
        quint16 severPort =quint16(ui->SeverPortEdit->text().toInt());

        tcpSocket->abort();
        tcpSocket->connectToHost(severIP,severPort,QTcpSocket::ReadWrite);
        if(tcpSocket->waitForConnected(1000))
        {
            ui->ListenPortEdit->setText(QString::number(tcpSocket->localPort()));
            ui->constatus->setText("已连接");
            ui->SetupButton->setText("断开");
            qDebug()<<"水听器连接成功";
        }
        else {
            ui->constatus->setText("连接失败");
            qDebug()<<"水听器连接失败";
        }
    }
    else {
        tcpSocket->abort();
        ui->constatus->setText("已断开");
        ui->SetupButton->setText("连接");
        qDebug()<<"水听器已断开";
    }

}



void widget::on_ClearButton_clicked()
{
    ui->ReceiveEdit->clear();
    receivetxt = "";
    ui->MessageBrowser->clear();
    message = "";
}

void widget::DisplayASCII(QString ascii)
{


    message = message+QString(ascii)+"\n";

    ui->MessageBrowser->setText(message);
    ui->MessageBrowser->moveCursor(QTextCursor::End);

}



widget::~widget()
{
    delete ui;
}





