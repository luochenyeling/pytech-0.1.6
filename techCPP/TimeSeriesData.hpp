// 使用循环队列实现时间序列数组, 减少memmove或者memcpy带来的效率损失

#ifndef  TIME_SERIES_DATA_HPP__
#define  TIME_SERIES_DATA_HPP__

#include <limits>
#include <cstring>

#define  UN_VALID_VALUE(T)   std::numeric_limits<T>::lowest()

template<typename T>
bool IsValid(const T& t)
{
    if (t == std::numeric_limits<T>::lowest() || t == std::numeric_limits<T>::max()){
        return false;
    }

    return true;
}

// 时间序列数据
// 最新的数据放在数组最末尾, 最老的数据放在数组首位
template<typename T>
class CTimeSeriesData
{
public:

    CTimeSeriesData(int nMaxCnt)
    : m_pData(nullptr)
    , m_nDataMaxCnt(nMaxCnt)
    , m_nDataCnt(0)
    , m_nBegIndex(-1)
    , m_nEndIndex(-1)
    {
        m_pData = new T[m_nDataMaxCnt];
        memset(m_pData, 0, sizeof(T) * m_nDataMaxCnt);
    }

    ~CTimeSeriesData()
    {
        if (m_pData){
            delete [] m_pData;
        }
    }

    const int& GetDataCnt() const
    {
        return m_nDataCnt;
    } 

    bool IsFull()
    {
        return m_nDataCnt == m_nDataMaxCnt;
    }

    // 重置数据缓存
    void Reset()
    {
        m_nDataCnt  = 0;
        m_nBegIndex = -1;
        m_nEndIndex = -1;
    }

    T GetData(int nIndex)
    {
        int nRealArrayIndex = GetRealIndexRelativeEnd(nIndex);
        if (nRealArrayIndex == -1){
            return UN_VALID_VALUE(T);
        }

        return m_pData[nRealArrayIndex];
    }

    // 获取当前周期的前一个周期的值
    // 输入是当前周期是否是一个新周期
    // 请注意这个逻辑, 如果来的数据是一个新周期的bar, 那么前一个值就在m_pData的最新位置
    // 否则, 仅仅是数据更新, 那么计算的时候,前值就应该是取-1处, 因为在0处,是当前周期的上一个值计算出来的
    // 尤其需要注意使用的是和append的前后位置, 一般是放在append之前调用
    T GetCurPreData(bool bCurNewPeriod)
    {
        if (bCurNewPeriod){
            return GetData(0);
        }
        else{
            return GetData(-1);
        }
    }

    bool AppendData(const T& tData, bool bNewPeriod)
    {
        if (!m_pData || m_nDataMaxCnt <= 0){
            return false;
        }

        if (bNewPeriod){
            if (m_nDataCnt == m_nDataMaxCnt){
                ++m_nBegIndex;
                ++m_nEndIndex;
                if (m_nEndIndex == m_nDataMaxCnt){
                    m_nEndIndex = 0;
                }

                if (m_nBegIndex == m_nDataMaxCnt){
                    m_nBegIndex = 0;
                }

                m_pData[m_nEndIndex] = tData;
            }
            else{
                if (m_nBegIndex == -1){
                    ++m_nBegIndex;
                }
                ++m_nEndIndex;
                ++m_nDataCnt;
                m_pData[m_nEndIndex] = tData;
            }
        }
        else{
            if (m_nEndIndex == -1){
                ++m_nBegIndex;
                ++m_nEndIndex;
                ++m_nDataCnt;
            }

            // 更新最新的数据
            m_pData[m_nEndIndex] = tData;
        }

        return true;
    }

    // 关注被移除的数据(即最老的数据)的版本
    // nRemove 为1(移除的是最老的数据, 队首数据)或者2(更新了最新的数据, 队尾数据)表示在成功返回Push后移除了数据, 0表示没有移除数据
    bool AppendData(const T& tData, bool bNewPeriod, int& nRemove, T& tRemoveData)
    {
        nRemove     = 0;
        tRemoveData = T();
        if (!m_pData || m_nDataMaxCnt <= 0){
            return false;
        }

        if (bNewPeriod){
            if (m_nDataCnt == m_nDataMaxCnt){           // 数据已满,需要移除数组的首部数据(最老的数据)
                ++m_nBegIndex;
                ++m_nEndIndex;
                if (m_nEndIndex == m_nDataMaxCnt){
                    m_nEndIndex = 0;
                }

                if (m_nBegIndex == m_nDataMaxCnt){
                    m_nBegIndex = 0;
                }

                nRemove             = 1;
                tRemoveData        = m_pData[m_nEndIndex];
                m_pData[m_nEndIndex] = tData;
            }
            else{
                if (m_nBegIndex == -1){
                    ++m_nBegIndex;
                }
                ++m_nEndIndex;
                ++m_nDataCnt;
                m_pData[m_nEndIndex] = tData;
            }
        }
        else{
            if (m_nEndIndex == -1){
                ++m_nBegIndex;
                ++m_nEndIndex;
                ++m_nDataCnt;
            }
            else{   // 否则表示有数据被更新
                nRemove              = 2;
                tRemoveData         = m_pData[m_nEndIndex];
            }

            // 更新最新的数据
            m_pData[m_nEndIndex]  = tData;
        }

        return true;
    }

