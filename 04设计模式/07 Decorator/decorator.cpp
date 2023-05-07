#include <iostream>

//shape abstruct
class Shape
{
public:
    virtual void draw() = 0;
};

//circle shape
class CircleShape : public Shape
{
public:
    void draw() override
    {
        std::cout << "darw a circle" << std::endl;
    }
};

//rectangle shape
class RectangleShape : public Shape
{
public:
    void draw() override
    {
        std::cout << "darw a rectangle" << std::endl;
    }
};

//decorator abstract
class ShapeDecorator : public Shape
{
protected:
    Shape* m_pShape = nullptr;
public:
    ShapeDecorator(Shape* shape) : m_pShape(shape){}

    virtual void draw() = 0;
};

//redShape
class RedShapeDectator : public ShapeDecorator
{
public:
    RedShapeDectator(Shape* shape) : ShapeDecorator(shape) {};

    void draw() override
    {
        ShapeDecorator::m_pShape->draw();
        setRedColor();
    }
private:
    void setRedColor()
    {
        std::cout << "red color" << std::endl;
    }
};

int main()
{
    Shape* shape = new CircleShape;
    shape->draw();

    RedShapeDectator* redColorShape = new RedShapeDectator(shape);
    redColorShape->draw();
    delete shape;
    delete redColorShape;


    shape = new RectangleShape;
    shape->draw();

    redColorShape = new RedShapeDectator(shape);
    redColorShape->draw();

    delete shape;
    delete redColorShape; 
    return 0;
}
