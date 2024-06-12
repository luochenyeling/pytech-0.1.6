//注意: 这里是指DMA(动态移动平均)函数, 不是通常的DMA(平均差)指标

#ifndef  MY_DMA_HPP__
#define  MY_DMA_HPP__

#include "TimeSeriesData.hpp"

class CMyDMA
{
public:
    CMyDMA(int nResultMaxCnt)
    : m_nResultMaxCnt(nResultMaxCnt)
    , m_pDMA(nullptr)
    , m_nDataCnt(0)
    {
        m_pDMA   = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyDMA()
    {
        if(m_pDMA){
            delete m_pDMA;
        }
    }

    void Append(const double& fData, double fSmooth, bool bNewPeriod)
    {
        if (!m_pDMA || fSmooth >= 1 || fSmooth <= 0){
            return;
        }

        double fPreDma  = UN_VALID_VALUE(double);
        double fCurDma  = UN_VALID_VALUE(double);

        // DMA(A, X) = Y = A * X + (1 - A) * Y', 其中Y'表示上一周期Y值
        if (bNewPeriod || m_nDataCnt == 0){
            ++m_nDataCnt;
        }

        if(m_nDataCnt == 1){
            fCurDma = fData;
        }
        else{
            fPreDma = m_pDMA->GetCurPreData(bNewPeriod);
            if(IsValid(fPreDma)){
                fCurDma = fSmooth * fData + (1 - fSmooth) * fPreDma;
            }
        }

        m_pDMA->AppendData(fCurDma, bNewPeriod);
    }

    double DMA(int nIndex)
    {
        return m_pDMA->GetData(nIndex);
    }

    void Reset()
    {
        m_nDataCnt = 0;
        m_pDMA->Reset();
    }

private:

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    CTimeSeriesData<double>*        m_pDMA;            // 计算结果

    unsigned int                    m_nDataCnt;        // 原始数据的个数
};


#endif          // MY_DMA_HPP__


