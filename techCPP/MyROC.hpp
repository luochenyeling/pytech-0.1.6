#ifndef  MY_ROC_HPP__
#define  MY_ROC_HPP__

#include "MyMA.hpp"
#include <math.h>

class CMyROC
{
public:

    CMyROC(int nPeriod, int nMAPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nMAPeriod(nMAPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pData(nullptr)
    , m_pROC(nullptr)
    , m_pMAROC(nullptr)
    {
        m_pData  = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pROC   = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pMAROC = new CMyMA(m_nMAPeriod, m_nResultMaxCnt);
    }

    ~CMyROC()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pROC){
            delete m_pROC;
        }

        if(m_pMAROC){
            delete m_pMAROC;
        }
    }

    // NN:=MIN(BARSCOUNT(C),N);
    // ROC:100*(CLOSE-REF(CLOSE,NN))/REF(CLOSE,NN);
    // MAROC:MA(ROC,M);
    void Append(const double& fData, bool bNewPeriod)
    {
        m_pData->AppendData(fData, bNewPeriod);
        int nDataCnt = m_pData->GetDataCnt();
        int nNN = (nDataCnt - 1 >= m_nPeriod ? m_nPeriod : nDataCnt - 1);
        double fNNPreData = m_pData->GetData(-nNN);
        double fROC = UN_VALID_VALUE(double);
        if (IsValid(fNNPreData) && fabs(fNNPreData) > 0){
            fROC = 100 * (fData - fNNPreData) / fNNPreData;
            m_pROC->AppendData(fROC, bNewPeriod);
            m_pMAROC->Append(fROC, bNewPeriod);
        }

        // һ����Ҫ����Чֵ�ŵ�MA����ȥ, ����������ʹ���, 
        // ��Ӧλ�õĲ�ѯ, �鲻���Զ�������Чֵ����
    }

    double ROC(int nIndex)
    {
        return m_pROC->GetData(nIndex);
    }

    double MAROC(int nIndex)
    {
        return m_pMAROC->MA(nIndex);
    }

    void Reset()
    {
        m_pData->Reset();
        m_pROC->Reset();
        m_pMAROC->Reset();
    }

private:

    int                             m_nPeriod;

    int                             m_nMAPeriod;

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    CTimeSeriesData<double>*        m_pData;           // Դ����

    CTimeSeriesData<double>*        m_pROC;            // ������: ROC

    CMyMA*                          m_pMAROC;          // �������ͼ�����: MAROC



};

#endif      // MY_ROC_HPP__


