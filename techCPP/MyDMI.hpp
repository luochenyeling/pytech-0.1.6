#ifndef MY_DMI_HPP__
#define MY_DMI_HPP__

#include "MyMA.hpp"
#include <algorithm>

// 预加载的数据最低要多少个Bar： (nPeriod + 2 * nInter) - 1

class CMyDMI
{
public:

    CMyDMI(int nPeriod, int nInter, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nInter(nInter)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_pHighData(nullptr)
    , m_pLowData(nullptr)
    , m_pCloseData(nullptr)
    , m_pMA(nullptr)
    , m_pPDI(nullptr)
    , m_pMDI(nullptr)
    , m_pADX(nullptr)
    , m_pADXR(nullptr)
    {
        m_pHighData  = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pLowData   = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pCloseData = new CTimeSeriesData<double>(m_nPeriod + 1);
        m_pMA        = new CMyMA(m_nInter, m_nResultMaxCnt);
        m_pPDI       = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pMDI       = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pADX       = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pADXR      = new CTimeSeriesData<double>(m_nResultMaxCnt);
    }

    ~CMyDMI()
    {
        if (m_pHighData){
            delete m_pHighData;
        }

        if (m_pLowData){
            delete m_pLowData;
        }

        if (m_pCloseData){
            delete m_pCloseData;
        }

        if (m_pPDI){
            delete m_pPDI;
        }

        if (m_pMDI){
            delete m_pMDI;
        }

        if (m_pADX){
            delete m_pADX;
        }

        if (m_pADXR){
            delete m_pADXR;
        }
    }

    void Append(const double& fHigh, const double& fLow, const double& fClose, bool bNewPeriod)
    {
        m_pHighData->AppendData(fHigh, bNewPeriod);

        m_pLowData->AppendData(fLow, bNewPeriod);

        m_pCloseData->AppendData(fClose, bNewPeriod);

        double fPDI  = UN_VALID_VALUE(double);
        double fMDI  = UN_VALID_VALUE(double);
        double fADX  = UN_VALID_VALUE(double);
        double fADXR = UN_VALID_VALUE(double);

        CalcDMI(0, bNewPeriod, fPDI, fMDI, fADX, fADXR);
        m_pPDI->AppendData(fPDI, bNewPeriod);
        m_pMDI->AppendData(fMDI, bNewPeriod);
        m_pADX->AppendData(fADX, bNewPeriod);
        m_pADXR->AppendData(fADXR, bNewPeriod);
    }

    void GetDMI(int nIndex, double& fPDI, double& fMDI, double& fADX, double& fADXR)
    {
        fPDI  = m_pPDI->GetData(nIndex);
        fMDI  = m_pMDI->GetData(nIndex);
        fADX  = m_pADX->GetData(nIndex);
        fADXR = m_pADXR->GetData(nIndex);
    }

    double PDI(int nIndex)
    {
        return m_pPDI->GetData(nIndex);
    }

    double MDI(int nIndex)
    {
        return m_pMDI->GetData(nIndex);
    }

    double ADX(int nIndex)
    {
        return m_pADX->GetData(nIndex);
    }

    double ADXR(int nIndex)
    {
        return m_pADXR->GetData(nIndex);
    }

    void Reset()
    {
        m_pHighData->Reset();
        m_pLowData->Reset();
        m_pCloseData->Reset();
        m_pMA->Reset();
        m_pPDI->Reset();
        m_pMDI->Reset();
        m_pADX->Reset();
        m_pADXR->Reset();
    }

private:

    // DMI的计算公式如下：
    // MTR:=SUM(MAX(MAX(HIGH-LOW,ABS(HIGH-REF(CLOSE,1))),ABS(REF(CLOSE,1)-LOW)),N);
    // HD :=HIGH-REF(HIGH,1);
    // LD :=REF(LOW,1)-LOW;
    // DMP:=SUM(IF(HD>0&&HD>LD,HD,0),N);
    // DMM:=SUM(IF(LD>0&&LD>HD,LD,0),N);
    // PDI: DMP*100/MTR;
    // MDI: DMM*100/MTR;
    // ADX: MA(ABS(MDI-PDI)/(MDI+PDI)*100,M);
    // ADXR:(ADX+REF(ADX,M))/2;
    void CalcDMI(int nIndex, bool bNewPeriod, double& fPDI, double& fMDI, double& fADX, double& fADXR)
    {
        fPDI  = UN_VALID_VALUE(double);
        fMDI  = UN_VALID_VALUE(double);
        fADX  = UN_VALID_VALUE(double);
        fADXR = UN_VALID_VALUE(double);

        int nTodayIndex = nIndex;

        double fSumTr         = 0.00;
        double fSumHighDiff = 0.00;
        double fSumLowDiff  = 0.00;

        int nSumCnt = 0;
        while(nSumCnt < m_nPeriod){
            double fTodayHigh   = m_pHighData->GetData(nTodayIndex);
            double fTodayLow    = m_pLowData->GetData(nTodayIndex);

            double fPreHigh  = m_pHighData->GetData(nTodayIndex - 1);
            double fPreLow   = m_pLowData->GetData(nTodayIndex - 1);
            double fPreClose = m_pCloseData->GetData(nTodayIndex - 1);
            if (!IsValid(fPreHigh) || !IsValid(fPreLow) || !IsValid(fPreClose) || !IsValid(fTodayHigh) || !IsValid(fTodayLow)){
                break;
            }

            double fHLDiff  = fTodayHigh - fTodayLow;
            double fHCDiff  = fabs(fTodayHigh - fPreClose);
            double fLCDiff  = fabs(fTodayLow - fPreClose);
            double fTr       = std::max(std::max(fHLDiff, fHCDiff), fLCDiff);

            fSumTr          += fTr;

            double fHighDiff = fTodayHigh - fPreHigh;
            double fLowDiff  = fPreLow - fTodayLow;

            if (fHighDiff > 0 && fHighDiff > fLowDiff){
                fSumHighDiff += fHighDiff;
            }

            if (fLowDiff > 0 && fLowDiff > fHighDiff){
                fSumLowDiff += fLowDiff;
            }

            ++nSumCnt;
            --nTodayIndex;
        }

        if (nSumCnt == 0 || fabs(fSumTr) < 1e-6){
            return;
        }

        // 计算PDI, MDI, ADX 和 ADXR
        fPDI = fSumHighDiff * 100 / fSumTr;
        fMDI = fSumLowDiff * 100 / fSumTr;

        double fSADX = fabs(fMDI - fPDI) / (fMDI + fPDI) * 100;
        m_pMA->Append(fSADX, bNewPeriod);
        fADX  = m_pMA->MA(0);
        double fADXPre6 = m_pMA->MA(-1 * m_nInter);
        if (IsValid(fADXPre6)){
            fADXR = (fADX + fADXPre6) / 2;
        }
    }

private:

    int                             m_nPeriod;         // PDI和MDI的计算周期

    int                             m_nInter;          // ADX的平滑周期

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pHighData;       // 原始最高数据

    CTimeSeriesData<double>*        m_pLowData;        // 原始最低数据

    CTimeSeriesData<double>*        m_pCloseData;      // 原始收盘数据

    CMyMA*                          m_pMA;             // fabs(mi - di)/(mi + di) * 100 的值的m_nInter的MA值

    CTimeSeriesData<double>*        m_pPDI;            // 结果：PDI值

    CTimeSeriesData<double>*        m_pMDI;            // 结果：MDI值

    CTimeSeriesData<double>*        m_pADX;            // 结果：ADX值

    CTimeSeriesData<double>*        m_pADXR;           // 结果：ADXR值

};

#endif  // MY_DMI_HPP__


