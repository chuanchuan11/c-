#include <iostream>

class Subject
{
public:
    virtual void request() = 0;
};

//real object
class RealSubject : public Subject
{
public:
    void request() override
    {
        std::cout << "this is real request" << std::endl;
    }
};

//proxy
class Proxy : public Subject
{
protected:
    RealSubject * realSubject = nullptr;
public:
    void request() override
    {
        std::cout << "proxy creat" << std::endl;
        if(realSubject == nullptr)
        {
            realSubject = new RealSubject;
        }
        realSubject ->request();
    }

    ~Proxy()
    {
        if(realSubject != nullptr)
        {
            delete realSubject;
        }
    }
};

int main()
{
    Proxy* proxy = new Proxy;
    proxy->request();
    delete proxy;
    return 0;
}
