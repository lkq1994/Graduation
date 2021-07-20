#include "analydata.h"

AnalyData::AnalyData()
{

}

QString AnalyData::byteArrayToHexStr(const QByteArray &data)
{
    QString temp = "";
    QString hex = data.toHex();

    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }

    return temp.trimmed().toUpper();
}

int AnalyData::HexStr2Int(QString qsData)
{
    if(0 == qsData.length())
    {
        return 0;
    }

    QString qsOne   = qsData.left(2);
    QString qsTwo   = qsData.mid(3,2);
    QString qsThird = qsData.mid(6,2);

    QString qsTemp = QString("").append(qsThird).append(qsTwo).append(qsOne);

    int iRet = qsTemp.toInt(nullptr,16);
    return iRet;
}

inline bool AnalyData::IsFristOne(int iNum)
{
    return ((iNum >>(24-1)) & 1);
}

float AnalyData::GetVoltage(int iNum)
{
    if( !IsFristOne(iNum) )
    {

    }else{
        if( iNum>8388608 )
        {
            iNum = iNum-16777216;
        }
        else if( iNum==8388608 )
        {
            iNum = 0;
        }
    }
    float dRet = (iNum/8388608.00000000)*4.096;
    return dRet;
}
