#ifndef   MY_MA_HPP__
#define   MY_MA_HPP__

#include "TimeSeriesData.hpp"
#include <stdio.h>

class CMyMA
{
public:

    CMyMA(int nPeriod, int nResultMaxCnt)
    : m_nPeriod(nPeriod)
    , m_nResultMaxCnt(nResultMaxCnt)
    , m_fDataSum(0.00)
    , m_pData(nullptr)
    , m_pMA(nullptr)
    {
        m_pData    = new CTimeSeriesData<double>(m_nPeriod);
        m_pMA      = new CTimeSeriesData<double>(nResultMaxCnt);
    }

    ~CMyMA()
    {
        if(m_pData){
            delete m_pData;
        }

        if(m_pMA){
            delete m_pMA;
        }
    }

    // 使用时切记原始数据的长度
    // 当nResultMaxCnt大于m_nPeriod时, 要获取原始数据, 要非常谨慎, 超过m_nPeriod的长度获取到的为空, 这个时候需要外部独立保存一份原始数据
    CTimeSeriesData<double>*  SrcData()
    {
        return m_pData;
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (!IsValid(fData)){
            return;
        }

        double fMA           = UN_VALID_VALUE(double);
        int    nRemove      = 0;
        bool   bJustUpdateNew = false;
        double fRemoveData  = 0.0;
        m_pData->AppendData(fData, bNewPeriod, nRemove, fRemoveData);
        m_fDataSum += (fData - fRemoveData);   // fRemoveData 在PushData里也会被初始化为0, 所以这里直接(fData - fRemoveData)即可, 不判断nRemove是否为0了
        if (m_pData->IsFull()){
            fMA = m_fDataSum / m_nPeriod;
        }

        m_pMA->AppendData(fMA, bNewPeriod);
    }

    double MA(int nIndex)
    {
        return m_pMA->GetData(nIndex);
    }

    void Reset()
    {
        m_fDataSum = 0.00;
        m_pData->Reset();
        m_pMA->Reset();
    }

private:

    int                             m_nPeriod;         // 计算周期

    int                             m_nResultMaxCnt;   // 最多保存多少个结果

    double                          m_fDataSum;        // 原始数据的和

    CTimeSeriesData<double>*        m_pData;           // 原始数据, 用于计算的数据, 注意其长度是m_nPeriod

    CTimeSeriesData<double>*        m_pMA;             // 计算结果
};



#endif    // MY_MA_HPP__
