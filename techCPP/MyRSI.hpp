#ifndef  MY_RSI_HPP__
#define  MY_RSI_HPP__

#include "MySMA.hpp"
#include <algorithm>

class CMyRSI
{
public:
    CMyRSI(int nN1, int nN2, int nN3, int nResultMaxCnt)
    : m_nN1(nN1)
    , m_nN2(nN2)
    , m_nN3(nN3)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pData(nullptr)
    , m_pRSI1(nullptr)
    , m_pRSI2(nullptr)
    , m_pRSI3(nullptr)
    {
        m_pData = new CTimeSeriesData<double>(2);

        m_pSMA11 = new CMySMA(m_nN1, 1, 2);
        m_pSMA12 = new CMySMA(m_nN1, 1, 2);

        m_pSMA21 = new CMySMA(m_nN2, 1, 2);
        m_pSMA22 = new CMySMA(m_nN2, 1, 2);

        m_pSMA31 = new CMySMA(m_nN3, 1, 2);
        m_pSMA32 = new CMySMA(m_nN3, 1, 2);

        m_pRSI1 = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pRSI2 = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pRSI3 = new CTimeSeriesData<double>(m_nResultMaxCnt);

    }

    ~CMyRSI()
    {
        if (m_pData){
            delete m_pData;
        }

        if(m_pSMA11){
            delete m_pSMA11;
        }

        if(m_pSMA12){
            delete m_pSMA12;
        }

        if(m_pSMA21){
            delete m_pSMA21;
        }

        if(m_pSMA22){
            delete m_pSMA22;
        }

        if(m_pSMA31){
            delete m_pSMA31;
        }

        if(m_pSMA32){
            delete m_pSMA32;
        }

        if (m_pRSI1){
            delete m_pRSI1;
        }

        if (m_pRSI2){
            delete m_pRSI2;
        }

        if (m_pRSI3){
            delete m_pRSI3;
        }
    }

    // RSI的计算公式如下：
    // LC:=REF(CLOSE,1);
    // RSI1:SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;
    // RSI2:SMA(MAX(CLOSE-LC,0),N2,1)/SMA(ABS(CLOSE-LC),N2,1)*100;
    // RSI3:SMA(MAX(CLOSE-LC,0),N3,1)/SMA(ABS(CLOSE-LC),N3,1)*100;
    void Append(const double& fData, bool bNewPeriod)
    {
        double fRSI1 = UN_VALID_VALUE(double);
        double fRSI2 = UN_VALID_VALUE(double);
        double fRSI3 = UN_VALID_VALUE(double);

        double fPreData = m_pData->GetCurPreData(bNewPeriod);

        if(IsValid(fPreData)){

            double fDiff = fData - fPreData;

            m_pSMA11->Append(std::max(fDiff, 0.00), bNewPeriod);
            m_pSMA12->Append(fabs(fDiff), bNewPeriod);

            m_pSMA21->Append(std::max(fDiff, 0.00), bNewPeriod);
            m_pSMA22->Append(fabs(fDiff), bNewPeriod);

            m_pSMA31->Append(std::max(fDiff, 0.00), bNewPeriod);
            m_pSMA32->Append(fabs(fDiff), bNewPeriod);

            fRSI1 = m_pSMA11->SMA(0) / m_pSMA12->SMA(0) * 100;
            fRSI2 = m_pSMA21->SMA(0) / m_pSMA22->SMA(0) * 100;
            fRSI3 = m_pSMA31->SMA(0) / m_pSMA32->SMA(0) * 100;
        }

        m_pData->AppendData(fData, bNewPeriod);

        m_pRSI1->AppendData(fRSI1, bNewPeriod);
        m_pRSI2->AppendData(fRSI2, bNewPeriod);
        m_pRSI3->AppendData(fRSI3, bNewPeriod);
    }

    double RSI1(int nIndex)
    {
        return m_pRSI1->GetData(nIndex);
    }

    double RSI2(int nIndex)
    {
        return m_pRSI2->GetData(nIndex);
    }

    double RSI3(int nIndex)
    {
        return m_pRSI3->GetData(nIndex);
    }

    void Reset()
    {
        m_pData->Reset();
        m_pSMA11->Reset();
        m_pSMA12->Reset();
        m_pSMA21->Reset();
        m_pSMA22->Reset();
        m_pSMA31->Reset();
        m_pSMA32->Reset();
        m_pRSI1->Reset();
        m_pRSI2->Reset();
        m_pRSI3->Reset();
    }

private:
    
    int                             m_nN1;

    int                             m_nN2;

    int                             m_nN3;

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pData;           // 原始数据

    CMySMA*                         m_pSMA11;          // 

    CMySMA*                         m_pSMA12;          // 

    CMySMA*                         m_pSMA21;          // 

    CMySMA*                         m_pSMA22;          // 

    CMySMA*                         m_pSMA31;          // 

    CMySMA*                         m_pSMA32;          // 

    CTimeSeriesData<double>*        m_pRSI1;           // 计算结果: RSI1

    CTimeSeriesData<double>*        m_pRSI2;           // 计算结果: RSI2

    CTimeSeriesData<double>*        m_pRSI3;           // 计算结果: RSI3
};

#endif   // MY_RSI_HPP__


