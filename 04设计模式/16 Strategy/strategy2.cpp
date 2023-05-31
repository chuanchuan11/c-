#include <iostream>
#include <string>
#include <vector>

typedef enum StrategyType
{
  strategy1,
  strategy2,
  strategy3,
}STRATEGYTYPE;

/*抽象策略类*/
class Strategy
{
public:
  virtual void AlgorithomInterface() = 0;
};

/*具体策略实现类*/
class ConcreteStrategy1 :public Strategy
{
  void AlgorithomInterface()
  {
    std::cout << "I am  AlgorithomInterface 1" << std::endl;
  }
};

/*具体策略实现类*/
class ConcreteStrategy2 :public Strategy
{
  void AlgorithomInterface()
  {
    std::cout << "I am  AlgorithomInterface 2" << std::endl;
  }
};

class Context
{
public:
  Context(){}
  Context(STRATEGYTYPE type)
  {
    switch (type)
    {
    case strategy1:
      m_strategy = new ConcreteStrategy1;
      break;

    case strategy2:
      m_strategy = new ConcreteStrategy2;
        break;
    default:
      break;
    }
  }

  ~Context(){ delete m_strategy; }

  void ContextInterface()
  {
    m_strategy->AlgorithomInterface();
  }

private:
  Strategy *m_strategy;
};

int main()
{
    Context *pContextA = new Context(strategy1);
    pContextA->ContextInterface();
    delete pContextA;

    Context *pContextB = new Context(strategy2);
    pContextB->ContextInterface();
    delete pContextB;

    return 0;
}