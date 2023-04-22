#include <iostream>
#include <string>

class House
{
public:
    void setDoor(std::string door)
    {
        m_door = door;
    }
    void setWindow(std::string window)
    {
        m_window = window;
    }
    void setWall(std::string wall)
    {
        m_wall = wall;
    }
    std::string getDoor()
    {
        return m_door;
    }
    std::string getWindow()
    {
        return m_window;
    }
    std::string getWall()
    {
        return m_wall;
    }
private:
    std::string m_door;
    std::string m_window;
    std::string m_wall;
};


class Builder
{
public: 
    Builder()
    {
        if(nullptr == m_house_ptr)
        {
            m_house_ptr = new House;
        }
    }
    void construct()
    {
        buildDoor();
        buildWindow();
        buildWall();
    }
    House* getHouse()
    {
        return m_house_ptr;
    }
private:
    House * m_house_ptr;

    void buildDoor()
    {
        m_house_ptr->setDoor("rectangle door");
    }
    void buildWindow()
    {
        m_house_ptr->setWindow("circle window");
    }
    void buildWall()
    {
        m_house_ptr->setWall("low wall");
    }
};

int main()
{

    House* house = nullptr;
    Builder* builder = new Builder;
    
    //builde house
    builder->construct();
    //get house
    house = builder->getHouse();
    //print
    std::cout << "my house:" << house->getDoor() << ", " << house->getWindow() << ", " << house->getWall() << std::endl;

    return 0;
}

//if the requirements changed.such as: window->rectangle
//we need change the source code of builder