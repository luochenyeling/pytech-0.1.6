//ע��: ������ָDMA(��̬�ƶ�ƽ��)����, ����ͨ����DMA(ƽ����)ָ��

#ifndef  MY_DMA_HPP__
#define  MY_DMA_HPP__

#include "TimeSeriesData.hpp"

class CMyDMA
{
public:
    CMyDMA(int nResultMaxCnt)
    : m_nResultMaxCnt(nResultMaxCnt)
    , m_pDMA(nullptr)
    , m_nDataCnt(0)
    {
        m_pDMA   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyDMA()
    {
        if(m_pDMA){
            delete m_pDMA;
        }
    }

    void Append(const double& fData, double fSmooth, bool bNewPeriod)
    {
        if (!m_pDMA || fSmooth >= 1 || fSmooth <= 0){
            return;
        }

        double fPreDma  = UN_VALID_VALUE(double);
        double fCurDma  = UN_VALID_VALUE(double);

        // DMA(A, X) = Y = A * X + (1 - A) * Y', ����Y'��ʾ��һ����Yֵ
        if (bNewPeriod || m_nDataCnt == 0){
            ++m_nDataCnt;
        }

        if(m_nDataCnt == 1){
            fCurDma = fData;
        }
        else{
            fPreDma = m_pDMA->GetCurPreData(bNewPeriod);
            if(IsValid(fPreDma)){
                fCurDma = fSmooth * fData + (1 - fSmooth) * fPreDma;
            }
        }

        m_pDMA->AppendData(fCurDma, bNewPeriod);
    }

    double DMA(int nIndex)
    {
        return m_pDMA->GetData(nIndex);
    }

    void Reset()
    {
        m_nDataCnt = 0;
        m_pDMA->Reset();
    }

private:

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    CTimeSeriesData<double>*        m_pDMA;            // ������

    unsigned int                    m_nDataCnt;        // ԭʼ���ݵĸ���
};


#endif          // MY_DMA_HPP__


