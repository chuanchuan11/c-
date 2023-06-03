#include <iostream>
#include <list>

class Observer;

//抽象被观察者
class Subject
{
public:
    Subject():m_state(0){}

    virtual ~Subject() = default;

    //增加观察者
    virtual void attach(Observer* pObserver) = 0;

    //移除观察者
    virtual void detach(Observer* pObserver) = 0;

    //通知
    virtual void notify() = 0;

    //获取状态
    virtual int getState()
    {
        return m_state;
    }

    //设置状态
    virtual void setState(int state)
    {
        std::cout << "subject state update: " << m_state << "->" << state << std::endl;
        m_state = state;
    }

protected:
    std::list<Observer*> m_pObserver_list;  //保存observer
    int m_state; //被监控的状态
};

//抽象观察者
class Observer
{
public:
    virtual ~Observer() = default;

    Observer(Subject* pSubject, const std::string &name="unknow") : m_pSubject(pSubject), m_strName(name) 
    {}

    //接受通知
    virtual void update() = 0;

    virtual const std::string name()
    {
        return m_strName;
    }

protected:
    Subject* m_pSubject;
    std::string m_strName;
};

//具体被观察者
class ConcreteSubject : public Subject
{
public:
    void attach(Observer* pObserver) override
    {
        std::cout << "attach observer: " << pObserver->name() << std::endl;
        m_pObserver_list.push_back(pObserver);
    }

    void detach(Observer* pObserver) override
    {
        std::cout << "detach observer: " << pObserver->name() << std::endl;
        m_pObserver_list.remove(pObserver);
    }

    void notify() override
    {
        for (auto& ele: m_pObserver_list)
        {
            ele->update();
        }
    }  
};

//具体观察者1
class ConcreteObserver1 : public Observer
{
public:
    ConcreteObserver1(Subject* pSubject, const std::string& name="unknow"):Observer(pSubject, name)
    {}

    void update() override
    {
        std::cout << "observer1: " << m_strName << " get notify, new state is: " <<  m_pSubject->getState() << std::endl;
    }

};

//具体观察者2
class ConcreteObserver2 : public Observer
{
public:
    ConcreteObserver2(Subject* pSubject, const std::string& name="unknow"):Observer(pSubject, name)
    {}

    void update() override
    {
        std::cout << "observer2: " << m_strName << " get notify, new state is: " <<  m_pSubject->getState() << std::endl;
    }

};

int main()
{
    Subject* pSubject = new ConcreteSubject;

    Observer* pObserver_1 = new ConcreteObserver1(pSubject, "PPP");
    Observer* pObserver_2 = new ConcreteObserver2(pSubject, "XXX");

    //注册观察者
    pSubject->attach(pObserver_1);
    pSubject->attach(pObserver_2);

    //通知
    pSubject->setState(2);
    pSubject->notify();

    //取消观察者2
    pSubject->detach(pObserver_2);

    //通知
    pSubject->setState(4);
    pSubject->notify();

    return 0;
}