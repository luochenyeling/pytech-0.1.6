#ifndef  MY_TRIX_HPP__
#define  MY_TRIX_HPP__

#include "MyMA.hpp"
#include "MyEMA.hpp"
#include <math.h>

class CMyTrix
{
public:

    CMyTrix(int nEMAPeriod, int nMAPeriod, int nResultMaxCnt)
    : m_pEMA1(nullptr)
    , m_pEMA2(nullptr)
    , m_pEMA3(nullptr)
    , m_pTRIX(nullptr)
    , m_pMATRIX(nullptr)
    {
        m_pEMA1   = new CMyEMA(nEMAPeriod, 2);
        m_pEMA2   = new CMyEMA(nEMAPeriod, 2);
        m_pEMA3   = new CMyEMA(nEMAPeriod, 2);

        m_pTRIX   = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pMATRIX = new CMyMA(nMAPeriod, nResultMaxCnt);
    }

    ~CMyTrix()
    {
        if (m_pEMA1){
            delete m_pEMA1;
        }

        if (m_pEMA2){
            delete m_pEMA2;
        }

        if (m_pEMA3){
            delete m_pEMA3;
        }

        if (m_pTRIX){
            delete m_pTRIX;
        }

        if (m_pMATRIX){
            delete m_pMATRIX;
        }
    }

    // TRIX指标的计算公式：
    // MTR:=EMA(EMA(EMA(CLOSE,N),N),N);
    // TRIX:(MTR-REF(MTR,1))/REF(MTR,1)*100;
    // MATRIX:MA(TRIX,M);

    void Append(const double& fData, bool bNewPeriod)
    {
        m_pEMA1->Append(fData, bNewPeriod);
        double fEMA1 = m_pEMA1->EMA(0);

        m_pEMA2->Append(fEMA1, bNewPeriod);
        double fEMA2 = m_pEMA2->EMA(0);

        m_pEMA3->Append(fEMA2, bNewPeriod);

        double fMTR  = m_pEMA3->EMA(0);
        double fMTR1  = m_pEMA3->EMA(-1);
        double fTRIX = 0.00;
        if (IsValid(fMTR) && IsValid(fMTR1) && fabs(fMTR1) > 1e-6){
            fTRIX = (fMTR - fMTR1) / fMTR1 * 100;
            m_pTRIX->AppendData(fTRIX, bNewPeriod);
            m_pMATRIX->Append(fTRIX, bNewPeriod);
        }
    }

    double TRIX(int nIndex)
    {
        return m_pTRIX->GetData(nIndex);
    }

    double MATRIX(int nIndex)
    {
        return m_pMATRIX->MA(nIndex);
    }

    void Reset()
    {
        m_pEMA1->Reset();
        m_pEMA2->Reset();
        m_pEMA3->Reset();
        m_pTRIX->Reset();
        m_pMATRIX->Reset();
    }


private:

    CMyEMA*                         m_pEMA1;

    CMyEMA*                         m_pEMA2;

    CMyEMA*                         m_pEMA3;

    CTimeSeriesData<double>*        m_pTRIX;

    CMyMA*                          m_pMATRIX;
};

#endif        // MY_TRIX_HPP__


