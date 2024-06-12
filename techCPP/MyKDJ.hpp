#ifndef  MY_KDJ_H__
#define  MY_KDJ_H__

#include "MySMA.hpp"
#include <math.h>

class CMyKDJ
{
public:

    CMyKDJ(int nPeriod, int nKPeriod, int nDPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nKPeriod(nKPeriod)
    , m_nDPeriod(nDPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pHighData(nullptr)
    , m_pLowData(nullptr)
    , m_pCloseData(nullptr)
    , m_pK(nullptr)
    , m_pD(nullptr)
    {
        m_pHighData  = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pLowData   = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pCloseData = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pSMA_K = new CMySMA(m_nKPeriod, 1, 2);
        m_pSMA_D = new CMySMA(m_nDPeriod, 1, 2);

        m_pK = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pD = new CTimeSeriesData<double>(m_nResultMaxCnt);
    }

    ~CMyKDJ()
    {
        if(m_pHighData){
            delete m_pHighData;
        }

        if(m_pLowData){
            delete m_pLowData;
        }

        if(m_pCloseData){
            delete m_pCloseData;
        }

        if(m_pSMA_K){
            delete m_pSMA_K;
        }

        if(m_pSMA_D){
            delete m_pSMA_D;
        }

        if (m_pK){
            delete m_pK;
        }

        if (m_pD){
            delete m_pD;
        }
    }

    //KDJ的计算公式：
    // RSV:=(CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N))*100;
    // K:SMA(RSV,M1,1);
    // D:SMA(K,M2,1);
    // J:3*K-2*D;
    void Append(const double& fHigh, const double& fLow, const double& fClose, bool bNewPeriod)
    {
        m_pHighData->AppendData(fHigh, bNewPeriod);
        m_pLowData->AppendData(fLow, bNewPeriod);
        m_pCloseData->AppendData(fClose, bNewPeriod);

        double fLLV = 0.00;
        double fHHV  = 0.00;
        int nLLVIndex = 0;
        int nHHVIndex  = 0;
        m_pLowData->PeriodLow(0, m_nPeriod, fLLV, nLLVIndex);
        m_pHighData->PeriodHigh(0, m_nPeriod, fHHV, nHHVIndex);
        double fRSV = 0.0;
        if (fabs(fHHV - fLLV) > 1e-6){
            fRSV = (fClose - fLLV) / (fHHV - fLLV) * 100;
        }

        m_pSMA_K->Append(fRSV, bNewPeriod);
        double fK   = m_pSMA_K->SMA(0);
        m_pSMA_D->Append(fK, bNewPeriod);
        double fD = m_pSMA_D->SMA(0);

        m_pK->AppendData(fK, bNewPeriod);
        m_pD->AppendData(fD, bNewPeriod);

        //J值这里不计算, 在获取的时候通过 3*K-2*D 实时计算返回
    }

    double K(int nIndex)
    {
        return m_pK->GetData(nIndex);
    }

    double D(int nIndex)
    {
        return m_pD->GetData(nIndex);
    }

    double J(int nIndex)
    {
        return 3 * K(nIndex) - 2 * D(nIndex);
    }

    void Reset()
    {
        m_pHighData->Reset();
        m_pLowData->Reset();
        m_pCloseData->Reset();
        m_pK->Reset();
        m_pD->Reset();
    }

private:

    int                             m_nPeriod;

    int                             m_nKPeriod;

    int                             m_nDPeriod;

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pHighData;       // 原始最高数据

    CTimeSeriesData<double>*        m_pLowData;        // 原始最低数据

    CTimeSeriesData<double>*        m_pCloseData;      // 原始收盘数据

    CMySMA*                         m_pSMA_K;

    CMySMA*                         m_pSMA_D;

    CTimeSeriesData<double>*        m_pK;               // 计算结果: K

    CTimeSeriesData<double>*        m_pD;               // 计算结果: D

                                                        // 计算结果J通过 3 * K - 2 * D来计算, 就不保存了, 节省空间
};


#endif     // KDJ


