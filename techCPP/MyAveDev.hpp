#ifndef  MY_AVEDEV_HPP__
#define  MY_AVEDEV_HPP__

#include "MyMA.hpp"
#include <math.h>

class CMyAveDev
{
public:

    CMyAveDev(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_pMA(nullptr)
    , m_pAveDev(nullptr)
    {
        m_pMA     = new CMyMA(m_nPeriod, 1);
        m_pAveDev = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyAveDev()
    {
        if (m_pMA){
            delete m_pMA;
        }

        if (m_pAveDev){
            delete m_pAveDev;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        m_pMA->Append(fData, bNewPeriod);
        double fAveDev = UN_VALID_VALUE(double);

        CTimeSeriesData<double>* pData = m_pMA->SrcData();
        if (pData && pData->GetDataCnt() == m_nPeriod){
            double fMA         = m_pMA->MA(0);
            if (IsValid(fMA)){
                double fAbsDifSum = 0.00;
                for (int i = 0; i < m_nPeriod; ++i){
                    double fSrcData = pData->GetData(-i);
                    fAbsDifSum += fabs(fMA - fSrcData);
                }

                fAveDev = fAbsDifSum / m_nPeriod;
            }
        }

        m_pAveDev->AppendData(fAveDev, bNewPeriod);
    }

    double AveDev(int nIndex)
    {
         return m_pAveDev->GetData(nIndex);
    }

    void Reset()
    {
        m_pMA->Reset();
        m_pAveDev->Reset();
    }

private:

    int                         m_nPeriod;

    CMyMA*                      m_pMA;

    CTimeSeriesData<double>*    m_pAveDev;

};

#endif      //MY_AVEDEV_HPP__


