// 最高(大)、最低(小)值

#ifndef  MY_HL_HPP__
#define  MY_HL_HPP__

#include <limits>

class CMyHL
{
public:

    CMyHL(int nHLType, int nPeriod)
    : m_nHlType(nHLType)
    , m_nPeriod(nPeriod)
    , m_nDataCnt(0)
    , m_nHLIndex(-1)
    , m_pData(nullptr)
    {
        m_pData = new double[m_nPeriod];
        memset(m_pData, 0, sizeof(double) * m_nPeriod);
        if (m_nHlType == 0){
            m_fHLData = std::numeric_limits<double>::max();
        }
        else{
            m_fHLData = std::numeric_limits<double>::lowest();
        }
    }

    ~CMyHL()
    {
        if(m_pData){
            delete m_pData;
        }
    }

    void Append(const double& fData, bool bNewPeriod)
    {
        if (bNewPeriod){
            if (m_nDataCnt < m_nPeriod){
                ++m_nDataCnt;
                m_pData[m_nDataCnt - 1] = fData;
                if ((m_nHlType == 0 && fData < m_fHLData) || (m_nHlType == 1 && fData > m_fHLData)){
                    m_fHLData = fData;
                    m_nHLIndex = m_nDataCnt - 1;
                }
            }
            else{
                memmove(m_pData, m_pData + 1, (m_nDataCnt - 1) * sizeof(double));
                m_pData[m_nDataCnt - 1] = fData;
                if ((m_nHlType == 0 && fData < m_fHLData) || (m_nHlType == 1 && fData > m_fHLData)){
                    m_fHLData = fData;
                    m_nHLIndex = m_nDataCnt - 1;
                }
                else if (m_nHLIndex == 0){    //  如果被移除的数刚好是最大或者最小值, 需要重新计算
                    m_fHLData = (m_nHlType == 0 ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
                    for (int i = 0; i < m_nDataCnt; ++i) {
                        if ((m_nHlType == 0 && m_pData[i] < m_fHLData) || (m_nHlType == 1 && m_pData[i] > m_fHLData)){
                            m_fHLData  = m_pData[i];
                            m_nHLIndex = i;
                        }
                    }
                }
                else{
                    --m_nHLIndex;           // 因为数据整体往前移动了1位, 所以索引也要-1
                }
            }
        }
        else{
            if (m_nDataCnt == 0){
                ++m_nDataCnt;
            }

            m_pData[m_nDataCnt - 1] = fData;
            if ((m_nHlType == 0 && fData < m_fHLData) || (m_nHlType == 1 && fData > m_fHLData)){
                m_fHLData = fData;
                m_nHLIndex = m_nDataCnt - 1;
            }
            else if (m_nHLIndex == m_nDataCnt - 1){ // 之前最新值是最大(小)值, 但是最新值被一个更小(大)的数覆盖了, 就要重新计算了
                m_fHLData = (m_nHlType == 0 ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
                for (int i = 0; i < m_nDataCnt; ++i) {
                    if ((m_nHlType == 0 && m_pData[i] < m_fHLData) || (m_nHlType == 1 && m_pData[i] > m_fHLData)){
                        m_fHLData  = m_pData[i];
                        m_nHLIndex = i;
                    }
                }
            }
        }
    }

    // 当前值是否是最值
    bool IsNewHL()
    {
        return m_nHLIndex == m_nDataCnt - 1;

        // 以上的判断, 没有采用 m_nHLIndex == m_nPeriod - 1 的条件, 
        // 认为即使数据不满l_periods_的个数, 也是满足条件的
    }

    double HL()
    {
        return m_fHLData;
    }

    void Reset()
    {
        m_nDataCnt = 0;
        m_nHLIndex = -1;
        memset(m_pData, 0, sizeof(double) * m_nPeriod);
        if (m_nHlType == 0){
            m_fHLData = std::numeric_limits<double>::max();
        }
        else{
            m_fHLData = std::numeric_limits<double>::lowest();
        }
    }

private:

    int        m_nHlType;             // 0 ： 最低  1 : 最高

    int        m_nPeriod;             // 要求>=2

    double     m_fHLData;            // 最值

    int        m_nDataCnt;           // 数据个数

    int        m_nHLIndex;           // 最值的索引

    double*    m_pData;              // 数据

};

#endif   //MY_HL_HPP__