// ±ê×¼²îº¯Êý
#ifndef  MY_STD_HPP__
#define  MY_STD_HPP__

#include "MyMA.hpp"

class CMyStd
{
public:

    CMyStd(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_pMA(nullptr)
    , m_pStd(nullptr)
    {
        m_pMA   = new CMyMA(m_nPeriod, nResultMaxCnt);
        m_pStd  = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyStd()
    {
        if (m_pMA){
            delete m_pMA;
        }

        if (m_pStd){
            delete m_pStd;
        }
    }

    CMyMA* MAData()
    {
        return m_pMA;
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        double fStd = UN_VALID_VALUE(double);
        if (m_nPeriod <= 1){
            m_pStd->AppendData(fStd, bNewPeriod);
            return;
        }

        m_pMA->Append(fData, bNewPeriod);

        CTimeSeriesData<double>* pData = m_pMA->SrcData();
        if (pData && pData->GetDataCnt() == m_nPeriod){
            double fMA         = m_pMA->MA(0);
            if (IsValid(fMA)){
                double fSqrSum = 0.00;
                for (int i = 0; i < m_nPeriod; ++i){
                    double fSrcData = pData->GetData(-i);
                    fSqrSum += (fSrcData * fSrcData);
                }

                double fMASqr = fSqrSum / m_nPeriod;
                fStd = sqrt((fMASqr - fMA * fMA) * m_nPeriod / (m_nPeriod - 1));
            }
        }

        m_pStd->AppendData(fStd, bNewPeriod);
    }

    double Std(int nIndex)
    {
        return m_pStd->GetData(nIndex);
    }

    void Reset()
    {
        m_pMA->Reset();
        m_pStd->Reset();
    }

private:

    int                         m_nPeriod;

    CMyMA*                      m_pMA;

    CTimeSeriesData<double>*    m_pStd;
};


#endif      // MY_STD_HPP__


