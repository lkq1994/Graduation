#ifndef ANALYDATA_H
#define ANALYDATA_H

#include <QByteArray>
#include <QString>

class AnalyData
{
public:
    AnalyData();

    //字节数组转16进制字符串
    static QString  byteArrayToHexStr(const QByteArray &data);

    static int      HexStr2Int(QString qsData);
    static bool     IsFristOne(int iNum);
    static float    GetVoltage(int iNum);
};

#endif // ANALYDATA_H
