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

        // 一定不要把无效值放到MA里面去, 否则结果出入就大了, 
        // 对应位置的查询, 查不到自动返回无效值即可
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

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pData;           // 源数据

    CTimeSeriesData<double>*        m_pROC;            // 计算结果: ROC

    CMyMA*                          m_pMAROC;          // 计算器和计算结果: MAROC



};

#endif      // MY_ROC_HPP__


