#ifndef  MY_CCI_HPP__
#define  MY_CCI_HPP__

// TYP:=(HIGH+LOW+CLOSE)/3;
// CCI:(TYP-MA(TYP,N))*1000/(15*AVEDEV(TYP,N));

#include "MyAveDev.hpp"
#include <math.h>

class CMyCCI
{
public:

    CMyCCI(int nPeriod, int nResultMaxCnt)
    : m_pMA(nullptr)
    , m_pAveDev(nullptr)
    , m_pCCI(nullptr)
    {
        m_pMA      = new CMyMA(nPeriod, 1);
        m_pAveDev  = new CMyAveDev(nPeriod, 1);
        m_pCCI     = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyCCI()
    {
        if(m_pMA){
            delete m_pMA;
        }

        if(m_pAveDev){
            delete m_pAveDev;
        }

        if(m_pCCI){
            delete m_pCCI;
        }
    }

    void Append(const double& fHigh, const double& fLow, const double& fClose, bool bNewPeriod)
    {
        double fTYP = (fHigh + fLow + fClose) / 3;
        m_pMA->Append(fTYP, bNewPeriod);
        m_pAveDev->Append(fTYP, bNewPeriod);

        double fMA  = m_pMA->MA(0);
        double fAD  = m_pAveDev->AveDev(0);
        double fCCI = UN_VALID_VALUE(double);
        if (IsValid(fAD) && fabs(fAD) > 1e-6){
            fCCI = (fTYP - fMA) * 1000 / (15 * fAD);
        }

        m_pCCI->AppendData(fCCI, bNewPeriod);
    }

    double CCI(int nIndex)
    {
        return m_pCCI->GetData(nIndex);
    }

    void Reset()
    {
        m_pMA->Reset();
        m_pAveDev->Reset();
        m_pCCI->Reset();
    }

private:

    CMyMA*                              m_pMA;

    CMyAveDev*                          m_pAveDev;

    CTimeSeriesData<double>*            m_pCCI;
};

#endif      // MY_CCI_HPP__


