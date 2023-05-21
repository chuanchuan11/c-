#include <iostream>

//abstract of color
class Color
{
public:
    virtual std::string GetColor() = 0;
};

//implement of color
class Blue : public Color
{
public:
    std::string GetColor()
    {
        return "blue";
    }
};

class Green : public Color
{
public:
    std::string GetColor()
    {
        return "green";
    }
};

//abstruct of shape
class Shape
{
public:
    Shape(Color* pColor) : m_pColor(pColor)
    {}

    virtual void show() = 0;

protected:
    Color* m_pColor;  //bridge shape and color
};

//implement of shape
class Circle : public Shape
{
public:
    Circle(Color* pColor) : Shape(pColor)
    {}

    void show()
    {
        std::cout << m_pColor->GetColor() << " Circle" << std::endl;
    }
};

int main()
{
    Shape* p_BlueCircle = new Circle(new Blue);
    p_BlueCircle->show();

    
    Shape* p_GreenCircle = new Circle(new Green);
    p_GreenCircle->show();

    delete p_BlueCircle;
    delete p_GreenCircle;

    return 0;
}