#include <iostream>
#include <memory>
#include <string.h>

//common base IF
class Fruit
{
public:
    virtual void getFruit() = 0;
};

//different object
class Apple : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am apple" << std::endl;
    }
};

class Bnana : public Fruit
{
public:
    void getFruit()
    {
        std::cout << "i am bnana" << std::endl;
    }
};

//factory
class factory
{
public:
    Fruit* FruitFactory(const char* type)
    {
        if(strcmp(type, "apple") == 0)
        {
            return new Apple;
        }
        else if(strcmp(type, "bnana") == 0)
        {
            return new Bnana;
        }
        else
        {
            std::cout << "unkonw type: " << type <<std::endl;
        }
    }

    //FoodFactory();  need add the new function when type changed
};

int main()
{

    factory* f = new factory;  //can be a global function or single class

    Fruit * fruit = f->FruitFactory("apple"); //creat apple
     fruit->getFruit();


    fruit = f->FruitFactory("bnana"); //creat bnana
    fruit->getFruit();


    std::cout << "hello world! " << std::endl;

    return 0;
}
