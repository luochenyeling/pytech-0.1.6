// BOLL:MA(CLOSE,M);
// UB:BOLL+2*STD(CLOSE,M);
// LB:BOLL-2*STD(CLOSE,M);

#ifndef  MY_BOLL_HPP__
#define  MY_BOLL_HPP__

#include "MyStd.hpp"

class CMyBOLL
{
public:

    CMyBOLL(int nPeriod, int nResultMaxCnt)
    : m_pStd(nullptr)
    {
        m_pStd = new CMyStd(nPeriod, nResultMaxCnt);
    }

    ~CMyBOLL()
    {
        if (m_pStd){
            delete m_pStd;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        m_pStd->Append(fData, bNewPeriod);
    }

    double BOLL(int nIndex)
    {
        CMyMA* pMA = m_pStd->MAData();
        return pMA->MA(nIndex);
    }

    double UPPER(int nIndex)
    {
        CMyMA* pMA = m_pStd->MAData();
        double fMA = pMA->MA(nIndex);
        double fStd = m_pStd->Std(nIndex);
        if (IsValid(fMA) && IsValid(fStd)){
            return fMA + 2 * fStd;
        }

        return UN_VALID_VALUE(double);
    }

    double LOWER(int nIndex)
    {
        CMyMA* pMA = m_pStd->MAData();
        double fMA = pMA->MA(nIndex);
        double fStd = m_pStd->Std(nIndex);
        if (IsValid(fMA) && IsValid(fStd)){
            return fMA - 2 * fStd;
        }

        return UN_VALID_VALUE(double);
    }

    void Reset()
    {
        m_pStd->Reset();
    }

private:

    CMyStd*                 m_pStd;
};


#endif      //