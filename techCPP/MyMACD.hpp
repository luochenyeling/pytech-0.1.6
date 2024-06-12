#ifndef  MY_MACD_HPP__
#define  MY_MACD_HPP__

#include "MyEMA.hpp"

class CMyMACD
{
public:

    CMyMACD(int nShortPeriod, int nLongPeriod, int nMidPeriod, int nResultMaxCnt)
    : m_pShortEMA(nullptr)
    , m_pLongEMA(nullptr)
    , m_pMidEMA(nullptr)
    , m_pDIF(nullptr)
    , m_pDEA(nullptr)
    {
        m_pShortEMA = new CMyEMA(nShortPeriod, 2);
        m_pLongEMA = new CMyEMA(nLongPeriod, 2);
        m_pMidEMA  = new CMyEMA(nMidPeriod, 2);
        m_pDIF = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pDEA = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyMACD()
    {
        if (m_pShortEMA){
            delete m_pShortEMA;
        }

        if (m_pLongEMA){
            delete m_pLongEMA;
        }

        if (m_pMidEMA){
            delete m_pMidEMA;
        }

        if (m_pDIF){
            delete m_pDIF;
        }

        if (m_pDEA){
            delete m_pDEA;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        m_pShortEMA->Append(fData, bNewPeriod);
        m_pLongEMA->Append(fData, bNewPeriod);
        double fDIF = m_pShortEMA->EMA(0) - m_pLongEMA->EMA(0);

        m_pMidEMA->Append(fDIF, bNewPeriod);

        double fDEA = m_pMidEMA->EMA(0);

        m_pDIF->AppendData(fDIF, bNewPeriod);
        m_pDEA->AppendData(fDEA, bNewPeriod);
    }

    double DIF(int nIndex)
    {
         return m_pDIF->GetData(nIndex);
    }

    double DEA(int nIndex)
    {
        return m_pDEA->GetData(nIndex);
    }

    double MACD(int nIndex)
    {
        return (DIF(nIndex) - DEA(nIndex)) * 2;
    }

    void Reset()
    {
        m_pShortEMA->Reset();
        m_pLongEMA->Reset();
        m_pMidEMA->Reset();
        m_pDIF->Reset();
        m_pDEA->Reset();
    }

private:

    CMyEMA*                         m_pShortEMA;

    CMyEMA*                         m_pLongEMA;

    CMyEMA*                         m_pMidEMA;

    CTimeSeriesData<double>*        m_pDIF;     // MACD的计算结果: DIF值(快线)

    CTimeSeriesData<double>*        m_pDEA;     // MACD的计算结果: DEA值(慢线)

                                                // MACD的计算结果: MACD值(柱)通过 (DIF - DEA) * 2 计算, 就不保存了, 节省空间
};

#endif      // MY_MACD_HPP__



