// OBV(������)ָ��
// ע��: ʵ��ʹ�õ�ʱ��Ҫ�����������㹻��, �������ܴ�, ��Ϊ������һ���ۼ���

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

    // VA:=IF(CLOSE>REF(CLOSE,1),VOL,-VOL);            VOL������
    // OBV:SUM(IF(CLOSE=REF(CLOSE,1),0,VA),0);
    // MAOBV:MA(OBV,M);
    void Append(const double& fClose, const double& fVol, bool bNewPeriod)
    {
        double fOBV = UN_VALID_VALUE(double);
        int nRemove        = 0;
        double fRemoveData = 0.00;
        m_pData->AppendData(fClose, bNewPeriod, nRemove, fRemoveData);
        if(nRemove == 2){   // �����һ��ֻ�Ǹ����滻���µ�����, ��ôҪ����һ���ۼӵ����ݼ���
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

    int                             m_nMAPeriod;       // OBV��ֵ����, Ĭ��30

    int                             m_nResultMaxCnt;   // ��ౣ����ٸ����

    double                          m_fSum;            // �������ݵ��ۼ�ֵ, �����˺������ݸ���ʱ���Ƴ��ľ�����

    double                          m_fPreVA;          // m_fSum��һ���ۼӵ�����

    CTimeSeriesData<double>*        m_pData;           // Դ����

    CTimeSeriesData<double>*        m_pOBV;            // ������: OBV

    CMyMA*                          m_pMAOBV;          // OBV�ľ�ֵ: MAOBV



};

#endif      // MY_OBV_HPP__


