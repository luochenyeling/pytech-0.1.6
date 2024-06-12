#ifndef  MY_WR_HPP__
#define  MY_WR_HPP__

#include "TimeSeriesData.hpp"

class CMyWR
{
public:

    CMyWR(int nPeriod1, int nPeriod2, int nResultMaxCnt)
    : m_nPeriod1(nPeriod1)
    , m_nPeriod2(nPeriod2)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pHighData(nullptr)
    , m_pLowData(nullptr)
    , m_pWR1(nullptr)
    , m_pWR2(nullptr)
    {
        int nDataSize = m_nPeriod1 >= m_nPeriod2 ? m_nPeriod1 : m_nPeriod2;
        m_pHighData    = new CTimeSeriesData<double>(nDataSize + 1);
        m_pLowData    = new CTimeSeriesData<double>(nDataSize + 1);
        m_pWR1  = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pWR2  = new CTimeSeriesData<double>(m_nResultMaxCnt);
    }

    ~CMyWR()
    {
  
    }

    // WR���㷨��ʽ��
    // WR1:100*(HHV(HIGH,N)-CLOSE)/(HHV(HIGH,N)-LLV(LOW,N));
    // WR2:100*(HHV(HIGH,N1)-CLOSE)/(HHV(HIGH,N1)-LLV(LOW,N1));
    void Append(const double& fHigh, const double& fLow, const double& fClose, bool bNewPeriod)
    {
        m_pHighData->AppendData(fHigh, bNewPeriod);
        m_pLowData->AppendData(fLow, bNewPeriod);

        double fHHV    = 0.00;
        int nHHVIndex = 0;
        double fLLV    = 0.00;
        int nLLVIndex  = 0;
        m_pHighData->PeriodHigh(0, m_nPeriod1, fHHV, nHHVIndex);
        m_pLowData->PeriodLow(0, m_nPeriod1, fLLV, nLLVIndex);

        double fWR1 = 100 * (fHHV - fClose) / (fHHV - fLLV);

        fHHV = 0.00;
        fLLV = 0.00;
        m_pHighData->PeriodHigh(0, m_nPeriod2, fHHV, nHHVIndex);
        m_pLowData->PeriodLow(0, m_nPeriod2, fLLV, nLLVIndex);

        double fWR2 = 100 * (fHHV - fClose) / (fHHV - fLLV);

        m_pWR1->AppendData(fWR1, bNewPeriod);
        m_pWR2->AppendData(fWR2, bNewPeriod);
    }

    double WR1(int nIndex)
    {
        return m_pWR1->GetData(nIndex);
     }

    double WR2(int nIndex)
    {
        return m_pWR2->GetData(nIndex);
    }

    void Reset()
    {
        m_pHighData->Reset();
        m_pLowData->Reset();
        m_pWR1->Reset();
        m_pWR2->Reset();
    }

private:

    int                             m_nPeriod1;         // WR1��������

    int                             m_nPeriod2;         // WR2��������

    int                             m_nResultMaxCnt;    // ��ౣ����ٸ����

    CTimeSeriesData<double>*        m_pHighData;        // ԭʼ����: ���ֵ

    CTimeSeriesData<double>*        m_pLowData;         // ԭʼ����: ���ֵ

    CTimeSeriesData<double>*        m_pWR1;             // ������: WR1

    CTimeSeriesData<double>*        m_pWR2;             // ������: WR2
};

#endif      // MY_WR_HPP__


