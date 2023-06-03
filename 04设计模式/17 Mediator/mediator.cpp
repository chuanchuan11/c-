#include <iostream>

/*
 * 约定协议
 * messageAB 是AB模块间通信的消息
 * messageAC 是AC模块间通信的消息
 * messageBC 是BC模块间通信的消息
*/
enum Message
{
    MessageAB,
    MessageAC,
    MessageBC
};

//声明ModuleBase
class ModuleBase;

//中介者基类, 提供消息转发接口
class MediatorBase
{
public:
    virtual void Transmit(Message msgType, ModuleBase* pFrom) = 0;
};

//Module基类，实现向外发消息
class ModuleBase
{
public:
    ModuleBase(MediatorBase* pMediator):m_pMediator(pMediator)
    {}
    //send messages by mediator
    void sendMessage(Message msgType)
    {
        m_pMediator->Transmit(msgType, this);
    }
    //receive messages
    virtual void notify(Message msgType) = 0;
private:
    MediatorBase* m_pMediator;
};

//module A
class ModuleA : public ModuleBase
{
public:
    ModuleA(MediatorBase* pMediator) : ModuleBase(pMediator)
    {}

    void notify(Message msgType) override
    {
        switch(msgType)
        {
            case MessageAB:
                std::cout << "ModuleA get messageAB from moduleB" << std::endl;
                break;
            case MessageAC:
                std::cout << "ModuleA get messageAC from moduleC" << std::endl;
                break;
            default:
                break;
        }
    }
};

//module B
class ModuleB : public ModuleBase
{
public:
    ModuleB(MediatorBase* pMediator) : ModuleBase(pMediator)
    {}

    void notify(Message msgType) override
    {
        switch(msgType)
        {
            case MessageAB:
                std::cout << "ModuleB get messageAB from moduleA" << std::endl;
                break;
            case MessageBC:
                std::cout << "ModuleB get messageBC from moduleC" << std::endl;
                break;
            default:
                break;
        }
    }
};

//module C
class ModuleC : public ModuleBase
{
public:
    ModuleC(MediatorBase* pMediator) : ModuleBase(pMediator)
    {}

    void notify(Message msgType) override
    {
        switch(msgType)
        {
            case MessageAC:
                std::cout << "ModuleC get messageAC from moduleA" << std::endl;
                break;
            case MessageBC:
                std::cout << "ModuleC get messageBC from moduleB" << std::endl;
                break;
            default:
                break;
        }
    }
};

//concrete mediator 
class ConcreteMediator : public MediatorBase
{
public:
    ConcreteMediator() : m_pModA(nullptr), m_pModB(nullptr), m_pModC(nullptr)
    {}
    //transmit message to different object
    void Transmit(Message msgType, ModuleBase* pFrom) override
    {
        switch(msgType)
        {
            case MessageAB:
            {
                ModuleA* pFromWhere = dynamic_cast<ModuleA*>(pFrom);
                //能通过dynamic_cast转换为不为NULL的指针，可确认指针指向子类类型,说明是从A->B
                if(nullptr != pFromWhere)
                {
                    m_pModB->notify(msgType);
                }
                else
                {
                    m_pModA->notify(msgType); //null为空, 说明是从B->A
                }
            }break;
            case MessageAC:
            {
                ModuleA* pFromWhere = dynamic_cast<ModuleA*>(pFrom);
                //能通过dynamic_cast转换为不为NULL的指针，可确认指针指向子类类型,说明是从A->C
                if(nullptr != pFromWhere)
                {
                    m_pModC->notify(msgType);
                }
                else
                {
                    m_pModA->notify(msgType); //null为空, 说明是从C->A
                }
            }break;
            case MessageBC:
            {
                ModuleB* pFromWhere = dynamic_cast<ModuleB*>(pFrom);
                //能通过dynamic_cast转换为不为NULL的指针，可确认指针指向子类类型,说明是从B->C
                if(nullptr != pFromWhere)
                {
                    m_pModC->notify(msgType);
                }
                else
                {
                    m_pModB->notify(msgType); //null为空, 说明是从C->B
                }
            }break;
            default:
                break;
        }
    }

    void setModuleA(ModuleBase* pModA) {m_pModA = pModA;}
    void setModuleB(ModuleBase* pModB) {m_pModB = pModB;}
    void setModuleC(ModuleBase* pModC) {m_pModC = pModC;}

private:
    ModuleBase* m_pModA;
    ModuleBase* m_pModB;
    ModuleBase* m_pModC;
};

int main()
{
    MediatorBase* pMediator = new ConcreteMediator;

    //为所有模块指定中介者
    ModuleBase* pModA = new ModuleA(pMediator);
    ModuleBase* pModB = new ModuleB(pMediator);
    ModuleBase* pModC = new ModuleC(pMediator);

    //为中介者设定所有模块
    ConcreteMediator* pConcreteMediator = dynamic_cast<ConcreteMediator*>(pMediator);
    pConcreteMediator->setModuleA(pModA);
    pConcreteMediator->setModuleB(pModB);
    pConcreteMediator->setModuleC(pModC);

    //各模块见开始互发消息
    pModA->sendMessage(MessageAC);
    pModB->sendMessage(MessageBC);
    pModC->sendMessage(MessageBC);
    return 0;
}