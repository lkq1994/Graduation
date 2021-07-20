/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *ReceiveEdit;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *HostNameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *IPaddressEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *AddressEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *SeverPortEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *ListenPortEdit;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *SendEdit;
    QPushButton *SendButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *SetupButton;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *ReceiveButton;
    QPushButton *ClearButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_7;
    QComboBox *SampBox;
    QLabel *label_8;
    QComboBox *GainBox;
    QPushButton *ConnectButton;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QVBoxLayout *verticalLayout_2;
    QwtPlot *SignalPlot;
    QHBoxLayout *horizontalLayout_9;
    QLabel *constatus;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(660, 533);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        ReceiveEdit = new QTextEdit(widget);
        ReceiveEdit->setObjectName(QString::fromUtf8("ReceiveEdit"));

        horizontalLayout_6->addWidget(ReceiveEdit);

        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        HostNameEdit = new QLineEdit(widget);
        HostNameEdit->setObjectName(QString::fromUtf8("HostNameEdit"));

        horizontalLayout->addWidget(HostNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        IPaddressEdit = new QLineEdit(widget);
        IPaddressEdit->setObjectName(QString::fromUtf8("IPaddressEdit"));

        horizontalLayout_2->addWidget(IPaddressEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        AddressEdit = new QLineEdit(widget);
        AddressEdit->setObjectName(QString::fromUtf8("AddressEdit"));

        horizontalLayout_3->addWidget(AddressEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        SeverPortEdit = new QLineEdit(widget);
        SeverPortEdit->setObjectName(QString::fromUtf8("SeverPortEdit"));

        horizontalLayout_4->addWidget(SeverPortEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        ListenPortEdit = new QLineEdit(widget);
        ListenPortEdit->setObjectName(QString::fromUtf8("ListenPortEdit"));

        horizontalLayout_5->addWidget(ListenPortEdit);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        SendEdit = new QLineEdit(widget);
        SendEdit->setObjectName(QString::fromUtf8("SendEdit"));
        SendEdit->setEnabled(true);
        SendEdit->setMinimumSize(QSize(200, 20));
        SendEdit->setMaximumSize(QSize(133, 16777215));

        horizontalLayout_7->addWidget(SendEdit);

        SendButton = new QPushButton(widget);
        SendButton->setObjectName(QString::fromUtf8("SendButton"));

        horizontalLayout_7->addWidget(SendButton);

        horizontalSpacer_5 = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        SetupButton = new QPushButton(widget);
        SetupButton->setObjectName(QString::fromUtf8("SetupButton"));

        horizontalLayout_7->addWidget(SetupButton);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        ReceiveButton = new QPushButton(widget);
        ReceiveButton->setObjectName(QString::fromUtf8("ReceiveButton"));

        horizontalLayout_8->addWidget(ReceiveButton);

        ClearButton = new QPushButton(widget);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));

        horizontalLayout_8->addWidget(ClearButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        SampBox = new QComboBox(widget);
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->addItem(QString());
        SampBox->setObjectName(QString::fromUtf8("SampBox"));

        horizontalLayout_8->addWidget(SampBox);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        GainBox = new QComboBox(widget);
        GainBox->addItem(QString());
        GainBox->addItem(QString());
        GainBox->setObjectName(QString::fromUtf8("GainBox"));

        horizontalLayout_8->addWidget(GainBox);

        ConnectButton = new QPushButton(widget);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));

        horizontalLayout_8->addWidget(ConnectButton);

        StartButton = new QPushButton(widget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));

        horizontalLayout_8->addWidget(StartButton);

        StopButton = new QPushButton(widget);
        StopButton->setObjectName(QString::fromUtf8("StopButton"));

        horizontalLayout_8->addWidget(StopButton);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        SignalPlot = new QwtPlot(widget);
        SignalPlot->setObjectName(QString::fromUtf8("SignalPlot"));
        SignalPlot->setMinimumSize(QSize(559, 211));

        verticalLayout_2->addWidget(SignalPlot);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        constatus = new QLabel(widget);
        constatus->setObjectName(QString::fromUtf8("constatus"));
        constatus->setMinimumSize(QSize(72, 0));

        horizontalLayout_9->addWidget(constatus);

        horizontalSpacer_4 = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "widget", nullptr));
        label->setText(QApplication::translate("widget", "\346\234\254\346\234\272\345\220\215\347\247\260", nullptr));
        label_2->setText(QApplication::translate("widget", "\346\234\254\346\234\272IP  ", nullptr));
        label_3->setText(QApplication::translate("widget", "\350\277\234\347\250\213IP  ", nullptr));
        label_4->setText(QApplication::translate("widget", "\350\277\234\347\250\213\347\253\257\345\217\243", nullptr));
        label_5->setText(QApplication::translate("widget", "\346\234\254\345\234\260\347\253\257\345\217\243", nullptr));
        SendButton->setText(QApplication::translate("widget", "\345\217\221\351\200\201", nullptr));
        SetupButton->setText(QApplication::translate("widget", "\350\277\236\346\216\245", nullptr));
        ReceiveButton->setText(QApplication::translate("widget", "\345\274\200\345\247\213\346\216\245\346\224\266", nullptr));
        ClearButton->setText(QApplication::translate("widget", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        label_7->setText(QApplication::translate("widget", "\351\207\207\346\240\267\347\216\207", nullptr));
        SampBox->setItemText(0, QApplication::translate("widget", "1kHz", nullptr));
        SampBox->setItemText(1, QApplication::translate("widget", "2kHz", nullptr));
        SampBox->setItemText(2, QApplication::translate("widget", "2.5kHz", nullptr));
        SampBox->setItemText(3, QApplication::translate("widget", "5kHz", nullptr));
        SampBox->setItemText(4, QApplication::translate("widget", "10kHz", nullptr));
        SampBox->setItemText(5, QApplication::translate("widget", "20kHz", nullptr));
        SampBox->setItemText(6, QApplication::translate("widget", "25kHz", nullptr));
        SampBox->setItemText(7, QApplication::translate("widget", "50kHz", nullptr));
        SampBox->setItemText(8, QApplication::translate("widget", "100kHz", nullptr));

        label_8->setText(QApplication::translate("widget", "\345\242\236\347\233\212", nullptr));
        GainBox->setItemText(0, QApplication::translate("widget", "20dB", nullptr));
        GainBox->setItemText(1, QApplication::translate("widget", "40dB", nullptr));

        ConnectButton->setText(QApplication::translate("widget", "\345\224\244\351\206\222\346\214\207\344\273\244", nullptr));
        StartButton->setText(QApplication::translate("widget", "\351\207\207\351\233\206\346\214\207\344\273\244", nullptr));
        StopButton->setText(QApplication::translate("widget", "\345\201\234\346\255\242\346\214\207\344\273\244", nullptr));
        constatus->setText(QApplication::translate("widget", "\347\255\211\345\276\205\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
