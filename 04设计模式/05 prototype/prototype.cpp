#include <iostream>
#include <string>

class Juice
{
public:
    virtual Juice* Clone() = 0; //for copy object
    virtual void Show() = 0;    //verify juice type
};

//child class
class AppleJuice : public Juice
{
public:
    virtual Juice* Clone() override
    {
        return new AppleJuice(*this); //return the copy of current object
    }

    virtual void Show() override
    {
        std::cout << "Apple juice" << std::endl;
    }
}; 

class LemonJuice : public Juice
{
public:
    virtual Juice* Clone() override
    {
        return new LemonJuice(*this); //return the copy of current object
    }

    virtual void Show() override
    {
        std::cout << "Lemon juice" << std::endl;
    }
}; 

int main()
{

    Juice* pJuice = new AppleJuice;
    pJuice->Show();

    /*
     * a long time later, we need a copy object for current object
     * but we don't remember or hard to confirm the concrete type of current object
    */
   Juice* pNewJuice = pJuice->Clone();
   pNewJuice->Show();

    return 0;
}
