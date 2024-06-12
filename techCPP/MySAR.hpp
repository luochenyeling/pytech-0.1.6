#ifndef  MY_SAR_HPP__
#define  MY_SAR_HPP__

#include "TimeSeriesData.hpp"

class  CMySAR
{
public:

    CMySAR(int nPeriod, int nBaseAF, int nAddAF, int nMaxAF, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_baseAF(nBaseAF / 100.00)
    , m_addAF(nAddAF / 100.00)
    , m_maxAF(nMaxAF / 100.00)
    , m_pHigh(nullptr)
    , m_pLow(nullptr)
    , m_pAF(nullptr)
    , m_pLastPrice(nullptr)
    , m_pSAR(nullptr)
    , m_pDirection(nullptr)
    {
        m_pHigh      = new CTimeSeriesData<double>(m_nPeriod + 1);  // ���Դ���ݵ����������ֵһ��Ҫ> m_nPeriod, ���������߼���������
        m_pLow       = new CTimeSeriesData<double>(m_nPeriod + 1);  // ���Դ���ݵ����������ֵһ��Ҫ> m_nPeriod, ���������߼���������
        m_pAF        = new CTimeSeriesData<double>(2);
        m_pLastPrice = new CTimeSeriesData<double>(2);
        m_pSAR       = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pDirection = new CTimeSeriesData<int>(nResultMaxCnt);
    }

    ~CMySAR()
    {
        if (m_pHigh){
            delete m_pSAR;
        }

        if (m_pLow){
            delete m_pSAR;
        }

        if (m_pLastPrice){
            delete m_pSAR;
        }

        if (m_pAF){
            delete m_pSAR;
        }

        if (m_pSAR){
            delete m_pSAR;
        }

        if(m_pDirection){
            delete m_pDirection;
        }
    }

    void Append(const double& fHigh, const double& fLow, bool bNewPeriod)
    {
        int    nUp      = m_pDirection->GetCurPreData(bNewPeriod);
        double fPreSAR  = m_pSAR->GetCurPreData(bNewPeriod);
        double fAF      = m_pAF->GetCurPreData(bNewPeriod);
        double fPrice   = m_pLastPrice->GetCurPreData(bNewPeriod);
        double fPreHigh = m_pHigh->GetCurPreData(bNewPeriod);
        double fPreLow  = m_pLow->GetCurPreData(bNewPeriod);

        m_pHigh->AppendData(fHigh, bNewPeriod);
        m_pLow->AppendData(fLow, bNewPeriod);

        int nDataCnt = m_pHigh->GetDataCnt();
        if (nDataCnt < m_nPeriod){
            m_pSAR->AppendData(UN_VALID_VALUE(double), bNewPeriod);
            m_pDirection->AppendData(1, bNewPeriod);
            return ;
        }

        // bar������=m_nPeriod��ʱ��ſ�ʼ�н��
        if(nDataCnt == m_nPeriod){;
            int    nLLVIndex = 0;
            double fHHV = 0.00;
            double fLLV = 0.00;
            m_pHigh->PeriodHigh(0, m_nPeriod, fHHV, nLLVIndex);
            m_pLow->PeriodLow(0, m_nPeriod, fLLV, nLLVIndex);
            m_pAF->AppendData(m_baseAF, bNewPeriod);
            m_pLastPrice->AppendData(fHHV, bNewPeriod);
            m_pSAR->AppendData(fLLV, bNewPeriod);
            m_pDirection->AppendData(1, bNewPeriod);
            return ;
        }

        if (nUp > 0) {                   //֮ǰ����������
            if (fLow >= fPreSAR) {         //������������
                if (fHigh > fPrice) {
                    fPrice = fHigh;
                    fAF += m_addAF;
                }
                if (fAF > m_maxAF) {
                    fAF = m_maxAF;
                }

                double fCurSAR = fPreSAR + fAF * (fPrice - fPreSAR);

                if (fLow < fCurSAR) {
                    fCurSAR = fLow;
                }

                if (fPreLow < fCurSAR) {
                    fCurSAR = fPreLow;
                }

                m_pAF->AppendData(fAF, bNewPeriod);
                m_pLastPrice->AppendData(fPrice, bNewPeriod);
                m_pSAR->AppendData(fCurSAR, bNewPeriod);
                m_pDirection->AppendData(nUp, bNewPeriod);
                return;
            }

            //ת��Ϊ�µ�����
            nUp = -1;
            fAF = m_baseAF;  //���³�ʼ��������
            double fTempPrice = fPrice;
            fPrice = fPreLow;
            if (fPrice > fLow) {
                fPrice = fLow;
            }

            double fCurSAR = fTempPrice + fAF * (fPrice - fTempPrice);

            if (fHigh > fCurSAR) {
                fCurSAR = fHigh;
            }

            if (fPreHigh > fCurSAR) {
                fCurSAR = fPreHigh;
            }

            m_pAF->AppendData(fAF, bNewPeriod);
            m_pLastPrice->AppendData(fPrice, bNewPeriod);
            m_pSAR->AppendData(fCurSAR, bNewPeriod);
            m_pDirection->AppendData(nUp, bNewPeriod);
            return;
        }

        if (nUp < 0) {                     //֮ǰ���µ�����
            if (fHigh <= fPreSAR) {      //�����µ�����
                if (fLow < fPrice) {
                    fPrice = fLow;
                    fAF   += m_addAF;
                }

                if (fAF > m_maxAF) {
                    fAF = m_maxAF;
                }

                double fCurSAR = fPreSAR + fAF * (fPrice - fPreSAR);

                if (fHigh > fCurSAR) {
                    fCurSAR = fHigh;
                }

                if (fPreHigh > fCurSAR) {
                    fCurSAR = fPreHigh;
                }

                m_pAF->AppendData(fAF, bNewPeriod);
                m_pLastPrice->AppendData(fPrice, bNewPeriod);
                m_pSAR->AppendData(fCurSAR, bNewPeriod);
                m_pDirection->AppendData(nUp, bNewPeriod);
                return;
            }

            //ת��Ϊ��������
            nUp = 1;
            fAF = m_baseAF;//���³�ʼ��������
            fPrice = fHigh;
            double fCurSAR = fLow;
            if (fPreLow < fCurSAR) {
                fCurSAR = fPreLow;
            }

            m_pAF->AppendData(fAF, bNewPeriod);
            m_pLastPrice->AppendData(fPrice, bNewPeriod);
            m_pSAR->AppendData(fCurSAR, bNewPeriod);
            m_pDirection->AppendData(nUp, bNewPeriod);
            return;
        }
    }

    double SAR(int nIndex)
    {
        return m_pSAR->GetData(nIndex);
    }

    int Direction(int nIndex)
    {
        return m_pDirection->GetData(nIndex);
    }

    void Reset()
    {
        m_pHigh->Reset();
        m_pLow->Reset();
        m_pAF->Reset();
        m_pLastPrice->Reset();
        m_pSAR->Reset();
        m_pDirection->Reset();
    }

private:

    int                         m_nPeriod;

    double                      m_baseAF;

    double                      m_addAF;

    double                      m_maxAF;

    CTimeSeriesData<double>*    m_pHigh;          // ��߼۵�Դ����

    CTimeSeriesData<double>*    m_pLow;           // ��ͼ۵�Դ����

    CTimeSeriesData<double>*    m_pAF;            // ��Ҫ���ڼ�¼��һ�ε�ֵ, ���Է���2����С�Ŀռ伴��

    CTimeSeriesData<double>*    m_pLastPrice;     // ��Ҫ���ڼ�¼��һ�ε�ֵ, ���Է���2����С�Ŀռ伴��

    CTimeSeriesData<double>*    m_pSAR;           // SAR���

    CTimeSeriesData<int>*       m_pDirection;     // ������ 1 : up   -1 : down
};

#endif      // MY_SAR_HPP__


