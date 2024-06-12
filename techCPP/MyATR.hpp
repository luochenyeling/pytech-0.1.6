// ASI值

#ifndef  MY_ATR_HPP__
#define  MY_ATR_HPP__

#include <limits>
#include <algorithm>
#include "TimeSeriesData.hpp"
#include "MyMA.hpp"
#include <math.h>

class CMyATR
{
public:

    CMyATR(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_pClose(nullptr)
    , m_pMTRMA(nullptr)
    , m_pMTR(nullptr)
    {
        if(nResultMaxCnt < nPeriod + 1){
            nResultMaxCnt = nPeriod + 1;
        }

        m_pClose   = new CTimeSeriesData<double>(nPeriod + 1);
        m_pMTRMA   = new CMyMA(m_nPeriod, nResultMaxCnt);
        m_pMTR     = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyATR()
    {
        if(m_pClose){
            delete m_pClose;
        }

        if(m_pMTRMA){
            delete m_pMTRMA;
        }

        if (m_pMTR){
            delete m_pMTR;
        }
    }

    // 计算公式如下: 
    // MTR:MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW));
    // ATR:MA(MTR, N);
    void Append(const double& fHigh, const double& fLow, const double& fClose, bool bNewPeriod)
    {
        double fMTR = UN_VALID_VALUE(double);
        double fPreClose = m_pClose->GetCurPreData(bNewPeriod);
        if(IsValid(fPreClose)){
            fMTR = std::max(std::max((fHigh - fLow), fabs(fPreClose - fHigh)), fabs(fPreClose - fLow));
        }

        m_pMTR->AppendData(fMTR, bNewPeriod);
        m_pMTRMA->Append(fMTR, bNewPeriod);
        m_pClose->AppendData(fClose, bNewPeriod);
    }

    // 
    double MTR(int nIndex)
    {
        return m_pMTR->GetData(nIndex);
    }

    double ATR(int nIndex)
    {
        return m_pMTRMA->MA(nIndex);
    }

    void Reset()
    {
        m_pClose->Reset();
        m_pMTRMA->Reset();
        m_pMTR->Reset();
    }

private:

    int                         m_nPeriod;        // 默认14

    CTimeSeriesData<double>*    m_pClose;         // 收盘价的源数据

    CMyMA*                      m_pMTRMA;         // MTR的MA结果, 即ATR

    CTimeSeriesData<double>*    m_pMTR;           // MTR的MA结果

};

#endif   //MY_HL_HPP__


