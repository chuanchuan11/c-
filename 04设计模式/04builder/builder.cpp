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
    House* getHouse()
    {
        return m_house_ptr;
    }

    virtual void buildDoor() = 0;
    virtual void buildWindow() = 0;
    virtual void buildWall() = 0;

protected:
    House * m_house_ptr;
};

class BuilderOldHourse : public Builder
{
public:
    void buildDoor() override
    {
        m_house_ptr->setDoor("rectangle door");
    }
    void buildWindow() override
    {
        m_house_ptr->setWindow("circle window");
    }
    void buildWall() override
    {
        m_house_ptr->setWall("low wall");
    }
};

//new requirements changed, only extend a class
class BuilderNewHourse : public Builder
{
public:
    void buildDoor() override
    {
        m_house_ptr->setDoor("circle door");
    }
    void buildWindow() override
    {
        m_house_ptr->setWindow("rectangle window");
    }
    void buildWall() override
    {
        m_house_ptr->setWall("low wall");
    }
};

class Director
{
public:
    Director(Builder* build)
    {
        m_build_ptr = build;
    }
    House* construct()
    {
        m_build_ptr->buildDoor();
        m_build_ptr->buildWindow();
        m_build_ptr->buildWall();
        return m_build_ptr->getHouse();
    }
private:
    Builder* m_build_ptr;
};

int main()
{

    House* house = nullptr;
    Builder* builder = nullptr;
    Director* director = nullptr;

    //builder object
    builder = new BuilderOldHourse;

    //director build house by builder
    director = new Director(builder);
    house = director->construct();

    //get house
    std::cout << "old house:" << house->getDoor() << ", " << house->getWindow() << ", " << house->getWall() << std::endl;
    
    ///////////////////////////////////new requirements changed, only creat a new object
    //build new object
    builder = new BuilderNewHourse;

    //director build house by builder
    director = new Director(builder);
    house = director->construct();
    
    std::cout << "new house:" << house->getDoor() << ", " << house->getWindow() << ", " << house->getWall() << std::endl;
    
    return 0;
}

//if the requirements changed. only extend a new class.