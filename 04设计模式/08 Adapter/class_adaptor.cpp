#include <iostream>

//target abstract class
class RobotTarget
{
public:
    RobotTarget(){};

    virtual void cry() = 0;

    virtual void move() = 0;

    virtual ~RobotTarget(){};
};

//implement class that need to adaptor
class DogAdaptee
{
public:
    DogAdaptee(){};

    virtual void wang()
    {
        std::cout << "wang wang" << std::endl;
    }

    virtual void run()
    {
        std::cout << "run run" << std::endl;
    }
};

//class adaptor
class DogAdapter : public RobotTarget, public DogAdaptee
{
public:
    DogAdapter(){};

    virtual void cry()
    {
        DogAdaptee::wang();
    }

    virtual void move()
    {
        DogAdaptee::run();
    }
};

int main()
{
    RobotTarget* pRobot = new DogAdapter;
    pRobot->cry();
    pRobot->move();

    delete pRobot;
    return 0;
}
