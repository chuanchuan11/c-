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

//common base Factory IF
class Factory
{
public:
    virtual  Fruit* CreatFactory() = 0;
};

//different creat factory
class AppleFactory : public Factory
{
public:
    Fruit* CreatFactory()
    {
        return new Apple;
    }
};

//only add new factory when changed, needn't change source code
class BnanaFactory : public Factory
{
public:
    Fruit* CreatFactory()
    {
        return new Bnana;
    }
};


//use
int main()
{

    Factory* factory = nullptr;
    Fruit * fruit = nullptr;

    factory = new AppleFactory;
    fruit = factory->CreatFactory();
    fruit->getFruit();

    //add new Fruit
    factory = new BnanaFactory;
    fruit = factory->CreatFactory();
    fruit->getFruit();

    return 0;
}
