#include <iostream>
#include <map>
#include <vector>
#include <utility>

enum Color
{
    BLACK,
    WHITE
};

//unsharedConncreteFlyweight 非共享具体享元类
typedef struct pointTag
{
    int x;
    int y;
    pointTag(){};
    pointTag(int a, int b)
    {
        x = a;
        y = b;
    }

    bool operator <(const pointTag& other) const
    {
        if(x < other.x)
        {
            return true;
        }
        else if(x == other.x)
        {
            return y < other.y;
        }

        return false;
    }
}Point;

//abstract flyweight
class CPiece
{
public:
    CPiece(Color color) : m_color(color) {};
    Color getColor()
    {
        return m_color;
    }

    //set external state
    void setPoint(Point point)
    {
        m_point = point;
    }
    Point getPoint()
    {
        return m_point;
    }

private:
    Color m_color;  //internal state
    Point m_point;  //external state
};

//conncreteFlyweight
class CGomoku : public CPiece
{
public:
    CGomoku(Color color) : CPiece(color) {};
};

//flyweight factory
class CPieceFactory
{
public:
    CPiece* getCpiece(Color color)
    {
        CPiece* pPiece = nullptr;
        for(auto it = m_vecPiece.begin(); it!=m_vecPiece.end(); ++it)
        {
            if(color == (*it)->getColor())
            {
                pPiece = *it;
                break;
            }
        }

        if(nullptr == pPiece)
        {
            pPiece = new CGomoku(color);
            m_vecPiece.push_back(pPiece);
        }
        return pPiece;
    }

    ~CPieceFactory()
    {
        for(auto it = m_vecPiece.begin(); it!= m_vecPiece.end(); ++it)
        {
            if(nullptr != (*it))
            {
                delete *it;
                *it = nullptr;
            }
        }
    }

private:
    std::vector<CPiece*> m_vecPiece;
};

class CChessBoard
{
public:
    void draw(CPiece* piece)
    {
        if(BLACK == piece->getColor())
        {
            std::cout << "draw a black, pos:" << piece->getPoint().x << "," << piece->getPoint().y << std::endl;
        }
        else
        {
            std::cout << "draw a white, pos:" << piece->getPoint().x << "," << piece->getPoint().y << std::endl;
        }
        m_mapPieces.insert(std::pair<Point, CPiece*>(piece->getPoint(), piece));
    }
private:
    std::map<Point, CPiece*> m_mapPieces; //save all external state
};

int main()
{
    CPieceFactory* pPieceFactory = new CPieceFactory;
    CChessBoard* PChessBoard = new CChessBoard;

    std::cout << "============round1==========" << std::endl;
    CPiece* pPiece = pPieceFactory->getCpiece(BLACK);
    pPiece->setPoint(Point(1,1));
    PChessBoard->draw(pPiece);

    std::cout << "============round2==========" << std::endl;
    pPiece = pPieceFactory->getCpiece(WHITE);
    pPiece->setPoint(Point(2,2));
    PChessBoard->draw(pPiece);

    std::cout << "============round3==========" << std::endl;
    pPiece = pPieceFactory->getCpiece(BLACK);
    pPiece->setPoint(Point(3,3));
    PChessBoard->draw(pPiece);

    std::cout << "============round4==========" << std::endl;
    pPiece = pPieceFactory->getCpiece(WHITE);
    pPiece->setPoint(Point(4,4));
    PChessBoard->draw(pPiece);

    return 0;
}