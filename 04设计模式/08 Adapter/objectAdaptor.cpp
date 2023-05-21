#include <iostream>

//target interface
class Electricity
{
public:
    virtual void Charge() = 0;
};

//already implement 
class Adaptee5V
{
public:
    void transfer()
    {
        std::cout << "5V charging..." << std::endl;
    }
};

//adapter
class ElecWithAdaptee5V : public Electricity
{
public:
    ElecWithAdaptee5V() : p_Adapter(nullptr)
    {
        p_Adapter = new Adaptee5V();
    }

    virtual void Charge()
    {
        p_Adapter->transfer();
    }

private:
    Adaptee5V* p_Adapter;
};


int main()
{
    Electricity* p_Ele = new ElecWithAdaptee5V;
    p_Ele->Charge();

    delete p_Ele;
    return 0;
}
