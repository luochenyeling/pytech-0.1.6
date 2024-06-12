// ��Ȩ�ƶ�ƽ��ֵ
// ��X1 + 2 * X2 + 3 * X3 + ... + XN* N) / (1 + 2 +3 + ... + N)

#ifndef   MY_WMA_HPP__
#define   MY_WMA_HPP__

#include "TimeSeriesData.hpp"
#include <stdio.h>

class CMyWMA
{
public:

    CMyWMA(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_fDataSum(0.00)
    , m_fWDataSum(0.00)
    , m_pData(nullptr)
    , m_pWMA(nullptr)
    {
        m_pData = new CTimeSeriesData<double>(m_nPeriod);
        m_pWMA   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyWMA()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pWMA){
            delete m_pWMA;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!IsValid(fData)){
            return;
        }

        double fWMA            = UN_VALID_VALUE(double);
        int    nRemove         = 0;
        bool   bJustUpdateNew = false;
        double fRemoveData     = 0.0;
        m_pData->AppendData(fData, bNewPeriod, nRemove, fRemoveData);
        double fOldDataSum = m_fDataSum;
        m_fDataSum += (fData - fRemoveData);   // fRemoveData ��PushData��Ҳ�ᱻ��ʼ��Ϊ0, ��������ֱ��(fData - fRemoveData)����, ���ж�bRemove��
        if(!m_pData->IsFull()){
            m_fWDataSum += fData * m_pData->GetDataCnt();
        }
        else{
            if(nRemove != 0){                  // �����ݱ��Ƴ�
                if(nRemove == 2) {             // ֻ�Ǹ��������µ�����
                    m_fWDataSum += m_nPeriod * (fData - fRemoveData);
                }
                else{                           // �Ƴ���ѭ�����������ϵ�����
                    m_fWDataSum = m_fWDataSum - fOldDataSum + m_nPeriod * fData;
                }
            }
            else{                               // ���ݸո�����
                m_fWDataSum += fData * m_nPeriod;
            }

            fWMA = m_fWDataSum / ((m_nPeriod + 1) * m_nPeriod / 2);

            //for compare test
            //double fsum = 0.00;
            //for (int n = m_nPeriod; n >= 1; --n) {
            //    fsum += n * m_pData->GetData(n - m_nPeriod);
            //}
            //double ftwma = fsum / ((m_nPeriod + 1) * m_nPeriod / 2);
        }

        m_pWMA->AppendData(fWMA, bNewPeriod);
    }

    double WMA(int nIndex)
    {
        return m_pWMA->GetData(nIndex);
    }

    void Reset()
    {
        m_fDataSum  = 0.00;
        m_fWDataSum = 0.00;
        m_pData->Reset();
        m_pWMA->Reset();
    }

private:

    int                             m_nPeriod;         // ��������

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    double                          m_fDataSum;        // ԭʼ���ݵĺ�(1 + X1 + X2 + ... + XN)

    double                          m_fWDataSum;       // ԭʼ���ݵļ�Ȩ��

    CTimeSeriesData<double>*        m_pData;           // ԭʼ���ݣ�X1 + 2 * X2 + 3 * X3 + ... + XN* N)

    CTimeSeriesData<double>*        m_pWMA;            // ������
};



#endif    // MY_WMA_HPP__
