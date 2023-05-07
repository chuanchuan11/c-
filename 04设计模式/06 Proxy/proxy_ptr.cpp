#include <iostream>

class Proxy_Ptr
{
public:
    //construct, proxy initialize counter
    Proxy_Ptr(int* p) : m_pData(p), m_pCnt(nullptr)
    {
        m_pCnt = new int(1);
    }

    //copy construct, counter+1
    Proxy_Ptr(const Proxy_Ptr& exist) : m_pData(exist.m_pData), m_pCnt(exist.m_pCnt)
    {
        ++(*m_pCnt);
    }

    //assign construct, old counter-1, new counter+1
    Proxy_Ptr& operator =(Proxy_Ptr& exist)
    {
        if(m_pData == exist.m_pData)
        {
            return *this;
        }
        if(m_pCnt != nullptr)
        {
            --(*m_pCnt);
            if(0 == *m_pCnt)
            {
                std::cout << "delete" << std::endl;
                delete m_pData;
                m_pData = nullptr;
            }
            m_pData = exist.m_pData;
            m_pCnt = exist.m_pCnt;
            ++(*m_pCnt);
        }

        return *this;
    }

    //destruct, counter-1
    ~Proxy_Ptr()
    {
        --(*m_pCnt);
        if(0 == *m_pCnt)
        {
            std::cout << "delete" << std::endl;
            delete m_pData;
            m_pData = nullptr;
        }
    }

    int operator* ()
    {
        return *m_pData;
    }

    void show()
    {
        std::cout << "Data: " << *m_pData << " ,counter: " << *m_pCnt;
    }

private:
    int* m_pData; //heap object
    int* m_pCnt;  //counter
};

int main()
{
    Proxy_Ptr p(new int(6));
    Proxy_Ptr p2(new int(666));

    p = p2;
    std::cout << "----no pointer to 6---" << std::endl;

    std::cout << "p->m_pData: " << *p << std::endl;
    p2.show();

    std::cout << "----begin destrction----" << std::endl;
    return 0;
}
