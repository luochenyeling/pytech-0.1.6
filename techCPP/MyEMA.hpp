#ifndef  MY_EMA_HPP__
#define  MY_EMA_HPP__

#include "TimeSeriesData.hpp"

class CMyEMA
{
public:
    CMyEMA(int nPeriod,int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pEMA(nullptr)
    , m_nDataCnt(0)
    {
        m_pEMA   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyEMA()
    {
        if(m_pEMA){
            delete m_pEMA;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!m_pEMA || m_nPeriod <= m_nWeight){
            return;
        }

        double fPreEma  = UN_VALID_VALUE(double);
        double fCurEma  = UN_VALID_VALUE(double);

        // SMA = (M * X + (N - M)* PreSMA)/N
        // EMA(X, N) = SMA(X, N + 1, 2) = (2 * X + ( nPeriod + 1 - 2) * PreSMA)/(nPeriod + 1)
        if (bNewPeriod || m_nDataCnt == 0){
            ++m_nDataCnt;
        }

        if(m_nDataCnt == 1){
            fCurEma = fData;
        }
        else{
            fPreEma = m_pEMA->GetCurPreData(bNewPeriod);
            if(IsValid(fPreEma)){
                fCurEma = ((double)(2 * fData + (m_nPeriod - 1) * fPreEma)) / ((double)(m_nPeriod + 1));
            }
        }

        m_pEMA->AppendData(fCurEma, bNewPeriod);
    }

    double EMA(int nIndex)
    {
        return m_pEMA->GetData(nIndex);
    }

    void Reset()
    {
        m_nDataCnt = 0;
        m_pEMA->Reset();
    }

private:

    int                             m_nPeriod;         // 计算周期

    int                             m_nWeight=2;         // 权重, EMA固定为2

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pEMA;            // 计算结果

    unsigned int                    m_nDataCnt;        // 原始数据的个数
};


#endif          // CMyEMA


