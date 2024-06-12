// MFI指标:资金流量指标

#ifndef  MY_MFI_HPP__
#define  MY_MFI_HPP__

#include "TimeSeriesData.hpp"
#include "MyMA.hpp"

class CMyMFI
{
public:

    CMyMFI(int nPeriod, int nMPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nMPeriod(nMPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pData(nullptr)
    , m_pVol(nullptr)
    , m_pMFI(nullptr)
    , m_pMAMFI(nullptr)
    {
        m_pData  = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pVol   = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pMFI = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pMAMFI = new CMyMA(m_nMPeriod, m_nResultMaxCnt);
    }

    ~CMyMFI()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pVol){
            delete m_pVol;
        }

        if(m_pMFI){
            delete m_pMFI;
        }

        if(m_pMAMFI){
            delete m_pMAMFI;
            m_pMAMFI = NULL;
        }
    }

    // TYP:=(HIGH + LOW + CLOSE)/3;
    // V1:=SUM(IF(TYP>REF(TYP,1),TYP*VOL,0),N)/SUM(IF(TYP<REF(TYP,1),TYP*VOL,0),N);
    // MFI:100-(100/(1+V1));
    void Append(const double& fHigh, const double& fLow, const double& fClose, const double& fVol, bool bNewPeriod)
    {
        double fTYP = (fHigh + fLow + fClose) / 3;
        m_pData->AppendData(fTYP, bNewPeriod);
        m_pVol->AppendData(fVol, bNewPeriod);

        double fSum1  = 0.00;
        double fSum2  = 0.00;
        for(int i = 0; abs(i) < m_nPeriod; --i){
            double fT     = m_pData->GetData(i);
            double fV     = m_pVol->GetData(i);
            double fPreT  = m_pData->GetData(i - 1);
            if(!IsValid(fT) || !IsValid(fPreT)){
                break;
            }

            if(fT > fPreT){
                fSum1 += fT * fV;
            }
            else if(fT < fPreT){
                fSum2 += fT * fV;
            }
        }

        double fMFI = UN_VALID_VALUE(double);
        if(fabs(fSum2) > 1e-6){
            double fV1 = fSum1 / fSum2;
            fMFI = 100.00 - 100.00 / (1 + fV1);
        }

        m_pMFI->AppendData(fMFI, bNewPeriod);

        m_pMAMFI->Append(fMFI, bNewPeriod);
    }

    double MFI(int nIndex)
    {
        return m_pMFI->GetData(nIndex);
    }

    double MAMFI(int nIndex)
    {
        return m_pMAMFI->MA(nIndex);
    }

    void Reset()
    {
        m_pData->Reset();
        m_pVol->Reset();
        m_pMFI->Reset();
        m_pMAMFI->Reset();
    }

private:

    int                             m_nPeriod;

    int                             m_nMPeriod;

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pData;           // 源数据: 通过H,L,C计算得到

    CTimeSeriesData<double>*        m_pVol;            // 源数据: 成交量

    CTimeSeriesData<double>*        m_pMFI;            // 计算结果: MFI

    CMyMA*                          m_pMAMFI;          // 平均值: MAMFI

};

#endif      // MY_MFI_HPP__


