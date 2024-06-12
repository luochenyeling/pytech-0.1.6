// DMA指标

#ifndef  MY_DMAI_HPP__
#define  MY_DMAI_HPP__

#include "MyMA.hpp"
#include <math.h>

class CMyDMAI
{
public:

    CMyDMAI(int nPeriod1, int nPeriod2, int nPeriod3, int nResultMaxCnt)
    : m_pMA1(nullptr)
    , m_pMA2(nullptr)
    , m_pMADIF(nullptr)
    , m_pDIF(nullptr)
    {
        m_pMA1      = new CMyMA(nPeriod1, 2);
        m_pMA2      = new CMyMA(nPeriod2, 2);
        m_pMADIF    = new CMyMA(nPeriod3, nResultMaxCnt);
        m_pDIF      = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyDMAI()
    {
        if (m_pMA1){
            delete m_pMA1;
        }

        if (m_pMA2){
            delete m_pMA2;
        }

        if (m_pMADIF){
            delete m_pMADIF;
        }

        if (m_pDIF){
            delete m_pDIF;
        }
    }

    // DMA指标计算公式：
    // DIF:MA(CLOSE,N1)-MA(CLOSE,N2);
    // DIFMA:MA(DIF,M);
    void Append(const double& fData, bool bNewPeriod)
    {
        m_pMA1->Append(fData, bNewPeriod);
        m_pMA2->Append(fData, bNewPeriod);
        double fDIF = UN_VALID_VALUE(double);
        double fMA1 = m_pMA1->MA(0);
        double fMA2 = m_pMA2->MA(0);
        if (IsValid(fMA1) && IsValid(fMA2))
        {
            fDIF = fMA1 - fMA2;
            m_pDIF->AppendData(fDIF, bNewPeriod);
            m_pMADIF->Append(fDIF, bNewPeriod);
        }
    }

    double DIF(int nIndex)
    {
        return m_pDIF->GetData(nIndex);
    }

    double MADIF(int nIndex)
    {
        return m_pMADIF->MA(nIndex);
    }

    void Reset()
    {
        m_pMA1->Reset();
        m_pMA2->Reset();
        m_pMADIF->Reset();
        m_pDIF->Reset();
    }

private:

    CMyMA*                          m_pMA1;

    CMyMA*                          m_pMA2;

    CMyMA*                          m_pMADIF;

    CTimeSeriesData<double>*        m_pDIF;
};

#endif      // MY_DMAI_HPP__


