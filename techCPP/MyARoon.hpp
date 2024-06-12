// AROON值

#ifndef  MY_AROON_HPP__
#define  MY_AROON_HPP__

#include <limits>
#include <algorithm>
#include "TimeSeriesData.hpp"
#include "MyMA.hpp"

class CMyARoon
{
public:

    CMyARoon(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_pHigh(nullptr)
    , m_pUp(nullptr)
    , m_pDown(nullptr)
    {
        if(nResultMaxCnt < nPeriod + 1){
            nResultMaxCnt = nPeriod + 1;
        }

        m_pHigh   = new CTimeSeriesData<double>(nPeriod + 1);
        m_pUp     = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pDown   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyARoon()
    {
        if(m_pHigh){
            delete m_pHigh;
        }

        if(m_pUp){
            delete m_pUp;
        }

        if(m_pDown){
            delete m_pDown;
        }
    }

    // 计算公式如下: 
    // 上轨:(N-HHVBARS(H,N))/N*100;
    // 下轨:(N-LLVBARS(H,N))/N*100;
    void Append(const double& fHigh, bool bNewPeriod)
    {
        int    nHIndex  = 0;
        double fPeriodHH = 0.0;
        int    nLIndex  = 0;
        double fPeriodHL = 0.0;
        m_pHigh->AppendData(fHigh, bNewPeriod);
        m_pHigh->PeriodHL(0, m_nPeriod, fPeriodHH, nHIndex, fPeriodHL, nLIndex);

        double fUp  = double(m_nPeriod - abs(nHIndex))/double(m_nPeriod) * 100.00;
        double fDown = double(m_nPeriod - abs(nLIndex))/double(m_nPeriod) * 100.00;
        m_pUp->AppendData(fUp, bNewPeriod);
        m_pDown->AppendData(fDown, bNewPeriod);
    }

    // 
    double Up(int nIndex)
    {
        return m_pUp->GetData(nIndex);
    }

    double Down(int nIndex)
    {
        return m_pDown->GetData(nIndex);
    }

    void Reset()
    {
        m_pHigh->Reset();
        m_pUp->Reset();
        m_pDown->Reset();
    }

private:

    int                         m_nPeriod;        // 默认25

    CTimeSeriesData<double>*    m_pHigh;          // 最高价的源数据

    CTimeSeriesData<double>*    m_pUp;            // 上轨值

    CTimeSeriesData<double>*    m_pDown;          // 下轨值
};

#endif   //MY_AROON_HPP__


