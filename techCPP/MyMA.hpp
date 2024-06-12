#ifndef   MY_MA_HPP__
#define   MY_MA_HPP__

#include "TimeSeriesData.hpp"
#include <stdio.h>

class CMyMA
{
public:

    CMyMA(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_fDataSum(0.00)
    , m_pData(nullptr)
    , m_pMA(nullptr)
    {
        m_pData    = new CTimeSeriesData<double>(m_nPeriod);
        m_pMA      = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyMA()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pMA){
            delete m_pMA;
        }
    }

    // ʹ��ʱ�м�ԭʼ���ݵĳ���
    // ��nResultMaxCnt����m_nPeriodʱ, Ҫ��ȡԭʼ����, Ҫ�ǳ�����, ����m_nPeriod�ĳ��Ȼ�ȡ����Ϊ��, ���ʱ����Ҫ�ⲿ��������һ��ԭʼ����
    CTimeSeriesData<double>*  SrcData()
    {
        return m_pData;
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!IsValid(fData)){
            return;
        }

        double fMA           = UN_VALID_VALUE(double);
        int    nRemove      = 0;
        bool   bJustUpdateNew = false;
        double fRemoveData  = 0.0;
        m_pData->AppendData(fData, bNewPeriod, nRemove, fRemoveData);
        m_fDataSum += (fData - fRemoveData);   // fRemoveData ��PushData��Ҳ�ᱻ��ʼ��Ϊ0, ��������ֱ��(fData - fRemoveData)����, ���ж�nRemove�Ƿ�Ϊ0��
        if (m_pData->IsFull()){
            fMA = m_fDataSum / m_nPeriod;
        }

        m_pMA->AppendData(fMA, bNewPeriod);
    }

    double MA(int nIndex)
    {
        return m_pMA->GetData(nIndex);
    }

    void Reset()
    {
        m_fDataSum = 0.00;
        m_pData->Reset();
        m_pMA->Reset();
    }

private:

    int                             m_nPeriod;         // ��������

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    double                          m_fDataSum;        // ԭʼ���ݵĺ�

    CTimeSeriesData<double>*        m_pData;           // ԭʼ����, ���ڼ��������, ע���䳤����m_nPeriod

    CTimeSeriesData<double>*        m_pMA;             // ������
};



#endif    // MY_MA_HPP__
