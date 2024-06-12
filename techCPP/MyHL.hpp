// ���(��)�����(С)ֵ

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
                else if (m_nHLIndex == 0){    //  ������Ƴ������պ�����������Сֵ, ��Ҫ���¼���
                    m_fHLData = (m_nHlType == 0 ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
                    for (int i = 0; i < m_nDataCnt; ++i) {
                        if ((m_nHlType == 0 && m_pData[i] < m_fHLData) || (m_nHlType == 1 && m_pData[i] > m_fHLData)){
                            m_fHLData  = m_pData[i];
                            m_nHLIndex = i;
                        }
                    }
                }
                else{
                    --m_nHLIndex;           // ��Ϊ����������ǰ�ƶ���1λ, ��������ҲҪ-1
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
            else if (m_nHLIndex == m_nDataCnt - 1){ // ֮ǰ����ֵ�����(С)ֵ, ��������ֵ��һ����С(��)����������, ��Ҫ���¼�����
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

    // ��ǰֵ�Ƿ�����ֵ
    bool IsNewHL()
    {
        return m_nHLIndex == m_nDataCnt - 1;

        // ���ϵ��ж�, û�в��� m_nHLIndex == m_nPeriod - 1 ������, 
        // ��Ϊ��ʹ���ݲ���l_periods_�ĸ���, Ҳ������������
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

    int        m_nHlType;             // 0 �� ���  1 : ���

    int        m_nPeriod;             // Ҫ��>=2

    double     m_fHLData;            // ��ֵ

    int        m_nDataCnt;           // ���ݸ���

    int        m_nHLIndex;           // ��ֵ������

    double*    m_pData;              // ����

};

#endif   //MY_HL_HPP__