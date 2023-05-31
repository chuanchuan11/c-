#include <iostream>
#include <string>
#include <vector>

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
  Context(Strategy *strategy) :m_strategy(strategy){}
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
    Context *pContextA = new Context(new ConcreteStrategy1());
    Context *pContextB = new Context(new ConcreteStrategy2());

    pContextA->ContextInterface();
    pContextB->ContextInterface();

    delete pContextA;
    delete pContextB;

    return 0;
}