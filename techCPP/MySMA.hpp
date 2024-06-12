#ifndef  MY_SMA_HPP__
#define  MY_SMA_HPP__

#include "TimeSeriesData.hpp"

class CMySMA
{
public:
    CMySMA(int nPeriod, int nWeight, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nWeight(nWeight)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pSMA(nullptr)
    , m_nDataCnt(0)
    {
        m_pSMA   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMySMA()
    {
        if(m_pSMA){
            delete m_pSMA;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!m_pSMA || m_nPeriod <= m_nWeight){
            return;
        }

        double fPreSma  = UN_VALID_VALUE(double);
        double fCurSma  = UN_VALID_VALUE(double);

        // SMA = (M * X + (N - M)* PreSMA)/N
        // ע���: SMA��ֵ����ǰSMAֵ,Ҳ����˵�и���ʷ�ۻ�, �����������û�ﵽN��ʱ, N��ȡֵҲ�ǹ̶�Ϊ����m_nPeriod

        if (bNewPeriod || m_nDataCnt == 0){
            ++m_nDataCnt;
        }

        if(m_nDataCnt == 1){
            fCurSma = fData;
        }
        else{
            fPreSma = m_pSMA->GetCurPreData(bNewPeriod);
            if (IsValid(fPreSma)){
                fCurSma = ((double)(m_nWeight * fData + (m_nPeriod - m_nWeight) * fPreSma)) / (double)m_nPeriod;
            }
        }

        m_pSMA->AppendData(fCurSma, bNewPeriod);
    }

    double SMA(int nIndex)
    {
        return m_pSMA->GetData(nIndex);
    }

    void Reset()
    {
        m_nDataCnt = 0;
        m_pSMA->Reset();
    }

private:

    int                             m_nPeriod;         // ��������

    int                             m_nWeight;         // Ȩ��

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    CTimeSeriesData<double>*        m_pSMA;            // ������

    unsigned int                    m_nDataCnt;        // ԭʼ���ݵĸ���
};


#endif      // MY_SMA_HPP__