    // 获取相对某个节点(计算时包括了该节点), nPeriod周期内的最高值
    // nIndex <=0, =0为当前; tHigh为最高值的数值, nHighIndex<=0, 相对当前(注意, 不是相对nIndex)往前推多少个周期
    // 例: PeriodHigh(-2, 20, tHigh, nHighIndex) 表示(相对当前)截至前2个周期, 获取其最近20个周期的最高值
    // 需要注意的是: 这个函数不能过于频繁使用, 效率不高
    bool PeriodHigh(int nIndex, int nPeriod, T& tHigh, int& nHighIndex)
    {
        if (nIndex > 0 || nPeriod <= 1 || !m_pData){
            return false;
        }

        int nLookBackIndex = nIndex;
        int nRealEndIndex  = GetRealIndexRelativeEnd(nLookBackIndex);
        if (nRealEndIndex == -1) {
            return false;
        }

        tHigh         = m_pData[nRealEndIndex];
        nHighIndex   = nLookBackIndex;
        int nCalcCnt = 1;
        while (nCalcCnt < nPeriod && nCalcCnt < m_nDataCnt){
            ++nCalcCnt;
            --nLookBackIndex;
            nRealEndIndex = GetRealIndexRelativeEnd(nLookBackIndex);
            if (nRealEndIndex == -1) {
                break;
            }

            if (m_pData[nRealEndIndex] > tHigh){
                tHigh       = m_pData[nRealEndIndex];
                nHighIndex = nLookBackIndex;
            }
        }

        return true;
    }

    // 获取相对某个节点, nPeriod周期内的最低值
    // nIndex <=0, =0为当前; tLow为最低值的数值, nLowIndex<=0, 相对当前往前推多少个周期
    // 例: PeriodLow(0, 20, tLow, nLowIndex) 表示获取最近20个周期的最低值
    // 需要注意的是: 这个函数不能过于频繁使用, 效率不高
    bool PeriodLow(int nIndex, int nPeriod, T& tLow, int& nLowIndex)
    {
        if (nIndex > 0 || nPeriod <= 1 || !m_pData){
            return false;
        }

        int nLookBackIndex = nIndex;
        int nRealEndIndex  = GetRealIndexRelativeEnd(nLookBackIndex);
        if (nRealEndIndex == -1) {
            return false;
        }

        tLow          = m_pData[nRealEndIndex];
        nLowIndex    = nLookBackIndex;
        int nCalcCnt = 1;
        while (nCalcCnt < nPeriod && nCalcCnt < m_nDataCnt){
            ++nCalcCnt;
            --nLookBackIndex;
            nRealEndIndex = GetRealIndexRelativeEnd(nLookBackIndex);
            if (nRealEndIndex == -1) {
                break;
            }

            if (m_pData[nRealEndIndex] < tLow){
                tLow       = m_pData[nRealEndIndex];
                nLowIndex = nLookBackIndex;
            }
        }

        return true;
    }

    // 同时获取相对某个节点, nPeriod周期内的最高、最低值
    // nIndex <=0, =0为当前; nHighIndex<= 0, nLowIndex<=0, 均是相对当前往前推多少个周期
    // 例: PeriodHL(0, 20, tHigh, nHighIndex, tLow, nLowIndex) 表示获取最近20个周期的最高值、最低值
    // 需要注意的是: 这个函数不能过于频繁使用, 效率不高
    bool PeriodHL(int nIndex, int nPeriod, T& tHigh, int& nHighIndex, T& tLow, int& nLowIndex)
    {
        if (nIndex > 0 || nPeriod <= 1 || !m_pData){
            return false;
        }

        int nLookBackIndex = nIndex;
        int nRealEndIndex  = GetRealIndexRelativeEnd(nLookBackIndex);
        if (nRealEndIndex == -1) {
            return false;
        }

        tHigh         = m_pData[nRealEndIndex];
        tLow          = m_pData[nRealEndIndex];
        nHighIndex   = nLookBackIndex;
        nLowIndex    = nLookBackIndex;
        int nCalcCnt = 1;
        while (nCalcCnt < nPeriod && nCalcCnt < m_nDataCnt){
            ++nCalcCnt;
            --nLookBackIndex;
            nRealEndIndex = GetRealIndexRelativeEnd(nLookBackIndex);
            if (nRealEndIndex == -1) {
                break;
            }

            if (m_pData[nRealEndIndex] > tHigh){
                tHigh       = m_pData[nRealEndIndex];
                nHighIndex = nLookBackIndex;
            }

            if (m_pData[nRealEndIndex] < tLow){
                tLow       = m_pData[nRealEndIndex];
                nLowIndex = nLookBackIndex;
            }
        }

        return true;
    }

private:

        // 返回 0 - m_nDataMaxCnt-1 的数, 如果返回-1,则不可使用返回值进行数据索引
        int GetRealIndexRelativeEnd(int nIndex)
        {
            if(m_nEndIndex < 0 || nIndex > 0){
                return -1;
            }

            int nRealArrayIndex = m_nEndIndex + nIndex;
            if (nRealArrayIndex < 0){
                if (m_nEndIndex < m_nBegIndex){
                    nRealArrayIndex = nRealArrayIndex + m_nDataMaxCnt;
                    if(nRealArrayIndex < m_nBegIndex){
                        return -1;
                    }
                }
                else{
                    return -1;
                }
            }
            else{
                if(m_nEndIndex >= m_nBegIndex && nRealArrayIndex < m_nBegIndex){
                    return -1;
                }
            }

            return nRealArrayIndex;
        }

private:

    T*     m_pData;                // 存放数据的数组

    int    m_nDataMaxCnt;          // 最多能存放的数据个数

    int    m_nDataCnt;             // 已经存放的数据的个数

    int    m_nBegIndex;            // 数据的起始下标(时间上来说是最老的数据)

    int    m_nEndIndex;            // 数据的结束下标(时间上来说是最新的数据)
};



#endif      // TIME_SERIES_DATA_HPP__