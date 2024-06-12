//BBI指标

#ifndef  MY_BBI_HPP__
#define  MY_BBI_HPP__

#include "MyMA.hpp"
#include <math.h>

class CMyBBI
{
public:

    CMyBBI(int nPeriod1, int nPeriod2, int nPeriod3, int nPeriod4, int nResultMaxCnt)
    : m_pMA1(nullptr)
    , m_pMA2(nullptr)
    , m_pMA3(nullptr)
    , m_pMA4(nullptr)
    , m_pBBI(nullptr)

    {
        m_pMA1   = new CMyMA(nPeriod1, 2);
        m_pMA2   = new CMyMA(nPeriod2, 2);
        m_pMA3   = new CMyMA(nPeriod3, 2);
        m_pMA4   = new CMyMA(nPeriod4, 2);
        m_pBBI   = new CTimeSeriesData<double>(nResultMaxCnt);

    }

    ~CMyBBI()
    {
        if (m_pMA1){
            delete m_pMA1;
        }

        if (m_pMA2){
            delete m_pMA2;
        }

        if (m_pMA3){
            delete m_pMA3;
        }

        if (m_pMA4){
            delete m_pMA4;
        }

        if (m_pBBI){
            delete m_pBBI;
        }
    }

    // BBI指标的计算公式：
    // BBI:(MA(CLOSE,M1)+MA(CLOSE,M2)+MA(CLOSE,M3)+MA(CLOSE,M4))/4;
    void Append(const double& fData, bool bNewPeriod)
    {
        double fBBI = UN_VALID_VALUE(double);
        m_pMA1->Append(fData, bNewPeriod);
        m_pMA2->Append(fData, bNewPeriod);
        m_pMA3->Append(fData, bNewPeriod);
        m_pMA4->Append(fData, bNewPeriod);

        double fMA1 = m_pMA1->MA(0);
        double fMA2 = m_pMA2->MA(0);
        double fMA3 = m_pMA3->MA(0);
        double fMA4 = m_pMA4->MA(0);

        if (IsValid(fMA1) && IsValid(fMA2) && IsValid(fMA3) && IsValid(fMA4)){
            fBBI = (fMA1 + fMA2 + fMA3 + fMA4) / 4;
        }

        m_pBBI->AppendData(fBBI, bNewPeriod);
    }

    double BBI(int nIndex)
    {
        return m_pBBI->GetData(nIndex);
    }

    void Reset()
    {
        m_pMA1->Reset();
        m_pMA2->Reset();
        m_pMA3->Reset();
        m_pMA4->Reset();
        m_pBBI->Reset();
    }

private:

    CMyMA*                         m_pMA1;      // 默认3

    CMyMA*                         m_pMA2;      // 默认6

    CMyMA*                         m_pMA3;      // 默认12

    CMyMA*                         m_pMA4;      // 默认24

    CTimeSeriesData<double>*       m_pBBI;      // BBI计算结果


};

#endif        // MY_TRIX_HPP__


