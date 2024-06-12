#ifndef   MY_MEAN_STD_HPP__
#define   MY_MEAN_STD_HPP__

#include "TimeSeriesData.hpp"
#include <stdio.h>

class CMyMeanStd
{
public:

    CMyMeanStd(int nPeriod, int nResultMaxCnt, int stddof)
    : m_nPeriod(nPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_nStdDof(stddof)
    , m_fDataSum(0.00)
    , m_pData(nullptr)
    , m_pMean(nullptr)
    , m_pStd(nullptr)
    {
        m_pData = new CTimeSeriesData<double>(m_nPeriod);
        m_pMean   = new CTimeSeriesData<double>(nResultMaxCnt);
        m_pStd   = new CTimeSeriesData<double>(nResultMaxCnt);
        if(m_nStdDof == 0){
            m_nStd = m_nPeriod;
        }
        else{
            m_nStd = m_nPeriod - 1;
        }
    }

    ~CMyMeanStd()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pMean){
            delete m_pMean;
        }

        if(m_pStd){
            delete m_pStd;
        }
    }

    CTimeSeriesData<double>*  SrcData()
    {
        return m_pData;
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!IsValid(fData)){
            return;
        }

        double fMean         = UN_VALID_VALUE(double);
        double fStd          = UN_VALID_VALUE(double);
        int   nRemove       = 0;
        double fRemoveData   = 0.0;

        double fPreMean      = m_pMean->GetData(0);
        double fPreStd       = m_pStd->GetData(0);

        m_pData->AppendData(fData, bNewPeriod, nRemove, fRemoveData);
        double fDiff = fData - fRemoveData;
        m_fDataSum += fDiff;
        if (m_pData->IsFull()){
            fMean = m_fDataSum / m_nPeriod;
            if(m_nStd > 0){
                if(nRemove == 0){
                    double fAS = 0.0;
                    for (int index = 0; index > -1 * m_pData->GetDataCnt(); --index){
                        fAS += pow((m_pData->GetData(index) - fMean), 2);
                    }

                    fStd = sqrt(fAS / m_nStd);
                }
                else{
                    // 注释代码的作用: 循环计算和推导公式的结果做比较
                    //double fAS = 0.0;
                    //for (int index = 0; index > -1 * m_pData->GetDataCnt(); --index){
                    //    fAS += pow((m_pData->GetData(index) - fMean), 2);
                    //}
                    //double fxStd = sqrt(fAS / m_nStd);

                    if(IsValid(fPreMean) && IsValid(fPreStd)){
                        // 有数据移除或者被替换时,推导出来的公式, 避免for循环耗时
                        double fAS = pow(fPreStd, 2) * m_nStd + pow(fDiff / m_nPeriod, 2) * (m_nPeriod - 1) + pow(fDiff - fDiff/m_nPeriod, 2) + 2 * fDiff * (fRemoveData - fPreMean);
                        fStd = sqrt(fAS / m_nStd);
                    }
                }
            }
        }

        m_pMean->AppendData(fMean, bNewPeriod);
        m_pStd->AppendData(fStd, bNewPeriod);
    }

    double Mean(int nIndex)
    {
        return m_pMean->GetData(nIndex);
    }

    double Std(int nIndex)
    {
        return m_pStd->GetData(nIndex);
    }

    void Reset()
    {
        m_fDataSum = 0.00;
        m_pData->Reset();
        m_pMean->Reset();
        m_pStd->Reset();
    }

private:

    int                             m_nPeriod;         // 计算周期

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    int                             m_nStdDof;        // 0 -- 分母是m_nPeriod, 1 -- 分母是m_nPeriod -1

    int                             m_nStd;           //

    double                          m_fDataSum;        // 原始数据的和

    CTimeSeriesData<double>*        m_pData;           // 原始数据

    CTimeSeriesData<double>*        m_pMean;           // Mean计算结果

    CTimeSeriesData<double>*        m_pStd;            // std计算结果
};



#endif    // MY_MEAN_STD_HPP__
