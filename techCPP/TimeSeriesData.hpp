// ʹ��ѭ������ʵ��ʱ����������, ����memmove����memcpy������Ч����ʧ

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

// ʱ����������
// ���µ����ݷ���������ĩβ, ���ϵ����ݷ���������λ
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

    // �������ݻ���
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

    // ��ȡ��ǰ���ڵ�ǰһ�����ڵ�ֵ
    // �����ǵ�ǰ�����Ƿ���һ��������
    // ��ע������߼�, �������������һ�������ڵ�bar, ��ôǰһ��ֵ����m_pData������λ��
    // ����, ���������ݸ���, ��ô�����ʱ��,ǰֵ��Ӧ����ȡ-1��, ��Ϊ��0��,�ǵ�ǰ���ڵ���һ��ֵ���������
    // ������Ҫע��ʹ�õ��Ǻ�append��ǰ��λ��, һ���Ƿ���append֮ǰ����
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

            // �������µ�����
            m_pData[m_nEndIndex] = tData;
        }

        return true;
    }

    // ��ע���Ƴ�������(�����ϵ�����)�İ汾
    // nRemove Ϊ1(�Ƴ��������ϵ�����, ��������)����2(���������µ�����, ��β����)��ʾ�ڳɹ�����Push���Ƴ�������, 0��ʾû���Ƴ�����
    bool AppendData(const T& tData, bool bNewPeriod, int& nRemove, T& tRemoveData)
    {
        nRemove     = 0;
        tRemoveData = T();
        if (!m_pData || m_nDataMaxCnt <= 0){
            return false;
        }

        if (bNewPeriod){
            if (m_nDataCnt == m_nDataMaxCnt){           // ��������,��Ҫ�Ƴ�������ײ�����(���ϵ�����)
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
            else{   // �����ʾ�����ݱ�����
                nRemove              = 2;
                tRemoveData         = m_pData[m_nEndIndex];
            }

            // �������µ�����
            m_pData[m_nEndIndex]  = tData;
        }

        return true;
    }

    // ��ȡ���ĳ���ڵ�(����ʱ�����˸ýڵ�), nPeriod�����ڵ����ֵ
    // nIndex <=0, =0Ϊ��ǰ; tHighΪ���ֵ����ֵ, nHighIndex<=0, ��Ե�ǰ(ע��, �������nIndex)��ǰ�ƶ��ٸ�����
    // ��: PeriodHigh(-2, 20, tHigh, nHighIndex) ��ʾ(��Ե�ǰ)����ǰ2������, ��ȡ�����20�����ڵ����ֵ
    // ��Ҫע�����: ����������ܹ���Ƶ��ʹ��, Ч�ʲ���
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

    // ��ȡ���ĳ���ڵ�, nPeriod�����ڵ����ֵ
    // nIndex <=0, =0Ϊ��ǰ; tLowΪ���ֵ����ֵ, nLowIndex<=0, ��Ե�ǰ��ǰ�ƶ��ٸ�����
    // ��: PeriodLow(0, 20, tLow, nLowIndex) ��ʾ��ȡ���20�����ڵ����ֵ
    // ��Ҫע�����: ����������ܹ���Ƶ��ʹ��, Ч�ʲ���
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

    // ͬʱ��ȡ���ĳ���ڵ�, nPeriod�����ڵ���ߡ����ֵ
    // nIndex <=0, =0Ϊ��ǰ; nHighIndex<= 0, nLowIndex<=0, ������Ե�ǰ��ǰ�ƶ��ٸ�����
    // ��: PeriodHL(0, 20, tHigh, nHighIndex, tLow, nLowIndex) ��ʾ��ȡ���20�����ڵ����ֵ�����ֵ
    // ��Ҫע�����: ����������ܹ���Ƶ��ʹ��, Ч�ʲ���
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

        // ���� 0 - m_nDataMaxCnt-1 ����, �������-1,�򲻿�ʹ�÷���ֵ������������
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

    T*     m_pData;                // ������ݵ�����

    int    m_nDataMaxCnt;          // ����ܴ�ŵ����ݸ���

    int    m_nDataCnt;             // �Ѿ���ŵ����ݵĸ���

    int    m_nBegIndex;            // ���ݵ���ʼ�±�(ʱ������˵�����ϵ�����)

    int    m_nEndIndex;            // ���ݵĽ����±�(ʱ������˵�����µ�����)
};



#endif      // TIME_SERIES_DATA_HPP__