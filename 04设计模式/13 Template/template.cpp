#include <iostream>

//abstract class
class AbstractClass
{
public:
    void TemplateMethod()
    {
        Method1();
        std::cout << "template method" << std::endl;
        Method2();
    }
protected:
    virtual void Method1()
    {
        std::cout << "default method1" << std::endl;
    }
    virtual void Method2()
    {
        std::cout << "default method2" << std::endl;
    }
};

//concrete classA
class ConcreteClassA : public AbstractClass
{
public:
    virtual void Method1()
    {
        std::cout << "ConcreteClassA method1" << std::endl;
    }
    virtual void Method2()
    {
        std::cout << "ConcreteClassA method2" << std::endl;
    }

};
//concrete classB
class ConcreteClassB : public AbstractClass
{
protected:
    virtual void Method1()
    {
        std::cout << "ConcreteClassB method1" << std::endl;
    }
};

int main()
{
    //usecase1:
    AbstractClass* pAbstractA =  new ConcreteClassA;
    pAbstractA->TemplateMethod();

    std::cout << "================case 2================" << std::endl;
    AbstractClass* pAbstractB =  new ConcreteClassB;
    pAbstractB->TemplateMethod();

    delete pAbstractA;
    delete pAbstractB;

    return 0;
}