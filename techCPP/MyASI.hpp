// ASI值

#ifndef  MY_ASI_HPP__
#define  MY_ASI_HPP__

#include <limits>
#include <algorithm>
#include "TimeSeriesData.hpp"
#include "MyMA.hpp"
#include <math.h>

class CMyASI
{
public:

    CMyASI(int nPeriod, int nMaPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_pHigh(nullptr)
    , m_pLow(nullptr)
    , m_pClose(nullptr)
    , m_pOpen(nullptr)
    , m_pSI(nullptr)
    , m_pASI(nullptr)
    , m_pASIMA(nullptr)
    {
        if(nResultMaxCnt < nPeriod + 1){
            nResultMaxCnt = nPeriod + 1;
        }

        m_pHigh    = new CTimeSeriesData<double>(nPeriod + 1);
        m_pLow     = new CTimeSeriesData<double>(nPeriod + 1);
        m_pClose   = new CTimeSeriesData<double>(nPeriod + 1);
        m_pOpen    = new CTimeSeriesData<double>(nPeriod + 1);
        m_pSI      = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pASI     = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pASIMA   = new CMyMA(nMaPeriod, nResultMaxCnt);
    }

    ~CMyASI()
    {
        if(m_pHigh){
            delete m_pHigh;
        }

        if(m_pLow){
            delete m_pLow;
        }

        if(m_pClose){
            delete m_pClose;
        }

        if(m_pOpen){
            delete m_pOpen;
        }

        if(m_pSI){
            delete m_pSI;
        }

        if(m_pASI){
            delete m_pASI;
        }

        if(m_pASIMA){
            delete m_pASIMA;
        }
    }

    // 计算公式如下: 
    // LC:=REF(CLOSE,1);
    // AA:=ABS(HIGH-LC);
    // BB:=ABS(LOW-LC);
    // CC:=ABS(HIGH-REF(LOW,1));
    // DD:=ABS(LC-REF(OPEN,1));
    // R:=IF(AA>BB AND AA>CC,AA+BB/2+DD/4,IF(BB>CC AND BB>AA,BB+AA/2+DD/4,CC+DD/4));
    // X:=(CLOSE-LC+(CLOSE-OPEN)/2+LC-REF(OPEN,1));
    // SI:=16*X/R*MAX(AA,BB);
    // ASI:SUM(SI,M1);
    // MAASI: MA(ASI,M2);
    void Append(const double& fHigh, const double& fLow, const double& fClose, const double& fOpen, bool bNewPeriod)
    {
        double fLC = m_pClose->GetCurPreData(bNewPeriod);
        double fPreLow = m_pLow->GetCurPreData(bNewPeriod);
        double fPreOpen = m_pOpen->GetCurPreData(bNewPeriod);
        if(!IsValid(fLC) || !IsValid(fPreLow) || !IsValid(fPreOpen)){
            m_pHigh->AppendData(fHigh, bNewPeriod);
            m_pLow->AppendData(fLow, bNewPeriod);
            m_pClose->AppendData(fClose, bNewPeriod);
            m_pOpen->AppendData(fOpen, bNewPeriod);
            m_pSI->AppendData(0.0, bNewPeriod);
            m_pASI->AppendData(0.00, bNewPeriod);
            m_pASIMA->Append(UN_VALID_VALUE(double), bNewPeriod);
            return;
        }

        double fAA = fabs(fHigh - fLC);
        double fBB = fabs(fLow - fLC);
        double fCC = fabs(fHigh - fPreLow);
        double fDD = fabs(fLC-fPreOpen);
        double fR = 0.0;
        if(fAA > fBB && fAA > fCC){
            fR = fAA + fBB / 2 + fDD / 4;
        }
        else if(fBB > fCC && fBB > fAA){
            fR = fBB + fAA / 2 + fDD / 4;
        }
        else{
            fR = fCC + fDD / 4;
        }

        double fX = fClose - fLC + (fClose - fOpen) / 2 + fLC - fPreOpen;
        double fSI = 16 * fX / fR * std::max(fAA, fBB);
        double fASI = fSI;
        int nStartIndex = 0;
        if(bNewPeriod){
            nStartIndex = 0;
        }
        else{
            nStartIndex = -1;
        }

        int nSumCnt = 1;
        for (int i = nStartIndex; nSumCnt < m_nPeriod; --i, ++nSumCnt){
            double fPreSI = m_pSI->GetData(i);
            if(!IsValid(fPreSI)){
                break;
            }

            fASI += fPreSI;
        }

        m_pHigh->AppendData(fHigh, bNewPeriod);
        m_pLow->AppendData(fLow, bNewPeriod);
        m_pClose->AppendData(fClose, bNewPeriod);
        m_pOpen->AppendData(fOpen, bNewPeriod);
        m_pSI->AppendData(fSI, bNewPeriod);
        m_pASI->AppendData(fASI, bNewPeriod);
        m_pASIMA->Append(fASI, bNewPeriod);
    }

    // 
    double ASI(int nIndex)
    {
        return m_pASI->GetData(nIndex);
    }

    double ASIMA(int nIndex)
    {
        return m_pASIMA->MA(nIndex);
    }

    void Reset()
    {
        m_pHigh->Reset();
        m_pLow->Reset();
        m_pClose->Reset();
        m_pOpen->Reset();
        m_pSI->Reset();
        m_pASI->Reset();
        m_pASIMA->Reset();
    }

private:

    int                         m_nPeriod;        // 默认26

    int                         m_nMaPeriod;      // 默认10

    CTimeSeriesData<double>*    m_pHigh;          // 最高价的源数据

    CTimeSeriesData<double>*    m_pLow;           // 最低价的源数据

    CTimeSeriesData<double>*    m_pClose;         // 收盘价的源数据

    CTimeSeriesData<double>*    m_pOpen;          // 开盘价的源数据

    CTimeSeriesData<double>*    m_pSI;            // SI结果

    CTimeSeriesData<double>*    m_pASI;           // ASI结果

    CMyMA*                      m_pASIMA;         // ASI的MA结果

};

#endif   //MY_HL_HPP__