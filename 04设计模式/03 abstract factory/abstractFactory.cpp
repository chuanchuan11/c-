#include <iostream>
#include <memory>
#include <string.h>

//common base IF
class Fruit
{
public:
    virtual void getFruit() = 0;
};

class Factory
{
public:
    virtual Fruit* creatApple() = 0;
    virtual Fruit* creatBnana() = 0;
};

//different object 1
class NorthApple : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am north apple" << std::endl;
    }
};
//different object 2
class SourthApple : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am sourth apple" << std::endl;
    }
};

//new object 1
class NorthBnana : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am north Bnana" << std::endl;
    }
};
//new object 2
class SourthBnana : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am sourth Bnana" << std::endl;
    }
};

//include different object in factory
class NorthFactory : public Factory
{
public:
    Fruit* creatApple()
    {
        return new NorthApple;
    }

    Fruit* creatBnana()
    {
        return new NorthBnana;
    }
};

class SourthFactory : public Factory
{
public:
    Fruit* creatApple()
    {
        return new SourthApple;
    }

    Fruit* creatBnana()
    {
        return new SourthBnana;
    }
};

//user
int main()
{

    Factory * factory = nullptr;
    Fruit * fruit = nullptr;
    //1-1
    factory = new NorthFactory;
    fruit =  factory->creatApple();
    fruit->getFruit();
    //2-1
    fruit =  factory->creatBnana();
    fruit->getFruit();



    //1-2
    factory = new SourthFactory;
    fruit = factory->creatApple();
    fruit->getFruit();
    //2-2
    fruit =  factory->creatBnana();
    fruit->getFruit();

    return 0;
}
