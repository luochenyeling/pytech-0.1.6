// MTM指标

#ifndef  MY_MTM_HPP__
#define  MY_MTM_HPP__

#include "MyMA.hpp"

class CMyMTM
{
public:

    CMyMTM(int nPeriod, int nMAPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nMAPeriod(nMAPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pData(nullptr)
    , m_pMTM(nullptr)
    , m_pMAMTM(nullptr)
    {
        m_pData  = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pMTM   = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pMAMTM = new CMyMA(m_nMAPeriod, m_nResultMaxCnt);
    }

    ~CMyMTM()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pMTM){
            delete m_pMTM;
        }

        if(m_pMAMTM){
            delete m_pMAMTM;
        }
    }

    // MTM:CLOSE-REF(CLOSE,MIN(BARSCOUNT(C),N));
    // MTMMA:MA(MTM,M);
    void Append(const double& fData, bool bNewPeriod)
    {
        double fMTM = UN_VALID_VALUE(double);
        m_pData->AppendData(fData, bNewPeriod);
        int nDataCnt = m_pData->GetDataCnt();
        int nNN = (nDataCnt - 1 >= m_nPeriod ? m_nPeriod : nDataCnt - 1);
        double fNNPreData = m_pData->GetData(-nNN);

        if (IsValid(fNNPreData)){
            fMTM = fData - fNNPreData;
        }

        m_pMTM->AppendData(fMTM, bNewPeriod);
        m_pMAMTM->Append(fMTM, bNewPeriod);
    }

    double MTM(int nIndex)
    {
        return m_pMTM->GetData(nIndex);
    }

    double MAMTM(int nIndex)
    {
        return m_pMAMTM->MA(nIndex);
    }

    void Reset()
    {
        m_pData->Reset();
        m_pMTM->Reset();
        m_pMAMTM->Reset();
    }

private:

    int                             m_nPeriod;

    int                             m_nMAPeriod;

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pData;           // 源数据

    CTimeSeriesData<double>*        m_pMTM;            // 计算结果: MTM

    CMyMA*                          m_pMAMTM;          // MTM的均值: MAMTM



};

#endif      // MY_MTM_HPP__


