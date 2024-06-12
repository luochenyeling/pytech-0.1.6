// OBV(能量潮)指标
// 注意: 实际使用的时候要求输入数据足够长, 否则误差很大, 因为这里是一个累计量

#ifndef  MY_OBV_HPP__
#define  MY_OBV_HPP__

#include "MyMA.hpp"

class CMyOBV
{
public:

    CMyOBV(int nMAPeriod, int nResultMaxCnt)
    : m_nMAPeriod(nMAPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_fSum(0.00)
    , m_fPreVA(0.00)
    , m_pData(nullptr)
    , m_pOBV(nullptr)
    , m_pMAOBV(nullptr)
    {
        m_pData  = new CTimeSeriesData<double>(2);
        m_pOBV   = new CTimeSeriesData<double>(m_nResultMaxCnt);
        m_pMAOBV = new CMyMA(m_nMAPeriod, m_nResultMaxCnt);
    }

    ~CMyOBV()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pOBV){
            delete m_pOBV;
        }

        if(m_pMAOBV){
            delete m_pMAOBV;
        }
    }

    // VA:=IF(CLOSE>REF(CLOSE,1),VOL,-VOL);            VOL是手数
    // OBV:SUM(IF(CLOSE=REF(CLOSE,1),0,VA),0);
    // MAOBV:MA(OBV,M);
    void Append(const double& fClose, const double& fVol, bool bNewPeriod)
    {
        double fOBV = UN_VALID_VALUE(double);
        int nRemove        = 0;
        double fRemoveData = 0.00;
        m_pData->AppendData(fClose, bNewPeriod, nRemove, fRemoveData);
        if(nRemove == 2){   // 如果这一次只是更新替换最新的数据, 那么要把上一次累加的数据减掉
            m_fSum -= m_fPreVA;
        }

        double fPreClose = m_pData->GetData(-1);
        if(IsValid(fPreClose)){
            double fVA = 0.00;
            if(fabs(fClose - fPreClose) > 1e-6){
                fVA = fClose > fPreClose ? fVol : -1 * fVol;
            }

            m_fSum   += fVA;
            m_fPreVA  = fVA;

            fOBV = m_fSum;
        }

        m_pOBV->AppendData(fOBV, bNewPeriod);
        m_pMAOBV->Append(fOBV, bNewPeriod);
    }

    double OBV(int nIndex)
    {
        return m_pOBV->GetData(nIndex);
    }

    double MAOBV(int nIndex)
    {
        return m_pMAOBV->MA(nIndex);
    }

    void Reset()
    {
        m_fSum   = 0.00;
        m_fPreVA = 0.00;
        m_pData->Reset();
        m_pOBV->Reset();
        m_pMAOBV->Reset();
    }
private:

    int                             m_nMAPeriod;       // OBV均值周期, 默认30

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    double                          m_fSum;            // 输入数据的累计值, 包括了后续数据更新时被移除的旧数据

    double                          m_fPreVA;          // m_fSum上一次累加的数据

    CTimeSeriesData<double>*        m_pData;           // 源数据

    CTimeSeriesData<double>*        m_pOBV;            // 计算结果: OBV

    CMyMA*                          m_pMAOBV;          // OBV的均值: MAOBV



};

#endif      // MY_OBV_HPP__


