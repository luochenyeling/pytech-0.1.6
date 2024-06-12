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
        m_pHigh      = new CTimeSeriesData<double>(m_nPeriod + 1);  // 存放源数据的数量的最大值一定要> m_nPeriod, 否则后面的逻辑会有问题
        m_pLow       = new CTimeSeriesData<double>(m_nPeriod + 1);  // 存放源数据的数量的最大值一定要> m_nPeriod, 否则后面的逻辑会有问题
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

        // bar的数量=m_nPeriod的时候才开始有结果
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

        if (nUp > 0) {                   //之前在上升趋势
            if (fLow >= fPreSAR) {         //延续上升趋势
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

            //转变为下跌趋势
            nUp = -1;
            fAF = m_baseAF;  //重新初始化加速器
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

        if (nUp < 0) {                     //之前是下跌趋势
            if (fHigh <= fPreSAR) {      //延续下跌趋势
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

            //转变为上升趋势
            nUp = 1;
            fAF = m_baseAF;//重新初始化加速器
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

    CTimeSeriesData<double>*    m_pHigh;          // 最高价的源数据

    CTimeSeriesData<double>*    m_pLow;           // 最低价的源数据

    CTimeSeriesData<double>*    m_pAF;            // 主要用于记录上一次的值, 所以分配2个大小的空间即可

    CTimeSeriesData<double>*    m_pLastPrice;     // 主要用于记录上一次的值, 所以分配2个大小的空间即可

    CTimeSeriesData<double>*    m_pSAR;           // SAR结果

    CTimeSeriesData<int>*       m_pDirection;     // 方向结果 1 : up   -1 : down
};

#endif      // MY_SAR_HPP__


